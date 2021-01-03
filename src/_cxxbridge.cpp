#include "mmscenegraph/symbol_export.h"
#include "mmscenegraph/_cpp.h"
#include <mmscenegraph.h>
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

class String;

#ifndef CXXBRIDGE1_RUST_STR
#define CXXBRIDGE1_RUST_STR
class Str final {
public:
  Str() noexcept;
  Str(const String &) noexcept;
  Str(const std::string &);
  Str(const char *);
  Str(const char *, std::size_t);

  Str &operator=(const Str &) noexcept = default;

  explicit operator std::string() const;

  const char *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;

  Str(const Str &) noexcept = default;
  ~Str() noexcept = default;

  using iterator = const char *;
  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool operator==(const Str &) const noexcept;
  bool operator!=(const Str &) const noexcept;
  bool operator<(const Str &) const noexcept;
  bool operator<=(const Str &) const noexcept;
  bool operator>(const Str &) const noexcept;
  bool operator>=(const Str &) const noexcept;

private:
  friend impl<Str>;
  const char *ptr;
  std::size_t len;
};

inline const char *Str::data() const noexcept { return this->ptr; }

inline std::size_t Str::size() const noexcept { return this->len; }

inline std::size_t Str::length() const noexcept { return this->len; }
#endif // CXXBRIDGE1_RUST_STR

#ifndef CXXBRIDGE1_RUST_BOX
#define CXXBRIDGE1_RUST_BOX
template <typename T>
class Box final {
public:
  using element_type = T;
  using const_pointer =
      typename std::add_pointer<typename std::add_const<T>::type>::type;
  using pointer = typename std::add_pointer<T>::type;

  Box() = delete;
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

  /* Deprecated */ using value_type = element_type;

private:
  class uninit;
  class allocation;
  Box(uninit) noexcept;
  void drop() noexcept;
  T *ptr;
};

template <typename T>
class Box<T>::uninit {};

template <typename T>
class Box<T>::allocation {
  static T *alloc() noexcept;
  static void dealloc(T *) noexcept;

public:
  allocation() noexcept : ptr(alloc()) {}
  ~allocation() noexcept {
    if (this->ptr) {
      dealloc(this->ptr);
    }
  }
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
  allocation alloc;
  ::new (alloc.ptr) T(val);
  this->ptr = alloc.ptr;
  alloc.ptr = nullptr;
}

template <typename T>
Box<T>::Box(T &&val) {
  allocation alloc;
  ::new (alloc.ptr) T(std::move(val));
  this->ptr = alloc.ptr;
  alloc.ptr = nullptr;
}

template <typename T>
Box<T>::~Box() noexcept {
  if (this->ptr) {
    this->drop();
  }
}

