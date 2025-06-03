#include "inc/edit_distance.h"

#include <iostream>

int main() {
    
    int distance = EditDistanceDeleteInsert(std::string("heal"), std::string("relax"), dp);

    std::cout << "Distance: " << distance << "\n";

    return 0;
}
