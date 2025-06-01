#include "../inc/test.h"
#include "../inc/algorithms.h"

#include <iostream>

int EditDistanceDeleteInsert(std::string str1, std::string str2, algorithm alg) {

    switch (alg) {
        case recursive:
            return editDistanceRecursive(str1, str2);
            break;
        case memo:
            return editDistanceMemo(str1, str2);
            break;
        case dp:
            return editDistanceDP(str1, str2);
            break;
        case dpoptimized:
            return editDistanceDPOptimized(str1, str2);
            break;
    } 

    std::cout << "Algoritmo invalido\n";

    return -1;    
}

int main() {
    std::cout << "xd\n";
}
