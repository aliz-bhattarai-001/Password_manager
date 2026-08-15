#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include <vector>

#include "app/app_manager.hpp"
#include "ui/screens/screen_core.hpp"
#include "ui/themes/theme_core.hpp"
#include "ui/ui_configurations.hpp"
#include "ui/widgets/button.hpp"
#include "ui/widgets/rounded_rectangle.hpp"
#include "ui/widgets/text_box.hpp"

void init_button_animation(std::vector<Button>& buttons,
                           sf::Vector2f pos_mouse);
void update_button_animation(std::vector<Button>& buttons, float fps);

class LoginScreen : public Screen {
 private:
  sf::RenderWindow* m_window = nullptr;

 public:
  Theme theme;
  Theme thm;

  AppManager* app = nullptr;

  std::vector<RoundedRectangleShape> rrs;
  std::vector<Button> buttons;
  std::vector<TextBox> text_fields;
  std::vector<sf::Text> texts;

  sf::Font fontB;
  sf::Font fontN;

  float fps = 60.f;

  void shaper(sf::RenderWindow* window) override {
    if (!window) return;
    m_window = window;  // Keep track of the window context
    if (app) thm = app->managerUi.current_theme;

    // resetting the vectors
    rrs.clear();
    buttons.clear();
    text_fields.clear();
    texts.clear();

    (void)fontB.openFromFile(Fonts::BOLD);
    (void)fontN.openFromFile(Fonts::MAIN_FONT);

    sf::Vector2f view_size = window->getView().getSize();
    sf::Vector2f center = {view_size.x * 0.5f, view_size.y * 0.5f};

    sf::Vector2f size_container = {450.f, 440.f};

    // setting up the container
    RoundedRectangleShape container(size_container, 0.1f);
    container.setPosition(center);
    container.setFillColor(thm.colorPrimary);
    rrs.push_back(container);

    // label for the login screen
    sf::Text label(fontB, "Welcome to the Password Manager");
    label.setCharacterSize(28);
    sf::FloatRect labelBounds = label.getLocalBounds();
    label.setOrigin({labelBounds.size.x * 0.5f, labelBounds.size.y * 0.5f});
    label.setPosition({center.x, center.y - 300.f});
    label.setFillColor(thm.colorPrimary);
    texts.push_back(label);


    // Title text center calculation
    sf::Text title(fontB, "Signup / Login");
    title.setCharacterSize(28);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin({titleBounds.size.x * 0.5f, titleBounds.size.y * 0.5f});
    title.setPosition({center.x, center.y - 150.f});
    texts.push_back(title);

    
    // Username textbox
    sf::Text text_username(fontN, "Username");
    text_username.setCharacterSize(18);
    text_username.setPosition({center.x - 150.f, center.y - 80.f});

    // textbox for username
    TextBox username({300.f, 40.f}, fontN);
    username.setPosition({center.x - 150.f, center.y - 55.f});

    texts.push_back(text_username);
    text_fields.push_back(username);

    // Password textbox
    sf::Text text_pass(fontN, "Password");
    text_pass.setCharacterSize(18);
    text_pass.setPosition({center.x - 150.f, center.y + 20.f});

    // textbox for password
    TextBox password({300.f, 40.f}, fontN);
    password.setPosition({center.x - 150.f, center.y + 45.f});
    password.setPassword(true);

    texts.push_back(text_pass);
    text_fields.push_back(password);

    // Register button
    sf::Text txt0(fontB, "Signup", 22);
    txt0.setFillColor(thm.colorText);
    Button regst({140.f, 40.f}, txt0);
    regst.setFillColor(thm.colorCard, thm.colorSuccess);
    regst.setPosition({center.x - 80.f, center.y + 140.f});

    // passing the username and password to the onClick function via lambda func
    regst.onClick = [this]() {
      std::string username = text_fields[0].getValue();
      std::string password = text_fields[1].getValue();
    };
    buttons.push_back(regst);

    // Login button
    sf::Text txt(fontB, "Login", 22);
    txt.setFillColor(thm.colorText);
    Button login({140.f, 40.f}, txt);
      login.setFillColor(thm.colorCard, thm.colorSuccess);
    login.setPosition({center.x + 80.f, center.y + 140.f});
    // same as above .onClick
    login.onClick = [this]() {
      std::string username = text_fields[0].getValue();
      std::string password = text_fields[1].getValue();
    };
    buttons.push_back(login);
  }


