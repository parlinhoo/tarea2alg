#pragma once

#include <string>
#include "algorithms.h"


enum algorithm {recursive, memo, dp, dpoptimized};
int EditDistanceDeleteInsert(std::string, std::string, algorithm);
