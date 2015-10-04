// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test.proto

#ifndef PROTOBUF_test_2eproto__INCLUDED
#define PROTOBUF_test_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace Protobuffer {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_test_2eproto();
void protobuf_AssignDesc_test_2eproto();
void protobuf_ShutdownFile_test_2eproto();

class Test;
class SubTest;

// ===================================================================

class Test : public ::google::protobuf::Message {
 public:
  Test();
  virtual ~Test();

  Test(const Test& from);

  inline Test& operator=(const Test& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Test& default_instance();

  void Swap(Test* other);

  // implements Message ----------------------------------------------

  Test* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Test& from);
  void MergeFrom(const Test& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string stringTest = 1;
  inline bool has_stringtest() const;
  inline void clear_stringtest();
  static const int kStringTestFieldNumber = 1;
  inline const ::std::string& stringtest() const;
  inline void set_stringtest(const ::std::string& value);
  inline void set_stringtest(const char* value);
  inline void set_stringtest(const char* value, size_t size);
  inline ::std::string* mutable_stringtest();
  inline ::std::string* release_stringtest();
  inline void set_allocated_stringtest(::std::string* stringtest);

  // required int64 int64Test = 2;
  inline bool has_int64test() const;
  inline void clear_int64test();
  static const int kInt64TestFieldNumber = 2;
  inline ::google::protobuf::int64 int64test() const;
  inline void set_int64test(::google::protobuf::int64 value);

  // optional .Protobuffer.SubTest testMessage = 3;
  inline bool has_testmessage() const;
  inline void clear_testmessage();
  static const int kTestMessageFieldNumber = 3;
  inline const ::Protobuffer::SubTest& testmessage() const;
  inline ::Protobuffer::SubTest* mutable_testmessage();
  inline ::Protobuffer::SubTest* release_testmessage();
  inline void set_allocated_testmessage(::Protobuffer::SubTest* testmessage);

  // @@protoc_insertion_point(class_scope:Protobuffer.Test)
 private:
  inline void set_has_stringtest();
  inline void clear_has_stringtest();
  inline void set_has_int64test();
  inline void clear_has_int64test();
  inline void set_has_testmessage();
  inline void clear_has_testmessage();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* stringtest_;
  ::google::protobuf::int64 int64test_;
  ::Protobuffer::SubTest* testmessage_;
  friend void  protobuf_AddDesc_test_2eproto();
  friend void protobuf_AssignDesc_test_2eproto();
  friend void protobuf_ShutdownFile_test_2eproto();

  void InitAsDefaultInstance();
  static Test* default_instance_;
};
// -------------------------------------------------------------------

class SubTest : public ::google::protobuf::Message {
 public:
  SubTest();
  virtual ~SubTest();

  SubTest(const SubTest& from);

