# Password Manager

A Password Manager built in C++ using:

- SFML 3
- OpenSSL
- nlohmann/json
- Modern CMake

This repository uses local vendored dependencies for:

- SFML
- nlohmann/json

and system-installed OpenSSL.

---

## Quick Start
First give execution permission to the scripts:
```bash
# From the root directory run
chmod +x *.sh
chmod +x ./builders/*.sh
```
Run dependency setup:

```bash
./build.sh setup
```

Build the project:

```bash
./build.sh d
```

Run the application:

```bash
./build/debug/bin/PasswordManager
```

---

## Documentation

Complete setup, build, dependency and troubleshooting instructions are available in:

📖 **[INSTRUCTIONS.md](./INSTRUCTIONS.md)**

---

## Build Commands

### Setup Dependencies

```bash
./build.sh setup
```

### Debug Build

```bash
./build.sh d
```

### Release Build

```bash
./build.sh b
```

### Clean Build Files

```bash
./build.sh clean
```

---

## Project Structure

```text
Password_manager/
├── assets/
├── builders/
├── docs/
├── include/
├── src/
├── vendor/
├── build.sh
├── setup.sh
├── CMakeLists.txt
└── INSTRUCTIONS.md
└── README.md
```

For detailed information, see:

📖 **INSTRUCTIONS.md**