// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 3/18/19.
// =======================================================================

#include "factory/cached_factory.h"
#include <iostream>

using namespace std;
using namespace lyz;

using SomeHeavyClass = string;

int main() {
  shared_ptr<SomeHeavyClass> obj = CachedFactory::createInstanceById<SomeHeavyClass>(10, "Arg0");
  cout << *obj << endl;
  cout << *CachedFactory::createInstanceById<SomeHeavyClass>(10, "Arg1") << endl;
}