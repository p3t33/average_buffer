# Average buffer
The main goal of this implementation is to create a generic "write only" buffer.
The buffer will grow by one node each time a new data is inserted into it, once
full buffer capacity is reached (capacity to be provided by the user), oldest
data will be removed and newest to be inserted in its place. 

### Assumptions and considerations
* No STL data structures to be used
* Buffer should not be allocated all at once but instead, it should grow at run
  time until full capacity is reached. This is why a fixed size array with 
  index = (counter % full_buffer_capacity) was not used.
* Smart pointers are not a necessity, row C style pointers could have work just
  fine (although using them would have meant implementing a destructor to free
  all of the run time allocated nodes with data)
* single linked list was chosen over double linked list to save the extra space
  that a "previous" smart pointer would have occupied at each node.
* getUpperQuarterAverage and getLowerQuarterAverage are policy based in case
  the current members number in buffer are not a multiply of 4. 
* buffer by its nature should be small.


### Getting Started
clone the project by typing in the command line:
```bash
git clone https://github.com/p3t33/average_buffer.git
```

### Compiling and running the server and clients
In order to compile source code to binary and run the 3 clients and server: 
```sh
./compile_run_and_test.sh
```

This will output binary file average_buffer_unit_test.out, and run it with
valgrind  


### Compilers and operating systems
* Development was done on Linux Mint 19 LTS OS.
* Source code was compiled with GNU g++ v7.4 and clang++ v6.0.0, std=14
* Tested for memory leaks using Valgrind v3.13.0

### Authors

**Kobi Medrish** - [p3t33](https://github.com/p3t33)

### License
Licensed under the [GPLv3](http://www.gnu.org/licenses/gpl-3.0.html) license.
