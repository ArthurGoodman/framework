#include "file.h"

#include <windows.h>
#include <fstream>
#include <iostream>

fr::File::File() {
}

fr::File::File(const std::string &path) {
    setPath(path);
}

bool fr::File::exists() const {
    DWORD fileAttributes = GetFileAttributesA(path.c_str());
    return fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}

std::string fr::File::getPath() const {
    return path;
}

void fr::File::setPath(const std::string &path) {
    char buffer[MAX_PATH];
    GetFullPathNameA(path.c_str(), MAX_PATH, buffer, 0);
    this->path = buffer;
}

std::string fr::File::getDirectoryPath() const {
    std::size_t i = path.find_last_of("/\\");
    return path.substr(0, i);
}

std::string fr::File::getName() const {
    std::size_t i = path.find_last_of("/\\");
    return path.substr(i + 1, path.size());
}

std::string fr::File::getSimpleName() const {
    std::string name = getName();
    std::size_t i = name.find_last_of(".");
    return name.substr(0, i);
}

std::string fr::File::read() const {
    try {
        std::ifstream file(path);
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    } catch (const std::ifstream::failure &e) {
        std::cerr << "error opening file '" << path << "'\n";
        return "";
    }
}
