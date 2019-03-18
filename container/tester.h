//
// Created by LI YANZHE on 2019-03-19.
//

#ifndef LYZTOYS_CONTAINER_TESTER_H_
#define LYZTOYS_CONTAINER_TESTER_H_

#include <cassert>
struct verify;
class tester {
  friend verify;
  static int livecount;
  const tester *self;
 public:
  tester() : self(this) { ++livecount; }
  tester(const tester &) : self(this) { ++livecount; }
  ~tester() {
    assert(self==this);
    --livecount;
  }
  tester &operator=(const tester &b) {
    assert(self==this && b.self==&b);
    return *this;
  }
  void cfunction() const { assert(self==this); }
  void mfunction() { assert(self==this); }
};

int tester::livecount = 0;

struct verify {
  ~verify() { assert(tester::livecount==0); }
} verifier;

#endif //LYZTOYS_CONTAINER_TESTER_H_
