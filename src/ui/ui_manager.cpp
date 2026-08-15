#include "ui_manager.hpp"

UiManager::UiManager() {}

UiManager::UiManager(sf::RenderWindow* win, std::string font_path)
    : current_font(font_path) {
    window = win;
}

void UiManager::setScreen(std::unique_ptr<Screen> next_screen) {
    current_screen = std::move(next_screen);
    changed_screen = true;
}

void UiManager::setTheme(Theme next_theme) {
    current_theme = next_theme;
    changed_screen = true;
}
