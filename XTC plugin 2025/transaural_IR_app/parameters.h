#pragma once
#include <string>

class Parameters {
public:
    float D, dp, do_, beta;
    int nSamplesIR, fs;
    std::string nombreArchivo;

    bool isValid() const;
};
