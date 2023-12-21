#pragma once

// Author: ThatOneDev

namespace vortex {
    class FileSystem {
        public:
            FileSystem() = delete;
            static char *getFileContents(const char *path);
            static bool exists(const char *path);
    };
}