  inline SubTest& operator=(const SubTest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SubTest& default_instance();

  void Swap(SubTest* other);

  // implements Message ----------------------------------------------

  SubTest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SubTest& from);
  void MergeFrom(const SubTest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string stringTest = 1;
  inline bool has_stringtest() const;
  inline void clear_stringtest();
  static const int kStringTestFieldNumber = 1;
  inline const ::std::string& stringtest() const;
  inline void set_stringtest(const ::std::string& value);
  inline void set_stringtest(const char* value);
  inline void set_stringtest(const char* value, size_t size);
  inline ::std::string* mutable_stringtest();
  inline ::std::string* release_stringtest();
  inline void set_allocated_stringtest(::std::string* stringtest);

  // required int64 int64Test = 2;
  inline bool has_int64test() const;
  inline void clear_int64test();
  static const int kInt64TestFieldNumber = 2;
  inline ::google::protobuf::int64 int64test() const;
  inline void set_int64test(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:Protobuffer.SubTest)
 private:
  inline void set_has_stringtest();
  inline void clear_has_stringtest();
  inline void set_has_int64test();
  inline void clear_has_int64test();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* stringtest_;
  ::google::protobuf::int64 int64test_;
  friend void  protobuf_AddDesc_test_2eproto();
  friend void protobuf_AssignDesc_test_2eproto();
  friend void protobuf_ShutdownFile_test_2eproto();

  void InitAsDefaultInstance();
  static SubTest* default_instance_;
};
// ===================================================================


// ===================================================================

// Test

// required string stringTest = 1;
inline bool Test::has_stringtest() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Test::set_has_stringtest() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Test::clear_has_stringtest() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Test::clear_stringtest() {
  if (stringtest_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    stringtest_->clear();
  }
  clear_has_stringtest();
}
inline const ::std::string& Test::stringtest() const {
  // @@protoc_insertion_point(field_get:Protobuffer.Test.stringTest)
  return *stringtest_;
}
inline void Test::set_stringtest(const ::std::string& value) {
  set_has_stringtest();
  if (stringtest_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    stringtest_ = new ::std::string;
  }
  stringtest_->assign(value);
  // @@protoc_insertion_point(field_set:Protobuffer.Test.stringTest)
}
inline void Test::set_stringtest(const char* value) {
  set_has_stringtest();
  if (stringtest_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    stringtest_ = new ::std::string;
  }
  stringtest_->assign(value);
  // @@protoc_insertion_point(field_set_char:Protobuffer.Test.stringTest)
}
inline void Test::set_stringtest(const char* value, size_t size) {
  set_has_stringtest();
  if (stringtest_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    stringtest_ = new ::std::string;
  }
  stringtest_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Protobuffer.Test.stringTest)
}
inline ::std::string* Test::mutable_stringtest() {
  set_has_stringtest();
  if (stringtest_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    stringtest_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Protobuffer.Test.stringTest)
  return stringtest_;
}
inline ::std::string* Test::release_stringtest() {
  clear_has_stringtest();
  if (stringtest_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = stringtest_;
    stringtest_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Test::set_allocated_stringtest(::std::string* stringtest) {
  if (stringtest_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete stringtest_;
  }
  if (stringtest) {
    set_has_stringtest();
    stringtest_ = stringtest;
  } else {
    clear_has_stringtest();
    stringtest_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Protobuffer.Test.stringTest)
}

// required int64 int64Test = 2;
inline bool Test::has_int64test() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Test::set_has_int64test() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Test::clear_has_int64test() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Test::clear_int64test() {
  int64test_ = GOOGLE_LONGLONG(0);
  clear_has_int64test();
}
inline ::google::protobuf::int64 Test::int64test() const {
  // @@protoc_insertion_point(field_get:Protobuffer.Test.int64Test)
  return int64test_;
}
inline void Test::set_int64test(::google::protobuf::int64 value) {
  set_has_int64test();
  int64test_ = value;
  // @@protoc_insertion_point(field_set:Protobuffer.Test.int64Test)
}

// optional .Protobuffer.SubTest testMessage = 3;
inline bool Test::has_testmessage() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Test::set_has_testmessage() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Test::clear_has_testmessage() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Test::clear_testmessage() {
  if (testmessage_ != NULL) testmessage_->::Protobuffer::SubTest::Clear();
  clear_has_testmessage();
}
inline const ::Protobuffer::SubTest& Test::testmessage() const {
  // @@protoc_insertion_point(field_get:Protobuffer.Test.testMessage)
  return testmessage_ != NULL ? *testmessage_ : *default_instance_->testmessage_;
}
inline ::Protobuffer::SubTest* Test::mutable_testmessage() {
  set_has_testmessage();
  if (testmessage_ == NULL) testmessage_ = new ::Protobuffer::SubTest;
  // @@protoc_insertion_point(field_mutable:Protobuffer.Test.testMessage)
  return testmessage_;
}
inline ::Protobuffer::SubTest* Test::release_testmessage() {
  clear_has_testmessage();
  ::Protobuffer::SubTest* temp = testmessage_;
  testmessage_ = NULL;
  return temp;
}
inline void Test::set_allocated_testmessage(::Protobuffer::SubTest* testmessage) {
  delete testmessage_;
  testmessage_ = testmessage;
  if (testmessage) {
    set_has_testmessage();
  } else {
    clear_has_testmessage();
  }
  // @@protoc_insertion_point(field_set_allocated:Protobuffer.Test.testMessage)
}

// -------------------------------------------------------------------

// SubTest

// required string stringTest = 1;
inline bool SubTest::has_stringtest() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SubTest::set_has_stringtest() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SubTest::clear_has_stringtest() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SubTest::clear_stringtest() {
  if (stringtest_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    stringtest_->clear();
  }
  clear_has_stringtest();
}
inline const ::std::string& SubTest::stringtest() const {
  // @@protoc_insertion_point(field_get:Protobuffer.SubTest.stringTest)
  return *stringtest_;
}
inline void SubTest::set_stringtest(const ::std::string& value) {
  set_has_stringtest();
  if (stringtest_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    stringtest_ = new ::std::string;
  }
  stringtest_->assign(value);
  // @@protoc_insertion_point(field_set:Protobuffer.SubTest.stringTest)
}
inline void SubTest::set_stringtest(const char* value) {
  set_has_stringtest();
  if (stringtest_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    stringtest_ = new ::std::string;
  }
  stringtest_->assign(value);
  // @@protoc_insertion_point(field_set_char:Protobuffer.SubTest.stringTest)
}
inline void SubTest::set_stringtest(const char* value, size_t size) {
  set_has_stringtest();
  if (stringtest_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    stringtest_ = new ::std::string;
  }
  stringtest_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Protobuffer.SubTest.stringTest)
}
inline ::std::string* SubTest::mutable_stringtest() {
  set_has_stringtest();
  if (stringtest_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    stringtest_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Protobuffer.SubTest.stringTest)
  return stringtest_;
}
inline ::std::string* SubTest::release_stringtest() {
  clear_has_stringtest();
  if (stringtest_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = stringtest_;
    stringtest_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SubTest::set_allocated_stringtest(::std::string* stringtest) {
  if (stringtest_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete stringtest_;
  }
  if (stringtest) {
    set_has_stringtest();
    stringtest_ = stringtest;
  } else {
    clear_has_stringtest();
    stringtest_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Protobuffer.SubTest.stringTest)
}

// required int64 int64Test = 2;
inline bool SubTest::has_int64test() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SubTest::set_has_int64test() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SubTest::clear_has_int64test() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SubTest::clear_int64test() {
  int64test_ = GOOGLE_LONGLONG(0);
  clear_has_int64test();
}
inline ::google::protobuf::int64 SubTest::int64test() const {
  // @@protoc_insertion_point(field_get:Protobuffer.SubTest.int64Test)
  return int64test_;
}
inline void SubTest::set_int64test(::google::protobuf::int64 value) {
  set_has_int64test();
  int64test_ = value;
  // @@protoc_insertion_point(field_set:Protobuffer.SubTest.int64Test)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Protobuffer

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_test_2eproto__INCLUDED
