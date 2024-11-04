#include "ideal_cache.h"

static bool is_number(std::string& str) {
	return !str.empty() && (str.find_first_not_of("-0123456789") == str.npos);
}

std::unordered_map <int, std::list <int>> predict_pages(const int buf[], int npages) {
	std::unordered_map <int, std::list <int>> Ideal_map;
 
  	for (int i = 0; i < npages; i++) {
		int page = buf[i];
     
 		(Ideal_map[page]).push_front(i);
   	}
   	for (auto i = Ideal_map.begin(), ie = Ideal_map.end(); i != ie; ++i) {
		(i->second).push_front(-1);
   	}
  	return Ideal_map;
}

int main() {
    std::string cache_sz_buf;
	std::cin >> cache_sz_buf;

	if (!is_number(cache_sz_buf)) {
		std::cout << "Cache size must be an integer!" << std::endl;
		return 1;
	}
	int try_cache_sz = std::atoi(cache_sz_buf.c_str());

	if (try_cache_sz <= 0) {
		std::cout << "Cache size must be > 0!" << std::endl;
		return 1;
	}

	size_t cache_sz = try_cache_sz;
	
	std::string npages_buf;
	std::cin >> npages_buf;

	if (!is_number(npages_buf)) {
    	std::cout << "Number of requests must be an integer!" << std::endl;
        return 1; 
  	}   
    int try_npages = std::atoi(npages_buf.c_str());
      
    if (try_npages < 0) {
   		std::cout << "Number of requests must be >= 0!" << std::endl;
        return 1;
  	}
      
    size_t npages = try_npages;

	int buf[npages];

	std::string page_buf;

	for (int i = 0; i < npages; i++) {
		std::cin >> page_buf;

		if (!is_number(page_buf)) {
			std::cout << "Request number must be an integer\n" << std::endl;
			return 1;
		}
		buf[i] = std::atoi(page_buf.c_str());
	}

	std::unordered_map<int, std::list<int>> Ideal_map = predict_pages(buf, npages);
	Ideal_cache cache (cache_sz);
	
	int page = 0 ;
	int ticks = 0;

	for (int i = 0; i < npages; i++) {
		page = buf[i];   
 		if ((Ideal_map[page]).size() > 0)
 			(Ideal_map[page]).pop_back();
 		if ((int)cache.insert_page(page, (Ideal_map[page]).back()) == 1)
 			ticks++;
 	}
	
    std::cout << ticks << std::endl;
    return 0;
}


