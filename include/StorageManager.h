// #pragma once

// #include "Vault.h"

// #include <filesystem>
// #include <optional>
// #include <string>
// #include <fstream>

// class StorageManager {
// public:
//     explicit StorageManager(std::filesystem::path path = "vault.dat");
//     ~StorageManager() = default;

//     // Vault Storage Operations
//     bool saveVault(const Vault& vault, const std::string& key);
//     std::optional<Vault> loadVault(const std::string& key);

//     // File Utilities
//     bool vaultFileExists() const;

//     // Path Management
//     const std::filesystem::path& getPath() const { return path_; }
//     void setPath(std::filesystem::path path) { path_ = std::move(path); }

// private:
//     std::filesystem::path path_;
// };

