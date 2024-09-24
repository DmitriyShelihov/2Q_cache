#ifndef _IDEAL_CACHE_
#define _IDEAL_CACHE_

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
	public: 
		Ideal_cache (size_t list_sz) 
			: id_list_size(list_sz) {} 
		Ideal_cache_input_res insert_page (int page_number, int next_hit) {
			if (id_umap.find(page_number) != id_umap.end()) { 				//page is currently in the list		
				(id_umap[page_number]).next_hit = next_hit;
				return tick;
			}
			else {															//insert page
				if (id_list.size() >= id_list_size) {
					int latest_page = page_number;
					if (next_hit != -1)	{ 
						int max = next_hit;
						for (std::list <int>::iterator i = id_list.begin(); i != id_list.end(); ++i) {
							if ((id_umap[*i]).next_hit == -1) {
								latest_page = *i;
								break;
							}
							else if ((id_umap[*i]).next_hit > max) {
								max = (id_umap[*i]).next_hit;
								latest_page = *i;
							}
						}
					} 
					if (latest_page == page_number)
						return miss;
					id_list.erase((id_umap[latest_page]).iter);
					id_umap.erase(latest_page);
				}
				id_list.push_front(page_number);
				id_umap[page_number] = {id_list.begin(), next_hit};
				return miss;
			}
		}
		void coloured_dump() {
              std::cout << "\033[0;33m" << "IDEAL_CACHE:\n" << "\033[0;0m";
              for (std::list <int>::iterator i = id_list.begin(); i != id_list.end(); ++i) 
                  std::cout << "\033[0;34m" << "[" << "\033[0;0m" << *i << "\033[0;34m" << "]" << "\033[0;0m";
              std::cout << std::endl;
        };

};

#endif 
