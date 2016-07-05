#pragma once

#include <string>
#include <list>

namespace fr {

class File;

class Directory {
    std::string path;

public:
    Directory();
    Directory(const std::string &path);

    bool exists() const;

    std::string getPath() const;
    void setPath(const std::string &path);

    std::string getName() const;

    std::list<File> getFiles() const;
};
}
