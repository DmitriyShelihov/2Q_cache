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
	T (*slow_get_page_)(KeyT key);
public:
	explicit Cache(T (*slow_get_page)(KeyT key), size_t size = 0) 
		: slow_get_page_(slow_get_page), size_(size) {}
	void insert(KeyT key);
	static int hits_;
};

template <typename T, typename KeyT>
int Cache<T, KeyT>::hits_ = 0;

template <typename T, typename KeyT>
void Cache<T, KeyT>::insert(KeyT key) {
	if (this->fumap_.find(key) != this->fumap_.end()) {
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
		return;
	}
	if (this->lumap_.find(key) != this->lumap_.end()) {
		this->lru_.erase(this->lumap_[key]);
		this->lru_.push_front(key);
		this->lumap_[key] = this->lru_.begin();
		++Cache<T, KeyT>::hits_;
		return;
	}

	this->page_umap_[key] = slow_get_page(key);

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
