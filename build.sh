#!/usr/bin/env bash

set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

case "${1:-}" in

    setup)
        "$PROJECT_ROOT/setup.sh"
        ;;

    d)
        "$PROJECT_ROOT/builders/build-debug.sh"
        ;;

    b)
        "$PROJECT_ROOT/builders/build-release.sh"
        ;;

    clean)
        rm -rf "$PROJECT_ROOT/build"
        echo "Build directory removed."
        ;;

    rebuild-debug)
        rm -rf "$PROJECT_ROOT/build/debug"
        "$PROJECT_ROOT/builders/build-debug.sh"
        ;;

    rebuild-release)
        rm -rf "$PROJECT_ROOT/build/release"
        "$PROJECT_ROOT/builders/build-release.sh"
        ;;

    *)
        echo "Usage:"
        echo "  ./build.sh setup"
        echo "  ./build.sh d"
        echo "  ./build.sh b"
        echo "  ./build.sh clean"
        echo "  ./build.sh rebuild-debug"
        echo "  ./build.sh rebuild-release"
        exit 1
        ;;
esac