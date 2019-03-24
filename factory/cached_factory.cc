//
// Created by LI YANZHE on 3/18/19.
//

#include "cached_factory.h"

using namespace lyz;

std::unordered_map<unsigned long, boost::any> CachedFactory::instances;
std::mutex CachedFactory::m;