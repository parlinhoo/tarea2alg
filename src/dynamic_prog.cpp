#include "../inc/algorithms.h"

#include <deque>
#include <iostream>

class char_list {
private:
    std::deque<char> container;

    char get_back_and_rotate() {
        char back = this->container.back();
        this->container.push_front(back);
        this->container.pop_back();
        return back;
    }

public:
    void insert_char(char chr) {
        this->container.push_front(chr);
    }

    void print() {
        for (size_t i = 0; i < this->container.size(); i++) {
            char actual = this->get_back_and_rotate();
            std::cout << actual << " ";
        }
        std::cout << "\n";
    }

    bool is_empty() {
        return this->container.empty();
    }

    bool find(char char_to_find) {
        bool found = false;
        for (size_t i = 0; i < this->container.size(); i++) {
            char actual = this->get_back_and_rotate();
            if (actual == char_to_find) found = true;
        }
        return found;
    }

    void pop_back_until_char(char chr) {
        if (this->container.empty()) return;
        char actual;
        do {
            actual = this->container.back();
            this->container.pop_back();
        } while (actual != chr && !this->container.empty());
    }
};

int editDistanceDP(std::string str1, std::string str2) {
    
    std::string LCS("");

    char_list list1;
    char_list list2;
    
    std::cout << str1 << "\n" << str2 << "\n";

    size_t index = 0;
    do {

        char char1 = index < str1.size() ? str1[index] : 0;
        char char2 = index < str2.size() ? str2[index] : 0;

        if (char1 != 0) list1.insert_char(char1);
        if (char2 != 0) list2.insert_char(char2);
        
        char repeating_char = 0;
        if (list1.find(char2)) repeating_char = char2;
        else if (list2.find(char1)) repeating_char = char1;

        if (repeating_char != 0) {
            LCS.push_back(repeating_char);

            list1.pop_back_until_char(repeating_char);
            list2.pop_back_until_char(repeating_char);
        }

        index++;

    } while (index < str1.size() || index < str2.size());
    
    return str1.size() + str2.size() - 2*LCS.size();
}
