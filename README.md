# 2Q cache implementation on C++


## Advantages 
* More efficient than LRU cache as it separates frequently used pages from rarely used ones
* Easy to implement
## To compile 
* Move to the build directory and enter: 
``` 
    cmake ..
```
* Then: 
```
    make
```
* To run the algorythm: 
```
    ./MAIN
```
Then: 
1) input to integers: fifo size and lru size

2) input one integer: number of requests 

3) input requests 

4) The algorithm will return the number of cache hits
   
* To generate tests(default 10): 
```
    ./TEST_GEN 10
```
* To run tests: 
```
    ./TESTS
```
