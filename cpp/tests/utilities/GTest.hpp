/*
 * Copyright (c) 2019, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#ifdef GTEST_INCLUDE_GTEST_GTEST_H_
#error "Don't include gtest/gtest.h directly, include GTest.hpp instead"
#endif

/**---------------------------------------------------------------------------*
 * @file GTest.hpp
 * @brief Work around for GTests emulation of variadic templates in
 * ::Testing::Types.
 *
 * Removes the 50 type limit in a type-parameterized test list.
 *
 * Uses macros to rename GTests's emulated variadic template types and then
 * redefines them properly.
 *---------------------------------------------------------------------------**/

#define Types Types_NOT_USED
#define Types0 Types0_NOT_USED
#define TypeList TypeList_NOT_USED
#define Templates Templates_NOT_USED
#define Templates0 Templates0_NOT_USED
#include <gtest/internal/gtest-type-util.h>
#undef Types
#undef Types0
#undef TypeList
#undef Templates
#undef Templates0

namespace testing {

template <class... TYPES>
struct Types {
  using type = Types;
};

template <class T, class... TYPES>
struct Types<T, TYPES...> {
  using Head = T;
  using Tail = Types<TYPES...>;

  using type = Types;
};

namespace internal {

using Types0 = Types<>;

template <GTEST_TEMPLATE_... TYPES>
struct Templates {};

template <GTEST_TEMPLATE_ HEAD, GTEST_TEMPLATE_... TAIL>
struct Templates<HEAD, TAIL...> {
  using Head = internal::TemplateSel<HEAD>;
  using Tail = Templates<TAIL...>;

  using type = Templates;
};

using Templates0 = Templates<>;

template <typename T>
struct TypeList {
  typedef Types<T> type;
};

template <class... TYPES>
struct TypeList<Types<TYPES...>> {
  using type = Types<TYPES...>;
};

}  // namespace internal
}  // namespace testing

#include <gtest/gtest.h>
