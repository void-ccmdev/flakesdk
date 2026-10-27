#include "output.h"

using namespace Flake;

void OutputServer::print(std::string& value) { std::cout << value.c_str(); m_log.push_back(value); }
void OutputServer::println(std::string& value) { std::cout << value.c_str() << std::endl; m_log.push_back(value + "\n"); }
void OutputServer::printErr(std::string& value) { std::cout << "Error: " << value.c_str() << std::endl; m_log.push_back("Error: " + value + "\n"); }
void OutputServer::printWarn(std::string& value) { std::cout << "Warning: " << value.c_str() << std::endl; m_log.push_back("Warning: " + value + "\n"); }