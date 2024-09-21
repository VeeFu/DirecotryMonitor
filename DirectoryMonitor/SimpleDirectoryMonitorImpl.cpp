#include "SimpleDirectoryMonitorImpl.h"

namespace DirectoryMonitor {

    SimpleDirectoryMonitorImpl::SimpleDirectoryMonitorImpl() {

    }

    SimpleDirectoryMonitorImpl::~SimpleDirectoryMonitorImpl() {

    }

    Error SimpleDirectoryMonitorImpl::subscribe(const std::filesystem::path& dir, const SimpleCallback& cb) {

        const auto hdl = FindFirstChangeNotificationW( 
            dir.native().c_str(),          // directory to watch 
            FALSE,                         // do not watch subtree 
            FILE_NOTIFY_CHANGE_FILE_NAME); // watch file name changes 

        if (hdl == INVALID_HANDLE_VALUE) 
        {
            printf("\n ERROR: FindFirstChangeNotification function failed.\n");
            return Error::unknown;
        }
        else {
            paths.push_back(dir);
            callbacks.push_back(cb);
            dwChangeHandles.push_back(hdl);
        }

        return Error::none;
    }

    void SimpleDirectoryMonitorImpl::run() {
    }
}
