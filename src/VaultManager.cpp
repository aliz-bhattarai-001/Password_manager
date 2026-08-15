#include "utilities.h"
#include "PasswordGenerator.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

VaultManager::VaultManager() : VaultManager("data") {}

VaultManager::VaultManager(const std::string& vaultDir)
    : m_vaultDir(vaultDir), m_generator(std::make_unique<RandomPasswordGenerator>()) {
    std::filesystem::create_directories(m_vaultDir);
    m_config.vaultPath = (std::filesystem::path(m_vaultDir) / "vault.enc").string();
    m_config.blockchainPath = (std::filesystem::path(m_vaultDir) / "chain.json").string();
}

VaultManager::~VaultManager() = default;

bool VaultManager::createVault(const std::string& masterPassword) {
    try {
        std::filesystem::create_directories(m_vaultDir);

        m_config.salt = HashManager::generateSalt();
        m_config.masterHash = HashManager::hashMasterPassword(masterPassword, m_config.salt);
        m_config.pbkdf2Iterations = 100000;

        std::string derivedKey = EncryptionManager::deriveKey(masterPassword, m_config.salt,
                                                              m_config.pbkdf2Iterations);

        m_vault.clear();
        m_encryption.clearKey();
        m_encryption.loadKey(derivedKey);

        if (!saveConfig()) {
            return false;
        }

        m_blockchain = Blockchain();
        if (!m_blockchain.saveToFile(m_config.blockchainPath)) {
            return false;
        }

        std::string emptyVaultCipher = EncryptionManager::encrypt("[]", derivedKey);
        std::ofstream out(m_config.vaultPath, std::ios::binary);
        if (!out.is_open()) {
            return false;
        }
        out << emptyVaultCipher;
        out.close();
        if (!out.good()) {
            return false;
        }

        m_unlocked = true;
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool VaultManager::unlock(const std::string& masterPassword) {
    if (!loadConfig()) {
        return false;
    }

    if (!HashManager::verifyMasterPassword(masterPassword, m_config.salt, m_config.masterHash)) {
        return false;
    }

    std::string derivedKey = EncryptionManager::deriveKey(masterPassword, m_config.salt,
                                                          m_config.pbkdf2Iterations);

    m_encryption.clearKey();
    m_encryption.loadKey(derivedKey);

    m_vault.clear();
    if (!m_vault.loadFromFile(m_config.vaultPath, m_encryption)) {
        m_encryption.clearKey();
        return false;
    }

    if (!m_blockchain.loadFromFile(m_config.blockchainPath)) {
        m_encryption.clearKey();
        return false;
    }

    logAction(AuditAction::LOGIN);
    m_unlocked = true;
    return true;
}

void VaultManager::lock() {
    if (m_unlocked) {
        logAction(AuditAction::LOGOUT);
    }
    m_vault.clear();
    m_encryption.clearKey();
    m_unlocked = false;
}

bool VaultManager::isUnlocked() const {
    return m_unlocked;
}

bool VaultManager::changeMasterPassword(const std::string& oldPwd, const std::string& newPwd) {
    if (!m_unlocked) {
        return false;
    }
    if (!HashManager::verifyMasterPassword(oldPwd, m_config.salt, m_config.masterHash)) {
        return false;
    }

    try {
        std::string oldKey = m_encryption.getKey();
        std::string newSalt = HashManager::generateSalt();
        std::string newKey = EncryptionManager::deriveKey(newPwd, newSalt, m_config.pbkdf2Iterations);

        std::vector<PasswordEntry> entries = m_vault.getAllEntries();
        for (const PasswordEntry& e : entries) {
            std::string plain = EncryptionManager::decrypt(e.encryptedPassword, oldKey);
            PasswordEntry updated = e;
            updated.encryptedPassword = EncryptionManager::encrypt(plain, newKey);
            if (!m_vault.updateEntry(e.id, updated)) {
                return false;
            }
        }

        m_encryption.loadKey(newKey);
        if (!m_vault.saveToFile(m_config.vaultPath, m_encryption)) {
            return false;
        }

        m_config.salt = newSalt;
        m_config.masterHash = HashManager::hashMasterPassword(newPwd, newSalt);
        if (!saveConfig()) {
            return false;
        }

        logAction(AuditAction::CHANGE_MASTER_PASSWORD);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

std::string VaultManager::addPassword(const std::string& site, const std::string& username,
                                      const std::string& password, const std::string& category) {
    if (!m_unlocked) {
        return "";
    }

    PasswordEntry entry;
    entry.site = site;
    entry.username = username;
    entry.encryptedPassword = EncryptionManager::encrypt(password, m_encryption.getKey());
    entry.category = category;
    m_vault.addEntry(entry);
    m_vault.saveToFile(m_config.vaultPath, m_encryption);
    logAction(AuditAction::ADD_ENTRY, entry.id);
    return entry.id;
}

bool VaultManager::deletePassword(const std::string& id) {
    if (!m_unlocked) {
        return false;
    }
    if (!m_vault.removeEntry(id)) {
        return false;
    }
    m_vault.saveToFile(m_config.vaultPath, m_encryption);
    logAction(AuditAction::DELETE_ENTRY, id);
    return true;
}

bool VaultManager::updatePassword(const std::string& id, const std::string& newPassword) {
    if (!m_unlocked) {
        return false;
    }
    auto existing = m_vault.getEntry(id);
    if (!existing.has_value()) {
        return false;
    }

    PasswordEntry updated = *existing;
    updated.encryptedPassword = EncryptionManager::encrypt(newPassword, m_encryption.getKey());
    if (!m_vault.updateEntry(id, updated)) {
        return false;
    }
    m_vault.saveToFile(m_config.vaultPath, m_encryption);
    logAction(AuditAction::UPDATE_ENTRY, id);
    return true;
}

std::optional<std::string> VaultManager::getPassword(const std::string& id) {
    if (!m_unlocked) {
        return std::nullopt;
    }
    auto entry = m_vault.getEntry(id);
    if (!entry.has_value()) {
        return std::nullopt;
    }
    try {
        return EncryptionManager::decrypt(entry->encryptedPassword, m_encryption.getKey());
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

std::vector<PasswordEntry> VaultManager::search(const std::string& query) {
    if (!m_unlocked) {
        return {};
    }
    return m_vault.searchEntries(query);
}

std::string VaultManager::generateAndStore(const std::string& site, const std::string& username,
                                           const GeneratorOptions& opts) {
    if (!m_unlocked) {
        return "";
    }
    std::string pwd = RandomPasswordGenerator(opts).generate();
    addPassword(site, username, pwd);
    return pwd;
}

std::string VaultManager::generatePreview(const GeneratorOptions& opts) {
    return RandomPasswordGenerator(opts).generate();
}

PasswordStrengthResult VaultManager::checkStrength(const std::string& password) {
    return PasswordStrengthChecker::check(password);
}

std::vector<std::string> VaultManager::getAuditLog() {
    return m_blockchain.getAuditLog();
}

bool VaultManager::verifyAuditLog() {
    return m_blockchain.isChainValid();
}

bool VaultManager::saveConfig() const {
    std::filesystem::create_directories(m_vaultDir);
    std::ofstream out(std::filesystem::path(m_vaultDir) / "config.json", std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    out << m_config.toJson().dump(2);
    out.close();
    return out.good();
}

bool VaultManager::loadConfig() {
    std::ifstream in(std::filesystem::path(m_vaultDir) / "config.json", std::ios::binary);
    if (!in.is_open()) {
        return false;
    }

    std::stringstream ss;
    ss << in.rdbuf();

    try {
        nlohmann::json j = nlohmann::json::parse(ss.str());
        m_config = VaultConfig::fromJson(j);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

void VaultManager::logAction(AuditAction action, const std::string& entryId, const std::string& metadata) {
    BlockData data{action, entryId, time(nullptr), metadata};
    m_blockchain.addBlock(data);
    m_blockchain.saveToFile(m_config.blockchainPath);
}
