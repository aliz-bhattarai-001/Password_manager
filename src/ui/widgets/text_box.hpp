#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include <vector>

class TextBox : public sf::Drawable, public sf::Transformable {
 public:
  TextBox(sf::Vector2f size, const sf::Font& font) : size(size), font(font) {
    box.setSize(size);
    box.setFillColor(sf::Color::White);
    box.setOutlineThickness(2.f);
    box.setOutlineColor(sf::Color(180, 180, 180));
    rebuild();
  };

  void handleEvent(const std::optional<sf::Event>& event) {
    if (!event || !focused) return;
    if (event->is<sf::Event::TextEntered>()) {
      const sf::Event::TextEntered* e = event->getIf<sf::Event::TextEntered>();
      char32_t c = e->unicode;

      if (c == 8)  // backspace
      {
        if (!value.empty()) value.pop_back();
      } else if (c >= 32) {
        value.push_back(static_cast<char>(c));
      }
      rebuild();
    }
  }

  void setFocused(bool f) {
    focused = f;
    box.setOutlineColor(focused ? sf::Color::Blue : sf::Color(180, 180, 180));
  }

  bool isFocused() const { return focused; }

  sf::FloatRect getGlobalBounds() const {
    return getTransform().transformRect(box.getGlobalBounds());
  }

  std::string getValue() const { return value; }

  void setPassword(bool p) {
    isPassword = p;
    rebuild();
  }

  void setCharacterSize(unsigned int s) {
    charSize = s;
    rebuild();
  }

 private:
  sf::RectangleShape box;
  sf::Vector2f size;

  const sf::Font& font;

  std::string value;
  std::vector<sf::Text> lines;

  bool focused = false;
  bool isPassword = false;

  unsigned int charSize = 18;
  float padding = 8.f;

  void rebuild() {
    lines.clear();
    std::string display = isPassword ? std::string(value.size(), '*') : value;

    float maxWidth = size.x - padding * 2.f;
    std::string currentLine;

    for (char c : display) {
      std::string test = currentLine + c;
      sf::Text measure(font, test, charSize);

      if (measure.getGlobalBounds().size.x > maxWidth) {
        lines.emplace_back(font, currentLine, charSize);
        currentLine = c;
      } else {
        currentLine = test;
      }
    }
    if (!currentLine.empty()) lines.emplace_back(font, currentLine, charSize);

    // overflow check
    float lineH = charSize + 6.f;
    float maxHeight = size.y - padding * 2.f;

    if (lines.size() * lineH > maxHeight && !value.empty()) {
      value.pop_back();
      rebuild();
    }
  }

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    states.transform *= getTransform();

    target.draw(box, states);

    float x = padding;
    float y = padding;

    for (size_t i = 0; i < lines.size(); i++) {
      sf::Text text = lines[i];
      text.setFillColor(sf::Color::Black);
      text.setPosition({x, y + i * (charSize + 6.f)});
      target.draw(text, states);
    }
  }
};