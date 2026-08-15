#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "screens/screen_core.hpp"
#include "themes/theme_core.hpp"

class UiManager {
public:
	sf::RenderWindow* window;
	std::unique_ptr<Screen> current_screen;
	Theme current_theme = Theme::light();
	sf::Font current_font;
	bool changed_screen;

	UiManager();
	UiManager(sf::RenderWindow* win, std::string font_path);
	void setScreen(std::unique_ptr<Screen> next_screen);
	void setTheme(Theme next_theme);
};



