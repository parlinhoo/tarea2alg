#include "../inc/testing.h"
#include <tuple>
#include <type_traits>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "../inc/edit_distance.h"

void saveToCSV(
        std::vector<std::tuple<std::string, std::string, std::string, size_t, size_t, size_t, size_t>>&
            data,
        const std::vector<std::string>& columns,
        const std::string& path
) {
    std::ofstream outFile(path);

    for (size_t i = 0; i < columns.size(); ++i) {
        outFile << columns[i];
        if (i < columns.size() - 1) {
            outFile << ',';
        }
    }
    outFile << '\n';

    for (auto& row : data) {
        outFile
            << std::get<0>(row) << ','
            << std::get<1>(row) << ','
            << std::get<2>(row) << ','
            << std::get<3>(row) << ','
            << std::get<4>(row) << ','
            << std::get<5>(row) << '\n';
    }
    outFile.close();
    
}

std::tuple<int64_t, size_t> testAlgorithm(std::string& str1, std::string& str2, algorithm algo) {

    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

    start_time = std::chrono::high_resolution_clock::now();
    int result = EditDistanceDeleteInsert(str1, str2, algo);
    end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

    return std::make_tuple(duration.count(), 0);
}

void testExtracts() {

    /* Pre-procesamiento */

    std::vector<std::string> names = {
        "a_story_of_a_little_pet_bear",
        "gift_of_the_magi",
        "invention_of_a_new_religion",
        "raven"
    };

    std::vector<std::tuple<std::string, std::string, size_t>> data;

    std::string path = "./data/";
    for (auto& name : names) {
        std::ifstream file(path + name + ".txt", std::ios::binary);
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        std::tuple<std::string, std::string, size_t> row = std::make_tuple(
                name,
                content,
                content.size()
        );

        data.push_back(row);
        std::cout << name << ", " << content.size() << "\n\n";
    }

    /* Testeo como tal */
    std::vector<std::tuple<std::string, std::string, std::string, size_t, size_t, size_t, size_t>>
        results; // columnas: algorithm,base_text,growing_text,base_text_size,growing_text_size,time,space


    
    size_t base_text_size = 10;
    size_t stride = 10;   // Ritmo al que growing text crece en cada test.
    size_t max_size = 1000;
    for (auto base_datum : data) {

        for (auto growing_datum : data) {
            std::string base_text = std::get<0>(base_datum);
            std::string growing_text = std::get<0>(growing_datum);

            if (base_text == growing_text) {
                continue;
            }

            std::cout << "Trying: " << base_text << "--" << growing_text << std::endl;

            for (int i = 0; i < 30; ++i) {
                size_t size = 10;
                while (size <= max_size) {

                    std::string base_content = std::get<1>(base_datum).substr(0, base_text_size);
                    std::string growing_content = std::get<1>(growing_datum).substr(0, size);


                    //if (size <= 10) {
                    //    auto recursive_result = testAlgorithm(base_content, growing_content, recursive);
                    //    std::cout << "\tTime taken for recursive: " << std::get<0>(recursive_result) << std::endl;;
                    //}
                    //
                    auto memo_measurements = testAlgorithm(base_content, growing_content, memo);
                    auto dp_measurements = testAlgorithm(base_content, growing_content, dp);
                    auto dpopt_measurements = testAlgorithm(base_content, growing_content, dpoptimized);
                    //std::cout << "\tTime taken for memo: " << std::get<0>(memo_measurements) << std::endl;
                    //std::cout << "##########\n\n";

                    std::tuple<std::string, std::string, std::string, size_t, size_t, size_t, size_t>
                        memo_results, dp_results, dpopt_results;

                        memo_results = std::make_tuple("memo", base_text, growing_text, base_text_size, 
                                size, std::get<0>(memo_measurements), 0);

                        dp_results = std::make_tuple("dp", base_text, growing_text, base_text_size, 
                                size, std::get<0>(dp_measurements), 0);

                        dpopt_results = std::make_tuple("dpopt", base_text, growing_text, base_text_size, 
                                size, std::get<0>(dpopt_measurements), 0);

                    results.push_back(memo_results);
                    results.push_back(dp_results);
                    results.push_back(dpopt_results);

                    size = size + stride;
                }
            }
        }
    }

    saveToCSV(
            results,
            {"algorithm", "base_text", "growing_text", "base_text_size", "growing_text_size", "time", "space"},
            "./data/results.csv"
    );
}

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
