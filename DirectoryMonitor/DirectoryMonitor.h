#include <functional>
#include <filesystem>

namespace DirectoryMonitor {

    enum class Error {
        none,
        unknown
    };

    using callback = std::function<void(const std::filesystem::path&)>;

    struct IDirectoryWatcher {
        virtual Error subscribe(const std::filesystem::path& dir, const callback& cb) = 0;
        virtual void run() = 0;
    };
}
