#include "mmscenegraph/symbol_export.h"
#include "mmscenegraph/_cpp.h"
#include "mmscenegraph.h"
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <new>
#include <string>
#include <type_traits>
#include <utility>

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

#ifndef CXXBRIDGE1_PANIC
#define CXXBRIDGE1_PANIC
template <typename Exception>
void panic [[noreturn]] (const char *msg);
#endif // CXXBRIDGE1_PANIC

namespace {
template <typename T>
class impl;
} // namespace

class String;

template <typename T>
::std::size_t size_of();
template <typename T>
::std::size_t align_of();

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

  void swap(Str &) noexcept;

private:
  class uninit;
  Str(uninit) noexcept;
  friend impl<Str>;

  std::array<std::uintptr_t, 2> repr;
};
#endif // CXXBRIDGE1_RUST_STR

#ifndef CXXBRIDGE1_RUST_SLICE
#define CXXBRIDGE1_RUST_SLICE
namespace detail {
template <bool>
struct copy_assignable_if {};

template <>
struct copy_assignable_if<false> {
  copy_assignable_if() noexcept = default;
  copy_assignable_if(const copy_assignable_if &) noexcept = default;
  copy_assignable_if &operator=(const copy_assignable_if &) noexcept = delete;
  copy_assignable_if &operator=(copy_assignable_if &&) noexcept = default;
};
} // namespace detail

template <typename T>
class Slice final
    : private detail::copy_assignable_if<std::is_const<T>::value> {
public:
  using value_type = T;

  Slice() noexcept;
  Slice(T *, std::size_t count) noexcept;

  Slice &operator=(const Slice<T> &) noexcept = default;
  Slice &operator=(Slice<T> &&) noexcept = default;

  T *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  T &operator[](std::size_t n) const noexcept;
  T &at(std::size_t n) const;
  T &front() const noexcept;
  T &back() const noexcept;

  Slice(const Slice<T> &) noexcept = default;
  ~Slice() noexcept = default;

  class iterator;
  iterator begin() const noexcept;
  iterator end() const noexcept;

  void swap(Slice &) noexcept;

private:
  class uninit;
  Slice(uninit) noexcept;
  friend impl<Slice>;
  friend void sliceInit(void *, const void *, std::size_t) noexcept;
  friend void *slicePtr(const void *) noexcept;
  friend std::size_t sliceLen(const void *) noexcept;

  std::array<std::uintptr_t, 2> repr;
};

template <typename T>
class Slice<T>::iterator final {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = typename std::add_pointer<T>::type;
  using reference = typename std::add_lvalue_reference<T>::type;

  reference operator*() const noexcept;
  pointer operator->() const noexcept;
  reference operator[](difference_type) const noexcept;

  iterator &operator++() noexcept;
  iterator operator++(int) noexcept;
  iterator &operator--() noexcept;
  iterator operator--(int) noexcept;

  iterator &operator+=(difference_type) noexcept;
  iterator &operator-=(difference_type) noexcept;
  iterator operator+(difference_type) const noexcept;
  iterator operator-(difference_type) const noexcept;
  difference_type operator-(const iterator &) const noexcept;

  bool operator==(const iterator &) const noexcept;
  bool operator!=(const iterator &) const noexcept;
  bool operator<(const iterator &) const noexcept;
  bool operator<=(const iterator &) const noexcept;
  bool operator>(const iterator &) const noexcept;
  bool operator>=(const iterator &) const noexcept;

private:
  friend class Slice;
  void *pos;
  std::size_t stride;
};

template <typename T>
Slice<T>::Slice() noexcept {
  sliceInit(this, reinterpret_cast<void *>(align_of<T>()), 0);
}

template <typename T>
Slice<T>::Slice(T *s, std::size_t count) noexcept {
  sliceInit(this, const_cast<typename std::remove_const<T>::type *>(s), count);
}

template <typename T>
T *Slice<T>::data() const noexcept {
  return reinterpret_cast<T *>(slicePtr(this));
}

template <typename T>
std::size_t Slice<T>::size() const noexcept {
  return sliceLen(this);
}

template <typename T>
std::size_t Slice<T>::length() const noexcept {
  return this->size();
}

template <typename T>
bool Slice<T>::empty() const noexcept {
  return this->size() == 0;
}

template <typename T>
T &Slice<T>::operator[](std::size_t n) const noexcept {
  assert(n < this->size());
  auto pos = static_cast<char *>(slicePtr(this)) + size_of<T>() * n;
  return *reinterpret_cast<T *>(pos);
}

template <typename T>
T &Slice<T>::at(std::size_t n) const {
  if (n >= this->size()) {
    panic<std::out_of_range>("rust::Slice index out of range");
  }
  return (*this)[n];
}

template <typename T>
T &Slice<T>::front() const noexcept {
  assert(!this->empty());
  return (*this)[0];
}

template <typename T>
T &Slice<T>::back() const noexcept {
  assert(!this->empty());
  return (*this)[this->size() - 1];
}

