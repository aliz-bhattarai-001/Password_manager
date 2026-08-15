#pragma once

// include major systems
#include <SFML/Graphics.hpp>
#include "event_manager.hpp"
#include "ui/ui_manager.hpp"

class AppManager {
 public:
  // window related
  sf::RenderWindow window;
  float fps;

  
  // managers
  UiManager managerUi; 
  EventManager managerEvent; 


  void init(std::string title, sf::Vector2u size);
  void run();
};