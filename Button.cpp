#include "Button.h"

Button::Button(const std::string& mesaj, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
    text.setString(mesaj);
    text.setCharacterSize(charSize);
    text.setFillColor(textColor);
    button.setSize(size);
    button.setFillColor(bgColor);
}

void Button::setFont(sf::Font &font) {
    text.setFont(font);
}

void Button::setBgColor(sf::Color color) {
    button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
    text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f pos) {
    button.setPosition(pos);
    float xPos = (pos.x + button.getLocalBounds().width / 3) - text.getLocalBounds().width / 2;
    float yPos = (pos.y + button.getLocalBounds().height / 5) - text.getLocalBounds().height / 2;
    text.setPosition(xPos, yPos);
}

void Button::drawTo(sf::RenderWindow &window) {
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow &window) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float btnPosX = button.getPosition().x;
    float btnPosY = button.getPosition().y;

    float btnPosXW = btnPosX + button.getLocalBounds().width;
    float btnPosYH = btnPosY + button.getLocalBounds().height;

    return mouseX < btnPosXW and mouseX > btnPosX and
            mouseY < btnPosYH and mouseY > btnPosY;
}

std::string Button::getText() {
    return text.getString();
}
