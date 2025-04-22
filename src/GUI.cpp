#include <SFML/Graphics.hpp>
#include "GUI.h"

sf::Text createText(const sf::Font& font, const std::string& String,
int CharSize, sf::Color color, unsigned int style) {
    sf::Text text;
    text.setFont(font);
    text.setString(String);
    text.setCharacterSize(CharSize);
    text.setFillColor(color);
    text.setStyle(style);
    return text;
}

void setText(sf::Text& text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2,
        textRect.top + textRect.height / 2);
    text.setPosition(sf::Vector2f(x, y));
}

std::string openWindow(float width, float height) {
    sf::RenderWindow Screen(sf::VideoMode(width, height), "Password Checker", sf::Style::Close);

    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text Title = createText(font, "Password Checker", 20, sf::Color::Black, (sf::Text::Bold | sf::Text::Underlined));
    setText(Title, width/2.0f, height/2.0f - 150.0f);

    sf::Text EnterPassword = createText(font, "Enter your password", 20, sf::Color::Black, (sf::Text::Bold));
    setText(EnterPassword, width/2.0f, height/2.0f - 75.0f);

    std::string StringPass;
    char a = '|';
    StringPass += a;

    // Keeps screen open for the bulk of the stuff
    while (Screen.isOpen()) {
        sf::Event event;
        while (Screen.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Screen.close();
                break;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (StringPass.length() > 1) {
                        StringPass.pop_back();
                        StringPass.pop_back();
                        char a = '|';
                        StringPass += a;
                    }
                } else if (event.key.code == sf::Keyboard::Enter) {
                    // If Password is between 1 and 30
                    if (StringPass.length() > 1) {
                        StringPass.pop_back();
                        return StringPass;
                    }
                } else {
                    if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z && (StringPass.size() <= 30)) {
                        StringPass.pop_back();
                        char c = 'A' + (event.key.code - sf::Keyboard::A);
                        StringPass += c;
                        char a = '|';
                        StringPass += a;
                    }
                }
            }
        }
        sf::Text Password = createText(font, StringPass, 18, sf::Color::Yellow, sf::Text::Bold);
        setText(Password, width / 2.0f, height / 2.0f - 45);

        Screen.clear(sf::Color::Blue);
        Screen.draw(Title);
        Screen.draw(EnterPassword);
        Screen.draw(Password);
        Screen.display();

    }
}

CheckButton::CheckButton(sf::Texture& texture) : CheckButtonTexture(texture) {
    CheckButtonSprite.setTexture(CheckButtonTexture);
}

void CheckButton::setPosition(float width, float height) {
    CheckButtonSprite.setPosition(width / 2.0f, height / 2.0f);
}

bool CheckButton::isChecked(const sf::Vector2f& mousePos) const {
    return CheckButtonSprite.getGlobalBounds().contains(mousePos);
}

