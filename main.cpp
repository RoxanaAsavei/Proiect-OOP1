#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include <iostream>
#include "grid.h"
#include "dice.h"

class Token {
private:
    std::string color;
    std::pair<int, int> current_position;
    int movement;
    bool is_home;
    sf::Sprite token;

public:
    Token() = default;
    Token(const std::string& color_, std::pair<int, int> current_position_, int movement_ = 0, bool is_home_ = 0) : color(color_), current_position(current_position_), movement(movement_), is_home(is_home_) {
        std::cout << "Constructor initializare token\n";
    }
    Token(const Token& other) : color(other.color), current_position(other.current_position), movement(other.movement), is_home(other.is_home) {
        std::cout << "Constructor de copiere token \n";
    }
    // operatorul egal
    Token& operator =(const Token& other) {
        this->color = other.color;
        this->current_position = other.current_position;
        this->movement = other.movement;
        this->is_home = other.is_home;
        return *this;
    }
    // destructorul
    ~Token() = default;
    // operatorul <<
    friend std::ostream& operator <<(std::ostream& os, const Token& token);
};

std::ostream& operator <<(std::ostream& os, const Token& token) {
    os << token.color << "\n";
    os << token.current_position.first << " " << token.current_position.second << "\n";
    os << token.movement << "\n";
    os << token.is_home << "\n";
    return os;
}

class Yard {
private:
    std::string color;
    int remaining_tokens; // the no of tokens inside the yard
    std::pair<int, int> left_corner;
    std::pair<int, int> right_corner;

public:
    // constructor fara parametri
    Yard() = default;
    // constructor cu parametri
    Yard(const std::string& color_, int remaining_tokens_, std::pair<int, int> left_corner_, std::pair <int, int> right_corner_) :
            color(color_), remaining_tokens(remaining_tokens_), left_corner(left_corner_), right_corner(right_corner_) {}
    // constructor de copiere
    Yard(const Yard& other) : color(other.color), remaining_tokens(other.remaining_tokens), left_corner(other.left_corner), right_corner(other.right_corner) {}
    // op =
    Yard& operator =(const Yard& other) {
        this->color = other.color;
        this->remaining_tokens = other.remaining_tokens;
        this->left_corner = other.left_corner;
        this->right_corner = other.right_corner;
        return *this;
    }
    // destructor
    ~Yard() {};
    // op <<
    friend std::ostream& operator <<(std::ostream& os, const Yard& yard);
};

// afisare pt yard
std::ostream& operator <<(std::ostream& os, const Yard& yard) {
    os << yard.color << "\n";
    os << yard.remaining_tokens << "\n";
    os << yard.left_corner.first << " " << yard.left_corner.second << "\n";
    os << yard.right_corner.first << " " << yard.right_corner.second << "\n";
    return os;
}

/*
class Dice {
public:
    int Roll() {
        return rand() % 6 + 1; // tb revazut, a dat de 3 ori consecutiv 6 ??
    }
};
 */

class Player{
private:
    Yard yard;
    std::string color;
    Token token1, token2, token3, token4;
public:
    // constructor fara parametri
    Player() = default;
    // costructor cu parametri
    Player(const Yard& yard_, const std::string& color_, const Token& token1_, const Token& token2_, const Token& token3_, const Token& token4_) : yard(yard_),
                                                                                                         color(color_), token1(token1_), token2(token2_), token3(token3_), token4(token4_) {}
    // constructor de copiere
    Player(const Player& other) : yard(other.yard), color(other.color), token1(other.token1),
                                  token2(other.token2), token3(other.token3), token4(other.token4) {}
    // operatorul =
    Player& operator =(const Player& other) {
        this->yard = other.yard;
        this->color = other.color;
        this->token1 = other.token1;
        this->token2 = other.token2;
        this->token3 = other.token3;
        this->token4 = other.token4;
        return *this;
    }
    // destructor
    ~Player() {}
    // op <<
    friend std::ostream& operator <<(std::ostream& os, const Player& player);
};

// afisare player
std::ostream& operator <<(std::ostream& os, const Player& player) {

    os << "Yard details\n";
    os << player.yard << "\n";
    os << "Color: " << player.color << "\n";
    os << "Tokens details" << "\n";
    os << player.token1 << "\n";
    os << player.token2 << "\n";
    os << player.token3 << "\n";
    os << player.token4 << "\n";
    return os;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(900, 900), "Ludo Game", sf::Style::Close | sf::Style::Titlebar);
    const int squareSize = 60; // size of each square
    const sf::Color ligth_yellow = sf::Color(253, 253, 150);
    const sf::Color ligth_blue = sf::Color(137, 207, 240);
    const sf::Color ligth_green = sf::Color(175, 225, 175);
    const sf::Color ligth_red = sf::Color(222, 49, 99);
    Grid grid(window, squareSize, sf::Color(60,179,113) , sf::Color(255, 255, 0), sf::Color(220, 20, 60),
              sf::Color(0, 191, 255), ligth_green, ligth_yellow, ligth_red, ligth_blue);
    grid.draw();

    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}
