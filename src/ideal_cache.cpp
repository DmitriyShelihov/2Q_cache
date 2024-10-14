#include "ideal_cache.h"

std::unordered_map <int, std::list <int>> predict_pages(const int buf[], int npages) {
	std::unordered_map <int, std::list <int>> Ideal_map;
 
  	for (int i = 0; i < npages; i++) {
		int page = buf[i];
     	if (Ideal_map.find(page) != Ideal_map.end()) {
        	if ((Ideal_map[page]).front() != -1)
             	(Ideal_map[page]).push_back(i);
         	else {
              	(Ideal_map[page]).pop_front();                        
                (Ideal_map[page]).push_back(i);
         	}
      	} else {
 			(Ideal_map[page]).push_front(-1);
      	}
   	}
  	return Ideal_map;
}


int main() {
    size_t cache_sz = 0;
    size_t npages = 0;
	
	std::cin >> cache_sz >> npages;
	
	int buf[npages];

	for (int i = 0; i < npages; i++)
		std::cin >> buf[i];

	std::unordered_map<int, std::list<int>> Ideal_map = predict_pages(buf, npages);
	Ideal_cache cache (cache_sz);
	
	int page = 0 ;
	int ticks = 0;

	for (int i = 0; i < npages; i++) {
		page = buf[i];   
        if ((int)cache.insert_page(page, (Ideal_map[page]).front()) == 1)
        	ticks++;
 	 
 		if ((Ideal_map[page]).size() > 0)
 			(Ideal_map[page]).pop_front();
 	}
	
    std::cout << ticks << std::endl;
    return 0;
}


