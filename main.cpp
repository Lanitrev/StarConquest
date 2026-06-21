#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"     // <-- dodane

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Cosmic Strategy", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    Menu menu;
    menu.resetStars(sf::Vector2u(desktop.width, desktop.height));

    GameState currentState = GameState::MainMenu;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            menu.handleEvents(window, event, currentState);
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        menu.update(mousePos, window);

        window.clear(BG_COLOR);
        menu.draw(window, currentState);
        window.display();
    }

    return 0;
}