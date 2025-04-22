#include <SFML/Graphics.hpp>
#include "GUI.h"
#include <chrono>

#include <iostream>
using namespace std;

sf::Text Screen::createText(const sf::Font& font, const std::string& String,
int CharSize, sf::Color color, unsigned int style) {
    sf::Text text;
    text.setFont(font);
    text.setString(String);
    text.setCharacterSize(CharSize);
    text.setFillColor(color);
    text.setStyle(style);
    return text;
}

void Screen::setText(sf::Text& text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2,
        textRect.top + textRect.height / 2);
    text.setPosition(sf::Vector2f(x, y));
}
void Screen::openWindow(float width, float height) {
    sf::RenderWindow Screen(sf::VideoMode(width, height), "Password Checker", sf::Style::Close);

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    // Load Check Button texture
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("Images/Check.png")) {
        std::cerr << "Error loading button texture!" << std::endl;
        return;
    }

    // Create CheckButton
    CheckButton checkButton(buttonTexture, width, height);

    // Set up title and instruction text
    sf::Text Title = createText(font, "Password Checker", 40, sf::Color::Black, (sf::Text::Bold | sf::Text::Underlined));
    setText(Title, width / 2.0f, height / 2.0f - 200.0f);

    sf::Text EnterPassword = createText(font, "Enter your password", 24, sf::Color::Black, sf::Text::Bold);
    setText(EnterPassword, width / 2.0f, height / 2.0f - 100.0f);

    std::string password = processEvents(Screen, font, Title, EnterPassword, width, height, checkButton); // Pass the button for handling
}

std::string Screen::processEvents(sf::RenderWindow& Screen, sf::Font& font,
    sf::Text& Title, sf::Text& EnterPassword, float width, float height, CheckButton& checkButton) {

    History history;

    std::string currentInput = "|"; // Including '|' initially for visual
    std::string lastPassword = "";  // Store the password
    bool passwordReceived = false; // Flag to check if password is received

    while (Screen.isOpen()) {
        sf::Event event;
        while (Screen.pollEvent(event)) {
            std::cout << event.type << std::endl;
            if (event.type == sf::Event::Closed) {
                Screen.close();
                exit(0); //done
//                return ""; // Window was closed
            }

            if (event.type == sf::Event::TextEntered) {
                handleTextEnteredEvent(event, currentInput, lastPassword, passwordReceived, history);
            }

            // Check if the check button was clicked
            if (event.type == sf::Event::MouseButtonPressed) {
                handleMousePressedEvent(event, currentInput, lastPassword, passwordReceived, history, checkButton);
            }
        }

        // Draw UI
        sf::Text PasswordText = createText(font, currentInput, 18, sf::Color::Black, sf::Text::Bold);
        setText(PasswordText, width / 2.0f, height / 2.0f - 45);

        // Call upon one of the other functions and if found print found or not
        sf::Text LastEntered = createText(font, "Last Password: " + lastPassword, 16, sf::Color::Blue, sf::Text::Italic);
        setText(LastEntered, width / 2.0f, height / 2.0f + 40);

        // Fix to change to check rank
        // If found display rank else diplay N/A
        sf::Text PasswordReceivedText;
        if (passwordReceived) {
            std::cout << "begening" << std::endl;
            PasswordReceivedText = createText(font, "Password Received", 16, sf::Color::Green, sf::Text::Bold);
            setText(PasswordReceivedText, width / 2.0f, height / 2.0f + 75); // Position below the last entered password
            auto start = std::chrono::high_resolution_clock::now();
            int trie_rank = trie.search(lastPassword);
            auto end = std::chrono::high_resolution_clock::now();
            trie_time = end - start;
            start = std::chrono::high_resolution_clock::now();
            int hash_rank = hash.search(lastPassword);
            end = std::chrono::high_resolution_clock::now();
            hash_time = end - start;
            std::cout << "hello" << std::endl;
            if (trie_rank != hash_rank){
                std::cout << "Wrong rank found" << "\nHash Rank: " << hash_rank << "\nTrie Rank: " << trie_rank << std::endl;
            }
            if (trie_rank != -1){
                // not valid
            }
            else {
                // assign rank and put on screen
            }
            std::cout << "end near" << std::endl;
            passwordReceived = false;

        }

        // Makes the background for the text
        sf::FloatRect textBounds = PasswordText.getGlobalBounds();
        sf::RectangleShape backgroundRect;
        backgroundRect.setSize(sf::Vector2f(400, textBounds.height + 20));
        backgroundRect.setFillColor(sf::Color::Yellow);
        backgroundRect.setOrigin(backgroundRect.getSize().x / 2, backgroundRect.getSize().y / 2);
        backgroundRect.setPosition(PasswordText.getPosition()); // Same center as text

        // Draws everything out
        Screen.clear(sf::Color(160, 160, 160));
        Screen.draw(Title);
        Screen.draw(EnterPassword);
        Screen.draw(backgroundRect);
        Screen.draw(PasswordText);
        Screen.draw(LastEntered);
        if (passwordReceived) {
            Screen.draw(PasswordReceivedText); // Draw the "Password Received" message
        }
        Screen.draw(checkButton.CheckButtonSprite); // Draw the check button
        history.drawHistory(Screen, font, 10.0f, height - 20.0f);
        Screen.display();
    }

    return lastPassword; // Return the password when the check button is clicked
}

