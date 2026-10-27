#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace Flake {
    class OutputServer {
    public:
        void print(std::string& value);
        void println(std::string& value);
        void printErr(std::string& value);
        void printWarn(std::string& value);

        std::vector<std::string> getOutputLog();
    private:
        std::vector<std::string> m_log;
    };
}