#include "../inc/testing.h"
#include <vector>
#include <iostream>
#include "../inc/edit_distance.h"

void testBaseCases() {
    std::vector<std::vector<std::string>> test_cases = {
        {"conflict", "relax"},
        {"conflict", "neighborhood"},
        {"conflict", "modification"},
        {"relax", "neighborhood"},
        {"relax", "modification"},
        {"neighborhood", "modification"},
    };

    std::vector<size_t> expected_results = {
        11,
        16,
        10,
        15,
        15,
        20
    };
    
    size_t test_case_ctr = 0;
    std::cout << "##### COMENZANDO CASOS DE PRUEBA #####" << std::endl;
    for (auto& test_case : test_cases) {
        int expected_result = expected_results[test_case_ctr++];
        int recursive_result = EditDistanceDeleteInsert(test_case[0], test_case[1], recursive);
        int memo_result = EditDistanceDeleteInsert(test_case[0], test_case[1], memo);
        int dp_result = EditDistanceDeleteInsert(test_case[0], test_case[1], dp);
        int dpopt_result = EditDistanceDeleteInsert(test_case[0], test_case[1], dpoptimized);

        std::cout << "\tcaso: (" << test_case[0] << ", " << test_case[1] << ")"
            << "\n\tResultado esperado: " << expected_result << std::endl;

        std::cout << "\t\t-recursive: " << recursive_result;
        if (recursive_result == expected_result) {
            std::cout << " O\n\n";
        } else {
            std::cout << " X\n\n";
        }


        std::cout << "\t\t-memo: " << memo_result;
        if (memo_result == expected_result) {
            std::cout << " O\n\n";
        } else {
            std::cout << " X\n\n";
        }

        std::cout << "\t\t-dp: " << dp_result;
        if (dp_result == expected_result) {
            std::cout << " O\n\n";
        } else {
            std::cout << " X\n\n";
        }

        std::cout << "\t\t-dpopt: " << dpopt_result;
        if (dpopt_result == expected_result) {
            std::cout << " O\n\n";
        } else {
            std::cout << " X\n\n";
        }

    }
}
