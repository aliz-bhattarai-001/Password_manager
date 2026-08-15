#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "rounded_rectangle.hpp"

class Button : public sf::Drawable, public sf::Transformable {
 public:
  struct Shape {
    sf::Vector2f origin;
    RoundedRectangleShape upper;
    RoundedRectangleShape lower;
    float offset_lower = 10.f;
  };
  struct Animation {
    bool isAnimating = false;
    float elasped_time = 0.f;
    float total_time = 0.2f;
  };

  Shape shape;
  Animation animation;
  sf::Text txt;
  float padding = 5.0f;
  sf::Vector2f size;
  std::function<void()> onClick; // function pointer for click event

  Button(sf::Vector2f size, sf::Text txt,
         std::function<void()> on_click = nullptr)
      : txt(std::move(txt)), size(size) ,onClick(on_click){

    shape.upper.setSize(size);
    shape.lower.setSize(size);
    shape.upper.setPosition({0.f, 0.f});
    shape.lower.setPosition({0.f, shape.offset_lower});

    sf::FloatRect b = this->txt.getLocalBounds();

    this->txt.setOrigin(
        {b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});

    this->txt.setPosition({0.f, 0.f});
  }

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    states.transform *= getTransform(); // kind of necessary to apply the transform of the button itself

    target.draw(shape.lower, states);
    target.draw(shape.upper, states);
    target.draw(txt, states);
  }

  void setFillColor(sf::Color upper, sf::Color lower) {
    shape.upper.setFillColor(upper);
    shape.lower.setFillColor(lower);
  }

  void changePosition(sf::Vector2f pos) {
     setPosition(pos); 
    }

  void changeSize(sf::Vector2f size) {
    this->size = size;
    shape.upper.setSize(size);
    shape.lower.setSize(size);
    shape.upper.setPosition({0.f, 0.f});
    shape.lower.setPosition({0.f, shape.offset_lower});
  }

  void fitText() {
    sf::FloatRect bRect = txt.getLocalBounds();

    txt.setOrigin({bRect.position.x + bRect.size.x / 2.f,
                   bRect.position.y + bRect.size.y / 2.f});

    float requiredX = bRect.size.x + 2.f * padding;
    float requiredY = bRect.size.y + 2.f * padding;

    if (requiredX > size.x) size.x = requiredX;

    if (requiredY > size.y) size.y = requiredY;

    shape.upper.setSize(size);
    shape.lower.setSize(size);
    shape.upper.setPosition({0.f, 0.f});
    shape.lower.setPosition({0.f, shape.offset_lower});
  }

  sf::FloatRect getLocalBounds() const {
    return {{-size.x / 2.f, -size.y / 2.f},
            {size.x, size.y + shape.offset_lower}};
  }

 // To get the global bounds of the button, 
 // we can use the getTransform() method to apply the button's transform to its local bounds. 
 // This will give us the global bounds of the button in the window's coordinate system.
  sf::FloatRect getGlobalBounds() const {
    return getTransform().transformRect(getLocalBounds());
  }

  void setAnimationTime(float seconds) { animation.total_time = seconds; }
};