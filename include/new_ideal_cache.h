#pragma once 
#include <unordered_map>
#include <set>
#include <list>

template <typename KeyT>
class IdealCache {
	size_t size_;
	std::set<std::pair<KeyT, int>, cmp> set_;
	std::unordered_map<> umap_;
public:
};
