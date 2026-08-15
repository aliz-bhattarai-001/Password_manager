// #pragma once

// #include "PasswordEntry.h"

// #include <vector>
// #include <optional>

// class Vault {
// public:
//     void addEntry(PasswordEntry entry);

//     bool removeEntry(const std::string& id);

//     bool updateEntry(
//         const std::string& id,
//         const PasswordEntry& updated);

//     std::optional<PasswordEntry>
//     getEntry(const std::string& id) const;

//     const std::vector<PasswordEntry>&
//     getAllEntries() const;

//     std::vector<PasswordEntry>
//     searchEntries(const std::string& query) const;

//     std::string serialize() const;
//     static Vault deserialize(const std::string& json);

// private:
//     std::vector<PasswordEntry> entries_;
// };