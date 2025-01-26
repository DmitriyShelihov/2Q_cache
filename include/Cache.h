#pragma once

#include <list>
#include <unordered_map>
#include <cstddef>

template <typename T, typename KeyT>
class Cache {
	using KeyTor = typename std::list<KeyT>::iterator;
	
	size_t size_;
	std::list<KeyT> fifo_;
	std::unordered_map<KeyT, KeyTor> fumap_;

	std::list<KeyT> lru_;
	std::unordered_map<KeyT, KeyTor> lumap_;
	
	std::unordered_map<KeyT, T> page_umap;
	T (*slow_get_page_)(const KeyT& key);

	void lru_hit(const KeyT& key);
	void fifo_hit(const KeyT& key);
	void cache_miss(const KeyT& key);
public:
	explicit Cache(T (*slow_get_page)(const KeyT& key), size_t size = 0) 
		: slow_get_page_(slow_get_page), size_(size) {}
	void insert(const KeyT& key);
	
	static int hits_;
};

template <typename T, typename KeyT>
void Cache<T, KeyT>::fifo_hit(const KeyT& key) {
	this->fifo_.erase(this->fumap_[key]);

	if (this->lru_.size() == this->size_) {
		this->page_umap_.erase(this->lru_.back());
		this->lumap_.erase(this->lru_.back());
		this->lru_.pop_back();
	}
	this->lru_.push_front(key);
	this->lumap_[key] = this->lru_.begin();
	this->fumap_.erase(key);
	++Cache<T, KeyT>::hits_;
}

template <typename T, typename KeyT>
void Cache<T, KeyT>::lru_hit(const KeyT& key) {
	this->lru_.erase(this->lumap_[key]);
	this->lru_.push_front(key);
	this->lumap_[key] = this->lru_.begin();
	++Cache<T, KeyT>::hits_;	
}

template <typename T, typename KeyT>
void Cache<T, KeyT>::cache_miss(const KeyT& key) {
	if (this->fifo_.size() < this->size_) {
		this->fifo_.push_front(key);
		this->fumap_[key] = this->fifo_.begin();
		return;
	}
	KeyT last = this->fifo_.back();
	this->fifo_.erase(this->fumap_[last]);
	this->fumap_.erase(last);
	this->page_umap_.erase(last);
	this->fifo_.push_front(key);
	this->fumap_[key] = this->fifo_.begin();
	return;
	
}

template <typename T, typename KeyT>
void Cache<T, KeyT>::insert(const KeyT& key) {
	if (this->fumap_.find(key) != this->fumap_.end()) { 
		this->fifo_hit(key); return; 
	}
	if (this->lumap_.find(key) != this->lumap_.end()) {
		this->lru_hit(key); return;
	}

	this->page_umap_[key] = slow_get_page(key);
	this->cache_miss(key);
	return;
}
