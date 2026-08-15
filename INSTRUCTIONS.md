# Password Manager

## Build and Setup Instructions

---

# 1. Overview

This project is a cross-platform Password Manager built with:

- C++17
- SFML 3
- OpenSSL
- nlohmann/json
- CMake

Supported platforms:

- Linux
- macOS

---

# 2. System Requirements

## Linux

Required packages:

### Fedora

```bash
sudo dnf install \
    gcc-c++ \
    cmake \
    git \
    openssl-devel
```

### Ubuntu / Debian

```bash
sudo apt update

sudo apt install \
    build-essential \
    cmake \
    git \
    libssl-dev
```

### Arch Linux

```bash
sudo pacman -S \
    base-devel \
    cmake \
    git \
    openssl
```

---

## macOS

Install Xcode Command Line Tools:

```bash
xcode-select --install
```

Install required packages:

```bash
brew install \
    cmake \
    git \
    openssl
```


---

# 3. Setup Dependencies

First give execution permission to the scripts:
```bash
# From the root directory run
chmod +x *.sh
chmod +x ./builders/*.sh
```

Then Run:

```bash
./build.sh setup
```

The setup script will:

- Verify required tools exist
- Verify OpenSSL is installed
- Download SFML 3.0.2
- Download nlohmann/json

Result:

```text
vendor/
├── SFML/
└── json/
```

---

# 5. Build the Project

## Debug Build

```bash
./build.sh d
```

Output:

```text
build/debug/bin/PasswordManager
```

---

## Release Build

```bash
./build.sh b
```

Output:

```text
build/release/bin/PasswordManager
```

---

# 6. Running the Application

## Debug Build

```bash
./build/debug/bin/PasswordManager
```

---

## Release Build

```bash
./build/release/bin/PasswordManager
```

---

# 7. Cleaning Build Files

Remove all generated build files:

```bash
./build.sh clean
```

---

# 8. Rebuilding

## Rebuild Debug

```bash
./build.sh rebuild-debug
```

## Rebuild Release

```bash
./build.sh rebuild-release
```

---

# 9. Troubleshooting

## OpenSSL Not Found

Linux:

```bash
pkg-config --modversion openssl
```

macOS:

```bash
brew install openssl
```

---

## SFML Include Errors

If VS Code shows:

```text
#include errors detected.
Please update your includePath.
```

Build the project once:

```bash
./build.sh d
```

This generates:

```text
build/debug/compile_commands.json
```

Configure VS Code:

```json
{
    "C_Cpp.default.compileCommands":
    "${workspaceFolder}/build/debug/compile_commands.json"
}
```

---

## Dependency Setup Failed

Delete vendor libraries:

```bash
rm -rf vendor/SFML
rm -rf vendor/json
```

Run setup again:

```bash
./build.sh setup
```

---

## Full Clean Rebuild

```bash
./build.sh clean

./build.sh setup

./build.sh d
```

