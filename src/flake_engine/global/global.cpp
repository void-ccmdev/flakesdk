#include "global.h"

#include "../output/output.h"

using namespace Flake;

void GlobalServer::setVariable(std::string& name, std::any& value) {
    for (auto& global : m_globals) {
        if (global.first == name) { global.second = value; return;}
    }
    m_globals.push_back( {name, value} );
}

std::any GlobalServer::getVariable(std::string& name) {
    for (auto& global : m_globals) {
        if (global.first == name) {
            return global.second;
        }
    }
    Flake::OutputServer output;
    output.printErr(std::string((std::string)"Can't find global variable: " + name));
    return nullptr;
}

void GlobalServer::removeVariable(std::string& name) {
    int index = 0;
    for (auto& global : m_globals) {
        index++;
        if (global.first == name) {
            m_globals.erase(m_globals.begin() + index);
            std::cout << index << std::endl;
            return;
        }
    }
    Flake::OutputServer output;
    output.printErr(std::string((std::string)"Can't remove variable: '" + name + (std::string)"' : Doesn't exist!"));
}