void Screen::handleTextEnteredEvent(const sf::Event& event, std::string& currentInput,
    std::string& lastPassword, bool& passwordReceived, History& history) {

    if (event.text.unicode == 8) { // Backspace
        if (currentInput.length() > 1) {
            currentInput.pop_back(); // remove '|'
            currentInput.pop_back(); // remove last char
            currentInput += '|';     // re-add '|'
        }
    } else if (event.text.unicode == 13) { // Enter
        if (currentInput.length() > 1) {
            lastPassword = currentInput.substr(0, currentInput.size() - 1); // Remove '|'
            history.addPassword(lastPassword);
            currentInput = "|";
            passwordReceived = true;
        }
    } else if ((event.text.unicode > 32 && event.text.unicode < 127) && currentInput.size() <= 30) {
        currentInput.pop_back(); // remove '|'
        currentInput += static_cast<char>(event.text.unicode);
        currentInput += '|';
    }
}

void Screen::handleMousePressedEvent(const sf::Event& event, std::string& currentInput,
    std::string& lastPassword, bool& passwordReceived, History& history, CheckButton& checkButton) {

    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (checkButton.isChecked(mousePos)) {
            if (currentInput.length() > 1) {
                lastPassword = currentInput.substr(0, currentInput.size() - 1);
                history.addPassword(lastPassword);
                currentInput = "|";
                passwordReceived = true;
            }
        }
    }
}

Screen::Screen(Trie &trie, Hash_Table_LL_Chaining &hash) {
    this->trie = trie;
    this->hash = hash;
}


CheckButton::CheckButton(sf::Texture& texture, float width, float height) : CheckButtonTexture(texture) {
    CheckButtonSprite.setTexture(CheckButtonTexture);

    sf::FloatRect bounds = CheckButtonSprite.getLocalBounds();
    CheckButtonSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    CheckButtonSprite.setPosition(width / 2.0f, height / 2.0f);

}

bool CheckButton::isChecked(const sf::Vector2f& mousePos) const {
    return CheckButtonSprite.getGlobalBounds().contains(mousePos);
}

void History::addPassword(const std::string& password) {
    passwordHistory.push_back(password);
    if (passwordHistory.size() > maxSize) {
        passwordHistory.erase(passwordHistory.begin());
    }
}

void History::drawHistory(sf::RenderWindow& window, const sf::Font& font, float startX, float startY) {
    sf::Text title("Recent Passwords:", font, 14);
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setPosition(startX, startY - (20.0f * (passwordHistory.size() + 1)));
    window.draw(title);

    for (std::size_t i = 0; i < passwordHistory.size(); ++i) {
        std::size_t index = passwordHistory.size() - 1 - i; // reverse index
        sf::Text entry(passwordHistory[index], font, 14);
        entry.setFillColor(sf::Color::Black);
        entry.setPosition(startX, startY - (i * 20.0f));
        window.draw(entry);
    }
}
