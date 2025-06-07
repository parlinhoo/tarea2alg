#include "../inc/algorithms.h"


std::string recursiveLCS(std::string str1, std::string str2, size_t str1_len, size_t str2_len) {
    if (!str1_len || !str2_len) {
        return "";
    } else if (str1[str1_len - 1] == str2[str2_len - 1]) {
        char& last_char = str1[str1_len - 1];
        std::string ret_string = recursiveLCS(str1, str2, str1_len - 1, str2_len - 1);
        ret_string.push_back(last_char);
        return ret_string;
    } else {
        std::string res_1 = recursiveLCS(str1, str2, str1_len - 1, str2_len);
        std::string res_2 = recursiveLCS(str1, str2, str1_len, str2_len - 1);
        if (res_1.size() > res_2.size()) {
            return res_1;
        } else {
            return res_2;
        }
    }
}

std::string LCS(std::string str1, std::string str2) {
    return recursiveLCS(str1, str2, str1.size(), str2.size());
}

int editDistanceRecursive(std::string str1, std::string str2) {
    return str1.size() + str2.size() - 2 * LCS(str1, str2).size();
}
