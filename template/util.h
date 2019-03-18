//
// Created by LI YANZHE on 3/18/19.
//

#ifndef LYZTOYS_TEMPLATE_UTIL_H
#define LYZTOYS_TEMPLATE_UTIL_H

#include <tuple>

#define GETTIME(X, MSG)                                              \
{                                                                    \
    struct timespec start, finish;                                   \
    double elapsed;                                                  \
    clock_gettime(CLOCK_MONOTONIC, &start);                          \
    X                                                                \
    clock_gettime(CLOCK_MONOTONIC, &finish);                         \
    elapsed = (finish.tv_sec - start.tv_sec);                        \
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1e9;               \
    std::cout <<#MSG<<" time = " << elapsed << "s" << std::endl;     \
}

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

}

#endif //LYZTOYS_TEMPLATE_UTIL_H
