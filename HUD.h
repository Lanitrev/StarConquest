#pragma once
#include <SFML/Graphics.hpp>

class HUD {
public:
    HUD();
    void draw(sf::RenderWindow& window, bool isSolaris);

private:
    sf::Texture tSolarisResources, tSolarisCommand, tSolarisButtons, tSolarisMinimap, tSolarisControl, tSolarisSelection;
    sf::Texture tVoidResources, tVoidCommand, tVoidButtons, tVoidMinimap, tVoidControl, tVoidSelection;

    sf::Sprite sResources, sCommand, sButtons, sMinimap, sControl, sSelection;
};