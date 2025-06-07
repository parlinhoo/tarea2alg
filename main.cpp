#include "inc/edit_distance.h"
#include "inc/testing.h"

#include <iostream>
#include <string>
#include <vector>

int main() {


    testBaseCases();
    // std::vector<std::string> test_cases;

    // test_cases.push_back("conflict");
    // test_cases.push_back("relax");
    // test_cases.push_back("neighborhood");
    // test_cases.push_back("modification");

    // for (size_t i = 0; i < test_cases.size(); i++) {
    //     std::string str1 = test_cases[i];
    //     for (size_t j = i; j < test_cases.size(); j++) {
    //         std::string str2 = test_cases[j];
    //         int distance_dp = EditDistanceDeleteInsert(str1, str2, dp);
    //         int distance_dpopt = EditDistanceDeleteInsert(str1, str2, dpoptimized);

    //         std::cout << str1 << " y " << str2 << " | dp: " <<  distance_dp << ", dpopt: " << distance_dpopt << "\n";
    //     }
    // }

    return 0;
}
