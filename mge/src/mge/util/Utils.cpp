#include "Utils.hpp"

#include <windows.h>

Utils::Utils()
{
    //ctor
}

Utils::~Utils()
{
    //dtor
}

std::vector<std::string> Utils::findFilesIn(std::string pFolder)
{
    std::vector<std::string> names;
    char search_path[200];
    sprintf(search_path, "%s/*.*", pFolder.c_str());
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path, &fd);
    if(hFind != INVALID_HANDLE_VALUE) {
        do {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                names.push_back(fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
}

float Utils::randomRange(float minimum, float maximum)
{
    return minimum + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(maximum-minimum)));
}
