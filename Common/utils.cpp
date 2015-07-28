#include <utils.h>

//Takes a file name and spits the contents into a string
bool ReadFile(const char* pFileName, std::string& outFile)
{
    std::ifstream f(pFileName);

    bool ret = false;
    
    if (f.is_open()) {
        std::string line;
        while (getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }

        f.close();

        ret = true;
    }
    else {
        printf("Failed to open file\n");
    }
    return ret;
}
