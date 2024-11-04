#include <iostream>
#include <unordered_map>
#include <list>

class Q2_cache_test {
	public:
		size_t fifo_size;
        size_t lru_size;

        std::unordered_map <int, std::list <int>::iterator> fifo_umap;
        std::unordered_map <int, std::list <int>::iterator> lru_umap;
        std::list <int> fifo;
        std::list <int> lru;

		Q2_cache_test (size_t fifo_sz, size_t lru_sz)
			: fifo_size(fifo_sz), lru_size(lru_sz) {}
		void insert_page(int page_number) {
			int key = page_number;
			if (fifo_umap.find(key) != fifo_umap.end()) {	
				fifo.erase(fifo_umap[key]);
			
				if (lru.size() >= lru_size) {
					lru_umap.erase(lru.back());
					lru.pop_back();
				}
				
				lru.push_front(key);
				lru_umap[key] = lru.begin();
				fifo_umap.erase(key);
				return;
			}
			if (lru_umap.find(key) != lru_umap.end()) {	 
				lru.erase(lru_umap[key]);
				lru.push_front(key);
				lru_umap[key] = lru.begin();
				return;
			} 
			if (fifo.size() < fifo_size) {
				fifo.push_front(key);
				fifo_umap[key] = fifo.begin();
				return;
			}
			int fifo_last = fifo.back();
			fifo.erase(fifo_umap[fifo_last]);
			fifo_umap.erase(fifo_last);
			fifo.push_front(key);
			fifo_umap[key] = fifo.begin();
			return;
		};

};

int main(int argc, char* argv[]) {			//argv[1] = Number of tests
	FILE* tests_src = fopen("Tests/tests.txt", "w");
	int ntests = atoi(argv[1]);

	for (int j = 0; j < ntests; j++) {
		int npages = rand() % 100000;		//number of pages. Max = 99999
		size_t cache_sz = rand() % 100 + 1;	//cache size. Max = 100 

		fprintf(tests_src, "%ld %d", cache_sz, npages);
		size_t fifo_sz = cache_sz/2;
		size_t lru_sz = cache_sz-fifo_sz;
		Q2_cache_test cache (fifo_sz, lru_sz);
		int page = 0;							
		for (int i = 0; i < npages; i++) {
			page = rand() % 100 + 1;				//max page id = 100
			fprintf(tests_src, " %d", page);			
			cache.insert_page(page);
		}

		fprintf(tests_src, "\n%ld", cache.fifo.size());

		for (std::list <int>::iterator i = cache.fifo.begin(); i != cache.fifo.end(); ++i)                  
			fprintf(tests_src, " %d", *i);
    
        fprintf(tests_src, "\n%ld", cache.lru.size());
        for (std::list <int>::iterator i = cache.lru.begin(); i != cache.lru.end(); ++i) 
        	fprintf(tests_src, " %d", *i);
        
        fprintf(tests_src, "\n");   
	}
	fclose(tests_src);
	return 0;
}
