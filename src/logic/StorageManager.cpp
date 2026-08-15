// #include "EncryptionManager.h"
// #include "StorageManager.h"

// bool StorageManager::saveVault(
//     const Vault& vault,
//     const std::string& key)
// {
//     std::string plaintext = vault.serialize();

//     std::string encrypted =
//         EncryptionManager::encrypt(
//             plaintext,
//             key);

//     auto tmp = path_;
//     tmp += ".tmp";

//     std::ofstream out(tmp, std::ios::binary);

//     if (!out)
//         return false;

//     out.write(
//         encrypted.data(),
//         encrypted.size());

//     out.close();

//     std::filesystem::rename(tmp, path_);

//     return true;
// }


// std::optional<Vault>
// StorageManager::loadVault(
//     const std::string& key)
// {
//     if (!vaultFileExists())
//         return std::nullopt;

//     std::ifstream in(path_, std::ios::binary);

//     std::string encrypted(
//         (std::istreambuf_iterator<char>(in)),
//         std::istreambuf_iterator<char>());

//     try {
//         std::string plaintext =
//             EncryptionManager::decrypt(
//                 encrypted,
//                 key);

//         return Vault::deserialize(plaintext);
//     }
//     catch (...) {
//         return std::nullopt;
//     }
// }