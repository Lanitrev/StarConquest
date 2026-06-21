#include "Menu.h"
#include "HUD.h"
#include "Game.h"
#include <cmath>
#include <iostream>

HUD hud;

Menu::Menu()
{
    if (!font.loadFromFile("assets/Audiowide-Regular.ttf"))
        font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    resetStars(sf::Vector2u(1920, 1080));

    title = sf::Text(TXT_TITLE, font, 100);
    title.setFillColor(sf::Color(80, 180, 255));
    title.setStyle(sf::Text::Bold);

    btnNewGame = sf::Text(TXT_NEW_GAME, font, 55);
    btnOptions = sf::Text(TXT_OPTIONS, font, 55);
    btnExit = sf::Text(TXT_EXIT, font, 55);

    btnSolaris = sf::Text(TXT_SOLARIS, font, 58);
    btnVoidborn = sf::Text(TXT_VOIDBORN, font, 58);

    description = sf::Text("", font, 34);
    description.setFillColor(sf::Color(220, 220, 220));

    btnStart = sf::Text(TXT_START_GAME, font, 48);
    btnBack = sf::Text(TXT_BACK, font, 52);

    btnVSync = sf::Text(TXT_VSYNC_ON, font, 50);
    btnBackOptions = sf::Text(TXT_BACK, font, 50);

    selectedFaction = new Faction(FactionType::SolarisDominion);

    hud = HUD();
    game = nullptr;
}

void Menu::resetStars(const sf::Vector2u& size)
{
    stars.clear();
    for (int i = 0; i < 450; ++i) {
        Star s;
        s.position = sf::Vector2f((float)(rand() % size.x), (float)(rand() % size.y));
        s.size = 1.0f + (rand() % 3);
        s.speed = 0.3f + (rand() % 5) / 2.0f;
        int b = 200 + rand() % 55;
        s.color = sf::Color(b, b, 255);
        stars.push_back(s);
    }
}

void Menu::handleEvents(sf::RenderWindow& window, sf::Event& event, GameState& currentState)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mouse = sf::Mouse::getPosition(window);

        if (currentState == GameState::MainMenu)
        {
            if (btnNewGame.getGlobalBounds().contains(mouse.x, mouse.y)) currentState = GameState::FactionSelect;
            else if (btnOptions.getGlobalBounds().contains(mouse.x, mouse.y)) currentState = GameState::OptionsMenu;
            else if (btnExit.getGlobalBounds().contains(mouse.x, mouse.y)) window.close();
        }
        else if (currentState == GameState::FactionSelect)
        {
            if (btnSolaris.getGlobalBounds().contains(mouse.x, mouse.y)) {
                delete selectedFaction;
                selectedFaction = new Faction(FactionType::SolarisDominion);
            }
            else if (btnVoidborn.getGlobalBounds().contains(mouse.x, mouse.y)) {
                delete selectedFaction;
                selectedFaction = new Faction(FactionType::VoidbornAscendancy);
            }
            else if (btnStart.getGlobalBounds().contains(mouse.x, mouse.y)) {
                selectedFaction->applyToGame();
                startNewGame();
                currentState = GameState::Playing;
            }
            else if (btnBack.getGlobalBounds().contains(mouse.x, mouse.y)) currentState = GameState::MainMenu;
        }
        else if (currentState == GameState::OptionsMenu)
        {
            if (btnVSync.getGlobalBounds().contains(mouse.x, mouse.y)) {
                vSyncEnabled = !vSyncEnabled;
                btnVSync.setString(vSyncEnabled ? TXT_VSYNC_ON : TXT_VSYNC_OFF);
            }
            else if (btnBackOptions.getGlobalBounds().contains(mouse.x, mouse.y))
                currentState = GameState::MainMenu;
        }
    }

    // INPUT DLA GRY (Playing)
    if (currentState == GameState::Playing && game) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            game->handleMouseClick(sf::Mouse::getPosition(window), window);
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::B) game->buildStructure();
            if (event.key.code == sf::Keyboard::C) game->collectResource();
            if (event.key.code == sf::Keyboard::R) game->researchTech();
            if (event.key.code == sf::Keyboard::F) game->attackPlaceholder();
            if (event.key.code == sf::Keyboard::M) std::cout << "Tryb Ruchu w³¹czony (PPM = rozkaz)" << std::endl;
            if (event.key.code == sf::Keyboard::A) std::cout << "Tryb Ataku w³¹czony (PPM = atak)" << std::endl;
            if (event.key.code == sf::Keyboard::S) game->stopCommand();
            if (event.key.code == sf::Keyboard::P) game->patrolCommand();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            sf::Vector2f worldPos = game->screenToWorld(sf::Mouse::getPosition(window), window);
            game->moveSelectedUnitTo(worldPos);
        }
    }
}

