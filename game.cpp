#include "Game.h"
#include <iostream>

Game::Game(Faction* pf) : playerFaction(pf) {
    gameView.reset(sf::FloatRect(0, 0, 1920, 1080));
    gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    background.setSize(sf::Vector2f(MAP_WIDTH, MAP_HEIGHT));
    background.setFillColor(sf::Color(10, 10, 30));
    background.setPosition(0, 0);

    initRandomStart();

    selectionOutline.setFillColor(sf::Color::Transparent);
    selectionOutline.setOutlineColor(sf::Color::White);
    selectionOutline.setOutlineThickness(4);
}

void Game::initStartingPosition(const std::string& startPoint) {
    sf::Vector2f startPos = START_POS_NORTH;  // na razie Północ, później switch po stringu

    spawnBase(startPos);
    spawnDrones(startPos, true);   // 3 Ziemskie + 1 Obcy
    currentSupply = 4;
    maxSupply = START_SUPPLY;
    std::cout << "[Game] Start w punkcie: " << startPoint << " | Supply: " << currentSupply << "/" << maxSupply << std::endl;
}

void Game::spawnBase(sf::Vector2f center) {
    GameEntity base;
    base.pos = center;
    base.color = playerFaction->primaryColor;
    base.type = "Base";
    base.size = 80.f;
    playerEntities.push_back(base);
}

void Game::spawnDrones(sf::Vector2f basePos, bool isPlayer) {
    // 3 drony Ziemskie
    for (int i = 0; i < 3; ++i) {
        GameEntity d;
        d.pos = basePos + sf::Vector2f(80 + i * 60, 60);
        d.color = sf::Color(100, 255, 100);
        d.type = "DronePlayer";
        d.size = 28.f;
        playerEntities.push_back(d);
    }
    // 1 dron Obcy
    GameEntity alien;
    alien.pos = basePos + sf::Vector2f(100, -60);
    alien.color = sf::Color(255, 80, 80);
    alien.type = "DroneEnemy";  // na razie neutralny do testu
    alien.size = 28.f;
    playerEntities.push_back(alien);
}

void Game::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    // na razie puste – później strzałki, zoom
}

void Game::draw(sf::RenderWindow& window) {
    window.setView(gameView);
    window.draw(background);

    // rysujemy jednostki
    for (const auto& e : playerEntities) {
        if (e.type == "Base") {
            sf::RectangleShape rect(sf::Vector2f(e.size, e.size));
            rect.setPosition(e.pos);
            rect.setFillColor(e.color);
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(4);
            window.draw(rect);
        }
        else {
            sf::CircleShape tri(e.size / 2.f, 3);
            tri.setPosition(e.pos);
            tri.setFillColor(e.color);
            window.draw(tri);
        }
    }

    // PODŚWIETLENIE ZAZNACZONEJ (poza pętlą – teraz działa)
    if (selectedEntity) {
        selectionOutline.setSize(sf::Vector2f(selectedEntity->size * 1.3f, selectedEntity->size * 1.3f));
        selectionOutline.setPosition(selectedEntity->pos - sf::Vector2f(selectedEntity->size * 0.15f, selectedEntity->size * 0.15f));
        window.draw(selectionOutline);
    }

    // surowce
    for (const auto& r : resources) {
        sf::CircleShape diamond(r.size / 2, 4);
        diamond.setPosition(r.pos);
        diamond.setFillColor(r.color);
        window.draw(diamond);
    }

    // Supply + instrukcja (reszta bez zmian)
    sf::Font font;
    font.loadFromFile("assets/Audiowide-Regular.ttf");
    sf::Text supplyText;
    supplyText.setFont(font);
    supplyText.setString("SUPPLY: " + std::to_string(currentSupply) + "/" + std::to_string(maxSupply));
    supplyText.setCharacterSize(28);
    supplyText.setFillColor(sf::Color::Yellow);
    supplyText.setPosition(50, 30);
    window.setView(window.getDefaultView());
    window.draw(supplyText);

    sf::Text info("Strzałki = kamera | LPM = zaznacz | PPM = rozkaz ruchu | B = budowa | C = zbieranie", font, 18);
    info.setPosition(20, window.getSize().y - 30);
    window.setView(window.getDefaultView());
    window.draw(info);
}

