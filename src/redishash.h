#ifndef REDISMAP_H
#define REDISMAP_H

// redis
#include "redisvalue.h"
#include "redisinterface.h"

template< typename Key, typename Value >
class RedisHash
{
    class iterator
    {
        public:
            // self operator overloadings
            iterator& operator =(iterator other)
            {
                this->list = other.list;
                this->connectionPool = other.connectionPool;
                this->pos = other.pos;
                this->posRedis = other.posRedis;
                this->cacheSize = other.cacheSize;
                this->queueElements = other.queueElements;
                this->binarizeKey = other.binarizeKey;
                this->binarizeValue = other.binarizeValue;

                // copy key data
                this->currentKey = other.currentKey;
                this->currentKeyVal = other.currentKeyVal;
                this->keyLoaded = other.keyLoaded;

                // copy value data
                this->currentValue = other.currentValue;
                this->currentValueVal = other.currentValueVal;
                this->valueLoaded = other.valueLoaded;

                return *this;
            }
            iterator& operator ++()
            {
                return this->forward(1);
            }
            iterator& operator ++(int elements)
            {
                Q_UNUSED(elements);
                return this->operator ++();
            }
            iterator& operator +=(int elements)
            {
                return this->forward(elements);
            }
            iterator erase(bool waitForAnswer = true)
            {
                iterator itr = *this;
                if(itr.currentKey.isEmpty()) return *this;
                itr.d->hdel(itr.currentKey, waitForAnswer);
                return itr.forward(1);
            }

            // copy operator overloadings
            iterator operator +(int elements)
            {
                iterator inew = *this;
                inew.forward(elements);
                return inew;
            }

            // comparing operator overloadings
            bool operator ==(iterator other)
            {
                return this->pos == other.pos;
            }
            bool operator !=(iterator other)
            {
                return !this->operator==(other);
            }

            // key value overloadings
            NORM2VALUE(Key) key()
            {
                this->loadEntry(true, false);
                return this->currentKeyVal;
            }
            NORM2VALUE(Value) value()
            {
                this->loadEntry(false, true);
                return this->currentValueVal;
            }
            NORM2VALUE(Value) operator *()
            {
                this->loadEntry(false, true);
                return this->currentValueVal;
            }
            NORM2POINTER(Value) operator ->()
            {
                this->loadEntry(false, true);
                return &this->currentValueVal;
            }

        private:
            iterator(QByteArray list, int pos, int cacheSize, bool binarizeKey, bool binarizeValue, QString connectionPool = "redis")
            {
                this->list = list;
                this->connectionPool = connectionPool;
                this->cacheSize = cacheSize;
                this->binarizeKey = binarizeKey;
                this->binarizeValue = binarizeValue;
                if(pos >= 0) this->forward(1);
            }

            // helper
            iterator& forward(int elements)
            {
                // reset current loaded key and value status
                if(elements > 0) {
                    this->keyLoaded = false;
                    this->valueLoaded = false;
                }

                // navigate elements forward
                for(int i = 0; i < elements; i++) {
                    if(!this->refillQueue()) return *this;

                    // save current key and value
                    this->currentKey = this->queueElements.takeFirst();
                    this->currentValue = this->queueElements.takeFirst();
                }
                return *this;
            }

            bool refillQueue()
            {
                // if queue is not empty, don't refill
                if(!this->queueElements.isEmpty()) return true;

                // if we reach the end of the redis position, set current pos to -1 and exit
                if(this->posRedis == 0) this->pos = -1;
                if(this->pos == -1) return false;

                // if redis pos is set to -1 (it's an invalid position) set position to begin
                // Note: this is a little hack for initialiating because redis start and end value are both 0
                if(this->posRedis == -1) this->posRedis = 0;

                // refill queue
                RedisInterface::scan(this->list, this->queueElements, this->cacheSize, this->posRedis, &this->posRedis, this->connectionPool);

                // if we couldn't get any items then we reached the end
                // Note: this could happend if we try to get data from an non-existing/empty key
                //       if this is the case then we call us again so that this iterator is set to end
                return this->queueElements.isEmpty() ? this->refillQueue() : true;
            }

            void loadEntry(bool key, bool value)
            {
                // load key (if not allready happened)
                if(key && !this->keyLoaded) {
                    this->currentKeyVal = RedisValue<Key>::deserialize(this->currentKey, this->binarizeKey);
                    this->keyLoaded = true;
                }

                // load value (if not allready happened)
                if(value && !this->valueLoaded) {
                    this->currentValueVal = RedisValue<Value>::deserialize(this->currentValue, this->binarizeValue);
                    this->valueLoaded = true;
                }
            }

            // data
            RedisInterface* d;
            int cacheSize;
            int posRedis = -1;
            int pos;
            QList<QByteArray> queueElements;
            QByteArray currentKey;
            QByteArray currentValue;
            NORM2VALUE(Key) currentKeyVal;
            NORM2VALUE(Value) currentValueVal;
            bool keyLoaded = false;
            bool valueLoaded = false;
            bool binarizeKey = false;
            bool binarizeValue = false;
            QByteArray list;
            QString connectionPool;

        friend class RedisHash;
    };

    public:
        RedisHash(QByteArray list, bool binarizeKey = false, bool binarizeValue = false, QString connectionPool = "redis")
        {
            this->binarizeKey = binarizeKey;
            this->binarizeValue = binarizeValue;
            this->list = list;
            this->connectionPool = connectionPool;
        }

        ~RedisHash()
        {

        }

        iterator begin(int cacheSize = 100)
        {
            return iterator(this->list, 0, cacheSize, this->binarizeKey, this->binarizeValue, this->connectionPool);
        }

