#pragma once


#include <string>
#include <vector>
#include <cstddef>

class EncryptionManager {
public:
    EncryptionManager() = default;
    ~EncryptionManager() {
        clearKey();
    }

    // Disable copy operations to prevent secret key leakage in memory
    EncryptionManager(const EncryptionManager&) = delete;
    EncryptionManager& operator=(const EncryptionManager&) = delete;

    // Allow move operations
    EncryptionManager(EncryptionManager&&) noexcept = default;
    EncryptionManager& operator=(EncryptionManager&&) noexcept = default;

    // Instance Key Management
    void loadKey(const std::string& derivedKey);
    void clearKey();
    bool isMasterKeyLoaded() const;
    const std::string& getKey() const;

    // Cryptographic & Cipher Operations
    static std::string deriveKey(const std::string& masterPassword, const std::string& salt, int iterations);
    static std::string generateIV();
    static std::string encrypt(const std::string& plaintext, const std::string& key);
    static std::string decrypt(const std::string& b64Ciphertext, const std::string& key);

    // Encoding & Conversion Utilities
    static std::string bytesToHex(const unsigned char* bytes, size_t len);
    static std::vector<unsigned char> hexToBytes(const std::string& hex);
    static std::string toBase64(const std::vector<unsigned char>& data);
    static std::vector<unsigned char> fromBase64(const std::string& b64);

private:
    std::string m_key;
    bool m_unlocked{false};
};