  // this is where  where the drawing occurs
  void drawer(sf::RenderWindow* window) override {
    window->clear(thm.colorBackground);

    for (auto& r : rrs) window->draw(r);                // draw all rounded rectangles from the vector
    for (auto& tb : text_fields) window->draw(tb);      // same for text fields
    for (auto& tx : texts) window->draw(tx);            // same for texts
    for (auto& b : buttons) window->draw(b);            // same for buttons
  }

  // Overriding the eventInitiator function to handle events
  void eventInitiator(std::optional<sf::Event> event) override {
    if (!event || !m_window) return;

    // handling window resize event 
    if (event->is<sf::Event::Resized>()) {
      auto* e = event->getIf<sf::Event::Resized>();
      sf::FloatRect visibleArea({0.f, 0.f}, {static_cast<float>(e->size.x),
                                             static_cast<float>(e->size.y)});
      m_window->setView(sf::View(visibleArea));
      shaper(m_window);
    }

    // handling mouse button pressed event 
    if (event->is<sf::Event::MouseButtonPressed>()) {
      auto* e = event->getIf<sf::Event::MouseButtonPressed>();

      sf::Vector2i mouse_pixel_pos = {e->position.x, e->position.y};
      sf::Vector2f pos = m_window->mapPixelToCoords(
          mouse_pixel_pos);  // Maps coordinates properly

      for (auto& tb : text_fields) tb.setFocused(false);

      for (auto& tb : text_fields) {
        if (tb.getGlobalBounds().contains(pos)) {
          tb.setFocused(true);
          break;
        }
      }

      init_button_animation(buttons, pos);
    }
    // the text boxes handle the text input events t
    // we just pass the event  
    for (auto& tb : text_fields) tb.handleEvent(event);
  }

  // updater function to update the button animations
  void updater() override { update_button_animation(buttons, fps); }
};

// Animation procedures
void init_button_animation(std::vector<Button>& buttons,
                           sf::Vector2f pos_mouse) {
  for (Button& b : buttons) {
    if (b.getGlobalBounds().contains(pos_mouse) && !b.animation.isAnimating) {
      b.animation.isAnimating = true;
      b.animation.elasped_time = 0.f;
      b.onClick();
    }
  }
}

// button animation update function
void update_button_animation(std::vector<Button>& buttons, float fps) {
  for (Button& b : buttons) {
    if (!b.animation.isAnimating) continue;

    float prct = (b.animation.total_time - b.animation.elasped_time) /
                 b.animation.total_time;
    float offset = 0.f;

    // Calculate the offset based on the percentage of elapsed time
    if (prct < 0.5f) {
      offset = 2.f * prct * b.shape.offset_lower;
    } else if (prct < 1.0f) {
      offset = 2.f * (1.f - prct) * b.shape.offset_lower;
    }

    // changes the position of the button's upper shape and text based on the calculated offset
    b.shape.upper.setPosition({0.f, offset});
    b.txt.setPosition({0.f, offset});

    b.animation.elasped_time += 1.f / fps;

    // if the elapsed time exceeds the total animation time, reset the animation state and positions
    if (b.animation.elasped_time >= b.animation.total_time) {
      b.animation.isAnimating = false;
      b.animation.elasped_time = 0.f;
      b.shape.upper.setPosition({0.f, 0.f});
      b.txt.setPosition({0.f, 0.f});
    }
  }
}