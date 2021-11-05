# Exercise EX1.2
This exercise is **part 2** of 3 of EX1. See also [Item 000](https://cppitems.github.io/#/item/000) for an overview and deadlines. The submission deadline for EX1 (all three parts) is **Mo 08.11.2021, 4pm**. The sources related to EX1.2 are available at [https://github.com/cppitems/ex1.2](https://github.com/cppitems/ex1.2).

For the submission of this exercise your solution must be in a Gitea repository called **ex1.2** by the above deadline.

## Running Result

```bash
wang@wang-virtual-machine:~/Documents/ex1.2/build$ ./benchmark 
Copy:
Old data before  | New data after   | Old Data after
  0x7f8892849800 |   0x7f8886981800 | 0x7f8892849800

Move:
Old data before  | New data after   | Old Data after
  0x7f8888fa9800 |   0x7f8888fa9800 | 0


Runtimes of constructing vector objects:

Copy constructor Vector(const Vector&)  called as Vector(vec)             2.73e-02 s
Move constructor Vector(Vector&&)       called as Vector(std::move(vec))  3.48e-03 s
```

## Task description

This exercise deals with a `Vector` type which implements parts of the functionality of an std::vector.

A defective implementation of the `Vector` class is provided in `vector.cpp` with the class declaration in `vector.hpp`. The class is defective w.r.t. to the *defaulted* implementations of 
1. the copy constructor, 
1. the move constructor, and
1. the destructor.
It is your task to change these three *defaulted* special member functions of `Vector` to match the demands for this resource owning type.

**You should only change code of these three special member functions in `vector.cpp`**, with all other functions already defined for you:

```C++
#include "vector.hpp"

// default constructor
Vector::Vector() {}
// constructor
Vector::Vector(size_type size, const value_type &value)
    : _size(size), _data(new Vector::value_type[size]) { // NOTE that some memory is allocated here!
  for (std::size_t i = 0; i < _size; ++i) {
    _data[i] = value;
  }
}
// access to raw pointer to the data
Vector::value_type *Vector::data() { return _data; }
// get the number of elements stored in the vector
Vector::size_type Vector::size() { return _size; }
// access an element of the vector
Vector::value_type &Vector::operator[](size_type pos) { return _data[pos]; }

// -------------------- YOUR IMPLEMENTATION STARTS HERE ---------------------
// copy constructor
Vector::Vector(const Vector &other) = default; // (1) implement correct copy constructor here

// move constructor
Vector::Vector(Vector &&other) = default;    // (2) implement correct move constructor here

// destructor
Vector::~Vector() = default;                 // (3) implement correct desctructor here
```

The best starting point is implementing the destructor `~Vector`, because it is needed everytime `Vector` is used. Once your destructor passes `TestA_destructor` you can move on to the copy and move constructors.

Prepare yourself for a discussion of your implementation.

## Tests
As usual, you are provided with several tests to check the correct functionality of your implementation. These will warn you about memory issues giving you some hints where the problems may be. The tests are
- TestA_destructor
- TestB_copyConstructor
- TestC_moveConstructor

## Benchmarking
For testing your implementation and its performance, a benchmark is provided in `src/benchmark.cpp`. 

It provides you with hints about the memory location of the allocated data. The initial output reflects how the copy and move constructors do not behave as expected for the data structure:
```
Copy:
Old data before  | New data after   | Old data after
  0x7f0b8f88a010 |   0x7f0b8f88a010 | 0x7f0b8f88a010     
# When old data is copied into new data, they should have different memory locations

Move:
Old data before  | New data after   | Old Data after
  0x7f0b8f88a010 |   0x7f0b8f88a010 | 0x7f0b8f88a010
  # When old data is copied into new data, old data should not know about the memory location any more
```

The executable also measures the runtime of the different constructors. 
For the *defaulted* special member functions, the runtime comparison is not yet meaningful; the output looks similar to this:
```
Copy constructor Vector(const Vector&)  called as Vector(vec)             4.90e-08 s
Move constructor Vector(Vector&&)       called as Vector(std::move(vec))  9.92e-08 s
```
After corretly impelementing all constructors you can expect the move construction to be much faster (in this setup about an order of magnitude) than the copy constructor.

## Sanitizing
The provided `CMakeLists.txt` builds the benchmark and turns on the AddressSanitizer (gcc/clang) to detect memory related problems (e.g., leaks and out-of-bound access). 
We will use this to detect problems in your submitted implementation and it is recommended that you also use the AddressSanitizer (or a equivalent tool on you platform) for tests during development. Note that these tools are available by default in the online IDE at [https://advcpp.ide.iue.tuwien.ac.at](https://advcpp.ide.iue.tuwien.ac.at) , but should also work with any standard gcc  or clang install.

CMake will check if there is an address sanitizer available and notify you when executing `cmake ..`:
```
-----> Congratulations, you are using the address sanitizer
```
**NOTE**: The sanitizer will only be turned on when the cmake build type is `Debug`. If you changed the build type to something different, the sanitizer will not be used.

**In case the address sanitizer cannot be turned on, you will receive a warning**:
```
-----> WARNING: ADDRESS SANITIZER IS NOT AVAILABLE
```

You are not required to work with the sanitizer, although we strongly encourage it to avoid memory related errors. If you cannot get sanitizers to work on your local machine, you can use the provided online IDE at [https://advcpp.ide.iue.tuwien.ac.at](https://advcpp.ide.iue.tuwien.ac.at) .
