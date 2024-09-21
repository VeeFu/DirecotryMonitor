# DirectoryMonitor

## Goal
Design & implement a notifier to monitor a specified directory path. Some consumers subscribe change events from the notifier. Once files are added or removed, the notifier send the changes to its consumers.

## Plan

    [X] Setup github project
    [X] Build Working prototype in constole application for Win32
        FindFirstChangNotification and WaitForMultipleObjects seem to be the relevant functions for Win32
    [X] Research and Notes
    [X] Design platform-agnositc interface
        Since cross-platform was mentioned in intoductory interview, this seems like a relevant iteration
    [X] Refactor prototype to use new interface


## Research Notes

### Standard C++ Support?

`std::filesystem` doesn't support a "directory monitor". This is not terribly surprising. If operating system facilities are not available, a "Pure C++" solution could poll the directory at some frequency, taking a 'snapshot' of the state. Between each poll duration, it would compare old and new snapshots, then report diffs to subscribers. 
There are several downsides to this approach:
* The subscribers would miss out on changes that are done and un-done within each poll.
* Recursive directory state would likely be pretty memory intense

### Prior Art

StackOverflow answer [here](https://stackoverflow.com/questions/931093/how-do-i-make-my-program-watch-for-file-modification-in-c) gives some other threads to tug on, including [QFileSystemWatcher](http://doc.qt.io/qt-5/qfilesystemwatcher.html) in the Qt library.


### ReadDirectoryChanges
[ReadDirectoryChanges](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-readdirectorychangesw)
seems to be a "one-shot" call that wraps away the complexity of FindFirstChangeNotification and WaitForMultipleObjects as well as providing information about *what* changed during each notification. FindFirstChangeNotification only says that *something* changed. It is up to the subscriber to determine *what* happened by, say, reading the filesystem. 

Would need to pull apart the [FILE_NOTIFICATION_INFORMATION](https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-file_notify_information) to provide it to the subscriber.

This function's last parameter also leads down an interesting path:
[`LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine`](https://learn.microsoft.com/en-us/windows/win32/fileio/i-o-completion-ports)

### I/O Completion Ports
Win32 provides some other facilities that may perform better for heavy duty operations.
[I/O Completion Ports](https://learn.microsoft.com/en-us/windows/win32/fileio/i-o-completion-ports) are likely a good path of exploration if greater performance is desired

