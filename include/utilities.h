#pragma once
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>
#include <memory>
#include <ctime>
#include <nlohmann/json.hpp>

// GeneratorOptions struct to hold password generation options
enum class StrengthLevel {
    WEAK, FAIR, GOOD, STRONG, VERY_STRONG
};

std::string strengthLevelToString(StrengthLevel level);

enum class AuditAction {
    LOGIN, LOGOUT, ADD_ENTRY, UPDATE_ENTRY, DELETE_ENTRY, CHANGE_MASTER_PASSWORD, VAULT_CREATED
};


std::string auditActionToString(AuditAction action);
AuditAction auditActionFromString(const std::string& action);

struct GeneratorOptions {
    int length = 16;
    bool useUppercase = true;
    bool useLowercase = true;
    bool useDigits = true;
    bool useSymbols = true;
    bool excludeAmbiguous = false;
};

// PasswordStrengthResult struct to hold the result of password strength evaluation
struct PasswordStrengthResult {
    int score;
    StrengthLevel level;
    std::vector<std::string> feedback;
    int entropyBits;
};

// PasswordEntry struct to hold a single stored password
struct PasswordEntry {
    std::string id;
    std::string site;
    std::string username;
    std::string encryptedPassword;
    std::string category;
    std::string notes;
    std::time_t createdAt;
    std::time_t updatedAt;

    nlohmann::json toJson() const;
    static PasswordEntry fromJson(const nlohmann::json& j);
};

// Block data structure for the blockchain audit trail
struct BlockData {
    AuditAction action;
    std::string entryId;
    std::time_t timestamp;
    std::string metadata;

    std::string toString() const;
};

//Hashing and Salt Generation Class
class HashManager {
public:
    
    static std::string sha256(const std::string& input);
    static std::string generateSalt(int byteLength = 32);
    static std::string hashMasterPassword(const std::string& password, const std::string& salt);
    static bool verifyMasterPassword(const std::string& password, const std::string& salt, const std::string& storedHash);

private:
    
    static std::string bytesToHex(const unsigned char* bytes, size_t len);
};



// Encryption and Decryption Class
class EncryptionManager{
    private:
        std::string m_key;
        bool m_unlocked=false;
        static std::string bytesToHex(const unsigned char* bytes, size_t len);
        static std::vector<unsigned char> hexToBytes(const std::string& hex);
        static std::string toBase64(const std::vector<unsigned char>& data);
        static std::vector<unsigned char> fromBase64(const std::string& b64);
    public:
        static std::string deriveKey(const std::string& masterPassword, const std::string& salt, int iteration=100000);
        static std::string generateIV();
        static std::string encrypt(const std::string& plaintext, const std::string& key);
        static std::string decrypt(const std::string& b64Ciphertext, const std::string& key);
        void loadKey(const std::string& derivedKey);
        void clearKey();
        bool isMasterKeyLoaded() const;
        const std::string& getKey() const;


};

//Password strength checker
class PasswordStrengthChecker {
private:
    static std::vector<std::string> m_commonPasswords;
    static bool m_commonLoaded;

    static bool hasUppercase(const std::string& pwd);
    static bool hasLowercase(const std::string& pwd);
    static bool hasDigit(const std::string& pwd);
    static bool hasSymbol(const std::string& pwd);
    static bool hasMinLength(const std::string& pwd, int min = 12);
    static bool hasNoRepeatingChars(const std::string& pwd);
    static bool hasNoSequentialChars(const std::string& pwd);
    static bool isCommonPassword(const std::string& pwd);
    static int getEntropyBits(const std::string& pwd);
    static int calculateScore(const std::string& pwd);
    static StrengthLevel scoreToLevel(int score);
    static std::vector<std::string> collectFeedback(const std::string& pwd);

public:
    static PasswordStrengthResult check(const std::string& pwd);
};

// Blockchain block
class Block {
private:
    int m_index;
    BlockData m_data;
    std::string m_previousHash;
    std::time_t m_timestamp;
    int m_nonce;
    std::string m_hash;

    Block(int index, const BlockData& data, const std::string& previousHash,
          std::time_t timestamp, int nonce, const std::string& hash);

public:
    Block(int index, const BlockData& data, const std::string& previousHash);

    std::string calculateHash() const;
    void mineBlock(int difficulty = 2);

    std::string toJson() const;
    static Block fromJson(const std::string& jsonStr);

    int getIndex() const;
    const BlockData& getData() const;
    const std::string& getPreviousHash() const;
    std::time_t getTimestamp() const;
    int getNonce() const;
    const std::string& getHash() const;
};

// Blockchain audit trail
class Blockchain {
private:
    std::vector<Block> m_chain;

    Block createGenesisBlock();

public:
    Blockchain();

    void addBlock(const BlockData& data);
    bool isChainValid() const;
    std::vector<std::string> getAuditLog() const;
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    const std::vector<Block>& getChain() const;
    const Block& getLatestBlock() const;
};

// Password vault
class PasswordVault {
private:
    std::unordered_map<std::string, PasswordEntry> m_entries;

    static std::string generateId();
    std::string toJson() const;
    bool fromJson(const std::string& json);

public:
    bool addEntry(PasswordEntry& entry);
    bool removeEntry(const std::string& id);
    bool updateEntry(const std::string& id, const PasswordEntry& updated);
    std::optional<PasswordEntry> getEntry(const std::string& id) const;
    std::vector<PasswordEntry> searchEntries(const std::string& query) const;
    std::vector<PasswordEntry> getAllEntries() const;
    bool saveToFile(const std::string& filename, const EncryptionManager& enc) const;
    bool loadFromFile(const std::string& filename, const EncryptionManager& enc);
    void clear();
};

// Vault configuration persisted to config.json
struct VaultConfig {
    std::string vaultPath;
    std::string blockchainPath;
    std::string salt;
    std::string masterHash;
    int pbkdf2Iterations = 100000;

    nlohmann::json toJson() const;
    static VaultConfig fromJson(const nlohmann::json& j);
};

class RandomPasswordGenerator;

// Vault manager orchestrator
class VaultManager {
private:
    HashManager m_hash;
    EncryptionManager m_encryption;
    std::unique_ptr<RandomPasswordGenerator> m_generator;
    PasswordVault m_vault;
    Blockchain m_blockchain;
    VaultConfig m_config;
    std::string m_vaultDir;
    bool m_unlocked = false;

    bool saveConfig() const;
    bool loadConfig();
    void logAction(AuditAction action, const std::string& entryId = "", const std::string& metadata = "");

public:
    VaultManager();
    explicit VaultManager(const std::string& vaultDir);
    ~VaultManager();

    bool createVault(const std::string& masterPassword);
    bool unlock(const std::string& masterPassword);
    void lock();
    bool isUnlocked() const;
    bool changeMasterPassword(const std::string& oldPwd, const std::string& newPwd);

    std::string addPassword(const std::string& site, const std::string& username,
                            const std::string& password, const std::string& category = "");
    bool deletePassword(const std::string& id);
    bool updatePassword(const std::string& id, const std::string& newPassword);
    std::optional<std::string> getPassword(const std::string& id);
    std::vector<PasswordEntry> search(const std::string& query);
    std::string generateAndStore(const std::string& site, const std::string& username,
                                 const GeneratorOptions& opts);
    std::string generatePreview(const GeneratorOptions& opts);
    PasswordStrengthResult checkStrength(const std::string& password);
    std::vector<std::string> getAuditLog();
    bool verifyAuditLog();
};

