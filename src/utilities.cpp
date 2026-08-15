#include "utilities.h"

#include <cctype>
#include <ctime>
#include <stdexcept>

nlohmann::json PasswordEntry::toJson() const {
    nlohmann::json j;
    j["id"] = id;
    j["site"] = site;
    j["username"] = username;
    j["encryptedPassword"] = encryptedPassword;
    j["category"] = category;
    j["notes"] = notes;
    j["createdAt"] = createdAt;
    j["updatedAt"] = updatedAt;
    return j;
}

PasswordEntry PasswordEntry::fromJson(const nlohmann::json& j) {
    PasswordEntry e;
    if (!j.is_object()) {
        return e;
    }
    e.id = j.value("id", std::string());
    e.site = j.value("site", std::string());
    e.username = j.value("username", std::string());
    e.encryptedPassword = j.value("encryptedPassword", std::string());
    e.category = j.value("category", std::string());
    e.notes = j.value("notes", std::string());
    e.createdAt = j.value("createdAt", std::time_t(0));
    e.updatedAt = j.value("updatedAt", std::time_t(0));
    return e;
}

namespace {
std::string formatTimestamp(std::time_t t) {
    std::tm tm = {};
    localtime_r(&t, &tm);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", &tm);
    return std::string(buf);
}
}  // namespace

nlohmann::json VaultConfig::toJson() const {
    nlohmann::json j;
    j["vaultPath"] = vaultPath;
    j["blockchainPath"] = blockchainPath;
    j["salt"] = salt;
    j["masterHash"] = masterHash;
    j["pbkdf2Iterations"] = pbkdf2Iterations;
    return j;
}

VaultConfig VaultConfig::fromJson(const nlohmann::json& j) {
    VaultConfig c;
    if (!j.is_object()) {
        return c;
    }
    c.vaultPath = j.value("vaultPath", std::string());
    c.blockchainPath = j.value("blockchainPath", std::string());
    c.salt = j.value("salt", std::string());
    c.masterHash = j.value("masterHash", std::string());
    c.pbkdf2Iterations = j.value("pbkdf2Iterations", 100000);
    return c;
}

std::string strengthLevelToString(StrengthLevel level) {
    switch (level) {
        case StrengthLevel::WEAK: return "WEAK";
        case StrengthLevel::FAIR: return "FAIR";
        case StrengthLevel::GOOD: return "GOOD";
        case StrengthLevel::STRONG: return "STRONG";
        case StrengthLevel::VERY_STRONG: return "VERY STRONG";
    }
    return "UNKNOWN";
}

std::string auditActionToString(AuditAction action) {
    switch (action) {
        case AuditAction::LOGIN: return "login";
        case AuditAction::LOGOUT: return "logout";
        case AuditAction::ADD_ENTRY: return "add_entry";
        case AuditAction::UPDATE_ENTRY: return "update_entry";
        case AuditAction::DELETE_ENTRY: return "delete_entry";
        case AuditAction::CHANGE_MASTER_PASSWORD: return "change_master_password";
        case AuditAction::VAULT_CREATED: return "vault_created";
    }
    return "unknown";
}

AuditAction auditActionFromString(const std::string& action) {
    if (action == "login") return AuditAction::LOGIN;
    if (action == "logout") return AuditAction::LOGOUT;
    if (action == "add_entry") return AuditAction::ADD_ENTRY;
    if (action == "update_entry") return AuditAction::UPDATE_ENTRY;
    if (action == "delete_entry") return AuditAction::DELETE_ENTRY;
    if (action == "change_master_password") return AuditAction::CHANGE_MASTER_PASSWORD;
    if (action == "vault_created") return AuditAction::VAULT_CREATED;
    throw std::invalid_argument("Unknown audit action: " + action);
}

std::string BlockData::toString() const {
    std::string actionName = auditActionToString(action);
    for (char& c : actionName) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return actionName + " | id:" + entryId + " | " + formatTimestamp(timestamp);
}
