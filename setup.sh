#!/usr/bin/env bash

set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "$0")" && pwd)"
VENDOR_DIR="$PROJECT_ROOT/vendor"

SFML_VERSION="3.0.2"

echo "===================================="
echo " PasswordManager Setup"
echo "===================================="
echo

#
# Verify required tools
#
for tool in git cmake; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "ERROR: Missing required tool: $tool"
        exit 1
    fi
done

#
# Verify compiler
#
if command -v g++ >/dev/null 2>&1; then
    COMPILER="g++"
elif command -v clang++ >/dev/null 2>&1; then
    COMPILER="clang++"
else
    echo "ERROR: No C++ compiler found."
    exit 1
fi

echo "[OK] Compiler : $COMPILER"
echo "[OK] Git"
echo "[OK] CMake"

#
# Verify OpenSSL
#
if ! pkg-config --exists openssl 2>/dev/null; then

    echo
    echo "OpenSSL development package not found."
    echo

    case "$(uname -s)" in

        Linux)
            echo "Fedora:"
            echo "  sudo dnf install openssl-devel"
            echo
            echo "Ubuntu/Debian:"
            echo "  sudo apt install libssl-dev"
            echo
            echo "Arch:"
            echo "  sudo pacman -S openssl"
            ;;

        Darwin)
            echo "macOS:"
            echo "  brew install openssl"
            ;;

    esac

    exit 1
fi

mkdir -p "$VENDOR_DIR"

#
# SFML
#
if [ ! -d "$VENDOR_DIR/SFML" ]; then

    echo
    echo "Downloading SFML ${SFML_VERSION}..."

    git clone \
        --depth 1 \
        --branch "${SFML_VERSION}" \
        https://github.com/SFML/SFML.git \
        "$VENDOR_DIR/SFML"

else

    echo "[OK] SFML already installed"

fi

echo
echo "Setup complete."