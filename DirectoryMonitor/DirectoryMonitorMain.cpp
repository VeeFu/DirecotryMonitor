// DirectoryMonitor.cpp : Defines the entry point for the application.
//

#include "DirectoryMonitorMain.h"
#include "SimpleDirectoryMonitorImpl.h"

void _tmain(int argc, TCHAR *argv[])
{
    if(argc != 2)
    {
        _tprintf(TEXT("Usage: %s <dir>\n"), argv[0]);
        return;
    }

    auto watcher = DirectoryMonitor::SimpleDirectoryMonitorImpl();
    watcher.subscribe(std::filesystem::path(argv[1]), [](const auto& watchedDirectory) {
        std::wcout << L"Something changed in \"" << watchedDirectory << L"\"\n";
    });
    watcher.run();
}

