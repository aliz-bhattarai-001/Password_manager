#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>
#include <string>
#include <optional>
class Screen {
public:
	std::string id = "";  // use id as a name for the screen

	virtual ~Screen() = default;
	virtual void shaper(sf::RenderWindow* window) = 0;
	virtual void drawer(sf::RenderWindow* window) = 0;
	virtual void eventInitiator(std::optional<sf::Event> event) = 0;
	virtual void updater() = 0;
};
