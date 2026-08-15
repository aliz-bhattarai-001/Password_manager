// #pragma once

// #include <string>
// #include <ctime>
// #include <nlohmann/json.hpp>

// class PasswordEntry {
// public:
//     PasswordEntry() = default;

//     PasswordEntry(
//         std::string website,
//         std::string username,
//         std::string email,
//         std::string password,
//         std::string notes);

//     const std::string& getId() const;
//     const std::string& getWebsite() const;
//     const std::string& getUsername() const;
//     const std::string& getEmail() const;
//     const std::string& getPassword() const;
//     const std::string& getNotes() const;

//     std::time_t getCreatedAt() const;
//     std::time_t getModifiedAt() const;

//     void setWebsite(const std::string& website);
//     void setUsername(const std::string& username);
//     void setEmail(const std::string& email);
//     void setPassword(const std::string& password);
//     void setNotes(const std::string& notes);

//     nlohmann::json toJson() const;
//     static PasswordEntry fromJson(const nlohmann::json& j);

// private:
//     void touch();

//     std::string id_;
//     std::string website_;
//     std::string username_;
//     std::string email_;
//     std::string password_;
//     std::string notes_;

//     std::time_t createdAt_{};
//     std::time_t modifiedAt_{};
// };