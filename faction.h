#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class FactionType { SolarisDominion, VoidbornAscendancy };

class Faction {
public:
    FactionType type;
    std::string name;
    sf::Color primaryColor;
    sf::Color accentColor;
    sf::String description;
    sf::String shortName;

    Faction(FactionType t);

    void applyToGame();        // bêdzie ustawiaæ kolory t³a, muzykê itp.
    sf::String getFlagSymbol() const;  // tymczasowa flaga tekstowa
};