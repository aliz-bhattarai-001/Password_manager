# pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Window configuration
namespace Window {
const unsigned int WIDTH  = 1200;
const unsigned int HEIGHT = 800;
const std::string TITLE   = "Password Manager";
const unsigned int FPS    = 60;
} // namespace Window

// Password manager Theme Colors
namespace Colors {

// Main Colors
const sf::Color PRIMARY_COLOR(15, 82, 87);          // #0F5257 Dark Teal
const sf::Color ACCENT_BLUE(11, 49, 66);            // #0B3142 Deep Space Blue
const sf::Color ACCENT_LILAC(156, 146, 163);        // #9C92A3 Lilac Ash
const sf::Color ACCENT_THISTLE(198, 185, 205);      // #C6B9CD Thistle
const sf::Color ACCENT_LAVENDER(214, 211, 240);     // #D6D3F0 Lavender


//Light theme colors
const sf::Color BACKGROUND(248, 249, 253);          // #F8F9FD
const sf::Color SURFACE(255, 255, 255);             // #FFFFFF
const sf::Color PANEL(242, 243, 250);               // #F2F3FA
const sf::Color CARD(236, 235, 247);                // #ECEBF7
const sf::Color BORDER(198, 185, 205);              // #C6B9CD

const sf::Color TEXT_PRIMARY(11, 49, 66);           // #0B3142
const sf::Color TEXT_SECONDARY(69, 82, 91);         // #45525B
const sf::Color TEXT_MUTED(110, 114, 128);          // #6E7280
const sf::Color TEXT_DISABLED(161, 167, 179);       // #A1A7B3


//Dark
const sf::Color DARK_BACKGROUND(7, 30, 38);         // #071E26
const sf::Color DARK_SURFACE(11, 49, 66);           // #0B3142
const sf::Color DARK_PANEL(18, 61, 80);             // #123D50
const sf::Color DARK_CARD(23, 72, 93);              // #17485D
const sf::Color DARK_MODAL(30, 85, 109);            // #1E556D

const sf::Color DARK_TEXT(245, 247, 250);           // #F5F7FA
const sf::Color DARK_TEXT_SECONDARY(217, 222, 229); // #D9DEE5
const sf::Color DARK_TEXT_MUTED(156, 146, 163);     // #9C92A3
const sf::Color DARK_BORDER(198, 185, 205);         // #C6B9CD


//Button Colors
const sf::Color BUTTON_HOVER(20, 105, 112);         // #146970
const sf::Color BUTTON_PRESSED(27, 124, 132);       // #1B7C84
const sf::Color LINK(214, 211, 240);                // Lavender


//Status Colors
const sf::Color SUCCESS(87, 204, 153);              // #57CC99
const sf::Color WARNING(246, 189, 96);              // #F6BD60
const sf::Color ERROR(231, 111, 81);                // #E76F51
const sf::Color DANGER(173, 40, 49);                // #AD2831
const sf::Color INFO(76, 201, 240);                 // #4CC9F0

}

// For fonts
namespace Fonts {

const std::string MAIN_FONT   = "assets/Fonts/SFPRODISPLAYREGULAR.OTF";
const std::string BOLD        = "assets/Fonts/SFPRODISPLAYBOLD.OTF";
const std::string ITALIC      = "assets/Fonts/SFPRODISPLAYLIGHTITALIC.OTF";
const std::string BOLD_ITALIC = "assets/Fonts/SFPRODISPLAYSEMIBOLDITALIC.OTF";


// Nested namespace for font sizes
namespace Sizes {
const unsigned int TITLE   = 50;
const unsigned int HEADING = 40;
const unsigned int BODY    = 22;
const unsigned int SMALL   = 18;
} 

}