#include "mmscenegraph/_cpp.h"
#include "mmscenegraph.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <string>
#include <type_traits>
#include <utility>

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

namespace {
template <typename T>
class impl;
} // namespace

#ifndef CXXBRIDGE1_RUST_STR
#define CXXBRIDGE1_RUST_STR
class Str final {
public:
  Str() noexcept;
  Str(const std::string &);
  Str(const char *);
  Str(const char *, size_t);

  Str &operator=(const Str &) noexcept = default;

  explicit operator std::string() const;

  const char *data() const noexcept;
  size_t size() const noexcept;
  size_t length() const noexcept;

  Str(const Str &) noexcept = default;
  ~Str() noexcept = default;

  using iterator = const char *;
  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

private:
  friend impl<Str>;
  const char *ptr;
  size_t len;
};

inline const char *Str::data() const noexcept { return this->ptr; }

inline size_t Str::size() const noexcept { return this->len; }

inline size_t Str::length() const noexcept { return this->len; }
#endif // CXXBRIDGE1_RUST_STR

#ifndef CXXBRIDGE1_RUST_BOX
#define CXXBRIDGE1_RUST_BOX
template <typename T>
class Box final {
public:
  using value_type = T;
  using const_pointer =
      typename std::add_pointer<typename std::add_const<T>::type>::type;
  using pointer = typename std::add_pointer<T>::type;

  Box(const Box &);
  Box(Box &&) noexcept;
  ~Box() noexcept;

  explicit Box(const T &);
  explicit Box(T &&);

  Box &operator=(const Box &);
  Box &operator=(Box &&) noexcept;

  const T *operator->() const noexcept;
  const T &operator*() const noexcept;
  T *operator->() noexcept;
  T &operator*() noexcept;

  template <typename... Fields>
  static Box in_place(Fields &&...);

  static Box from_raw(T *) noexcept;

  T *into_raw() noexcept;

private:
  Box() noexcept;
  void uninit() noexcept;
  void drop() noexcept;
  T *ptr;
};

template <typename T>
Box<T>::Box(const Box &other) : Box(*other) {}

template <typename T>
Box<T>::Box(Box &&other) noexcept : ptr(other.ptr) {
  other.ptr = nullptr;
}

template <typename T>
Box<T>::Box(const T &val) {
  this->uninit();
  ::new (this->ptr) T(val);
}

template <typename T>
Box<T>::Box(T &&val) {
  this->uninit();
  ::new (this->ptr) T(std::move(val));
}

template <typename T>
Box<T>::~Box() noexcept {
  if (this->ptr) {
    this->drop();
  }
}

template <typename T>
Box<T> &Box<T>::operator=(const Box &other) {
  if (this != &other) {
    if (this->ptr) {
      **this = *other;
    } else {
      this->uninit();
      ::new (this->ptr) T(*other);
    }
  }
  return *this;
}

template <typename T>
Box<T> &Box<T>::operator=(Box &&other) noexcept {
  if (this->ptr) {
    this->drop();
  }
  this->ptr = other.ptr;
  other.ptr = nullptr;
  return *this;
}

template <typename T>
const T *Box<T>::operator->() const noexcept {
  return this->ptr;
}

template <typename T>
const T &Box<T>::operator*() const noexcept {
  return *this->ptr;
}

template <typename T>
T *Box<T>::operator->() noexcept {
  return this->ptr;
}

template <typename T>
T &Box<T>::operator*() noexcept {
  return *this->ptr;
}

template <typename T>
template <typename... Fields>
Box<T> Box<T>::in_place(Fields &&... fields) {
  Box box;
  box.uninit();
  ::new (box.ptr) T{std::forward<Fields>(fields)...};
  return box;
}

template <typename T>
Box<T> Box<T>::from_raw(T *raw) noexcept {
  Box box;
  box.ptr = raw;
  return box;
}

template <typename T>
T *Box<T>::into_raw() noexcept {
  T *raw = this->ptr;
  this->ptr = nullptr;
  return raw;
}

template <typename T>
Box<T>::Box() noexcept = default;
#endif // CXXBRIDGE1_RUST_BOX