        iterator end(int cacheSize = 100)
        {
            return iterator(this->list, -1, cacheSize, this->binarizeKey, this->binarizeValue, this->connectionPool);
        }

        iterator erase(iterator pos, bool waitForAnswer = true)
        {
            return pos.erase(waitForAnswer);
        }

        bool clear(bool async = true)
        {
            return RedisInterface::del(this->list, async, this->connectionPool);
        }

        int count()
        {
            return RedisInterface::hlen(this->list, this->connectionPool);
        }

        bool empty()
        {
            return this->isEmpty();
        }

        bool isEmpty()
        {
            return !RedisInterface::hlen(this->list, this->connectionPool);
        }

        bool exists(Key key)
        {
            return RedisInterface::hexists(this->list, RedisValue<Key>::serialize(key, this->binarizeKey), this->connectionPool);
        }

        bool exists()
        {
            return RedisInterface::exists(this->list, this->connectionPool);
        }

        bool remove(Key key, bool waitForAnswer = true)
        {
            return RedisInterface::hdel(this->list, RedisValue<Key>::serialize(key, this->binarizeKey), waitForAnswer, this->connectionPool);
        }

        NORM2VALUE(Value) take(Key key, bool waitForAnswer = true, bool *removeResult = 0)
        {
            NORM2VALUE(Value) value = this->value(key);
            bool rResult = this->remove(key, waitForAnswer);
            if(removeResult) *removeResult = rResult;
            return value;
        }

        bool insert(Key key, Value value, bool waitForAnswer = false)
        {
            return RedisInterface::hset(this->list, RedisValue<Key>::serialize(key, this->binarizeKey),
                                   RedisValue<Value>::serialize(value, this->binarizeValue), waitForAnswer, this->connectionPool);
        }

        NORM2VALUE(Value) value(Key key)
        {
            return RedisValue<Value>::deserialize(RedisInterface::hget(this->list, RedisValue<Key>::serialize(key, this->binarizeKey)), this->binarizeValue, this->connectionPool);
        }

        QList<NORM2VALUE(Key)> keys(int fetchChunkSize = -1)
        {
            // create result data list
            QList<NORM2VALUE(Key)> list;

            // if fetch chunk size is smaller or equal 0, so exec hkeys
            QList<QByteArray> elements;
            if(fetchChunkSize <= 0) RedisInterface::hkeys(this->list, elements, this->connectionPool);

            // otherwise get keys using scan
            else {
                int pos = 0;
                do RedisInterface::scan(this->list, &elements, 0, fetchChunkSize, pos, &pos, this->connectionPool);
                while(pos);
            }

            // deserialize byte array data to Key Type
            for(auto itr = elements.begin(); itr != elements.end(); itr = elements.erase(itr)) {
                list.append(RedisValue<Key>::deserialize(*itr, this->binarizeKey));
            }

            // return list
            return list;
        }

        QList<NORM2VALUE(Value)> values(int fetchChunkSize = -1)
        {
            // create result data list
            QList<NORM2VALUE(Value)> list;

            // if fetch chunk size is smaller or equal 0, so exec hvals
            QList<QByteArray> elements;
            if(fetchChunkSize <= 0) RedisInterface::hvals(this->list, elements, this->connectionPool);

            // otherwise get values using scan
            else {
                int pos = 0;
                do RedisInterface::scan(this->list, 0, &elements, fetchChunkSize, pos, &pos, this->connectionPool);
                while(pos);
            }

            // deserialize byte array data to Value Type
            for(auto itr = elements.begin(); itr != elements.end(); itr = elements.erase(itr)) {
                list.append(RedisValue<Value>::deserialize(*itr, this->binarizeValue));
            }

            // return list
            return list;
        }

        QMap<NORM2VALUE(Key),NORM2VALUE(Value)> toMap(int fetchChunkSize = -1)
        {
            // create result data list
            QMap<NORM2VALUE(Key),NORM2VALUE(Value)> map;

            // if fetch chunk size is smaller or equal 0, so exec hgetall
            QList<QByteArray> elements;
            if(fetchChunkSize <= 0) RedisInterface::hgetall(this->list, elements, this->connectionPool);

            // otherwise get key values using scan
            else {
                int pos = 0;
                do RedisInterface::scan(this->list, elements, fetchChunkSize, pos, &pos, this->connectionPool);
                while(pos);
            }

            // deserialize the data
            for(auto itr = elements.begin(); itr != elements.end();itr += 2) {
                map.insert(RedisValue<Key>::deserialize(*itr, this->binarizeKey), RedisValue<Value>::deserialize(*(itr + 1), this->binarizeValue));
            }

            // return map
            return map;
        }

        QHash<NORM2VALUE(Key),NORM2VALUE(Value)> toHash(int fetchChunkSize = -1)
        {
            // create result data list
            QHash<NORM2VALUE(Key),NORM2VALUE(Value)> hash;

            // if fetch chunk size is smaller or equal 0, so exec hgetall
            QList<QByteArray> elements;
            if(fetchChunkSize <= 0) RedisInterface::hgetall(this->list, elements, this->connectionPool);

            // otherwise get key values using scan
            else {
                int pos = 0;
                do RedisInterface::scan(this->list, elements, fetchChunkSize, pos, &pos, this->connectionPool);
                while(pos);
            }

            // deserialize the data
            for(auto itr = elements.begin(); itr != elements.end();itr += 2) {
                hash.insert(RedisValue<Key>::deserialize(*itr, this->binarizeKey), RedisValue<Value>::deserialize(*(itr + 1), this->binarizeValue));
            }

            // return hash
            return hash;
        }

    private:
        bool binarizeKey;
        bool binarizeValue;
        QByteArray list;
        QString connectionPool;
};


#endif // REDISMAP_H
