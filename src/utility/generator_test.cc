//
// Created by robert on 14/9/17.
//
#include <iostream>
#include <map>
#include "generator.h"
int main(int argc, char** argv) {
    int keys = 10;
    double alpha = 0.5;
    int n = 1000;
    if (argc == 4) {
        keys = atoi(argv[1]);
        alpha = atof(argv[2]);
        n = atoi(argv[3]);
    }
    std::map<int, int> counts;
    ZipfGenerator generator(keys, alpha);
    for (int i = 0; i < n; ++i) {
        const int key = generator.gen();
        if (counts.find(key) == counts.cend()) {
            counts[key] = 1;
        } else {
            counts[key]++;
        }
    }

    for (std::map<int, int>::const_iterator it = counts.cbegin(); it != counts.cend(); ++it) {
        std::cout << "key: " << it->first << " val: " << it->second << std::endl;
    }
}
