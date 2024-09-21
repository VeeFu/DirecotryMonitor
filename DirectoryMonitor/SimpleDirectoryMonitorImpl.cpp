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

        while (true) 
        { 
            dwWaitStatus = WaitForMultipleObjects( dwChangeHandles.size(), dwChangeHandles.data(), FALSE, INFINITE);

            // NOTE: WAIT_TIMEOUT is defined with value 0x102
            // The simple parallel vectors implementation will not function for the 258th subscriber
            if (dwWaitStatus == WAIT_FAILED)  {
                printf("\n ERROR: WaitForMultipleObjects failed.\n");
                ExitProcess(GetLastError());
            }
            else if (dwWaitStatus == WAIT_TIMEOUT) {
                printf("\nNo changes in the timeout period.\n");
                break;
            }

            if (FindNextChangeNotification(dwChangeHandles[dwWaitStatus]) == FALSE) {
                printf("\n ERROR: FindNextChangeNotification function failed.\n");
                ExitProcess(GetLastError()); 
            }
            else {
                callbacks[dwWaitStatus](paths[dwWaitStatus]);
            }
        }
    }
}
