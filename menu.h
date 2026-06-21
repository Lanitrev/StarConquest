#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "HUD.h"
#include "Faction.h"
#include <vector>

enum class GameState { MainMenu, FactionSelect, OptionsMenu, Playing };

struct Star {
    sf::Vector2f position;
    float size = 1.0f;
    sf::Color color;
    float speed = 1.0f;
};

class Menu {
public:
    Menu();
    void handleEvents(sf::RenderWindow& window, sf::Event& event, GameState& currentState);
    void update(sf::Vector2i mousePos, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, const GameState& currentState);
    void resetStars(const sf::Vector2u& size);

private:
    sf::Font font;
    std::vector<Star> stars;

    sf::Text title;
    sf::Text btnNewGame, btnOptions, btnExit;
    sf::Text btnSolaris, btnVoidborn;
    sf::Text description;
    sf::Text btnStart, btnBack;
    sf::Text btnVSync, btnBackOptions;

    Faction* selectedFaction = nullptr;
    HUD hud;

    bool selectedSolaris = true;
    bool vSyncEnabled = true;
    float titleOffset = 0.0f;
};