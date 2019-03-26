// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 3/18/19.
// =======================================================================

#include "cached_factory.h"

using namespace lyz;

std::unordered_map<std::size_t, any_provider::any> CachedFactory::instances;
std::mutex CachedFactory::m;