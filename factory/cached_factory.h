//
// Created by LI YANZHE on 3/18/19.
//

#ifndef LYZTOYS_FACTORY_CACHED_FACTORY_H
#define LYZTOYS_FACTORY_CACHED_FACTORY_H

#include <memory>
#include <any>
#include <mutex>
#include <unordered_map>
#include "../template/util.h"
#ifdef CACHED_FACTORY_PRINT_TIME
#include <iostream>
#endif

namespace lyz {

class CachedFactory {
 public:
  template<class T, typename ...Arg>
  static std::shared_ptr<T> getInstance(Arg &&... param1) {
    auto &&params_tp = std::forward_as_tuple(std::forward<Arg>(param1)...);
    unsigned long param_hash = typeid(T).hash_code();
    unsigned long *pph = &param_hash;
    for_each_in_tuple(
        params_tp,
        [pph](auto x) {
          *pph += std::hash<decltype(x)>()(x);
        }
    );
    return getInstance<T, std::string>(param_hash, std::forward<Arg>(param1)...);
  }

 private:
  static std::mutex m;
  static std::unordered_map<unsigned long, std::any> instances;

  template<class T, typename ...Arg>
  static std::shared_ptr<T> getInstance(unsigned long id, Arg &&... param1) {
    std::lock_guard<std::mutex> guard(m);
    auto itr = instances.find(id);
    if (itr != instances.end()) {
      return std::any_cast<std::shared_ptr<T>>(itr->second);
    } else {
#ifdef CACHED_FACTORY_PRINT_TIME
      auto t_start = std::chrono::high_resolution_clock::now();
#endif
      std::shared_ptr<T> ins(new T(std::forward<Arg>(param1)...));
#ifdef CACHED_FACTORY_PRINT_TIME
      auto t_end = std::chrono::high_resolution_clock::now();
      float ms = std::chrono::duration<float, std::milli>(t_end - t_start).count();
      std::cout << "Class<" << typeid(T).name() << "> Init success, hash = " << id << " time used = " << ms << " ms"
                << std::endl;
#endif
      instances[id] = std::any(ins);
      return ins;
    }
  }
};

}
#endif //LYZTOYS_FACTORY_CACHED_FACTORY_H
