//
// Created by robert on 13/9/17.
//
#include <random>
#include <algorithm>
#ifndef B_TREE_GENERATOR_H
#define B_TREE_GENERATOR_H

class ZipfGenerator {
public:
    explicit ZipfGenerator(int keys, double skew): n(keys), alpha(skew), sum_prob(0), shuffles(0) {

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

        std::random_shuffle(&shuffles[0], &shuffles[keys - 1]);
    }

    ~ZipfGenerator() {
        delete[] shuffles;
        delete[] sum_prob;
    }

    int gen() {
//        return rand() % n;
        double z = rand() / (double) RAND_MAX;            // Uniform random number (0 < z < 1)

        // Compute normalization constant on first call only


        int l = 0, r = n - 1;
        int m = 0;
        while (l <= r) {
            m = (l + r) >> 1;
            if (sum_prob[m] < z) {
                l = m + 1;
            } else if (sum_prob[m] == z) {
                l = m;
                break;
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
