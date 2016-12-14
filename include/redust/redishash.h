#ifndef REDISMAP_H
#define REDISMAP_H

// core
#include <QByteArray>
#include <QString>

// redis
#include "typeserializer.h"
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
                this->redisServer = other.redisServer;
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
                if(this->currentKey.isEmpty()) return *this;
                RedisInterface::hdel(*this->redisServer, this->currentKey, waitForAnswer);
                return this->forward(1);
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
                return this->list == other.list &&
                       this->pos == other.pos &&
                       this->queueElements.size() == other.queueElements.size();
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
            iterator(RedisServer& redisServer, QByteArray list, int pos, int cacheSize, bool binarizeKey, bool binarizeValue)
            {
                this->list = list;
                this->redisServer = &redisServer;
                this->cacheSize = cacheSize;
                this->binarizeKey = binarizeKey;
                this->binarizeValue = binarizeValue;
                this->pos = pos;
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
                    this->currentKey = this->queueElements.front();
                    this->queueElements.pop_front();
                    this->currentValue = this->queueElements.front();
                    this->queueElements.pop_front();
                }
                return *this;
            }

            bool refillQueue()
            {
                // if queue is not empty, don't refill
                if(this->queueElements.size() > 0) return true;

                // if we reach the end of the redis position, set current pos to -1 and exit
                if(this->posRedis == 0) this->pos = -1;
                if(this->pos == -1) return false;

                // if redis pos is set to -1 (it's an invalid position) set position to begin
                // Note: this is a little hack for initialiating because redis start and end value are both 0
                if(this->posRedis == -1) this->posRedis = 0;

                // refill queue
                RedisInterface::scan(*this->redisServer, this->list, this->queueElements, this->cacheSize, this->posRedis, &this->posRedis);

                // if we couldn't get any items then we reached the end
                // Note: this could happend if we try to get data from an non-existing/empty key
                //       if this is the case then we call us again so that this iterator is set to end
                return this->queueElements.size() > 0 ? this->refillQueue() : true;
            }

            void loadEntry(bool key, bool value)
            {
                // load key (if not allready happened)
                if(key && !this->keyLoaded) {
                    this->currentKeyVal = TypeSerializer<Key>::deserialize(this->currentKey, this->binarizeKey);
                    this->keyLoaded = true;
                }

                // load value (if not allready happened)
                if(value && !this->valueLoaded) {
                    this->currentValueVal = TypeSerializer<Value>::deserialize(this->currentValue, this->binarizeValue);
                    this->valueLoaded = true;
                }
            }

            // data
            int cacheSize;
            int posRedis = -1;
            int pos;
            std::list<QByteArray> queueElements;
            QByteArray currentKey;
            QByteArray currentValue;
            NORM2VALUE(Key) currentKeyVal;
            NORM2VALUE(Value) currentValueVal;
            bool keyLoaded = false;
            bool valueLoaded = false;
            bool binarizeKey = false;
            bool binarizeValue = false;
            QByteArray list;
            RedisServer* redisServer;

        friend class RedisHash;
    };

    public:
        RedisHash(RedisServer& redisServer, QByteArray list, bool binarizeKey = false, bool binarizeValue = false)
        {
            this->redisServer = &redisServer;
            this->binarizeKey = binarizeKey;
            this->binarizeValue = binarizeValue;
            this->list = list;
        }

        ~RedisHash()
        {

        }

        iterator begin(int cacheSize = 100)
        {
            return iterator(*this->redisServer, this->list, 0, cacheSize, this->binarizeKey, this->binarizeValue);
        }

        iterator end(int cacheSize = 100)
        {
            return iterator(*this->redisServer, this->list, -1, cacheSize, this->binarizeKey, this->binarizeValue);
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
            return RedisInterface::hlen(*this->redisServer, this->list);
        }

        bool empty()
        {
            return this->isEmpty();
        }

        bool isEmpty()
        {
            return !RedisInterface::hlen(*this->redisServer, this->list);
        }

        bool exists(Key key)
        {
            return RedisInterface::hexists(this->list, TypeSerializer<Key>::serialize(key, this->binarizeKey), this->connectionPool);
        }

        bool exists()
        {
            return RedisInterface::exists(this->list, this->connectionPool);
        }

        bool remove(Key key, bool waitForAnswer = true)
        {
            return RedisInterface::hdel(*this->redisServer, this->list, TypeSerializer<Key>::serialize(key, this->binarizeKey), waitForAnswer);
        }

        NORM2VALUE(Value) take(Key key, bool waitForAnswer = true, bool *removeResult = 0)
        {
            NORM2VALUE(Value) value = this->value(key);
            bool rResult = this->remove(key, waitForAnswer);
            if(removeResult) *removeResult = rResult;
            return value;
        }

        bool insert(Key key, Value value, bool waitForAnswer = false, bool onlySetIfNotExists = false)
        {
            return RedisInterface::hset(*this->redisServer, this->list, TypeSerializer<Key>::serialize(key, this->binarizeKey),
                                   TypeSerializer<Value>::serialize(value, this->binarizeValue), waitForAnswer, onlySetIfNotExists);
        }

        bool insert(QMap<Key, Value> values, bool waitForAnswer = false)
        {
            QList<QByteArray> keys;
            QList<QByteArray> vals;
            for(auto itr = values.begin(); itr != values.end(); itr++) {
                keys.append(TypeSerializer<Key>::serialize(itr.key(), this->binarizeKey));
                vals.append(TypeSerializer<Value>::serialize(itr.value(), this->binarizeValue));
            }
            return RedisInterface::hmset(this->list, keys, vals, waitForAnswer, this->connectionPool);
        }

        bool insert(QHash<Key, Value> values, bool waitForAnswer = false)
        {
            QList<QByteArray> keys;
            QList<QByteArray> vals;
            for(auto itr = values.begin(); itr != values.end(); itr++) {
                keys.append(TypeSerializer<Key>::serialize(itr.key(), this->binarizeKey));
                vals.append(TypeSerializer<Value>::serialize(itr.value(), this->binarizeValue));
            }
            return RedisInterface::hmset(this->list, keys, vals, waitForAnswer, this->connectionPool);
        }

        bool insert(QList<Key> keys, QList<Value> values, bool waitForAnswer = false)
        {
            if(keys.count() != values.count()) return false;
            return RedisInterface::hmset(this->list, keys, values, waitForAnswer, this->connectionPool);
        }

        NORM2VALUE(Value) value(Key key)
        {
            return TypeSerializer<Value>::deserialize(RedisInterface::hget(*this->redisServer, this->list, TypeSerializer<Key>::serialize(key, this->binarizeKey)), this->binarizeValue);
        }

        int valueLength(Key key)
        {
            return RedisInterface::hstrlen(*this->redisServer, this->list, TypeSerializer<Key>::serialize(key, this->binarizeKey));
        }

        QList<NORM2VALUE(Key)> keys(int fetchChunkSize = -1)
        {
            // create result data list
            QList<NORM2VALUE(Key)> list;

            // if fetch chunk size is smaller or equal 0, so exec hkeys
            std::list<QByteArray> elements;
            if(fetchChunkSize <= 0) RedisInterface::hkeys(*this->redisServer, this->list, elements);

            // otherwise get keys using scan
            else {
                int pos = 0;
                do RedisInterface::scan(*this->redisServer, this->list, &elements, 0, fetchChunkSize, pos, &pos);
                while(pos);
            }

            // deserialize byte array data to Key Type
            for(auto itr = elements.begin(); itr != elements.end(); itr = elements.erase(itr)) {
                list.append(TypeSerializer<Key>::deserialize(*itr, this->binarizeKey));
            }

            // return list
            return list;
        }

        QList<NORM2VALUE(Value)> values(int fetchChunkSize = -1)
        {
            // create result data list
            QList<NORM2VALUE(Value)> list;

            // if fetch chunk size is smaller or equal 0, so exec hvals
            std::list<QByteArray> elements;
            if(fetchChunkSize <= 0) RedisInterface::hvals(*this->redisServer, this->list, elements);

            // otherwise get values using scan
            else {
                int pos = 0;
                do RedisInterface::scan(*this->redisServer, this->list, 0, &elements, fetchChunkSize, pos, &pos);
                while(pos);
            }

            // deserialize byte array data to Value Type
            for(auto itr = elements.begin(); itr != elements.end(); itr = elements.erase(itr)) {
                list.append(TypeSerializer<Value>::deserialize(*itr, this->binarizeValue));
            }

            // return list
            return list;
        }

        QList<NORM2VALUE(Value)> values(QList<NORM2VALUE(Key)> keys)
        {
            // serialize all keys to QBytearray list and execute hmget command
            std::list<QByteArray> sKeys;
            for(auto itr = keys.begin(); itr != keys.end(); itr++) {
                sKeys << TypeSerializer<Key>::serialize(*itr, this->binarizeKey);
            }
            std::list<QByteArray> sValues = RedisInterface::hmget(*this->redisServer, this->list, sKeys);

            // deserialize values to Value Type and append it to values list
            QList<NORM2VALUE(Value)> values;
            while(sValues.size() > 0) {
                values.append(TypeSerializer<Value>::deserialize(sValues.front(), this->binarizeValue));
                sValues.pop_front();
            }
            return values;
        }

        QMap<NORM2VALUE(Key),NORM2VALUE(Value)> toMap(int fetchChunkSize = -1)
        {
            // create result data list
            QMap<NORM2VALUE(Key),NORM2VALUE(Value)> map;

            // if fetch chunk size is smaller or equal 0, so exec hgetall
            std::list<QByteArray> elements;
            if(fetchChunkSize <= 0) RedisInterface::hgetall(*this->redisServer, this->list, elements);

            // otherwise get key values using scan
            else {
                int pos = 0;
                do RedisInterface::scan(*this->redisServer, this->list, elements, fetchChunkSize, pos, &pos);
                while(pos);
            }

            // deserialize the data
            for(auto itr = elements.begin(); itr != elements.end();) {
                QByteArray key = *itr++;
                QByteArray value = *itr++;
                map.insert(TypeSerializer<Key>::deserialize(key, this->binarizeKey), TypeSerializer<Value>::deserialize(value, this->binarizeValue));
            }

            // return map
            return map;
        }

        QHash<NORM2VALUE(Key),NORM2VALUE(Value)> toHash(int fetchChunkSize = -1)
        {
            // create result data list
            QHash<NORM2VALUE(Key),NORM2VALUE(Value)> hash;

            // if fetch chunk size is smaller or equal 0, so exec hgetall
            std::list<QByteArray> elements;
            if(fetchChunkSize <= 0) RedisInterface::hgetall(*this->redisServer, this->list, elements);

            // otherwise get key values using scan
            else {
                int pos = 0;
                do RedisInterface::scan(*this->redisServer, this->list, elements, fetchChunkSize, pos, &pos);
                while(pos);
            }

            // deserialize the data
            for(auto itr = elements.begin(); itr != elements.end();) {
                QByteArray key = *itr++;
                QByteArray value = *itr++;
                hash.insert(TypeSerializer<Key>::deserialize(key, this->binarizeKey), TypeSerializer<Value>::deserialize(value, this->binarizeValue));
            }

            // return hash
            return hash;
        }

    private:
        bool binarizeKey;
        bool binarizeValue;
        QByteArray list;
        RedisServer* redisServer;
};


#endif // REDISMAP_H