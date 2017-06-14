# b-tree

This is an efficient in-memory B+ tree implementation, supporting any type of keys and values (provided that the assignment function and compare function of the data types used exist or are implemented).

```bash
mkdir build
cd build
```

Generate the makefile by CMake:
```bash
cmake ..
```

Compile the source files:
```bash
make 
```
Make sure every thing is right by running test:
```bash
make test
```

After the compiling, two executables, ```b_tree``` and ```btree_test``` will be generated. ```b_tree``` runs performance benchmark and ```btree_test``` runs the tests.

## How to use our B+tree
```c++
BPlusTree<long, int, 16> tree; // constrcut a B+ tree instance, in which the keys are of long type, the values are of int type and the fanout is 16.
tree.insert(16, 0); // insert key-value pair (16, 0) to the tree
tree.insert(17, 17); // insert key-value pair (17, 17) to the tree

tree.update(16, 16); // update the value associated with key 16
tree.delete_key(17); // remove key-value pair with key 17

int value;
if (tree.search(16, value)) // retrieve the value associated with key 16.
    std::cout << "value is " << value << std::endl;
else
    std::cout << "not found" << std::endl;
    
std::cout << "B+tree: " << tree << std::endl; // dump the tree
```




