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

        Error subscribe(const std::filesystem::path& dir, const callback& cb);
        void run();

    private:

        DWORD dwWaitStatus; 
        HANDLE dwChangeHandles[2]; 
        TCHAR lpDrive[4];
        TCHAR lpFile[_MAX_FNAME];
        TCHAR lpExt[_MAX_EXT];

    };

}
