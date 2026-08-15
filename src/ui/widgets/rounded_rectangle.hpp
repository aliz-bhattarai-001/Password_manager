#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
class RoundedRectangleShape : public sf::Shape {
 protected:
  sf::Vector2f size;
  float radiusCorner;  // in percentage (0-0.5)

  size_t nPoints;  // consists of circle points
  float radius;
  float nScale = 2.f;  // scaler to reduce/increase number of points

 public:
  void updatePointCount() {
    radius = (size.x < size.y ? size.x : size.y) * radiusCorner;
    size_t circlePoints = (radius > 0 ? int(sqrtf(radius)) : 1) * 4 * nScale;
    circlePoints = circlePoints >= 8 ? circlePoints : 8;
    nPoints =
        circlePoints % 4 == 0 ? circlePoints : circlePoints + circlePoints % 4;
  }

  RoundedRectangleShape() : size({0, 0}), radiusCorner(0.1) {
    updatePointCount();
    update();
  }

  RoundedRectangleShape(sf::Vector2f size, float rad_corner = 0.1)
      : size(size), radiusCorner(rad_corner) {
    updatePointCount();
    update();
  }

  void setRadiusCorner(float rad) {
    radiusCorner = rad;
    updatePointCount();
    update();
  }

  void setSize(sf::Vector2f size) {
    this->size = size;
    updatePointCount();
    update();
  }

  std::size_t getPointCount() const override { return nPoints; }

  sf::Vector2f getPoint(std::size_t index) const override {
    static constexpr float pi = 3.141592654f;

    size_t num_corner_points = nPoints / 4;
    size_t& ncp = num_corner_points;
    float step_angle = (pi / 2.f) / (ncp - 1.f);
    float a = size.x / 2 - radius;
    float b = size.y / 2 - radius;

    sf::Vector2f req_point;
    if (index < 1 * ncp) {
      float angle = -pi / 2.f + (index - 0) * step_angle;
      req_point = {a + radius * std::cos(angle), -b + radius * std::sin(angle)};
    } else if (index < 2 * ncp) {
      float angle = 0.f + (index - 1 * ncp) * step_angle;
      req_point = {a + radius * std::cos(angle), b + radius * std::sin(angle)};
    } else if (index < 3 * ncp) {
      float angle = pi / 2.f + (index - 2 * ncp) * step_angle;
      req_point = {-a + radius * std::cos(angle), b + radius * std::sin(angle)};
    } else if (index < 4 * ncp) {
      float angle = pi + (index - 3 * ncp) * step_angle;
      req_point = {-a + radius * std::cos(angle), -b + radius * std::sin(angle)};
    }

    return req_point;
  }
};