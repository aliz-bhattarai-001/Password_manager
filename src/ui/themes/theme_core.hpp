#pragma once

#include <SFML/Graphics/Color.hpp>

class Theme {
 public:

 // main colors
  sf::Color colorPrimary;
  sf::Color colorSecondary;
  sf::Color colorTertiary;

  // button and other accent colors
  sf::Color colorAccent;
  sf::Color colorHighlight;
  sf::Color colorInteractive;
  sf::Color colorPressed;

  // cards modals and stuff
  sf::Color colorSurface;
  sf::Color colorPanel;
  sf::Color colorCard;
  sf::Color colorModal;

  // for border colors
  sf::Color colorBorder;

  // Text for colors
  sf::Color colorText;
  sf::Color colorTextSecondary;
  sf::Color colorTextMuted;
  sf::Color colorTextDisabled;

  // For background colors
  sf::Color colorBackground;

  // colors for status messages
  sf::Color colorSuccess;
  sf::Color colorWarning;
  sf::Color colorError;
  sf::Color colorDanger;
  sf::Color colorInfo;

  // to toggle between light and dark themes
  static Theme light();
  static Theme dark();

  int sizeFontS;
  int sizeFontM;
  int sizeFontL;
};