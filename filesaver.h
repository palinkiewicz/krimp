#ifndef FILESAVER_H
#define FILESAVER_H

#include <string>

class Image;

class FileSaver
{
public:
    FileSaver();
    bool savePpm(std::string path, Image img);
    Image loadPpm(std::string path);
};

#endif // FILESAVER_H
