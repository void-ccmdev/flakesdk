#pragma once

#include <string>

namespace Flake
{   
    struct File {
        std::string name;
        std::string path;
    };

    class FileServer {
    public:
        File createFile(std::string& name, std::string& path);

        void writeFile(File& file, std::string& content);
        void appendToFile(File& file, std::string& content);
        std::string readFile(File& file);
        void removeFile(File& file);

        void createFolder(std::string& name, std::string& path);
        void removeFolder(std::string& path);
    };
}