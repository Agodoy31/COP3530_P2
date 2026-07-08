#pragma once
#include <string>
#include <filesystem>

bool isValidFilePath(std::string& path) {
    if (path.starts_with('"') && path.ends_with('"') && path.length() >= 2) {
        path = path.substr(1, path.length() - 2);
    }

    return std::filesystem::exists(path) && !std::filesystem::is_directory(path);
}
