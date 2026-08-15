#include "app_manager.hpp"
#include "ui/screens/screen_login.hpp"

void AppManager::init(std::string title, sf::Vector2u size) {
  fps = 60;
  window = sf::RenderWindow(sf::VideoMode(size), title);
  window.setFramerateLimit(fps);

  // ui manager
managerUi = UiManager(&window,"assets/Fonts/SFPRODISPLAYREGULAR.OTF");
  // managerUi.setScreen(std::make_unique<UserModeScreen>(this));

  auto login_screen = std::make_unique<LoginScreen>();
  login_screen->app = this;

  managerUi.setScreen(std::move(login_screen));

  // event manager
  managerEvent.window = &window;
}

void AppManager::run() {


  // while window is still open
  while (window.isOpen()) {
    // handle events
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else {
        managerEvent.handleEvent(event, this);
      }
    }

    // initialization here
    if (managerUi.changed_screen) {
      managerUi.current_screen->shaper(&window);
      managerUi.changed_screen = false;
    }

    // Per frame updates here
    managerUi.current_screen->updater();

    // fill window with color
    window.clear(sf::Color::White);

    // draw calls here
    // managerUi.currentDraw(); (pick some suitable name for the function)
    managerUi.current_screen->drawer(&window);
    // display
    window.display();
  }
}