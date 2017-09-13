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
        if (alpha <= 0)
            alpha = 0.00000001;
        for (int i = 1; i <= n; ++i) {
            c = c + (1.0 / pow((double) i, alpha));
        }
        c = 1.0 / c;
        shuffles = new int[keys];
        for (int i = 0; i < keys; ++i) {
            shuffles[i] = i;
        }

        std::random_shuffle(&shuffles[0], &shuffles[keys - 1]);
    }

    ~ZipfGenerator() {
        delete[] shuffles;
    }

    int gen() {
        double z;                     // Uniform random number (0 < z < 1)
        double sum_prob;              // Sum of probabilities
        double zipf_value;            // Computed exponential value to be returned

        // Compute normalization constant on first call only

        // Pull a uniform random number (0 < z < 1)
        do {
            z = (double) rand() / RAND_MAX * 2.0 - 1.0;
        } while ((z == 0) || (z == 1));

        // Map z to the value
        sum_prob = 0;
        for (int i = 1; i <= n; i++) {
            sum_prob = sum_prob + c / pow((double) i, alpha);
            if (sum_prob >= z) {
                zipf_value = i;
                break;
            }
        }

        // Assert that zipf_value is between 1 and N

        return shuffles[(int)zipf_value - 1];
    }
private:
    int n;
    double alpha;
    double c;
    int *shuffles;
};
#endif //B_TREE_GENERATOR_H
