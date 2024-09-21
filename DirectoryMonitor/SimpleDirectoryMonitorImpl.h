#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

#include "DirectoryMonitor.h"

namespace DirectoryMonitor {

    class SimpleDirectoryMonitorImpl : public IDirectoryWatcher

    {
    public:
        SimpleDirectoryMonitorImpl();
        virtual ~SimpleDirectoryMonitorImpl();

        Error subscribe(const std::filesystem::path& dir, const SimpleCallback& cb);
        void run();

    private:

        DWORD dwWaitStatus; 
        std::vector<HANDLE>                 dwChangeHandles;
        std::vector<SimpleCallback>         callbacks;
        std::vector<std::filesystem::path>  paths;
        TCHAR lpFile[_MAX_FNAME];
        TCHAR lpExt[_MAX_EXT];

    };

}
