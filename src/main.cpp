// library
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>

#include "app/app_manager.hpp"

// main program
int main() {
  AppManager app;
  app.init("Password Manager", {1200, 800});
  app.run();
  return 0;
}