void Menu::update(sf::Vector2i mousePos, const sf::RenderWindow& window)
{
    titleOffset += 0.025f;

    sf::Vector2u size = window.getSize();
    for (auto& s : stars) {
        s.position.x -= s.speed;
        if (s.position.x < 0) {
            s.position.x = size.x;
            s.position.y = rand() % size.y;
        }
    }

    if (game != nullptr) {
        game->update();   // kamera co klatkê
    }
}

void Menu::draw(sf::RenderWindow& window, const GameState& currentState)
{
    for (const auto& s : stars) {
        sf::RectangleShape p(sf::Vector2f(s.size, s.size));
        p.setPosition(s.position);
        p.setFillColor(s.color);
        window.draw(p);
    }

    float titleY = 140.0f + std::sin(titleOffset) * 22.0f;
    title.setOrigin(title.getLocalBounds().width / 2.0f, title.getLocalBounds().height / 2.0f);
    title.setPosition(window.getSize().x / 2.0f, titleY);
    window.draw(title);

    if (currentState == GameState::MainMenu)
    {
        btnNewGame.setPosition(window.getSize().x / 2.f, 380); btnNewGame.setOrigin(btnNewGame.getLocalBounds().width / 2, btnNewGame.getLocalBounds().height / 2); window.draw(btnNewGame);
        btnOptions.setPosition(window.getSize().x / 2.f, 470); btnOptions.setOrigin(btnOptions.getLocalBounds().width / 2, btnOptions.getLocalBounds().height / 2); window.draw(btnOptions);
        btnExit.setPosition(window.getSize().x / 2.f, 560); btnExit.setOrigin(btnExit.getLocalBounds().width / 2, btnExit.getLocalBounds().height / 2); window.draw(btnExit);
    }
    else if (currentState == GameState::FactionSelect)
    {
        btnSolaris.setPosition(window.getSize().x / 2.f - 380, 340);
        btnVoidborn.setPosition(window.getSize().x / 2.f + 380, 340);
        btnSolaris.setOrigin(btnSolaris.getLocalBounds().width / 2, btnSolaris.getLocalBounds().height / 2);
        btnVoidborn.setOrigin(btnVoidborn.getLocalBounds().width / 2, btnVoidborn.getLocalBounds().height / 2);

        if (selectedFaction->type == FactionType::SolarisDominion) {
            btnSolaris.setFillColor(sf::Color(210, 210, 225));
            for (int i = 3; i >= 1; --i) {
                sf::Text glow = btnSolaris;
                glow.setFillColor(sf::Color(255, 245, 140, 90 - i * 22));
                glow.move(-i * 2.5f, -i * 2.5f);
                window.draw(glow);
            }
        }
        else btnSolaris.setFillColor(sf::Color(90, 90, 100));

        if (selectedFaction->type == FactionType::VoidbornAscendancy) {
            btnVoidborn.setFillColor(sf::Color(140, 80, 255));
            for (int i = 3; i >= 1; --i) {
                sf::Text glow = btnVoidborn;
                glow.setFillColor(sf::Color(255, 255, 255, 80 - i * 20));
                glow.move(-i * 2.5f, -i * 2.5f);
                window.draw(glow);
            }
        }
        else btnVoidborn.setFillColor(sf::Color(90, 90, 100));

        window.draw(btnSolaris);
        window.draw(btnVoidborn);

        description.setString(selectedFaction->description);
        description.setPosition(window.getSize().x / 2.f - description.getLocalBounds().width / 2, 520);
        window.draw(description);

        btnStart.setPosition(window.getSize().x / 2.f, 680); btnStart.setOrigin(btnStart.getLocalBounds().width / 2, btnStart.getLocalBounds().height / 2); window.draw(btnStart);
        btnBack.setPosition(window.getSize().x / 2.f, 750); btnBack.setOrigin(btnBack.getLocalBounds().width / 2, btnBack.getLocalBounds().height / 2); window.draw(btnBack);
    }
    else if (currentState == GameState::OptionsMenu)
    {
        btnVSync.setString(vSyncEnabled ? TXT_VSYNC_ON : TXT_VSYNC_OFF);
        btnVSync.setPosition(window.getSize().x / 2.f, 420); btnVSync.setOrigin(btnVSync.getLocalBounds().width / 2, btnVSync.getLocalBounds().height / 2); window.draw(btnVSync);
        btnBackOptions.setPosition(window.getSize().x / 2.f, 520); btnBackOptions.setOrigin(btnBackOptions.getLocalBounds().width / 2, btnBackOptions.getLocalBounds().height / 2); window.draw(btnBackOptions);
    }
    else if (currentState == GameState::Playing)
    {
        window.clear(sf::Color(10, 15, 35));
        if (game) game->draw(window);
        hud.draw(window, selectedFaction->type == FactionType::SolarisDominion);
    }
}

void Menu::startNewGame() {
    if (game) delete game;
    game = new Game(selectedFaction);
    std::cout << "[Menu] Gra wystartowa³a!" << std::endl;
}