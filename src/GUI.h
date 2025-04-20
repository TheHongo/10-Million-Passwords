#ifndef GUI_H
#define GUI_H

#include <string>
#include <SFML/Graphics.hpp>

class Screen {
private:
    sf::Text createText(const sf::Font& font, const std::string& String, int CharSize, sf::Color color, unsigned int style);
    void setText(sf::Text& text, float x, float y);
public:
    std::string openWindow(float width, float height);
};

class CheckButton {
private:
    sf::Sprite CheckButtonSprite;
    const sf::Texture& CheckButtonTexture;
public:
    CheckButton(sf::Texture& texture);
    void setPosition(float width, float height);
    bool isChecked(const sf::Vector2f& mousePos) const;
};

#endif