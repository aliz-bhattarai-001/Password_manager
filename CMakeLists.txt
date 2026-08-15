cmake_minimum_required(VERSION 3.16)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(PasswordManager
    src/main.cpp
    src/PasswordGenerator.cpp
    src/utilities.cpp
    src/HashManager.cpp
    src/EncryptionManager.cpp
    src/PasswordStrengthChecker.cpp
    src/Block.cpp
    src/Blockchain.cpp
    src/PasswordVault.cpp
    src/VaultManager.cpp
)

target_include_directories(PasswordManager PRIVATE include)
target_link_libraries(PasswordManager OpenSSL::SSL OpenSSL::Crypto nlohmann_json::nlohmann_json)
