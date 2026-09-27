#include "LittleFS.h"
#ifndef LOCALSTORAGE
#define LOCALSTORAGE
class LocalStorage{
    public: 
        void Write(String json);
        String Read();
        void Delete();
        LocalStorage();

    private:
        File file;
};

#endif