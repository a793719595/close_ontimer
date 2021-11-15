/****************************************************************************
 *
 * Copyright 2020 XiaoMi All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
#pragma once

/** 有些类不允许复制对象，这些类包含一个私有的复制构造函数和赋值运算符来禁用复制。*/
#define IDM_DISABLE_COPY(Class) \
  Class(const Class&) = delete; \
  Class& operator=(const Class&) = delete;

/** 禁用移动构造函数和移动赋值运算符 */
#define IDM_DISABLE_MOVE(Class) \
  Class(Class&&) = delete;      \
  Class& operator=(Class&&) = delete;

/** 禁用复制构造函数、赋值运算符、移动构造函数和移动赋值运算符 */
#define IDM_DISABLE_COPY_MOVE(Class) \
  IDM_DISABLE_COPY(Class)            \
  IDM_DISABLE_MOVE(Class)

/** 复制构造函数实现 */
#define IDM_COPY_CONSTRUCTOR(Class)               \
  Class::Class(const Class& other) {              \
    if (other.d_ptr_ != nullptr) {                \
      d_ptr_ = new Class##Private(*other.d_ptr_); \
    }                                             \
  }

/** 移动构造函数实现 */
#define IDM_MOVE_CONSTRUCTOR(Class) \
  Class::Class(Class&& other) {     \
    d_ptr_ = other.d_ptr_;          \
    other.d_ptr_ = nullptr;         \
  }

/** 赋值运算符实现 */
#define IDM_COPY_ASSIGNMENT_OPERATOR(Class)     \
  Class& Class::operator=(const Class& other) { \
    if (this != &other) {                       \
      *d_ptr_ = *other.d_ptr_;                  \
    }                                           \
    return *this;                               \
  }

/** 移动赋值运算符实现 */
#define IDM_MOVE_ASSIGNMENT_OPERATOR(Class) \
  Class& Class::operator=(Class&& other) {  \
    if (this != &other) {                   \
      if (d_ptr_ != nullptr) delete d_ptr_; \
      d_ptr_ = other.d_ptr_;                \
      other.d_ptr_ = nullptr;               \
    }                                       \
    return *this;                           \
  }

/** 构造函数实现 */
#define IDM_CONSTRUCTOR(Class) \
  Class::Class() : d_ptr_(new Class##Private) {}

/** 析构函数实现 */
#define IDM_DESTRUCTOR(Class) \
  Class::~Class() { delete d_ptr_; }

/** copy--声明 */
#define IDM_COPY_DECLARATION(Class) \
  Class(const Class& other);        \
  Class& operator=(const Class& other);

/** copy--定义 */
#define IDM_COPY_IMPLEMENT(Class) \
  IDM_COPY_CONSTRUCTOR(Class)     \
  IDM_COPY_ASSIGNMENT_OPERATOR(Class)

/** move--声明 */
#define IDM_MOVE_DECLARATION(Class) \
  Class(Class&& other);             \
  Class& operator=(Class&& other);

/** move--定义 */
#define IDM_MOVE_IMPLEMENT(Class) \
  IDM_MOVE_CONSTRUCTOR(Class)     \
  IDM_MOVE_ASSIGNMENT_OPERATOR(Class)

/** move和copy--声明 */
#define IDM_COPY_MOVE_DECLARATION(Class) \
  IDM_COPY_DECLARATION(Class)            \
  IDM_MOVE_DECLARATION(Class)

/** move和copy--定义 */
#define IDM_COPY_MOVE_IMPLEMENT(Class) \
  IDM_COPY_IMPLEMENT(Class)            \
  IDM_MOVE_IMPLEMENT(Class)

/** 构造和析构函数--声明 */
#define IDM_CONSTRUCTOR_DESTRUCTOR_DECLARATION(Class) \
  Class();                                            \
  ~Class();

/** 构造和析构函数--定义 */
#define IDM_CONSTRUCTOR_DESTRUCTOR_IMPLEMENT(Class) \
  IDM_CONSTRUCTOR(Class)                            \
  IDM_DESTRUCTOR(Class)

/** 六个默认函数--声明 */
#define IDM_DEFAULT_FUNCTION_DECLARATION(Class) \
  IDM_CONSTRUCTOR_DESTRUCTOR_DECLARATION(Class) \
  IDM_COPY_MOVE_DECLARATION(Class)

/** 六个默认函数--定义 */
#define IDM_DEFAULT_FUNCTION_IMPLEMENT(Class) \
  IDM_CONSTRUCTOR_DESTRUCTOR_IMPLEMENT(Class) \
  IDM_COPY_MOVE_IMPLEMENT(Class)

template <typename T>
constexpr inline const T& IDM_Min(const T& a, const T& b) {
  return (a < b) ? a : b;
}
template <typename T>
constexpr inline const T& IDM_Max(const T& a, const T& b) {
  return (a < b) ? b : a;
}
template <typename T>
constexpr inline const T& IDM_Bound(const T& min, const T& val, const T& max) {
  return IDM_Max(min, Min(max, val));
}