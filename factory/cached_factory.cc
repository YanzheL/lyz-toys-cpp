// =======================================================================
// Copyright (c) 2016-2020 by LI YANZHE. All rights reserved.
// Author: LI YANZHE <lee.yanzhe@yanzhe.org>
// Created by LI YANZHE on 3/18/19.
// =======================================================================

#include "cached_factory.h"

using namespace lyz;

std::unordered_map<std::type_index, CachedFactory::InstanceMap> CachedFactory::instances;
std::unordered_map<std::type_index, std::mutex> CachedFactory::cls_locks;