template <typename T>
typename Slice<T>::iterator::reference
Slice<T>::iterator::operator*() const noexcept {
  return *static_cast<T *>(this->pos);
}

template <typename T>
typename Slice<T>::iterator::pointer
Slice<T>::iterator::operator->() const noexcept {
  return static_cast<T *>(this->pos);
}

template <typename T>
typename Slice<T>::iterator::reference Slice<T>::iterator::operator[](
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto pos = static_cast<char *>(this->pos) + this->stride * n;
  return *reinterpret_cast<T *>(pos);
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator++() noexcept {
  this->pos = static_cast<char *>(this->pos) + this->stride;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator++(int) noexcept {
  auto ret = iterator(*this);
  this->pos = static_cast<char *>(this->pos) + this->stride;
  return ret;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator--() noexcept {
  this->pos = static_cast<char *>(this->pos) - this->stride;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator--(int) noexcept {
  auto ret = iterator(*this);
  this->pos = static_cast<char *>(this->pos) - this->stride;
  return ret;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator+=(
    typename Slice<T>::iterator::difference_type n) noexcept {
  this->pos = static_cast<char *>(this->pos) + this->stride * n;
  return *this;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator-=(
    typename Slice<T>::iterator::difference_type n) noexcept {
  this->pos = static_cast<char *>(this->pos) - this->stride * n;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator+(
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ret = iterator(*this);
  ret.pos = static_cast<char *>(this->pos) + this->stride * n;
  return ret;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator-(
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ret = iterator(*this);
  ret.pos = static_cast<char *>(this->pos) - this->stride * n;
  return ret;
}

template <typename T>
typename Slice<T>::iterator::difference_type
Slice<T>::iterator::operator-(const iterator &other) const noexcept {
  auto diff = std::distance(static_cast<char *>(other.pos),
                            static_cast<char *>(this->pos));
  return diff / this->stride;
}

template <typename T>
bool Slice<T>::iterator::operator==(const iterator &other) const noexcept {
  return this->pos == other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator!=(const iterator &other) const noexcept {
  return this->pos != other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator<(const iterator &other) const noexcept {
  return this->pos < other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator<=(const iterator &other) const noexcept {
  return this->pos <= other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator>(const iterator &other) const noexcept {
  return this->pos > other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator>=(const iterator &other) const noexcept {
  return this->pos >= other.pos;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::begin() const noexcept {
  iterator it;
  it.pos = slicePtr(this);
  it.stride = size_of<T>();
  return it;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::end() const noexcept {
  iterator it = this->begin();
  it.pos = static_cast<char *>(it.pos) + it.stride * this->size();
  return it;
}

template <typename T>
void Slice<T>::swap(Slice &rhs) noexcept {
  std::swap(*this, rhs);
}
#endif // CXXBRIDGE1_RUST_SLICE

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
  Box(Box &&) noexcept;
  ~Box() noexcept;

  explicit Box(const T &);
  explicit Box(T &&);

  Box &operator=(Box &&) noexcept;

  const T *operator->() const noexcept;
  const T &operator*() const noexcept;
  T *operator->() noexcept;
  T &operator*() noexcept;

  template <typename... Fields>
  static Box in_place(Fields &&...);

  void swap(Box &) noexcept;

  static Box from_raw(T *) noexcept;

  T *into_raw() noexcept;

  /* Deprecated */ using value_type = element_type;

private:
  class uninit;
  class allocation;
  Box(uninit) noexcept;
  void drop() noexcept;

  friend void swap(Box &lhs, Box &rhs) noexcept { lhs.swap(rhs); }

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
void Box<T>::swap(Box &rhs) noexcept {
  using std::swap;
  swap(this->ptr, rhs.ptr);
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
  ~ThingR() = delete;

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
  ~ReadOperation() = delete;

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
  ~WriteOperation() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_mmscenegraph$WriteOperation

extern "C" {
MMSCENEGRAPH_SYMBOL_EXPORT ::mmscenegraph::ThingC *mmscenegraph$cxxbridge1$make_demo(::rust::Str appname) noexcept {
  ::std::unique_ptr<::mmscenegraph::ThingC> (*make_demo$)(::rust::Str) = ::mmscenegraph::make_demo;
  return make_demo$(appname).release();
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

namespace geom {
extern "C" {
bool mmscenegraph$geom$cxxbridge1$read(::rust::Slice<::std::uint32_t> buffer) noexcept;

bool mmscenegraph$geom$cxxbridge1$write(::rust::Slice<const ::std::uint32_t> buffer) noexcept;
} // extern "C"
} // namespace geom

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

namespace geom {
MMSCENEGRAPH_SYMBOL_EXPORT bool read(::rust::Slice<::std::uint32_t> buffer) noexcept {
  return mmscenegraph$geom$cxxbridge1$read(buffer);
}

MMSCENEGRAPH_SYMBOL_EXPORT bool write(::rust::Slice<const ::std::uint32_t> buffer) noexcept {
  return mmscenegraph$geom$cxxbridge1$write(buffer);
}
} // namespace geom
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
