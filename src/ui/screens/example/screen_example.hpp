// #pragma once

// #include <SFML/Graphics.hpp>

// #include "ui/screens/screen_core.hpp"
// #include "ui/widgets/button.hpp"
// #include "ui/widgets/floating_box.hpp"
// #include "ui/widgets/rounded_rectangle.hpp"
// #include "ui/widgets/text_box.hpp"

// class AppManager;

// // These two functions are for handling animation of buttons, you can make your
// // own, But probably just copying them in your own screen will be easier since
// // it handles it good enough
// void init_button_animation(std::vector<Button>& buttons,
//                            sf::Vector2f pos_mouse);
// void update_button_animation(std::vector<Button>& buttons, float fps);

// // Actual Screen , make sure it inherits from public Screen
// // Also you must at least create all the function (functions that have override
// // in them) here even if they are empty inside
// class ExampleScreen : public Screen {
//  public:
//   AppManager* app = nullptr;

//   std::vector<RoundedRectangleShape> roundedRects;
//   std::vector<Button> buttons;
//   std::vector<TextBox> textboxes;
//   std::vector<FloatingBox> floatingboxes;

//   float fps = 60.f;
//   sf::Font font;

//   //// declare the pointer in here ///////
//   FloatingBox* passwordLimitPtr;
//   FloatingBox* otherErrorPtr;

//   int num = 0;
//   //////////// when time to display make it true ///////////
//   bool display_pass_floater = false;
//   bool display_other_floater = false;

//   void shaper(sf::RenderWindow* window) override {
//     roundedRects.clear();
//     buttons.clear();
//     floatingboxes.clear();

//     RoundedRectangleShape rect = {{500, 500}, 0.15f};
//     rect.setFillColor(sf::Color(51, 51, 51));
//     rect.setPosition((sf::Vector2f)(window->getSize()) * 0.5f);

//     if (font.openFromFile("assets/fonts/SFPRODISPLAYREGULAR.OTF"))
//       ;
//     sf::Text txt1(font);
//     sf::Text txt2(font);

//     txt1.setCharacterSize(18);
//     txt1.setFillColor(sf::Color::White);
//     txt1.setString("Aliz said Carpe diem and ,say yess and move on");
//     Button btn = {{100, 50}, txt1, [] {
//                     std::cout << "I did something bro" << std::endl;
//                   }};
//     btn.setFillColor(sf::Color(120, 120, 120), sf::Color(100, 100, 100));
//     btn.setPosition((sf::Vector2f)(window->getSize()) * 0.5f);
//     btn.fitText();

//     txt2.setString("Continue");
//     Button btn2 = {{100, 50}, txt2, [] {
//                      std::cout << "I did something bro 2" << std::endl;
//                    }};
//     btn2.setFillColor(sf::Color(130, 80, 30), sf::Color(110, 60, 10));
//     btn2.setPosition((sf::Vector2f)(window->getSize()) * 0.75f);
//     btn2.fitText();
//     btn2.animation.total_time = 0.1;
//     btn2.animation.elasped_time = 0.1;

//     // text box use
//     if (textboxes.empty()) {
//       TextBox username({300.f, 100.f}, font);
//       username.setPosition({100.f, 350.f});
//       textboxes.push_back(username);

//       TextBox passwordBox({300.f, 40.f}, font);
//       passwordBox.setPosition({100.f, 100.f});
//       passwordBox.setPassword(true);
//       textboxes.push_back(passwordBox);
//     }

//     sf::Text txt3(font);
//     txt3.setString("Submit");
//     Button submitBtn = {{100, 50}, txt3, [this]() {
//                           std::string username = textboxes[0].getValue();

//                           std::cout << "Name: " << username << std::endl;
//                         }};
//     submitBtn.setFillColor(sf::Color(50, 150, 50), sf::Color(30, 130, 30));
//     submitBtn.setPosition({100, 500});
//     submitBtn.fitText();
//     buttons.push_back(submitBtn);
//     roundedRects.push_back(rect);
//     buttons.push_back(btn);
//     buttons.push_back(btn2);

//     /////// Example of the floating msg box
//     sf::Text pass_warn(font);
//     pass_warn.setString(std::string("Password size limit reached"));
//     FloatingBox passwordLimit(pass_warn, true);
//     passwordLimit.setPos();  // if u donot give the data the position has its
//                              // default at top center
//     passwordLimit
//         .setOpacLev();  // if u donot give the data the level is 50 by default
//     floatingboxes.push_back(passwordLimit);
//     passwordLimitPtr = &floatingboxes.back();

//     sf::Text other_warn(font);
//     other_warn.setString(std::string("Put the error in here!!!"));
//     FloatingBox otherWarning(
//         other_warn, false);  //////// pass the text object in here and choice to
//                              /// whether to set the warning sticker or not
//     otherWarning.setPos(sf::Vector2f(100, 100));
//     otherWarning.setOpacLev(70);
//     floatingboxes.push_back(otherWarning);
//     otherErrorPtr = &floatingboxes.back();
//   }

