#pragma once

#include <iostream>
#include <unordered_map>
#include <list>

enum Ideal_cache_input_res {
	tick = 1,
	miss = 0
};

struct page_info {
	std::list <int>::iterator iter;
	int next_hit;
};

class Ideal_cache {
	private: 
		std::list <int> id_list;
		std::unordered_map <int, struct page_info> id_umap;
		size_t id_list_size;
		int cur_max = -1;
		int latest_page;
	public: 
		Ideal_cache (size_t list_sz) 
			: id_list_size(list_sz) {} 
		Ideal_cache_input_res insert_page (int page_number, int next_hit) {
			if (next_hit == -1) {
				if (id_umap.find(page_number) != id_umap.end()) {
					auto g = (id_umap[page_number]).iter;
					id_list.erase(g);
					id_umap.erase(page_number);
					
					int new_cur_max = -1;

					for (auto i = id_umap.begin(), ie = id_umap.end(); i != ie; ++i) {
						if ((i->second).next_hit > new_cur_max) {
							new_cur_max = (i->second).next_hit;
							latest_page = *((i->second).iter);
						}
					}
					cur_max = new_cur_max;
					return tick;
				} 
				return miss;
			}
			if (id_umap.find(page_number) != id_umap.end()) {
				if (next_hit > cur_max) {
					cur_max = next_hit;
					latest_page = page_number;
				}
				(id_umap[page_number]).next_hit = next_hit;
				return tick;
			} 
			if (id_list.size() < id_list_size) {
				if (next_hit > cur_max) {
					cur_max = next_hit;
					latest_page = page_number;
				}
				id_list.push_front(page_number);
					 
				struct page_info info {id_list.begin(), next_hit};
				id_umap[page_number] = info;
				
				return miss;
			} 
			if (next_hit > cur_max) 
				return miss;
			id_list.erase((id_umap[latest_page]).iter);
			id_umap.erase(latest_page);

			id_list.push_front(page_number);
			id_umap[page_number] = {id_list.begin(), next_hit};

			int new_cur_max = -1;
 
            for (auto i = id_umap.begin(), ie = id_umap.end(); i != ie; ++i) {
              	if ((i->second).next_hit > new_cur_max) {
                  	new_cur_max = (i->second).next_hit;
                  	latest_page = *((i->second).iter);
               	}
          	}
         	cur_max = new_cur_max;

			return miss;
		}
			
		void coloured_dump() {
              std::cout << "\033[0;33m" << "IDEAL_CACHE:\n" << "\033[0;0m";
              for (std::list <int>::iterator i = id_list.begin(); i != id_list.end(); ++i) 
                  std::cout << "\033[0;34m" << "[" << "\033[0;0m" << *i << "\033[0;34m" << "]" << "\033[0;0m";
              std::cout << std::endl;
        };
};

