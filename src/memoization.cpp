#include "../inc/algorithms.h"
#include <utility>
#include <map>

std::string recursive_lcs_memo(std::string str1, std::string str2,
        size_t str1_len, size_t str2_len,
        std::map<std::pair<size_t, size_t>, std::string>& lcs_memo) {
    if (!str1_len || !str2_len) {
        return "";
    } else if (str1[str1_len - 1] == str2[str2_len - 1]) {
        char& last_char = str1[str1_len - 1];
        std::string ret_string;

        auto key = std::make_pair(str1_len - 1, str2_len - 1);
        if (lcs_memo.count(key)) {
            ret_string = lcs_memo[key];
        } else {
            ret_string = recursive_lcs_memo(str1, str2, str1_len - 1, str2_len - 1, lcs_memo);
            lcs_memo[key] = ret_string;
        }

        ret_string.push_back(last_char);
        return ret_string;
    } else {
        std::string res_1, res_2;

        auto res_1_key = std::make_pair(str1_len - 1, str2_len);
        auto res_2_key = std::make_pair(str1_len , str2_len - 1);
        
        if (lcs_memo.count(res_1_key)) {
            res_1 = lcs_memo[res_1_key];
        } else {
            res_1 = recursive_lcs_memo(str1, str2, str1_len - 1, str2_len, lcs_memo);
            lcs_memo[res_1_key] = res_1;
        }

        if (lcs_memo.count(res_2_key)) {
            res_2 = lcs_memo[res_2_key];
        } else {
            res_2 = recursive_lcs_memo(str1, str2, str1_len, str2_len - 1, lcs_memo);
            lcs_memo[res_2_key] = res_2;
        }

        if (res_1.size() > res_2.size()) {
            return res_1;
        } else {
            return res_2;
        }
    }
}

std::string lcs_memo(std::string str1, std::string str2) {
    std::map<std::pair<size_t, size_t>, std::string> lcs_memo;
    return recursive_lcs_memo(str1, str2, str1.size(), str2.size(), lcs_memo);
}

int editDistanceMemo(std::string str1, std::string str2) {
    return str1.size() + str2.size() - 2 * lcs_memo(str1, str2).size();
}
