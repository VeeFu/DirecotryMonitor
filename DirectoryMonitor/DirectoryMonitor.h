#include <functional>
#include <filesystem>

namespace DirectoryMonitor {

    enum class Error {
        none,
        unknown
    };

    using SimpleCallback= std::function<void(const std::filesystem::path&)>;

    struct IDirectoryWatcher {
        virtual Error subscribe(const std::filesystem::path& dir, const SimpleCallback& cb) = 0;
        virtual void run() = 0;
    };
}
