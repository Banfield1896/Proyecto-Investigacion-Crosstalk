#pragma once
#include <vector>
#include <string>

class IRFileManager {
public:
    bool saveIR(const std::string& path,
                const std::vector<float>& leftIR,
                const std::vector<float>& rightIR,
                int sampleRate);
};
