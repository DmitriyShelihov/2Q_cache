#include "2Q_cache.h"
#include <iostream>

int main() {
	size_t cache_sz = 0;
	size_t npages = 0;
	std::cin >> cache_sz >> npages;
	Q2_cache cache (cache_sz);

	int ticks = 0;
	int page = 0;
	int input_res = 0;
	for (int i = 0; i < npages; i++) {
		std::cin >> page;
		input_res = cache.insert_page(page);
		if (input_res == 2 || input_res == 3)
			ticks++;
	}
	std::cout << ticks << std::endl;

	return 0;
}
