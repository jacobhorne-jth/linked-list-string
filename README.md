# linked-list-string
A C++ implementation of a custom String class using a singly-linked list of characters, complete with modern C++20 comparisons and comprehensive unit tests.

**Overview**

This project reimagines the classic String class by storing characters in a dynamically allocated singly-linked list, rather than contiguous memory arrays.

The implementation emphasizes:

- Efficient memory usage proportional to the string’s length

- Clean separation of linked list logic via a list namespace

- Modern C++20 features like the spaceship operator (<=>) for comparisons

- Robust unit testing with GoogleTest

- Strict memory allocation tracking to avoid leaks

This approach demonstrates how data structures and object-oriented design principles can powerfully reshape familiar abstractions like strings.

**Features**

- Custom String Implementation
    A String class built from the ground up to use a linked list of Node elements, eliminating static arrays or C-style strings.

- Namespace Separation
    All linked list operations and node definitions are encapsulated within the list namespace to improve modularity and clarity.

- Modern Comparison Operators
    Leverages C++20's <compare> header to define <=> ("spaceship") and == operators, replacing six separate comparison methods with two concise, expressive functions.

- Dynamic Memory Tracking
    Integration with AllocationTracker ensures all allocations and deallocations are monitored and reported, helping prevent leaks and dangling pointers.

- Comprehensive Testing

    - student_gtests.cpp: Focused tests for all list namespace functions.

    - string_gtests.cpp: Tests covering String class constructors, operators, and member functions.

    - standard_main.cpp: Runtime validation and reporting of memory usage.

- CMake-Based Build System
    Simple cross-platform builds via CMakeLists.txt and CMakePresets.json, with sanitizer and Valgrind configurations pre-defined.

**How It Works**

Each String object holds a pointer head to the first list::Node. Each Node contains:

- char data: the character stored

- Node* next: pointer to the next node (or nullptr)

Operations like concatenation, substring, and assignment dynamically create or destroy nodes to resize the string appropriately.

**Example**

Below is an example String initialization and concatenation:
```text
String s1("Hello");
String s2(" World");
String s3 = s1 + s2;
std::cout << s3 << std::endl;
```
Output:
```text
Hello World
```

Internally, this creates a linked list of 11 nodes, one for each character.

**Project Structure**

```text
linked-list-string/
├── CMakeLists.txt
├── CMakePresets.json
├── src/
│   ├── list.hpp           # Definition of list::Node and helper functions
│   ├── list.cpp           # Linked list operations (create, copy, free, etc.)
│   ├── string.hpp         # String class declaration
│   ├── string.cpp         # String class implementation
│   └── standard_main.cpp  # Main program with allocation reporting
├── gtest/
│   ├── gtestmain.cpp      # GoogleTest main
│   ├── string_gtests.cpp  # Tests for String class
│   └── student_gtests.cpp # Tests for list helpers
```

**How to Build**

_Requires:_

- CMake 3.21+

- C++20-compatible compiler (e.g., g++-10+ or clang++)

- GoogleTest installed

_Example (Linux):_

```text
cmake --preset linux
cmake --build build
```
To run standard_main with sanitizers:
```text
./build/standard_main
```
To run the tests:
```text
./build/string_gtests
./build/student_gtests
```
To build a Valgrind-compatible binary:
```text
cmake --preset linux-valgrind
cmake --build build_valgrind
valgrind ./build_valgrind/standard_main
```

**Important C++ Details**

- String never directly uses new or delete. All allocations occur in list helpers like list::copy, list::concat, or list::free.

- The <=> operator in String uses std::strong_ordering for clean, safe comparisons.

- String’s destructor ensures all nodes are deallocated via list::free.

**Design Highlights**

- No Null Terminators: The end of the list is marked by nullptr, not '\0'.

- Recursion-Friendly Helpers: Many list functions can be implemented recursively for clarity.

- Memory Safety: The AllocationTracker logs every heap allocation to detect leaks.

**Future Improvements**

- Implement iterators for more natural loops over String.

- Add move semantics optimizations.

- Expand String interface to support substrings, insertions, and erasure.

<br>

License

This project is intended for educational use.