template <typename T>
Box<T> &Box<T>::operator=(const Box &other) {
  if (this->ptr) {
    **this = *other;
  } else {
    allocation alloc;
    ::new (alloc.ptr) T(*other);
    this->ptr = alloc.ptr;
    alloc.ptr = nullptr;
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
  allocation alloc;
  auto ptr = alloc.ptr;
  ::new (ptr) T{std::forward<Fields>(fields)...};
  alloc.ptr = nullptr;
  return from_raw(ptr);
}

template <typename T>
Box<T> Box<T>::from_raw(T *raw) noexcept {
  Box box = uninit{};
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
Box<T>::Box(uninit) noexcept {}
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

#ifndef CXXBRIDGE1_IS_COMPLETE
#define CXXBRIDGE1_IS_COMPLETE
namespace detail {
namespace {
template <typename T, typename = std::size_t>
struct is_complete : std::false_type {};
template <typename T>
struct is_complete<T, decltype(sizeof(T))> : std::true_type {};
} // namespace
} // namespace detail
#endif // CXXBRIDGE1_IS_COMPLETE

#ifndef CXXBRIDGE1_LAYOUT
#define CXXBRIDGE1_LAYOUT
class layout {
  template <typename T>
  friend std::size_t size_of();
  template <typename T>
  friend std::size_t align_of();
  template <typename T>
  static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_size_of() {
    return T::layout::size();
  }
  template <typename T>
  static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_size_of() {
    return sizeof(T);
  }
  template <typename T>
  static
      typename std::enable_if<detail::is_complete<T>::value, std::size_t>::type
      size_of() {
    return do_size_of<T>();
  }
  template <typename T>
  static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_align_of() {
    return T::layout::align();
  }
  template <typename T>
  static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_align_of() {
    return alignof(T);
  }
  template <typename T>
  static
      typename std::enable_if<detail::is_complete<T>::value, std::size_t>::type
      align_of() {
    return do_align_of<T>();
  }
};

template <typename T>
std::size_t size_of() {
  return layout::size_of<T>();
}

template <typename T>
std::size_t align_of() {
  return layout::align_of<T>();
}
#endif // CXXBRIDGE1_LAYOUT

namespace {
namespace repr {
struct PtrLen final {
  void *ptr;
  ::std::size_t len;
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
  struct WriteOperation;
}

namespace mmscenegraph {
#ifndef CXXBRIDGE1_STRUCT_mmscenegraph$SharedThing
#define CXXBRIDGE1_STRUCT_mmscenegraph$SharedThing
struct SharedThing final {
  ::std::int32_t z;
  ::rust::Box<::mmscenegraph::ThingR> y;
  ::std::unique_ptr<::mmscenegraph::ThingC> x;

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_mmscenegraph$SharedThing

#ifndef CXXBRIDGE1_STRUCT_mmscenegraph$ThingR
#define CXXBRIDGE1_STRUCT_mmscenegraph$ThingR
struct ThingR final : public ::rust::Opaque {
private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_mmscenegraph$ThingR

#ifndef CXXBRIDGE1_STRUCT_mmscenegraph$ReadOperation
#define CXXBRIDGE1_STRUCT_mmscenegraph$ReadOperation
struct ReadOperation final : public ::rust::Opaque {
  MMSCENEGRAPH_SYMBOL_EXPORT ::std::uint8_t get_id() const noexcept;
  MMSCENEGRAPH_SYMBOL_EXPORT ::std::size_t get_num() const noexcept;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_mmscenegraph$ReadOperation

#ifndef CXXBRIDGE1_STRUCT_mmscenegraph$WriteOperation
#define CXXBRIDGE1_STRUCT_mmscenegraph$WriteOperation
struct WriteOperation final : public ::rust::Opaque {
  MMSCENEGRAPH_SYMBOL_EXPORT ::std::uint8_t get_id() const noexcept;
  MMSCENEGRAPH_SYMBOL_EXPORT ::std::size_t get_num() const noexcept;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_mmscenegraph$WriteOperation

extern "C" {
MMSCENEGRAPH_SYMBOL_EXPORT ::mmscenegraph::ThingC *mmscenegraph$cxxbridge1$make_demo(::rust::repr::PtrLen appname) noexcept {
  ::std::unique_ptr<::mmscenegraph::ThingC> (*make_demo$)(::rust::Str) = ::mmscenegraph::make_demo;
  return make_demo$(::rust::impl<::rust::Str>::new_unchecked(appname)).release();
}

MMSCENEGRAPH_SYMBOL_EXPORT const ::std::string *mmscenegraph$cxxbridge1$get_name(const ::mmscenegraph::ThingC &thing) noexcept {
  const ::std::string &(*get_name$)(const ::mmscenegraph::ThingC &) = ::mmscenegraph::get_name;
  return &get_name$(thing);
}

MMSCENEGRAPH_SYMBOL_EXPORT void mmscenegraph$cxxbridge1$do_thing(::mmscenegraph::SharedThing *state) noexcept {
  void (*do_thing$)(::mmscenegraph::SharedThing) = ::mmscenegraph::do_thing;
  do_thing$(::std::move(*state));
}
::std::size_t mmscenegraph$cxxbridge1$ThingR$operator$sizeof() noexcept;
::std::size_t mmscenegraph$cxxbridge1$ThingR$operator$alignof() noexcept;

void mmscenegraph$cxxbridge1$print_r(const ::mmscenegraph::ThingR &r) noexcept;
::std::size_t mmscenegraph$cxxbridge1$ReadOperation$operator$sizeof() noexcept;
::std::size_t mmscenegraph$cxxbridge1$ReadOperation$operator$alignof() noexcept;

::std::uint8_t mmscenegraph$cxxbridge1$ReadOperation$get_id(const ::mmscenegraph::ReadOperation &self) noexcept;

::std::size_t mmscenegraph$cxxbridge1$ReadOperation$get_num(const ::mmscenegraph::ReadOperation &self) noexcept;

::mmscenegraph::ReadOperation *mmscenegraph$cxxbridge1$new_read_operation(::std::uint8_t id, ::std::size_t num) noexcept;
::std::size_t mmscenegraph$cxxbridge1$WriteOperation$operator$sizeof() noexcept;
::std::size_t mmscenegraph$cxxbridge1$WriteOperation$operator$alignof() noexcept;

::std::uint8_t mmscenegraph$cxxbridge1$WriteOperation$get_id(const ::mmscenegraph::WriteOperation &self) noexcept;

::std::size_t mmscenegraph$cxxbridge1$WriteOperation$get_num(const ::mmscenegraph::WriteOperation &self) noexcept;

::mmscenegraph::WriteOperation *mmscenegraph$cxxbridge1$new_write_operation(::std::uint8_t id, ::std::size_t num) noexcept;
} // extern "C"

::std::size_t ThingR::layout::size() noexcept {
  return mmscenegraph$cxxbridge1$ThingR$operator$sizeof();
}

::std::size_t ThingR::layout::align() noexcept {
  return mmscenegraph$cxxbridge1$ThingR$operator$alignof();
}

MMSCENEGRAPH_SYMBOL_EXPORT void print_r(const ::mmscenegraph::ThingR &r) noexcept {
  mmscenegraph$cxxbridge1$print_r(r);
}

::std::size_t ReadOperation::layout::size() noexcept {
  return mmscenegraph$cxxbridge1$ReadOperation$operator$sizeof();
}

::std::size_t ReadOperation::layout::align() noexcept {
  return mmscenegraph$cxxbridge1$ReadOperation$operator$alignof();
}

MMSCENEGRAPH_SYMBOL_EXPORT ::std::uint8_t ReadOperation::get_id() const noexcept {
  return mmscenegraph$cxxbridge1$ReadOperation$get_id(*this);
}

MMSCENEGRAPH_SYMBOL_EXPORT ::std::size_t ReadOperation::get_num() const noexcept {
  return mmscenegraph$cxxbridge1$ReadOperation$get_num(*this);
}

MMSCENEGRAPH_SYMBOL_EXPORT ::rust::Box<::mmscenegraph::ReadOperation> new_read_operation(::std::uint8_t id, ::std::size_t num) noexcept {
  return ::rust::Box<::mmscenegraph::ReadOperation>::from_raw(mmscenegraph$cxxbridge1$new_read_operation(id, num));
}

::std::size_t WriteOperation::layout::size() noexcept {
  return mmscenegraph$cxxbridge1$WriteOperation$operator$sizeof();
}

::std::size_t WriteOperation::layout::align() noexcept {
  return mmscenegraph$cxxbridge1$WriteOperation$operator$alignof();
}

MMSCENEGRAPH_SYMBOL_EXPORT ::std::uint8_t WriteOperation::get_id() const noexcept {
  return mmscenegraph$cxxbridge1$WriteOperation$get_id(*this);
}

MMSCENEGRAPH_SYMBOL_EXPORT ::std::size_t WriteOperation::get_num() const noexcept {
  return mmscenegraph$cxxbridge1$WriteOperation$get_num(*this);
}

MMSCENEGRAPH_SYMBOL_EXPORT ::rust::Box<::mmscenegraph::WriteOperation> new_write_operation(::std::uint8_t id, ::std::size_t num) noexcept {
  return ::rust::Box<::mmscenegraph::WriteOperation>::from_raw(mmscenegraph$cxxbridge1$new_write_operation(id, num));
}
} // namespace mmscenegraph

extern "C" {
::mmscenegraph::ThingR *cxxbridge1$box$mmscenegraph$ThingR$alloc() noexcept;
void cxxbridge1$box$mmscenegraph$ThingR$dealloc(::mmscenegraph::ThingR *) noexcept;
void cxxbridge1$box$mmscenegraph$ThingR$drop(::rust::Box<::mmscenegraph::ThingR> *ptr) noexcept;

static_assert(::rust::detail::is_complete<::mmscenegraph::ThingC>::value, "definition of ThingC is required");
static_assert(sizeof(::std::unique_ptr<::mmscenegraph::ThingC>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::mmscenegraph::ThingC>) == alignof(void *), "");
void cxxbridge1$unique_ptr$mmscenegraph$ThingC$null(::std::unique_ptr<::mmscenegraph::ThingC> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::mmscenegraph::ThingC>();
}
void cxxbridge1$unique_ptr$mmscenegraph$ThingC$raw(::std::unique_ptr<::mmscenegraph::ThingC> *ptr, ::mmscenegraph::ThingC *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::mmscenegraph::ThingC>(raw);
}
const ::mmscenegraph::ThingC *cxxbridge1$unique_ptr$mmscenegraph$ThingC$get(const ::std::unique_ptr<::mmscenegraph::ThingC>& ptr) noexcept {
  return ptr.get();
}
::mmscenegraph::ThingC *cxxbridge1$unique_ptr$mmscenegraph$ThingC$release(::std::unique_ptr<::mmscenegraph::ThingC>& ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$mmscenegraph$ThingC$drop(::std::unique_ptr<::mmscenegraph::ThingC> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::mmscenegraph::ThingC>::value>{}(ptr);
}

::mmscenegraph::ReadOperation *cxxbridge1$box$mmscenegraph$ReadOperation$alloc() noexcept;
void cxxbridge1$box$mmscenegraph$ReadOperation$dealloc(::mmscenegraph::ReadOperation *) noexcept;
void cxxbridge1$box$mmscenegraph$ReadOperation$drop(::rust::Box<::mmscenegraph::ReadOperation> *ptr) noexcept;

::mmscenegraph::WriteOperation *cxxbridge1$box$mmscenegraph$WriteOperation$alloc() noexcept;
void cxxbridge1$box$mmscenegraph$WriteOperation$dealloc(::mmscenegraph::WriteOperation *) noexcept;
void cxxbridge1$box$mmscenegraph$WriteOperation$drop(::rust::Box<::mmscenegraph::WriteOperation> *ptr) noexcept;
} // extern "C"

namespace rust {
inline namespace cxxbridge1 {
template <>
MMSCENEGRAPH_SYMBOL_EXPORT ::mmscenegraph::ThingR *Box<::mmscenegraph::ThingR>::allocation::alloc() noexcept {
  return cxxbridge1$box$mmscenegraph$ThingR$alloc();
}
template <>
MMSCENEGRAPH_SYMBOL_EXPORT void Box<::mmscenegraph::ThingR>::allocation::dealloc(::mmscenegraph::ThingR *ptr) noexcept {
  cxxbridge1$box$mmscenegraph$ThingR$dealloc(ptr);
}
template <>
MMSCENEGRAPH_SYMBOL_EXPORT void Box<::mmscenegraph::ThingR>::drop() noexcept {
  cxxbridge1$box$mmscenegraph$ThingR$drop(this);
}
template <>
MMSCENEGRAPH_SYMBOL_EXPORT ::mmscenegraph::ReadOperation *Box<::mmscenegraph::ReadOperation>::allocation::alloc() noexcept {
  return cxxbridge1$box$mmscenegraph$ReadOperation$alloc();
}
template <>
MMSCENEGRAPH_SYMBOL_EXPORT void Box<::mmscenegraph::ReadOperation>::allocation::dealloc(::mmscenegraph::ReadOperation *ptr) noexcept {
  cxxbridge1$box$mmscenegraph$ReadOperation$dealloc(ptr);
}
template <>
MMSCENEGRAPH_SYMBOL_EXPORT void Box<::mmscenegraph::ReadOperation>::drop() noexcept {
  cxxbridge1$box$mmscenegraph$ReadOperation$drop(this);
}
template <>
MMSCENEGRAPH_SYMBOL_EXPORT ::mmscenegraph::WriteOperation *Box<::mmscenegraph::WriteOperation>::allocation::alloc() noexcept {
  return cxxbridge1$box$mmscenegraph$WriteOperation$alloc();
}
template <>
MMSCENEGRAPH_SYMBOL_EXPORT void Box<::mmscenegraph::WriteOperation>::allocation::dealloc(::mmscenegraph::WriteOperation *ptr) noexcept {
  cxxbridge1$box$mmscenegraph$WriteOperation$dealloc(ptr);
}
template <>
MMSCENEGRAPH_SYMBOL_EXPORT void Box<::mmscenegraph::WriteOperation>::drop() noexcept {
  cxxbridge1$box$mmscenegraph$WriteOperation$drop(this);
}
} // namespace cxxbridge1
} // namespace rust