#ifndef CXXBRIDGE1_RUST_OPAQUE
#define CXXBRIDGE1_RUST_OPAQUE
class Opaque {
public:
  Opaque() = delete;
  Opaque(const Opaque &) = delete;
  ~Opaque() = delete;
};
#endif // CXXBRIDGE1_RUST_OPAQUE

namespace {
namespace repr {
struct PtrLen final {
  void *ptr;
  size_t len;
};
} // namespace repr

template <>
class impl<Str> final {
public:
  static Str new_unchecked(repr::PtrLen repr) noexcept {
    Str str;
    str.ptr = static_cast<const char *>(repr.ptr);
    str.len = repr.len;
    return str;
  }
};

template <typename T, typename = size_t>
struct is_complete : std::false_type {};

template <typename T>
struct is_complete<T, decltype(sizeof(T))> : std::true_type {};

template <bool> struct deleter_if {
  template <typename T> void operator()(T *) {}
};

template <> struct deleter_if<true> {
  template <typename T> void operator()(T *ptr) { ptr->~T(); }
};
} // namespace
} // namespace cxxbridge1
} // namespace rust

namespace mmscenegraph {
  struct SharedThing;
  using ThingC = ::mmscenegraph::ThingC;
  struct ThingR;
  struct ReadOperation;
}

namespace mmscenegraph {
#ifndef CXXBRIDGE1_STRUCT_mmscenegraph$SharedThing
#define CXXBRIDGE1_STRUCT_mmscenegraph$SharedThing
struct SharedThing final {
  int32_t z;
  ::rust::Box<::mmscenegraph::ThingR> y;
  ::std::unique_ptr<::mmscenegraph::ThingC> x;
};
#endif // CXXBRIDGE1_STRUCT_mmscenegraph$SharedThing

#ifndef CXXBRIDGE1_STRUCT_mmscenegraph$ReadOperation
#define CXXBRIDGE1_STRUCT_mmscenegraph$ReadOperation
struct ReadOperation final : public ::rust::Opaque {
  uint8_t get_id() const noexcept;
  size_t get_num() const noexcept;
};
#endif // CXXBRIDGE1_STRUCT_mmscenegraph$ReadOperation

extern "C" {
__declspec(dllexport) ::mmscenegraph::ThingC *mmscenegraph$cxxbridge1$make_demo(::rust::repr::PtrLen appname) noexcept {
  ::std::unique_ptr<::mmscenegraph::ThingC> (*make_demo$)(::rust::Str) = ::mmscenegraph::make_demo;
  return make_demo$(::rust::impl<::rust::Str>::new_unchecked(appname)).release();
}

__declspec(dllexport) const ::std::string *mmscenegraph$cxxbridge1$get_name(const ::mmscenegraph::ThingC &thing) noexcept {
  const ::std::string &(*get_name$)(const ::mmscenegraph::ThingC &) = ::mmscenegraph::get_name;
  return &get_name$(thing);
}

__declspec(dllexport) void mmscenegraph$cxxbridge1$do_thing(::mmscenegraph::SharedThing *state) noexcept {
  void (*do_thing$)(::mmscenegraph::SharedThing) = ::mmscenegraph::do_thing;
  do_thing$(::std::move(*state));
}

void mmscenegraph$cxxbridge1$print_r(const ::mmscenegraph::ThingR &r) noexcept;

uint8_t mmscenegraph$cxxbridge1$ReadOperation$get_id(const ::mmscenegraph::ReadOperation &self) noexcept;

size_t mmscenegraph$cxxbridge1$ReadOperation$get_num(const ::mmscenegraph::ReadOperation &self) noexcept;

::mmscenegraph::ReadOperation *mmscenegraph$cxxbridge1$new_read_operation(uint8_t id, size_t num) noexcept;
} // extern "C"

void print_r(const ::mmscenegraph::ThingR &r) noexcept {
  mmscenegraph$cxxbridge1$print_r(r);
}

uint8_t ReadOperation::get_id() const noexcept {
  return mmscenegraph$cxxbridge1$ReadOperation$get_id(*this);
}

size_t ReadOperation::get_num() const noexcept {
  return mmscenegraph$cxxbridge1$ReadOperation$get_num(*this);
}

::rust::Box<::mmscenegraph::ReadOperation> new_read_operation(uint8_t id, size_t num) noexcept {
  return ::rust::Box<::mmscenegraph::ReadOperation>::from_raw(mmscenegraph$cxxbridge1$new_read_operation(id, num));
}
} // namespace mmscenegraph

