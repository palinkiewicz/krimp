#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class QImage;

class FileHandler
{
public:
    FileHandler();
    bool savePpm(std::string path, QImage* img);
    QImage* loadPpm(std::string path);
};

#endif // FILEHANDLER_H
