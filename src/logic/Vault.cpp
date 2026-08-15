// #include "Vault.h"

// void Vault::addEntry(PasswordEntry entry)
// {
//     entries_.push_back(std::move(entry));
// }

// bool Vault::removeEntry(const std::string& id)
// {
//     auto it = std::remove_if(
//         entries_.begin(),
//         entries_.end(),
//         [&](const auto& e)
//         {
//             return e.getId() == id;
//         });

//     if (it == entries_.end())
//         return false;

//     entries_.erase(it, entries_.end());
//     return true;
// }


// // converting to a json format
// std::string Vault::serialize() const
// {
//     nlohmann::json j;

//     for (const auto& e : entries_)
//         j["entries"].push_back(e.toJson());

//     return j.dump(4); // returns json object as a string with 4 spaces indentation
// }


// // deserializing from a json format to a Vault object
// Vault Vault::deserialize(const std::string& jsonText)
// {
//     Vault vault;

//     auto j = nlohmann::json::parse(jsonText);

//     for (const auto& item : j["entries"])
//         vault.entries_.push_back(
//             PasswordEntry::fromJson(item));

//     return vault;
// }