void Game::setStartingLocation(const std::string& location) {
    playerEntities.clear();
    resources.clear();
    sf::Vector2f pos = START_POS_NORTH;
    if (location == "East") pos = START_POS_EAST;
    if (location == "South") pos = START_POS_SOUTH;
    if (location == "West") pos = START_POS_WEST;
    spawnBase(pos);
    spawnDrones(pos, true);
    for (int i = 0; i < 3; ++i) {
        GameEntity r;
        r.pos = pos + sf::Vector2f(250 + i * 140, 180);
        r.color = sf::Color(255, 215, 0);
        r.type = "Mineral";
        r.size = 32.f;
        resources.push_back(r);
    }
    std::cout << "[Game] Start w punkcie: " << location << " | Supply: " << currentSupply << "/" << maxSupply << std::endl;
}

void Game::update() {
    // kamera (strzałki)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  cameraCenter.x -= 8;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) cameraCenter.x += 8;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    cameraCenter.y -= 8;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  cameraCenter.y += 8;

    gameView.setCenter(cameraCenter);
}

void Game::collectResource() {
    currentSupply += 3;
    if (currentSupply > maxSupply) currentSupply = maxSupply;
    std::cout << "Zebrano surowce! Supply: " << currentSupply << "/" << maxSupply << std::endl;
}

void Game::buildStructure() {
    maxSupply += 25;
    if (maxSupply > MAX_SUPPLY) maxSupply = MAX_SUPPLY;
    std::cout << "Zbudowano strukturę! Max Supply: " << maxSupply << std::endl;
    // później dodamy obiekt budynku na mapie
}

void Game::researchTech() {
    std::cout << "Badania rozpoczęte (placeholder) - odblokowano ulepszenia dronów" << std::endl;
    // później zwiększy damage/speed
}

void Game::attackPlaceholder() {
    std::cout << "Placeholder walki - dron Obcy atakuje (później pełna walka)" << std::endl;
}

void Game::initRandomStart() {
    std::string locations[8] = { "North", "NorthEast", "East", "SouthEast", "South", "SouthWest", "West", "NorthWest" };
    int randIdx = rand() % 8;
    setStartingLocation(locations[randIdx]);
    cameraCenter = playerEntities[0].pos;  // kamera na bazę
    gameView.setCenter(cameraCenter);
    std::cout << "[Game] Losowy start: " << locations[randIdx] << std::endl;
}

void Game::issueMoveCommand(sf::Vector2f target) {
    if (selectedEntity) {
        selectedEntity->pos = target;
        std::cout << "➡️ Rozkaz RUCHU do (" << target.x << ", " << target.y << ")" << std::endl;
    }
}

void Game::handleMouseClick(sf::Vector2i mouseScreen, const sf::RenderWindow& window) {
    sf::Vector2f worldPos = window.mapPixelToCoords(mouseScreen, gameView);  // <--- KLUCZOWE – z widokiem
    std::cout << "[Debug] Klik w świecie: (" << worldPos.x << ", " << worldPos.y << ")" << std::endl;

    // ZAZNACZANIE JEDNOSTEK
    for (auto& e : playerEntities) {
        float dx = e.pos.x - worldPos.x;
        float dy = e.pos.y - worldPos.y;
        if (dx * dx + dy * dy < e.size * e.size * 1) {
            selectedEntity = &e;
            std::cout << "✅ ZAZNACZONO: " << e.type << std::endl;
            return;
        }
    }

    // ZEBRANIE SUROWCA
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        float dx = it->pos.x - worldPos.x;
        float dy = it->pos.y - worldPos.y;
        if (dx * dx + dy * dy < it->size * it->size * 1) {
            std::cout << "⛏️ Zebrano surowiec!" << std::endl;
            collectResource();
            resources.erase(it);
            return;
        }
    }

    std::cout << "Kliknięto pustkę" << std::endl;
}

void Game::issueCommand(const std::string& command, sf::Vector2f target) {
    if (selectedEntity) {
        if (command == "Move") {
            selectedEntity->pos = target;
            std::cout << "➡️ Rozkaz RUCHU wykonany" << std::endl;
        }
        else if (command == "Attack") {
            std::cout << "⚔️ Rozkaz ATAKU na wroga wykonany" << std::endl;
        }
    }
}

void Game::stopCommand() {
    std::cout << "⛔ Rozkaz STOP – jednostka zatrzymana" << std::endl;
}

void Game::patrolCommand() {
    std::cout << "🔄 Rozkaz PATROL – jednostka patroluje między punktami" << std::endl;
}

sf::Vector2f Game::screenToWorld(sf::Vector2i screenPos, sf::RenderWindow& win) const {
    return win.mapPixelToCoords(screenPos, gameView);
}

void Game::moveSelectedUnitTo(sf::Vector2f target) {
    if (selectedEntity) {
        selectedEntity->pos = target;
        std::cout << "➡️ Jednostka przemieszczona dokładnie do ("
            << target.x << ", " << target.y << ")" << std::endl;
    }
}