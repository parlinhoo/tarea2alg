#include "../inc/algorithms.h"
#include <utility>
#include <map>
#include <vector>
#include <iostream>

std::string recursiveLCSMemo(std::string str1, std::string str2,
        size_t str1_len, size_t str2_len,
        std::vector<std::vector<std::pair<bool, std::string>>>& lcs_memo) {
    if (!str1_len || !str2_len) {
        return "";
    } else if (str1[str1_len - 1] == str2[str2_len - 1]) {
        char& last_char = str1[str1_len - 1];
        std::string ret_string;

        if (std::get<0>(lcs_memo[str1_len - 1][str2_len - 1])) {
            ret_string = std::get<1>(lcs_memo[str1_len - 1][str2_len - 1]);
        } else {
            ret_string = recursiveLCSMemo(str1, str2, str1_len - 1, str2_len - 1, lcs_memo);
            auto element = std::make_pair(true, ret_string);
            lcs_memo[str1_len - 1][str2_len - 1] = element;
        }

        ret_string.push_back(last_char);
        return ret_string;
    } else {
        std::string res_1, res_2;

        if (std::get<0>(lcs_memo[str1_len - 1][str2_len])) {
            res_1 = std::get<1>(lcs_memo[str1_len - 1][str2_len]);
        } else {
            res_1 = recursiveLCSMemo(str1, str2, str1_len - 1, str2_len, lcs_memo);
            auto element = std::make_pair(true, res_1);
            lcs_memo[str1_len - 1][str2_len] = element;
        }

        if (std::get<0>(lcs_memo[str1_len][str2_len - 1])) {
            res_2 = std::get<1>(lcs_memo[str1_len][str2_len - 1]);
        } else {
            res_2 = recursiveLCSMemo(str1, str2, str1_len, str2_len - 1, lcs_memo);
            auto element = std::make_pair(true, res_2);
            lcs_memo[str1_len][str2_len - 1] = element;
        }

        if (res_1.size() > res_2.size()) {
            return res_1;
        } else {
            return res_2;
        }
    }
}

std::string LCSMemo(std::string str1, std::string str2) {
    std::vector<std::vector<std::pair<bool, std::string>>> lcs_memo;
    for (size_t i = 0; i <= str1.size(); ++i) {
        std::vector<std::pair<bool, std::string>> row;
        for (size_t j = 0; j <= str2.size(); ++j) {
            auto element = std::make_pair(false, "");
            row.push_back(element);
        }
        lcs_memo.push_back(row);
    }
    return recursiveLCSMemo(str1, str2, str1.size(), str2.size(), lcs_memo);
}

int editDistanceMemo(std::string str1, std::string str2) {
    return str1.size() + str2.size() - 2 * LCSMemo(str1, str2).size();
}
