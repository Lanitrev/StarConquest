#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "faction.h"

struct Entity {
    sf::Vector2f position;
    float size;
    sf::Color color;
    std::string type; // "Base", "Drone"
};

class Game {
public:
    Game();
    void initGame(FactionType playerFaction);
    void update();
    void draw(sf::RenderWindow& window);
    void handleInput(const sf::Event& event, const sf::Vector2i& mousePos);

private:
    std::vector<Entity> playerUnits;
    std::vector<Entity> resources;
    sf::View gameView;
    sf::Vector2f cameraPos;
    FactionType playerFaction;
    int currentSupply = 4; // start
    int maxSupply = 8;

    void createStartingBaseAndUnits();
};