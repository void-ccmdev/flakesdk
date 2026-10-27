#pragma once

#include <string>
#include <vector>
#include <any>

namespace Flake {
    class GlobalServer {
    public:
        void setVariable(std::string& name, std::any& value);
        std::any getVariable(std::string& name);
        void removeVariable(std::string& name);
    private:
        std::vector<std::pair<std::string, std::any>> m_globals;
    };
}