extern "C" {
#ifndef CXXBRIDGE1_RUST_BOX_mmscenegraph$ThingR
#define CXXBRIDGE1_RUST_BOX_mmscenegraph$ThingR
void cxxbridge1$box$mmscenegraph$ThingR$uninit(::rust::Box<::mmscenegraph::ThingR> *ptr) noexcept;
void cxxbridge1$box$mmscenegraph$ThingR$drop(::rust::Box<::mmscenegraph::ThingR> *ptr) noexcept;
#endif // CXXBRIDGE1_RUST_BOX_mmscenegraph$ThingR

#ifndef CXXBRIDGE1_UNIQUE_PTR_mmscenegraph$ThingC
#define CXXBRIDGE1_UNIQUE_PTR_mmscenegraph$ThingC
static_assert(::rust::is_complete<::mmscenegraph::ThingC>::value, "definition of ThingC is required");
static_assert(sizeof(::std::unique_ptr<::mmscenegraph::ThingC>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::mmscenegraph::ThingC>) == alignof(void *), "");
void cxxbridge1$unique_ptr$mmscenegraph$ThingC$null(::std::unique_ptr<::mmscenegraph::ThingC> *ptr) noexcept {
  new (ptr) ::std::unique_ptr<::mmscenegraph::ThingC>();
}
void cxxbridge1$unique_ptr$mmscenegraph$ThingC$raw(::std::unique_ptr<::mmscenegraph::ThingC> *ptr, ::mmscenegraph::ThingC *raw) noexcept {
  new (ptr) ::std::unique_ptr<::mmscenegraph::ThingC>(raw);
}
const ::mmscenegraph::ThingC *cxxbridge1$unique_ptr$mmscenegraph$ThingC$get(const ::std::unique_ptr<::mmscenegraph::ThingC>& ptr) noexcept {
  return ptr.get();
}
::mmscenegraph::ThingC *cxxbridge1$unique_ptr$mmscenegraph$ThingC$release(::std::unique_ptr<::mmscenegraph::ThingC>& ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$mmscenegraph$ThingC$drop(::std::unique_ptr<::mmscenegraph::ThingC> *ptr) noexcept {
  ::rust::deleter_if<::rust::is_complete<::mmscenegraph::ThingC>::value>{}(ptr);
}
#endif // CXXBRIDGE1_UNIQUE_PTR_mmscenegraph$ThingC

#ifndef CXXBRIDGE1_RUST_BOX_mmscenegraph$ReadOperation
#define CXXBRIDGE1_RUST_BOX_mmscenegraph$ReadOperation
void cxxbridge1$box$mmscenegraph$ReadOperation$uninit(::rust::Box<::mmscenegraph::ReadOperation> *ptr) noexcept;
void cxxbridge1$box$mmscenegraph$ReadOperation$drop(::rust::Box<::mmscenegraph::ReadOperation> *ptr) noexcept;
#endif // CXXBRIDGE1_RUST_BOX_mmscenegraph$ReadOperation
} // extern "C"

namespace rust {
inline namespace cxxbridge1 {
template <>
void Box<::mmscenegraph::ThingR>::uninit() noexcept {
  cxxbridge1$box$mmscenegraph$ThingR$uninit(this);
}
template <>
void Box<::mmscenegraph::ThingR>::drop() noexcept {
  cxxbridge1$box$mmscenegraph$ThingR$drop(this);
}
template <>
void Box<::mmscenegraph::ReadOperation>::uninit() noexcept {
  cxxbridge1$box$mmscenegraph$ReadOperation$uninit(this);
}
template <>
void Box<::mmscenegraph::ReadOperation>::drop() noexcept {
  cxxbridge1$box$mmscenegraph$ReadOperation$drop(this);
}
} // namespace cxxbridge1
} // namespace rust
