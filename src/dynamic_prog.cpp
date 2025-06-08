#include "../inc/algorithms.h"

#include <iostream>
#include <vector>

void print_table(std::vector<std::vector<unsigned int>> &matrix) {

    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            std::cout << matrix[i][j] << " "; 
        }
    } 
}

int editDistanceDP(std::string str1, std::string str2) {

    size_t size1 = str1.length();
    size_t size2 = str2.length();

    std::vector<std::vector<unsigned int>> LCS(size1+1, std::vector<unsigned int>(size2+1, 0));

    for (size_t i = 0; i < size1; i++) {
        for (size_t j = 0; j < size2; j++) {
            if (str1[i] == str2[j]) {
                LCS[i+1][j+1] = LCS[i][j]+1;
            }
            else {
                LCS[i+1][j+1] = LCS[i+1][j] > LCS[i][j+1] ? LCS[i+1][j] : LCS[i][j+1];
            }
        } 
    }

    return size1 + size2 - 2*LCS[size1][size2]; 
}
