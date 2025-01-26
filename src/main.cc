#include "Cache.h"
#include <iostream>

static int slow_get_page(int key) {
	return key;
}

template <typename T, typename KeyT>
static struct Input {
	int n_;
	std::vector<KeyT> data_;
	Input(ifstream& in = std::cin&);
};

template <typename T, typename KeyT>
Input<T, KeyT>::Input(ifstream& in) {
	int n; in >> n;
	if (n < 0) {
		return 1;
	} 
	data`
	for (int i = 0; i < n; ++i) {
		KeyT key;
		in >> data[];
	}
}

int main() {
	
}
