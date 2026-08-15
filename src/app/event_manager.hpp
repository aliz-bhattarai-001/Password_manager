#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "ui/ui_manager.hpp"
#include "ui/widgets/button.hpp"

class AppManager;

class EventManager {
 public:
  sf::RenderWindow* window;
  std::vector<Button> buttons;
  void handleEvent(std::optional<sf::Event> e, AppManager* manager_app);
};

