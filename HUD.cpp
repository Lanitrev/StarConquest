#include "HUD.h"

HUD::HUD() {
    // Preload obu wersji raz na zawsze
    tSolarisResources.loadFromFile("assets/hud/panel_resources.png");
    tSolarisCommand.loadFromFile("assets/hud/panel_command.png");
    tSolarisButtons.loadFromFile("assets/hud/panel_buttons.png");
    tSolarisMinimap.loadFromFile("assets/hud/panel_minimap.png");
    tSolarisControl.loadFromFile("assets/hud/panel_control.png");
    tSolarisSelection.loadFromFile("assets/hud/panel_selection.png");

    tVoidResources.loadFromFile("assets/hud/panel_resources_void.png");
    tVoidCommand.loadFromFile("assets/hud/panel_command_void.png");
    tVoidButtons.loadFromFile("assets/hud/panel_buttons_void.png");
    tVoidMinimap.loadFromFile("assets/hud/panel_minimap_void.png");
    tVoidControl.loadFromFile("assets/hud/panel_control_void.png");
    tVoidSelection.loadFromFile("assets/hud/panel_selection_void.png");

    // Domyœlnie Solaris
    sResources.setTexture(tSolarisResources);
    sCommand.setTexture(tSolarisCommand);
    sButtons.setTexture(tSolarisButtons);
    sMinimap.setTexture(tSolarisMinimap);
    sControl.setTexture(tSolarisControl);
    sSelection.setTexture(tSolarisSelection);
}

void HUD::draw(sf::RenderWindow& window, bool isSolaris) {
    sf::Vector2u size = window.getSize();

    if (isSolaris) {
        sResources.setTexture(tSolarisResources);
        sCommand.setTexture(tSolarisCommand);
        sButtons.setTexture(tSolarisButtons);
        sMinimap.setTexture(tSolarisMinimap);
        sControl.setTexture(tSolarisControl);
        sSelection.setTexture(tSolarisSelection);
    }
    else {
        sResources.setTexture(tVoidResources);
        sCommand.setTexture(tVoidCommand);
        sButtons.setTexture(tVoidButtons);
        sMinimap.setTexture(tVoidMinimap);
        sControl.setTexture(tVoidControl);
        sSelection.setTexture(tVoidSelection);
    }

    // Twoje aktualne pozycje
    sResources.setScale(0.3f, 0.3f);
    sResources.setPosition(size.x - 510, -110);
    window.draw(sResources);

    sMinimap.setScale(0.3f, 0.3f);
    sMinimap.setPosition(-35, size.y - 470);
    window.draw(sMinimap);

    sControl.setScale(0.15f, 0.15f);
    sControl.setPosition(-15, size.y - 103);
    window.draw(sControl);

    sCommand.setScale(0.3f, 0.3f);
    sCommand.setPosition(size.x - 505, size.y - 355);
    window.draw(sCommand);

    sButtons.setScale(0.22f, 0.22f);
    sButtons.setPosition(size.x - 370, size.y - 145);
    window.draw(sButtons);

    sSelection.setScale(0.3f, 0.3f);
    sSelection.setPosition(size.x / 2.f - 320, size.y - 260);
    window.draw(sSelection);
}