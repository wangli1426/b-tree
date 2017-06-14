//
// Created by Li Wang on 6/11/17.
//

#include <iostream>
#include "../b_plus_tree.h"

// This is an example showing how to use customized data types in the B+tree.

namespace customized_data_types {
    // this key pointer points to a char array
    struct string_pointer {
        const char *point;

        bool operator<(const string_pointer &p) const {
            return strcmp((char *) this->point, (char *) p.point) < 0;
        }

        bool operator==(const string_pointer &p) const {
            return strcmp((char *) this->point, (char *) p.point) == 0;
        }

        string_pointer() {
            point = 0;
        }

        string_pointer(const char *point) {
            this->point = point;
        }

        friend std::ostream &operator<<(std::ostream &os, string_pointer const &m) {
            return os << std::string((char *) m.point);
        }
    };
}

using namespace customized_data_types;

int main() {

    BPlusTree<string_pointer, long, 4> tree;
    const char *str = "abc123";
    tree.insert(string_pointer(str), 4);
    std::cout << "tree:" << tree << std::endl;

    long value;
    tree.search(string_pointer("abc123"), value);
    std::cout << "abc123: " << value << std::endl;

}