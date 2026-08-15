#include "event_manager.hpp"

#include "app_manager.hpp"
#include "ui/screens/screen_core.hpp"

class AppManager;
void EventManager::handleEvent(std::optional<sf::Event> e,
                               AppManager* manager_app) {
  if (manager_app->managerUi.current_screen) {
    manager_app->managerUi.current_screen->eventInitiator(e);
  }
}
