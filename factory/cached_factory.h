//
// Created by LI YANZHE on 3/18/19.
//

#ifndef LYZTOYS_FACTORY_CACHED_FACTORY_H
#define LYZTOYS_FACTORY_CACHED_FACTORY_H

#include <functional>
#include <memory>
#include <any>
#include <mutex>
#include <unordered_map>
#include "../util.h"
//#define CACHED_FACTORY_PRINT_TIME
#ifdef CACHED_FACTORY_PRINT_TIME
#include <iostream>
#endif

namespace lyz {

class CachedFactory {
 public:
  template<class T>
  static void putInstance(T *ins) {
    putInstance<T>(ins, std::hash<T>());
  }

  template<class T>
  static void putInstance(T *ins, std::function<std::size_t(const T &)> hfunc) {
    std::lock_guard<std::mutex> guard(m);
    std::size_t id = typeid(T).hash_code();
    id += hfunc(*ins);
    std::shared_ptr<T> p(ins);
    instances[id] = std::any(p);
  }

  template<class T>
  static std::shared_ptr<T> getInstance(std::size_t ins_id) {
    std::lock_guard<std::mutex> guard(m);
    std::size_t id = typeid(T).hash_code() + ins_id;
    auto itr = instances.find(id);
    if (itr!=instances.end()) {
      return std::any_cast<std::shared_ptr<T>>(itr->second);
    } else {
      return nullptr;
    }
  }

  template<class T, typename ...Arg>
  static std::shared_ptr<T> createInstance(Arg &&... params) {
    std::lock_guard<std::mutex> guard(m);
    auto id = calculateId<T>(params...);
    auto itr = instances.find(id);
    if (itr!=instances.end()) {
      return std::any_cast<std::shared_ptr<T>>(itr->second);
    } else {
      std::shared_ptr<T> ins;
#ifdef CACHED_FACTORY_PRINT_TIME
      GETTIME_HIGH(ins = std::make_shared<T>(params...);, "Class init")
#else
      ins = std::make_shared<T>(params...);
#endif
      instances[id] = std::any(ins);
      return ins;
    }
  }

 private:
  static std::mutex m;
  static std::unordered_map<std::size_t, std::any> instances;

  template<class T, typename ...Arg>
  static std::size_t calculateId(Arg &&... param1) {
    auto &&params_tp = std::forward_as_tuple(std::forward<Arg>(param1)...);
    std::size_t id = typeid(T).hash_code();
    for_each_in_tuple(
        params_tp,
        [&](auto x) {
          id += std::hash<decltype(x)>()(x);
        }
    );
    return id;
  }
};

}
#endif //LYZTOYS_FACTORY_CACHED_FACTORY_H
