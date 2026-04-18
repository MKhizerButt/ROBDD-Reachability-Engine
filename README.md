# ROBDD Manager and Reachability Analysis

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=flat&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=flat&logo=cmake&logoColor=white)
![Testing](https://img.shields.io/badge/Tested_with-GTest-brightgreen)
![Formal Verification](https://img.shields.io/badge/Domain-Formal_Verification-purple)

A high-performance C++ Reduced Ordered Binary Decision Diagram (ROBDD) package utilizing custom hash tables and computed caches for efficient boolean logic manipulation. This project also features a Symbolic Traversal engine to verify state reachability in Finite State Machines (FSM).

## 🚀 Features

* **Core ROBDD Operations**: Full support for Boolean manipulation using the optimized ITE (If-Then-Else) algorithm (`AND`, `OR`, `XOR`, `NAND`, `NOR`, `XNOR`, and `Negation`).
* **High Performance**:
  * Employs a custom **Unique Table** implemented via hashing to ensure strict canonical representation (no isomorphic subgraphs).
  * Uses a **Computed Table (Operation Cache)** to memoize intermediate operations and drastically reduce algorithmic time complexity.
* **Symbolic Traversal (Reachability Analysis)**: Implements image computation to systematically discover and verify reachable state spaces of discrete systems (FSMs) from an initial state.
* **Visualization**: Native support to export BDD structures into standard `.dot` format for graphical rendering via Graphviz.
* **Robust Testing**: Fully developed under **Test-Driven Development (TDD)** principles using the Google Test (GTest) framework, ensuring high reliability and edge-case coverage.

## 📂 Project Structure

```text
├── CMakeLists.txt      # Top-level build configuration
├── Readme.md           # Project documentation
├── benchmarks/         # Benchmark circuit files (.bench)
├── src/                
│   ├── Manager.h/cpp   # Core ROBDD engine and Unique Table implementation
│   ├── main.cpp        # Application entry point
│   ├── bench/          # Profiling and benchmarking tools
│   ├── verify/         # Graph isomorphism verification scripts
│   └── test/           # Google Test suite (TDD unit tests)
```

## 🛠️ Prerequisites

To build and run this project, you will need:

* C++ Compiler: Supporting C++17 standard (e.g., GCC, Clang)
* CMake: Version 3.10 or higher
* Google Test (GTest): Integrated via CMake
* Graphviz (Optional): To render the generated .dot visual output

## ⚙️ Build Instructions
This project uses CMake as its build system. To compile the application and the test suite, run the following commands from the root directory:

```text
# Create a build directory
mkdir build
cd build

## Generate Makefiles and compile
cmake ..
make
```

## 🧪 Running Tests
Since the package was built using TDD, there is a comprehensive suite of unit tests verifying all logic, node reduction, caching, and reachability computations.

To run the test suite:
```text
# From within the build directory
./VDSProject_test  # Executable name may vary based on CMake configuration
```

## 💻 Usage Example
Here is a minimal example demonstrating how to initialize the manager, build a simple boolean function $f = (a + b) \cdot (c \oplus d)$, and visualise it.

```text
#include "Manager.h"

int main() {
    ClassProject::Manager bdd;

    // Create variables
    BDD_ID a = bdd.createVar("a");
    BDD_ID b = bdd.createVar("b");
    BDD_ID c = bdd.createVar("c");
    BDD_ID d = bdd.createVar("d");

    // Define the boolean function: f = (a OR b) AND (c XOR d)
    BDD_ID or_ab  = bdd.or2(a, b);
    BDD_ID xor_cd = bdd.xor2(c, d);
    BDD_ID f      = bdd.and2(or_ab, xor_cd);

    // Output the visual graph representation
    bdd.visualizeBDD("output_graph.dot", f);

    return 0;
}
```

## 📈 Benchmarks & Performance
The project includes tools to benchmark runtime and memory usage (RSS/VM). The optimized package correctly processes complex circuits (like the c3540 benchmark) in highly constrained time and memory environments.

# 👨‍💻 Author
M Khizer Butt 
