#include <gtest/gtest.h>
#include "2Q_cache.h"
#include "ideal_cache.h"


#define SIZE_OF_INPUT_DATA 1000	//[bytes] The max size in bytes of all input pages

void next_object(char** buf, int times) {
	for (int i = 0; i < times; i++) {
		while ((**buf) != ' ' && (**buf) != '\n')
			(*buf)++;
		if ((**buf) != '\n')
			(*buf)++;
	}
}

FILE* tests_src = fopen("tests.txt", "r");

class Q2cacheTest: public ::testing::Test {
	public: 
		size_t fifo_sz_exp = 0;					//fifo sz after inserting pages we expect
		size_t fifo_sz_cur = 0;					//fifo sz after inserting pages we got
		char* fifo_bf_test;
		char* fifo_bf;

		size_t lru_sz_exp = 0;					//lru sz after inserting pages we expect
		size_t lru_sz_cur = 0;					//lru_sz after inserting pages we got
		char* lru_bf_test;
		char* lru_bf;
		
		char* save_fifo_bf;
		char* save_fifo_bf_test;
		char* save_lru_bf_test;
		char* save_lru_bf;
	
	protected: 
		void SetUp() {
			size_t fifo_sz = 0;
			size_t lru_sz = 0;
			int npages = 0;
			char* buf = (char*)calloc(SIZE_OF_INPUT_DATA, sizeof(char));
			char* save_buf = buf;
			fgets(buf, SIZE_OF_INPUT_DATA, tests_src);
			int sscanf_res = sscanf(buf, "%ld %ld %d", &fifo_sz, &lru_sz, &npages);
			Q2_cache cache (fifo_sz, lru_sz);
			
			next_object(&buf, 3);

			int page = 0;
			int ticks = 0;
			int perfect_ticks = 0;

			Ideal_cache id_cache (fifo_sz + lru_sz);
			
			for (int i = 0; i < npages; i++) {
				int sscanf_res = sscanf(buf, "%d", &page);
				int insert_result = (int) cache.insert_page(page);
				if (insert_result == 2 || insert_result == 3) 
					ticks++;
							
				next_object(&buf, 1);
			}

			free(save_buf);

			cache.file_dump("cache_dump.txt");
			FILE* cache_dump = fopen("cache_dump.txt", "r");
			int fifo_sz_get = 0;
			int lru_sz_get = 0;

			fscanf(cache_dump, "%d %d ", &fifo_sz_get, &lru_sz_get);

			fifo_bf = (char*)calloc(fifo_sz*2*sizeof(int), sizeof(char));
			save_fifo_bf = fifo_bf;
			fgets(fifo_bf, fifo_sz*2*sizeof(int), tests_src);
		
			sscanf(fifo_bf, "%ld", &fifo_sz_exp);
			next_object(&fifo_bf, 1);
		
			fifo_bf_test = (char*)calloc(fifo_sz*2*sizeof(int), sizeof(char));		//fifo after inserting pages
			save_fifo_bf_test = fifo_bf_test;
			fgets(fifo_bf_test, fifo_sz*2*sizeof(int), cache_dump);
			sscanf(fifo_bf_test, "%ld", &fifo_sz_cur);
			next_object(&fifo_bf_test, 1);

			lru_bf = (char*)calloc(lru_sz*2*sizeof(int), sizeof(char));
			save_lru_bf = lru_bf;
			fgets(lru_bf, lru_sz*2*sizeof(int), tests_src);
			sscanf(lru_bf, "%ld", &lru_sz_exp);
			next_object(&lru_bf, 1);

			lru_bf_test = (char*)calloc(lru_sz*2*sizeof(int), sizeof(char));		//lru after inserting pages
			save_lru_bf_test = lru_bf_test;
			fgets(lru_bf_test, lru_sz*2*sizeof(int), cache_dump);
																
			sscanf(lru_bf_test, "%ld", &lru_sz_cur);
			next_object(&lru_bf_test, 1);
			fclose(cache_dump);
		}
		void TearDown() {
			free(save_fifo_bf);
			free(save_fifo_bf_test);
			free(save_lru_bf);
			free(save_lru_bf_test);
		}

};

#define ASSERTION							\
	ASSERT_EQ(fifo_sz_exp, fifo_sz_cur); 	\
	ASSERT_STREQ(fifo_bf_test, fifo_bf);	\
	ASSERT_EQ(lru_sz_exp, lru_sz_cur);		\
	ASSERT_STREQ(lru_bf_test, lru_bf);


TEST_F(Q2cacheTest, test1) {
	ASSERTION
}

TEST_F(Q2cacheTest, test2) {
	ASSERTION
}

TEST_F(Q2cacheTest, test3) {
	ASSERTION
}

TEST_F(Q2cacheTest, test4) {
	ASSERTION
}

TEST_F(Q2cacheTest, test5) {
	ASSERTION
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
