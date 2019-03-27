// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 3/18/19.
// =======================================================================

#ifndef LYZTOYS_FACTORY_CACHED_FACTORY_H
#define LYZTOYS_FACTORY_CACHED_FACTORY_H

#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <typeindex>
#include "../util.h"
#if __cplusplus >= 201703L
#include <any>
namespace any_provider = std;
#else
#include <boost/any.hpp>
namespace any_provider = boost;
#endif
//#define CACHED_FACTORY_PRINT_TIME
#ifdef CACHED_FACTORY_PRINT_TIME
#include <iostream>
#endif

namespace lyz {

class CachedFactory {
 public:
  template<class T>
  static std::shared_ptr<T> putInstance(T *ins) {
    return putInstance<T>(ins, std::hash<T>());
  }

  template<class T>
  static std::shared_ptr<T> putInstance(T *ins, std::function<std::size_t(const T &)> hfunc) {
    auto tid = std::type_index(typeid(T));
    std::lock_guard<std::mutex> guard(cls_locks[tid]);
    std::size_t id = hfunc(*ins);
    std::shared_ptr<T> p(ins);
    instances[tid][id] = any_provider::any(p);
    return p;
  }

  template<class T>
  static std::shared_ptr<T> getInstance(std::size_t id) {
    auto tid = std::type_index(typeid(T));
    auto &map = instances[tid];
    auto itr = map.find(id);
    if (itr != map.end()) {
      return any_provider::any_cast<std::shared_ptr<T>>(itr->second);
    } else {
      return nullptr;
    }
  }

  template<class T, typename ...Arg>
  static std::shared_ptr<T> createInstanceById(std::size_t id, Arg &&... params) {
    auto tid = std::type_index(typeid(T));
    auto &map = instances[tid];
    auto itr = map.find(id);
    if (itr != map.end()) {
      return any_provider::any_cast<std::shared_ptr<T>>(itr->second);
    } else {
      std::lock_guard<std::mutex> guard(cls_locks[tid]);
      std::shared_ptr<T> ins;
#ifdef CACHED_FACTORY_PRINT_TIME
      GETTIME_HIGH(ins = std::make_shared<T>(params...);, "Class init")
#else
      ins = std::make_shared<T>(params...);
#endif
      map[id] = any_provider::any(ins);
      return ins;
    }
  }

  template<class T, typename ...Arg>
  static std::shared_ptr<T> createInstance(Arg &&... params) {
    auto id = calculateId<T>(params...);
    return createInstanceById<T>(id, params...);
  }

 private:
  typedef std::unordered_map<std::size_t, any_provider::any> InstanceMap;
  static std::unordered_map<std::type_index, InstanceMap> instances;
  static std::unordered_map<std::type_index, std::mutex> cls_locks;

  template<class T, typename ...Arg>
  static std::size_t calculateId(Arg &&... param1) {
    auto &&params_tp = std::forward_as_tuple(std::forward<Arg>(param1)...);
    std::size_t id = 0;
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
