//
// Created by robert on 13/9/17.
//
#include <random>
#include <algorithm>
#ifndef B_TREE_GENERATOR_H
#define B_TREE_GENERATOR_H

class ZipfGenerator {
public:
    ZipfGenerator(int keys, double skew): n(keys), alpha(skew) {

        for (int i = 1; i <= n; ++i) {
            c = c + (1.0 / pow((double) i, alpha));
        }
        c = 1.0 / c;

        double sum = 0;
        sum_prob = new double[keys];
        for (int i = 0 ; i < n; ++i) {
            sum += c / pow((double)i + 1, alpha);
            sum_prob[i] = sum;
        }

        shuffles = new int[keys];
        for (int i = 0; i < keys; ++i) {
            shuffles[i] = i;
        }

//        std::random_shuffle(&shuffles[0], &shuffles[keys - 1]);
    }

    ~ZipfGenerator() {
        delete[] shuffles;
        delete[] sum_prob;
    }

    int gen() {
        double z;                  // Uniform random number (0 < z < 1)

        // Compute normalization constant on first call only

        // Pull a uniform random number (0 < z < 1)
        do {
            z = (double) rand() / RAND_MAX;
        } while ((z == 0) || (z == 1));

        int l = 0, r = n - 1;
        int m = 0;
        bool found = false;
        while (l <= r) {
            m = (l + r) >> 1;
            if (sum_prob[m] < z) {
                l = m + 1;
            } else if (sum_prob[m] == z) {
                l = m;
                return true;
            } else {
                r = m - 1;
            }
        }

        // Assert that zipf_value is between 1 and N

        return shuffles[l];
    }
private:
    int n;
    double alpha;
    double c;
    int *shuffles;
    double* sum_prob;
};
#endif //B_TREE_GENERATOR_H
