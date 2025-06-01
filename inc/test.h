#pragma once

#include <string>

enum algorithm {recursive, memo, dp, dpoptimized};

int EditDistanceDeleteInsert(std::string, std::string, algorithm);
