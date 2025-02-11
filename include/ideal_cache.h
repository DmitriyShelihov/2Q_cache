#pragma once 

#include <unordered_map>
#include <set>
#include <list>
#include <vector>
#include <cstddef>

template <typename KeyT, typename Compare = std::less<KeyT>>
class IdealCache {
	using PairT = std::pair<KeyT, size_t>;
	using ListT = std::list<size_t>;

private:
	size_t size_;
	struct cmp_for_set;
	std::set<PairT, cmp_for_set> set_;
	std::unordered_map<KeyT, size_t> umap_;
	std::unordered_map<KeyT, ListT> data_;
	std::vector<KeyT> keys_;
	Compare cmp_;
	size_t ans_ = 0;

	struct cmp_for_set {
		bool operator() (const PairT& a, const PairT& b) const{
			return cmp_(a.second, b.second);
		}
	};

private:
	inline void map_keys(const std::vector<KeyT>& keys);
	inline bool insert_page(const KeyT& key, size_t next_hit);
public:
	explicit IdealCache(const std::vector<KeyT>& keys, size_t size = 0, const Compare& cmp = Compare()) 
		: size_(size), cmp_(cmp), keys_(keys), set_(cmp_for_set(cmp_)) { map_keys(keys); }
	inline size_t get_ans();
};

template <typename KeyT, typename Compare>
void IdealCache<KeyT, Compare>::map_keys(const std::vector<KeyT>& keys) {
	for (size_t i = 1, ie = keys.size()+1; i < ie; ++i) {
		this->data_[keys[i-1]].push_front(i);
	}
	for (auto& i : this->data_) { i.second.push_front(0); }
}

template <typename KeyT, typename Compare>
bool IdealCache<KeyT, Compare>::insert_page(const KeyT& key, size_t next_hit) {
	auto& umap_ = this->umap_; 
	auto& set_ = this->set_;

	if (umap_.find(key) != umap_.end()) {
		for (auto i: set_) {
			if (cmp_(i.first, key)) {
				set_.erase(i);
				break;
			}
		}
		if (next_hit == 0) { 
			umap_.erase(key);
		} else {
			set_.insert({key, next_hit});
			umap_[key] = next_hit;
		}
		return true;
	}
	if (next_hit == 0) {
		return false;
	}
	if (set_.size() < this->size_) {
		set_.insert({key, next_hit});
		umap_[key] = next_hit;
		return false;
	}
	if (next_hit > set_.rbegin()->second)
		return false;
	
	umap_.erase(set_.rbegin()->first);
			
	auto max_iter = set_.rbegin();

	for (auto i: set_) {
		if (cmp_(i.first, max_iter->first)) {
			set_.erase(i);
			break;
		}
	}
	set_.insert({key, next_hit});
	umap_[key] = next_hit;
	return false;
}

template <typename KeyT, typename Compare>
size_t IdealCache<KeyT, Compare>::get_ans() {
	for (auto i: keys_) {
		if (data_[i].size() > 0) {
			data_[i].pop_back();
		}
		ans_ += insert_page(i, data_[i].back());
	}
	return ans_;
}

