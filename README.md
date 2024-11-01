# Implementation of the 2Q caching algorithm in C++

## About algorithm 

Built on the basis of lru cache, with the difference that two queues are used:
1. LRU - for frequently occurring requests (which were encountered more than once)
2. FIFO - for rarely occurring requests

This optimizes the lru cache algorithm, since in the 2Q cache, rarely hitting requests do not crowd out frequently hitting ones, which allows you to increase the number of cache hits

## To build and run
1. Copy files from the repository to your folder using:\
   `git clone git@github.com:DmitriyShelihov/2Q_cache.git`
2. In the build folder, build the project using:
   ```
   cmake ..
   make
   ```
3. To run the algorithm:\
   `./MAIN`
4. Enter cache size and number of pages to save in cache. Then enter pages:
   ```
   4 10
   1 2 1 2 2 3 1 2 1 2
   ```
5. Output: number of cache hits:
   ```
   7
   ```
