// #include "PasswordEntry.h"

// #include <random>
// #include <sstream>

// namespace {

// std::string generateId()
// {
//     static std::random_device rd;
//     static std::mt19937 gen(rd());

//     std::uniform_int_distribution<> dist(0, 15);

//     std::stringstream ss;

//     for (int i = 0; i < 32; ++i)
//         ss << std::hex << dist(gen);

//     return ss.str();
// }

// }

// PasswordEntry::PasswordEntry(
//     std::string website,
//     std::string username,
//     std::string email,
//     std::string password,
//     std::string notes)
//     : id_(generateId()),
//       website_(std::move(website)),
//       username_(std::move(username)),
//       email_(std::move(email)),
//       password_(std::move(password)),
//       notes_(std::move(notes))
// {
//     createdAt_ = std::time(nullptr);
//     modifiedAt_ = createdAt_;
// }

// void PasswordEntry::touch()
// {
//     modifiedAt_ = std::time(nullptr);
// }

// nlohmann::json PasswordEntry::toJson() const
// {
//     return {
//         {"id", id_},
//         {"website", website_},
//         {"username", username_},
//         {"email", email_},
//         {"password", password_},
//         {"notes", notes_},
//         {"createdAt", createdAt_},
//         {"modifiedAt", modifiedAt_}
//     };
// }