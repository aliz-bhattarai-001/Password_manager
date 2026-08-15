#include "utilities.h"

#include <openssl/rand.h>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

std::string PasswordVault::generateId() {
    unsigned char bytes[3];
    if (RAND_bytes(bytes, sizeof(bytes)) != 1) {
        throw std::runtime_error("RAND_bytes failed to generate entry ID");
    }
    char buf[7];
    snprintf(buf, sizeof(buf), "%02x%02x%02x", bytes[0], bytes[1], bytes[2]);
    return std::string(buf);
}

bool PasswordVault::addEntry(PasswordEntry& entry) {
    do {
        entry.id = generateId();
    } while (m_entries.count(entry.id) != 0);

    entry.createdAt = time(nullptr);
    entry.updatedAt = entry.createdAt;
    m_entries[entry.id] = entry;
    return true;
}

bool PasswordVault::removeEntry(const std::string& id) {
    return m_entries.erase(id) > 0;
}

bool PasswordVault::updateEntry(const std::string& id, const PasswordEntry& updated) {
    auto it = m_entries.find(id);
    if (it == m_entries.end()) {
        return false;
    }

    PasswordEntry& e = it->second;
    e.site = updated.site;
    e.username = updated.username;
    e.encryptedPassword = updated.encryptedPassword;
    e.category = updated.category;
    e.notes = updated.notes;
    e.updatedAt = time(nullptr);
    return true;
}

std::optional<PasswordEntry> PasswordVault::getEntry(const std::string& id) const {
    auto it = m_entries.find(id);
    if (it == m_entries.end()) {
        return std::nullopt;
    }
    return it->second;
}

std::vector<PasswordEntry> PasswordVault::searchEntries(const std::string& query) const {
    std::string q = query;
    std::transform(q.begin(), q.end(), q.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    auto contains = [&q](const std::string& field) {
        std::string lower = field;
        std::transform(lower.begin(), lower.end(), lower.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return lower.find(q) != std::string::npos;
    };

    std::vector<PasswordEntry> result;
    for (const auto& pair : m_entries) {
        const PasswordEntry& e = pair.second;
        if (contains(e.site) || contains(e.username) || contains(e.category) || contains(e.notes)) {
            result.push_back(e);
        }
    }
    return result;
}

std::vector<PasswordEntry> PasswordVault::getAllEntries() const {
    std::vector<PasswordEntry> result;
    result.reserve(m_entries.size());
    for (const auto& pair : m_entries) {
        result.push_back(pair.second);
    }
    return result;
}

bool PasswordVault::saveToFile(const std::string& filename, const EncryptionManager& enc) const {
    std::string ciphertext = EncryptionManager::encrypt(toJson(), enc.getKey());

    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    out << ciphertext;
    out.close();
    return out.good();
}

bool PasswordVault::loadFromFile(const std::string& filename, const EncryptionManager& enc) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }

    std::stringstream ss;
    ss << in.rdbuf();

    std::string plaintext;
    try {
        plaintext = EncryptionManager::decrypt(ss.str(), enc.getKey());
    } catch (const std::exception&) {
        return false;
    }

    return fromJson(plaintext);
}

void PasswordVault::clear() {
    m_entries.clear();
}

std::string PasswordVault::toJson() const {
    nlohmann::json arr = nlohmann::json::array();
    for (const auto& pair : m_entries) {
        arr.push_back(pair.second.toJson());
    }
    return arr.dump();
}

bool PasswordVault::fromJson(const std::string& json) {
    try {
        nlohmann::json arr = nlohmann::json::parse(json);
        if (!arr.is_array()) {
            return false;
        }

        std::unordered_map<std::string, PasswordEntry> loaded;
        for (const auto& element : arr) {
            PasswordEntry e = PasswordEntry::fromJson(element);
            if (!e.id.empty()) {
                loaded[e.id] = e;
            }
        }

        m_entries = std::move(loaded);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}
