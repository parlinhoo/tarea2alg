#include "../inc/algorithms.h"

#include <string>
#include <vector>
#include <iostream>

int editDistanceDPOptimized(std::string str1, std::string str2) {

    size_t size1 = str1.length();
    size_t size2 = str2.length();

    std::vector<unsigned int> upper_row(size2+1, 0);
    std::vector<unsigned int> actual_row(size2+1, 0);

    for (size_t i = 0; i < size1; i++) {
        for (size_t j = 0; j < size2; j++) {
            if (str1[i] == str2[j]) {
                actual_row[j+1] = upper_row[j] + 1;
            }
            else {
                actual_row[j+1] = actual_row[j] > upper_row[j+1] ? actual_row[j] : upper_row[j+1];
            }
        }
        upper_row = std::vector<unsigned int>(actual_row);
        actual_row = std::vector<unsigned int>(size2+1, 0);
    }

    return size1 + size2 - 2*upper_row[size2];
}
