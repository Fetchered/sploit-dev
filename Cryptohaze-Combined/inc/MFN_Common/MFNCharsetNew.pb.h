// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MFNCharsetNew.proto

#ifndef PROTOBUF_MFNCharsetNew_2eproto__INCLUDED
#define PROTOBUF_MFNCharsetNew_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_MFNCharsetNew_2eproto();
void protobuf_AssignDesc_MFNCharsetNew_2eproto();
void protobuf_ShutdownFile_MFNCharsetNew_2eproto();

class MFNCharsetNewProtobuf;

// ===================================================================

class MFNCharsetNewProtobuf : public ::google::protobuf::Message {
 public:
  MFNCharsetNewProtobuf();
  virtual ~MFNCharsetNewProtobuf();
  
  MFNCharsetNewProtobuf(const MFNCharsetNewProtobuf& from);
  
  inline MFNCharsetNewProtobuf& operator=(const MFNCharsetNewProtobuf& from) {
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
  static const MFNCharsetNewProtobuf& default_instance();
  
  void Swap(MFNCharsetNewProtobuf* other);
  
  // implements Message ----------------------------------------------
  
  MFNCharsetNewProtobuf* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MFNCharsetNewProtobuf& from);
  void MergeFrom(const MFNCharsetNewProtobuf& from);
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
  
  // optional uint32 charset_size = 1;
  inline bool has_charset_size() const;
  inline void clear_charset_size();
  static const int kCharsetSizeFieldNumber = 1;
  inline ::google::protobuf::uint32 charset_size() const;
  inline void set_charset_size(::google::protobuf::uint32 value);
  
  // repeated bytes charset_position_data = 2;
  inline int charset_position_data_size() const;
  inline void clear_charset_position_data();
  static const int kCharsetPositionDataFieldNumber = 2;
  inline const ::std::string& charset_position_data(int index) const;
  inline ::std::string* mutable_charset_position_data(int index);
  inline void set_charset_position_data(int index, const ::std::string& value);
  inline void set_charset_position_data(int index, const char* value);
  inline void set_charset_position_data(int index, const void* value, size_t size);
  inline ::std::string* add_charset_position_data();
  inline void add_charset_position_data(const ::std::string& value);
  inline void add_charset_position_data(const char* value);
  inline void add_charset_position_data(const void* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& charset_position_data() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_charset_position_data();
  
  // @@protoc_insertion_point(class_scope:MFNCharsetNewProtobuf)
 private:
  inline void set_has_charset_size();
  inline void clear_has_charset_size();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::std::string> charset_position_data_;
  ::google::protobuf::uint32 charset_size_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_MFNCharsetNew_2eproto();
  friend void protobuf_AssignDesc_MFNCharsetNew_2eproto();
  friend void protobuf_ShutdownFile_MFNCharsetNew_2eproto();
  
  void InitAsDefaultInstance();
  static MFNCharsetNewProtobuf* default_instance_;
};
// ===================================================================


// ===================================================================

// MFNCharsetNewProtobuf

// optional uint32 charset_size = 1;
inline bool MFNCharsetNewProtobuf::has_charset_size() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MFNCharsetNewProtobuf::set_has_charset_size() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MFNCharsetNewProtobuf::clear_has_charset_size() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MFNCharsetNewProtobuf::clear_charset_size() {
  charset_size_ = 0u;
  clear_has_charset_size();
}
inline ::google::protobuf::uint32 MFNCharsetNewProtobuf::charset_size() const {
  return charset_size_;
}
inline void MFNCharsetNewProtobuf::set_charset_size(::google::protobuf::uint32 value) {
  set_has_charset_size();
  charset_size_ = value;
}

// repeated bytes charset_position_data = 2;
inline int MFNCharsetNewProtobuf::charset_position_data_size() const {
  return charset_position_data_.size();
}
inline void MFNCharsetNewProtobuf::clear_charset_position_data() {
  charset_position_data_.Clear();
}
inline const ::std::string& MFNCharsetNewProtobuf::charset_position_data(int index) const {
  return charset_position_data_.Get(index);
}
inline ::std::string* MFNCharsetNewProtobuf::mutable_charset_position_data(int index) {
  return charset_position_data_.Mutable(index);
}
inline void MFNCharsetNewProtobuf::set_charset_position_data(int index, const ::std::string& value) {
  charset_position_data_.Mutable(index)->assign(value);
}
inline void MFNCharsetNewProtobuf::set_charset_position_data(int index, const char* value) {
  charset_position_data_.Mutable(index)->assign(value);
}
inline void MFNCharsetNewProtobuf::set_charset_position_data(int index, const void* value, size_t size) {
  charset_position_data_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MFNCharsetNewProtobuf::add_charset_position_data() {
  return charset_position_data_.Add();
}
inline void MFNCharsetNewProtobuf::add_charset_position_data(const ::std::string& value) {
  charset_position_data_.Add()->assign(value);
}
inline void MFNCharsetNewProtobuf::add_charset_position_data(const char* value) {
  charset_position_data_.Add()->assign(value);
}
inline void MFNCharsetNewProtobuf::add_charset_position_data(const void* value, size_t size) {
  charset_position_data_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
MFNCharsetNewProtobuf::charset_position_data() const {
  return charset_position_data_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
MFNCharsetNewProtobuf::mutable_charset_position_data() {
  return &charset_position_data_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MFNCharsetNew_2eproto__INCLUDED
