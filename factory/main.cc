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
  shared_ptr<SomeHeavyClass> obj;
  GETTIME_HIGH(
      for (int i = 0; i < 10000000; ++i) {
        obj = CachedFactory::createInstance<SomeHeavyClass>(10, "Arg0");
      },
      createInstance
  )
  cout << (*obj)[0] << endl;
}