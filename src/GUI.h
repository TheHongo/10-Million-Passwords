#ifndef GUI_H
#define GUI_H

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>

#include "Trie.h"
#include "Hash_Table_LL_Chaining.h"

using namespace std;

class CheckButton {
private:
    const sf::Texture& CheckButtonTexture;
public:
    sf::Sprite CheckButtonSprite;
    CheckButton(sf::Texture& texture, float width, float height);
    bool isChecked(const sf::Vector2f& mousePos) const;
};

class History {
private:
    vector<string> passwordHistory;
    const size_t maxSize = 5;

public:
    void addPassword(const string& password);
    void drawHistory(sf::RenderWindow& window, const sf::Font& font, float startX, float startY);
};

class Screen {
    Trie trie;
    Hash_Table_LL_Chaining hash;
    std::chrono::high_resolution_clock::duration trie_time;
    std::chrono::high_resolution_clock::duration hash_time;

public:
    Screen(Trie& trie, Hash_Table_LL_Chaining& hash);
    sf::Text createText(const sf::Font& font, const string& String, int CharSize,
                    sf::Color color, unsigned int style);
    void setText(sf::Text& text, float x, float y);
    void openWindow(float width, float height);
    string processEvents(sf::RenderWindow& Screen, sf::Font& font, sf::Text& Title,
                                sf::Text& EnterPassword, float width, float height,
                                CheckButton& checkButton); // Handle events
    void handleTextEnteredEvent(const sf::Event& event, string& currentInput,
                                string& lastPassword, bool& passwordReceived, History& history);
    void handleMousePressedEvent(const sf::Event& event, string& currentInput,
                                 string& lastPassword, bool& passwordReceived,
                                 History& history, CheckButton& checkButton);
    CheckButton* checkButton;
};

#endif