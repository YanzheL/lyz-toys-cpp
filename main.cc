//
// Created by LI YANZHE on 3/18/19.
//

#include "factory/cached_factory.h"
#include <iostream>

using namespace std;
using namespace lyz;

using SomeHeavyClass = string;

int main() {
  shared_ptr<SomeHeavyClass> obj = CachedFactory::createInstanceById<SomeHeavyClass>(10, "Arg0");
  cout << *obj << endl;
}