cmake_minimum_required(VERSION 3.21)

project(
    PasswordManager
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# Dependencies
#

find_package(OpenSSL REQUIRED)

add_subdirectory(
    "${CMAKE_SOURCE_DIR}/vendor/SFML"
    "${CMAKE_BINARY_DIR}/vendor/sfml"
)

#
# Sources
#

file(
    GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)


#
# Executable
#

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

#
# Includes
#

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE

        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/src"

        "${CMAKE_SOURCE_DIR}/src/app"
        "${CMAKE_SOURCE_DIR}/src/logic"
        "${CMAKE_SOURCE_DIR}/src/ui"

        "${CMAKE_SOURCE_DIR}/src/ui/screens"
        "${CMAKE_SOURCE_DIR}/src/ui/themes"
        "${CMAKE_SOURCE_DIR}/src/ui/widgets"
)

#
# Warnings
#

if(MSVC)

    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
        /W4
    )

else()

    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

endif()

#
# Link Libraries
#

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE

        SFML::Graphics
        SFML::Window
        SFML::System

        OpenSSL::SSL
        OpenSSL::Crypto
)

#
# Copy assets after build
#

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)

#
# Output directory
#

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES

    RUNTIME_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/bin"

    RUNTIME_OUTPUT_DIRECTORY_DEBUG
        "${CMAKE_BINARY_DIR}/bin"

    RUNTIME_OUTPUT_DIRECTORY_RELEASE
        "${CMAKE_BINARY_DIR}/bin"
)