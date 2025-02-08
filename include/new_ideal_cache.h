#pragma once 
#include <unordered_map>
#include <set>
#include <list>
#include <vector>
#include <cstddef>

template <typename KeyT, typename Compare = std::less<KeyT>>
class IdealCache {
public:
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
		Compare cmp_;
		bool operator() (const PairT& a, const PairT& b) const{
			return cmp_(a.second, b.second);
		}
		cmp_for_set(Compare cmp) : cmp_(cmp) {};
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
	std::cout << "dump before insert\n";
	std::cout << "cache_size: " << this->size_ << std::endl;
	for (auto i : this->umap_) {
		std::cout << i.first << std::endl;
	}
	std::cout << "set_: \n";
	for (auto i : this->set_) {
		std::cout << i.first << " "  <<i.second << "\n";
	}
	std::cout << "set.size() = " << this->set_.size() << std::endl;
	std::cout << "dump ended\n";
	auto& umap_ = this->umap_; 
	auto& set_ = this->set_;

	if (umap_.find(key) != umap_.end()) {
		for (auto i = set_.begin(), ie = set_.end(); i != ie; ++i) {
			if (cmp_(i->first, key) == true) {
				set_.erase(i);
				break;
			}
		}
		if (next_hit == 0) { 
			umap_.erase(key);
		} else {
			set_.insert(PairT(key, next_hit));
			umap_[key] = next_hit;
		}
		return true;
	}
	if (next_hit == 0) {
		return false;
	}
	if (set_.size() < this->size_) {
		std::cout << "Cache is not full\n";
		std::cout << set_.size();
		set_.insert({key, next_hit});
		std::cout << set_.size();
		std::cout << "check ended\n";
		umap_[key] = next_hit;
		
		return false;
	}
	if (next_hit > set_.rbegin()->first)
		return false;
	
	umap_.erase((*(set_.rbegin())).first);
			
	auto max_iter = set_.rbegin();

	for (auto i = set_.begin(), ie = set_.end(); i != ie; ++i) {
		if (cmp_(i->first, max_iter->first) == true) {
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
	for (size_t i = 0; i < this->keys_.size(); ++i) {
		if (this->data_[this->keys_[i]].size() > 0) {
			this->data_[this->keys_[i]].pop_back();
		}
		ans_ += this->insert_page(this->keys_[i], this->data_[this->keys_[i]].back());
	}
	return ans_;
}

