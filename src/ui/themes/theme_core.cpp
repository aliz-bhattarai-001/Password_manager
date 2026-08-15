#include "theme_core.hpp"
#include "../ui_configurations.hpp"


// colors used from ui_configurations.hpp to set up the light and dark themes
Theme Theme::light()
{
    Theme theme;

    theme.colorPrimary   = Colors::PRIMARY_COLOR;
    theme.colorSecondary = Colors::ACCENT_BLUE;
    theme.colorTertiary  = Colors::ACCENT_LILAC;

    theme.colorAccent      = Colors::ACCENT_LAVENDER;
    theme.colorHighlight   = Colors::ACCENT_LAVENDER;
    theme.colorInteractive = Colors::PRIMARY_COLOR;
    theme.colorPressed     = Colors::BUTTON_PRESSED;

    theme.colorSurface = Colors::SURFACE;
    theme.colorPanel   = Colors::PANEL;
    theme.colorCard    = Colors::CARD;
    theme.colorModal   = Colors::SURFACE;

    theme.colorBorder = Colors::BORDER;

    theme.colorText          = Colors::TEXT_PRIMARY;
    theme.colorTextSecondary = Colors::TEXT_SECONDARY;
    theme.colorTextMuted     = Colors::TEXT_MUTED;
    theme.colorTextDisabled  = Colors::TEXT_DISABLED;

    theme.colorBackground = Colors::BACKGROUND;

    theme.colorSuccess = Colors::SUCCESS;
    theme.colorWarning = Colors::WARNING;
    theme.colorError   = Colors::ERROR;
    theme.colorDanger  = Colors::DANGER;
    theme.colorInfo    = Colors::INFO;

    theme.sizeFontS = Fonts::Sizes::SMALL;
    theme.sizeFontM = Fonts::Sizes::BODY;
    theme.sizeFontL = Fonts::Sizes::HEADING;

    return theme;
}

// same as above but for dark theme
Theme Theme::dark()
{
    Theme theme;

    theme.colorPrimary   = Colors::PRIMARY_COLOR;
    theme.colorSecondary = Colors::DARK_SURFACE;
    theme.colorTertiary  = Colors::ACCENT_LILAC;

    theme.colorAccent      = Colors::ACCENT_LAVENDER;
    theme.colorHighlight   = Colors::DARK_CARD;
    theme.colorInteractive = Colors::ACCENT_LAVENDER;
    theme.colorPressed     = Colors::BUTTON_PRESSED;

    theme.colorSurface = Colors::DARK_SURFACE;
    theme.colorPanel   = Colors::DARK_PANEL;
    theme.colorCard    = Colors::DARK_CARD;
    theme.colorModal   = Colors::DARK_MODAL;

    theme.colorBorder = Colors::DARK_BORDER;

    theme.colorText          = Colors::DARK_TEXT;
    theme.colorTextSecondary = Colors::DARK_TEXT_SECONDARY;
    theme.colorTextMuted     = Colors::DARK_TEXT_MUTED;
    theme.colorTextDisabled  = Colors::TEXT_DISABLED;

    theme.colorBackground = Colors::DARK_BACKGROUND;

    theme.colorSuccess = Colors::SUCCESS;
    theme.colorWarning = Colors::WARNING;
    theme.colorError   = Colors::ERROR;
    theme.colorDanger  = Colors::DANGER;
    theme.colorInfo    = Colors::INFO;

    theme.sizeFontS = Fonts::Sizes::SMALL;
    theme.sizeFontM = Fonts::Sizes::BODY;
    theme.sizeFontL = Fonts::Sizes::HEADING;

    return theme;
}