//   void drawer(sf::RenderWindow* window) override {
//     for (RoundedRectangleShape& rrs : roundedRects) {
//       window->draw(rrs);
//     }
//     for (Button& b : buttons) {
//       window->draw(b);
//     }
//     for (TextBox& tb : textboxes) window->draw(tb);

//     int butn_no = 0;
//     for (FloatingBox& fb : floatingboxes) {
//       if (butn_no == 0) {
//         if (display_pass_floater) window->draw(fb);
//       }
//       if (butn_no == 1) {
//         if (display_other_floater) window->draw(fb);
//       }
//       butn_no++;
//     }
//   }

//   void eventInitiator(std::optional<sf::Event> event) {
//     if (event->is<sf::Event::MouseButtonPressed>()) {
//       sf::Vector2f pos_mouse =
//           (sf::Vector2f)event->getIf<sf::Event::MouseButtonPressed>()->position;
//       events(buttons, pos_mouse);
//       for (TextBox& tb : textboxes) tb.setFocused(false);

//       for (TextBox& tb : textboxes) {
//         if (tb.getGlobalBounds().contains(pos_mouse)) {
//           tb.setFocused(true);
//           break;
//         }
//       }
//       init_button_animation(buttons, pos_mouse);
//     }
//     // text input
//     for (TextBox& tb : textboxes) tb.handleEvent(event);
//   }

//   void events(std::vector<Button>& buttons, sf::Vector2f pos_mouse) {
//     int button_no = 0;
//     for (Button& butn : buttons) {
//       if (butn.getGlobalBounds().contains(pos_mouse)) {
//         //////////////////////////////////////////////////////
//         //////// initiating the flaoting box in here /////////
//         //////// you initialze where it see fits in  /////////
//         //////// same way as this one, this is just  /////////
//         //////// a example to show                   /////////
//         //////////////////////////////////////////////////////
//         if (button_no == 0) {
//           if (!display_pass_floater) {
//             std::cout << "hey dude i reached in here" << std::endl;
//             display_pass_floater = true;
//             passwordLimitPtr->startTimer();
//           }
//         }
//         if (button_no == 1) {
//           if (!display_other_floater) {
//             display_other_floater = true;
//             otherErrorPtr->startTimer();
//           }
//         }
//       }
//       button_no++;
//     }
//   }

//   void updater() override {
//     // button animation and the floating animation
//     update_button_animation(buttons, fps);

//     ////// checking if the timer is done /////////
//     static float time = 0;
//     static float time_sum = 0;
//     if (display_pass_floater) {
//       // std::cout << time_sum + ++time*(1.f/60.f) << " seconds" << std::endl;
//       if (passwordLimitPtr->checkTime(5.f)) {
//         std::cout << "reached here";
//         display_pass_floater = false;
//       }
//     }
//     if (display_other_floater) {
//       if (otherErrorPtr->checkTime()) {  // default is the 2  seconsd
//         display_other_floater = false;
//       }
//     }
//   }
//   for (TextBox& tb : textboxes) window->draw(tb);
// }

//   void eventInitiator(std::optional<sf::Event> event) {
//   if (event->is<sf::Event::MouseButtonPressed>()) {
//     sf::Vector2f pos_mouse =
//         (sf::Vector2f)event->getIf<sf::Event::MouseButtonPressed>()->position;
//     for (TextBox& tb : textboxes) tb.setFocused(false);

//     for (TextBox& tb : textboxes) {
//       if (tb.getGlobalBounds().contains(pos_mouse)) {
//         tb.setFocused(true);
//         break;
//       }
//     }
//     init_button_animation(buttons, pos_mouse);
//   }
//   // text input
//   for (TextBox& tb : textboxes) tb.handleEvent(event);
// };

// void updater() override {
//   // button animation for now, add per frame updates here
//   update_button_animation(buttons, fps);
// };

// // animation of the buttons
// void init_button_animation(std::vector<Button>& buttons,
//                            sf::Vector2f pos_mouse) {
//   for (Button& b : buttons) {
//     if (b.getGlobalBounds().contains(pos_mouse) &&
//         b.animation.isAnimating == false) {
//       b.animation.isAnimating = true;
//       b.animation.elasped_time = 0.f;
//       b.onClick();
//     }
//   }
// }
// void update_button_animation(std::vector<Button>& buttons, float fps) {
//   for (Button& b : buttons) {
//     if (!b.animation.isAnimating) continue;

//     float prct = (b.animation.total_time - b.animation.elasped_time) /
//                  b.animation.total_time;

//     float offset = 0.f;

//     if (prct < 0.5f) {
//       offset = 2.f * prct * b.shape.offset_lower;
//     } else if (prct < 1.0f) {
//       offset = 2.f * (1.f - prct) * b.shape.offset_lower;
//     }

//     b.shape.upper.setPosition({0.f, offset});
//     b.txt.setPosition({0.f, offset});

//     b.animation.elasped_time += 1.f / fps;

//     if (b.animation.elasped_time >= b.animation.total_time) {
//       b.animation.isAnimating = false;
//       b.animation.elasped_time = 0.f;

//       b.shape.upper.setPosition({0.f, 0.f});
//       b.txt.setPosition({0.f, 0.f});
//     }
//   }
// }