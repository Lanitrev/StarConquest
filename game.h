#pragma once
#include <SFML/Graphics.hpp>
#include "Faction.h"
#include "Constants.h"
#include <vector>

struct GameEntity {  // placeholder dla wszystkich obiektów
    sf::Vector2f pos;
    sf::Color color;
    std::string type;   // "Base", "DronePlayer", "DroneEnemy"
    float size = 40.f;
    int supplyCost = 1;
};

class Game {
public:
    Game(Faction* playerFaction);
    void initStartingPosition(const std::string& startPoint = "North");  // Pó³noc, Wschód itd.
    void update();
    void handleInput(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    int getCurrentSupply() const { return currentSupply; }
    int getMaxSupply() const { return maxSupply; }
    void setStartingLocation(const std::string& location);  // "North", "East" itd.
    void handleMouseClick(sf::Vector2i mouse, const sf::RenderWindow& window);
    void collectResource();
    void buildStructure();
    void researchTech();
    void attackPlaceholder();
    void initRandomStart();   // losowy z 8 punktów
    void issueMoveCommand(sf::Vector2f target);  // rozkaz ruchu zaznaczonej jednostce
    void issueCommand(const std::string& command, sf::Vector2f target = { 0,0 });
    void stopCommand();
    void patrolCommand();
    sf::Vector2f screenToWorld(sf::Vector2i screenPos) const;
    void moveSelectedUnitTo(sf::Vector2f target);

private:
    Faction* playerFaction;
    std::vector<GameEntity> playerEntities;
    std::vector<GameEntity> neutralEntities;  // póŸniej surowce

    int currentSupply = 4;
    int maxSupply = START_SUPPLY;

    sf::View gameView;
    sf::RectangleShape background;  // kosmos

    void spawnBase(sf::Vector2f center);
    void spawnDrones(sf::Vector2f basePos, bool isPlayerFaction);
    sf::Vector2f cameraCenter = { 1000, 1000 };
    GameEntity* selectedEntity = nullptr;
    std::vector<GameEntity> resources;   // surowce

    enum class StartLocation { North, NE, East, SE, South, SW, West, NW };
    StartLocation currentStart = StartLocation::North;
    sf::RectangleShape selectionOutline;
};