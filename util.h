// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 3/18/19.
// =======================================================================

#ifndef LYZTOYS_UTIL_H
#define LYZTOYS_UTIL_H

#include <tuple>
#include <type_traits>
#include <chrono>
#include <initializer_list>
#include <array>

#define GETTIME(X, MSG)                                             \
do {                                                                 \
    struct timespec start, finish;                                   \
    double elapsed;                                                  \
    clock_gettime(CLOCK_MONOTONIC, &start);                         \
    {X}                                                              \
    clock_gettime(CLOCK_MONOTONIC, &finish);                        \
    elapsed = (finish.tv_sec - start.tv_sec);                        \
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1e9;               \
    std::cout <<#MSG<<" time = " << elapsed << "s" << std::endl;     \
} while(0)

#define GETTIME_HIGH(X, MSG)                                                     \
do {                                                                              \
  auto t_start = std::chrono::high_resolution_clock::now();                       \
  { X }                                                                           \
  auto t_end = std::chrono::high_resolution_clock::now();                         \
  double dur = std::chrono::duration<double, std::nano>(t_end - t_start).count(); \
  long s = (long) (dur / 1e9);                                                    \
  long ms = (long) ((dur / 1e6) - s * 1e3);                                       \
  long us = (long) ((dur / 1e3) - s * 1e6 - ms * 1e3);                            \
  long ns = ((long) dur) % 1000;                                                  \
  std::cout << #MSG                                                               \
  << " time = "                                                                   \
  << s << " s "                                                                   \
  << ms << " ms "                                                                 \
  << us << " us "                                                                 \
  << ns << " ns"                                                                  \
  << std::endl;                                                                   \
} while(0)

#define HAS_MEMBER_FUNC(type, name)                             \
(std::is_member_function_pointer<decltype(&type::name)>::value)

namespace lyz {

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
for_each_in_tuple(std::tuple<Tp...> &, FuncT) {}

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
for_each_in_tuple(std::tuple<Tp...> &t, FuncT f) {
  f(std::get<I>(t));
  for_each_in_tuple<I + 1, FuncT, Tp...>(t, f);
}

template<typename ...Args>
inline constexpr size_t IDX_V1(const Args... params) {
  constexpr size_t N = sizeof...(params);
  constexpr size_t NDIMS = N / 2 + 1;
  std::initializer_list<size_t> args{params...};
  auto ibegin = args.begin();
  auto sbegin = ibegin + NDIMS;
  size_t res = 0;
  for (int dim = 0; dim < NDIMS; ++dim) {
    size_t factor = dim > 0 ? sbegin[dim - 1] : 0;
    res = res * factor + ibegin[dim];
  }
  return res;
}

template<typename ...Args>
inline constexpr size_t IDX_V2(const Args... params) {
  constexpr size_t N = sizeof...(Args);
  constexpr size_t NDIMS = N / 2 + 1;
  std::array<size_t, N> args{params...};
  auto ibegin = args.begin();
  auto sbegin = ibegin + NDIMS;
  size_t res = 0;
  for (int dim = 0; dim < NDIMS; ++dim) {
    size_t factor = dim > 0 ? sbegin[dim - 1] : 0;
    res = res * factor + ibegin[dim];
  }
  return res;
}

template<typename R, typename ... Args>
typename std::enable_if<!std::is_void<R>::value>::type
call_func(void *function, Args &&... args) {
  return reinterpret_cast<R(*)(Args...)>(function)(args...);
}

template<typename R, typename ... Args>
typename std::enable_if<std::is_void<R>::value>::type
call_func(void *function, Args &&... args) {
  reinterpret_cast<R(*)(Args...)>(function)(args...);
}

template<typename T, typename R, typename ...Args>
struct GenericMemberFuncType {
  typedef R (T::*type)(Args...);
  typedef R return_type;
};

template<typename T, typename R, typename ...Args>
typename std::enable_if<std::is_void<R>::value>::type
member_func_wrapper(
    typename GenericMemberFuncType<T, R, Args...>::type mfp,
    T *p,
    Args...args
) {
  (p->*mfp)(args...);
}

template<typename T, typename R, typename ...Args>
typename std::enable_if<!std::is_void<R>::value>::type
member_func_wrapper(
    typename GenericMemberFuncType<T, R, Args...>::type mfp,
    T *p,
    Args...args
) {
  return (p->*mfp)(args...);
}

}
#endif //LYZTOYS_UTIL_H
