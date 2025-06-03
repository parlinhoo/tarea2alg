#include "../inc/algorithms.h"

#include <string>
#include <iostream>

int editDistanceDPOptimized(std::string str1, std::string str2) {
    
    std::string LCS("");

    size_t cand_index1 = 0;
    size_t cand_index2 = 0;
    size_t index = 0;

    while (index < str1.size() || index < str2.size()) {
        //std::cout << "Index " << index << ", ci1: " << cand_index1 << " | ci2: " << cand_index2 << "\n";
        bool found = false;
        for (size_t i = cand_index1; i < index; i++) {
            if (i >= str1.size() || index >= str2.size()) break;
            if (str1[i] == str2[index]) {
                //std::cout << str2[index] << " esta en candidatos 1 en la pos " << i << "\n"; 
                found = true;
                LCS.push_back(str2[index]);
                cand_index1 = i+1;
                cand_index2 = index+1;
                index++;
                break;
            }
        }
        if (found) continue;
        for (size_t i = cand_index2; i < index; i++) {
            if (i >= str2.size() || index >= str1.size()) break;
            if (str2[i] == str1[index]) {
                //std::cout << str1[index] << " esta en candidatos 2 en la pos " << i << "\n"; 
                found = true;
                LCS.push_back(str1[index]);
                cand_index1 = index+1;
                cand_index2 = i+1;
                index++;
                break;
            }
        }
        if (found) continue;
        if (str1[index] == str2[index]) {
            //std::cout << "ambos en la pos " << index << " son iguales\n";
            LCS.push_back(str1[index]);
            cand_index1 = index+1;
            cand_index2 = index+1;
        }
        index++;
    }

    //std::cout << str1 << "\n" << str2 << "\nSubcadena: " << LCS << " de largo " << LCS.size() << "\n";

    return str1.size() + str2.size() - 2*LCS.size();
}
