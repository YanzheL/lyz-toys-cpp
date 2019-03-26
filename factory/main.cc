//
// Created by LI YANZHE on 3/18/19.
//

#include "cached_factory.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace lyz;

using SomeHeavyClass = vector<string>;

int main() {
  auto obj = CachedFactory::createInstance<SomeHeavyClass>(10L, "Arg0");
  cout << (*obj)[0] << endl;
}