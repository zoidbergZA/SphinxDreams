#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

class Utils
{
    public:
        Utils();
        virtual ~Utils();

        static std::vector<std::string> findFilesIn(std::string pFolder);
        static float randomRange(float minimum, float maximum);

    protected:
    private:
};

#endif // UTILS_H
