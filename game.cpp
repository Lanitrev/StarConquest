#include "game.h"
#include "constants.h"
#include <iostream>

Game::Game() {
    gameView.reset(sf::FloatRect(0, 0, 2000, 2000));
    cameraPos = {1000, 1000};
}

void Game::initGame(FactionType playerFaction) {
    this->playerFaction = playerFaction;
    createStartingBaseAndUnits();
    std::cout << "[GAME] Gra zainicjowana dla frakcji: " << (playerFaction == FactionType::SolarisDominion ? "Ziemianie (3 drony)" : "Obcy (1 dron)") << std::endl;
}

void Game::createStartingBaseAndUnits() {
    playerUnits.clear();

    // Główna baza - duży kwadrat w centrum punktu startowego
    Entity base;
    base.position = {1000, 1000};
    base.size = 80;
    base.type = "Base";
    base.color = (playerFaction == FactionType::SolarisDominion) ? SOLARIS_COLOR : VOIDBORN_COLOR;
    playerUnits.push_back(base);

    if (playerFaction == FactionType::SolarisDominion) {
        // 3 drony Ziemian - trójkąty
        for(int i = 0; i < 3; i++) {
            Entity drone;
            drone.position = {1000 + 100 + i*60.f, 1000};
            drone.size = 25;
            drone.type = "Drone";
            drone.color = sf::Color(100, 220, 255);
            playerUnits.push_back(drone);
        }
    } else {
        // 1 dron Obcych - romb/kolo placeholder
        Entity drone;
        drone.position = {1100, 1050};
        drone.size = 30;
        drone.type = "AlienDrone";
        drone.color = sf::Color(220, 50, 255);
        playerUnits.push_back(drone);
    }

    maxSupply = 8;
    currentSupply = 4; // baza + drony

    std::cout << "[GAME] Start: Baza + drony utworzone. Supply: " << currentSupply << "/" << maxSupply << std::endl;
}

void Game::update() {
    // później animacje, AI itp.
}

void Game::draw(sf::RenderWindow& window) {
    window.setView(gameView);
    
    // Tło kosmosu + grid
    sf::RectangleShape background(sf::Vector2f(4000, 4000));
    background.setFillColor(sf::Color(5, 5, 15));
    window.draw(background);

    // Prosty grid
    sf::VertexArray grid(sf::Lines, 82);
    for (int i = 0; i < 41; ++i) {
        // vertical
        grid[2*i].position = sf::Vector2f(i*100, 0);
        grid[2*i].color = sf::Color(40,40,60);
        grid[2*i+1].position = sf::Vector2f(i*100, 4000);
        grid[2*i+1].color = sf::Color(40,40,60);
    }

    window.draw(grid);

    // Rysowanie jednostek
    for(const auto& e : playerUnits) {
        if(e.type == "Base") {
            sf::RectangleShape baseShape(sf::Vector2f(e.size, e.size));
            baseShape.setPosition(e.position - sf::Vector2f(e.size/2, e.size/2));
            baseShape.setFillColor(e.color);
            baseShape.setOutlineColor(sf::Color::White);
            baseShape.setOutlineThickness(4);
            window.draw(baseShape);
        } else {
            // Drony jako trójkąty/koła
            sf::CircleShape drone(e.size);
            drone.setPosition(e.position - sf::Vector2f(e.size, e.size));
            drone.setFillColor(e.color);
            drone.setOutlineColor(sf::Color::Yellow);
            drone.setOutlineThickness(2);
            window.draw(drone);
        }
    }

    // Minimap placeholder lub info
    window.setView(window.getDefaultView());
}

void Game::handleInput(const sf::Event& event, const sf::Vector2i& mousePos) {
    // do późniejszego użycia (drag mapy, selection)
}