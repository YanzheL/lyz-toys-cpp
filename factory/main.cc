// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 3/18/19.
// =======================================================================

#include "cached_factory.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace lyz;

using SomeHeavyClass = vector<string>;

int main() {
  shared_ptr<SomeHeavyClass> obj;
  GETTIME_HIGH(
      for (int i = 0; i < 10000000; ++i) {
        obj = CachedFactory::createInstance<SomeHeavyClass>(10, "Arg0");
      },
      createInstance
  )
  GETTIME_HIGH(
      for (int i = 0; i < 10000000; ++i) {
        obj = CachedFactory::createInstanceById<SomeHeavyClass>(i, 10, "Arg0");
      },
      createInstanceById
  )
  GETTIME_HIGH(
      for (int i = 0; i < 10000000; ++i) {
        obj = CachedFactory::getInstance<SomeHeavyClass>(i);
      },
      getInstance
  )
  GETTIME_HIGH(
      for (int i = 0; i < 10000000; ++i) {
        SomeHeavyClass *x = new SomeHeavyClass(10, "Arg0");
        obj = CachedFactory::putInstance<SomeHeavyClass>(x, [=](const SomeHeavyClass &o) { return i + 10000000; });
      },
      putInstance
  )
  cout << (*obj)[0] << endl;
}