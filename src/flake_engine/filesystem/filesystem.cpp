#include "filesystem.h"

#include "../output/output.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace Flake;

void FileServer::writeFile(File& file, std::string& content)
{
    std::filesystem::path directory = file.path;
    std::filesystem::path filePath = directory / file.name;

    std::error_code error;
    std::filesystem::create_directories(directory, error);

    if (error) {
        Flake::OutputServer output;
        output.printErr("Couldn't create directory '" +
                        directory.string() + "': " +
                        error.message());
        return;
    }

    std::ofstream newFile(filePath);

    if (!newFile.is_open()) {
        Flake::OutputServer output;
        output.printErr("Couldn't open file '" + filePath.string() + "'");
        return;
    }

    newFile << content;
}

void FileServer::appendToFile(File& file, std::string& content)
{
    std::filesystem::path directory = file.path;
    std::filesystem::path filePath = directory / file.name;

    std::error_code error;
    std::filesystem::create_directories(directory, error);

    if (error) {
        Flake::OutputServer output;
        output.printErr("Couldn't create directory '" +
                        directory.string() + "': " +
                        error.message());
        return;
    }

    std::ofstream targetFile(filePath, std::ios::app);

    if (!targetFile.is_open()) {
        Flake::OutputServer output;
        output.printErr((std::string)"Couldn't open file for writing.");
        return;
    }

    targetFile << content;
}

std::string FileServer::readFile(File& file)
{
    std::ifstream read_file(file.path + file.name);

    if (!read_file.is_open()) {
        Flake::OutputServer output;
        output.printErr("Couldn't open file '" + file.name + "' at '" + file.path + "'");
        return {};
    }

    std::stringstream content;
    content << read_file.rdbuf();

    return content.str();
}

void FileServer::removeFile(File& file)
{
    std::filesystem::path filePath = std::filesystem::path(file.path) / file.name;

    std::error_code error;
    bool removed = std::filesystem::remove(filePath, error);

    if (error) {
        Flake::OutputServer output;
        output.printErr(
            "Couldn't remove file '" +
            filePath.string() +
            "': " +
            error.message()
        );
        return;
    }

    if (!removed) {
        Flake::OutputServer output;
        output.printErr(
            "File does not exist: " + filePath.string()
        );
        return;
    }
}

File FileServer::createFile(std::string& name, std::string& path)
{
    File file;
    file.name = name;
    file.path = path;

    return file;
}

void FileServer::createFolder(std::string& name, std::string& path)
{
    std::filesystem::path folderPath = std::filesystem::path(path) / name;
    std::error_code err;
    std::filesystem::create_directories(folderPath, err);
}

void FileServer::removeFolder(std::string& path)
{
    std::filesystem::path folderPath = std::filesystem::path(path);
    std::error_code err;
    bool removed = std::filesystem::remove(path);

    if(!removed) {
        Flake::OutputServer output;
        output.printErr(
            "Couldn't remove: " + folderPath.string()
        );
        return;
    }
}