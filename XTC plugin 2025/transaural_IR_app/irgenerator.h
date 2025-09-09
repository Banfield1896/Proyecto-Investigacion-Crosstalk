#pragma once
#include "Parameters.h"
#include <vector>

class IRGenerator {
public:
    std::pair<std::vector<float>, std::vector<float>> generate(const Parameters& params);
};
