#pragma once
#include <SFML/Graphics.hpp>

const sf::Color BG_COLOR(20, 5, 35);

const sf::Color SOLARIS_COLOR(170, 185, 207);
const sf::Color VOIDBORN_COLOR(180, 100, 255);

const sf::String TXT_TITLE = "COSMIC STRATEGY";
const sf::String TXT_NEW_GAME = "NOWA GRA";
const sf::String TXT_OPTIONS = "OPCJE";
const sf::String TXT_EXIT = L"WYJŒCIE";
const sf::String TXT_SOLARIS = "SOLARIS DOMINION";
const sf::String TXT_VOIDBORN = "VOIDBORN ASCENDANCY";
const sf::String TXT_START_GAME = L"ROZPOCZNIJ POTYCZKÊ";
const sf::String TXT_BACK = "WROC";
const sf::String TXT_VSYNC_ON = L"V-SYNC: W£¥CZONY";
const sf::String TXT_VSYNC_OFF = L"V-SYNC: WY£¥CZONY";
const sf::String TXT_SOLARIS_DESC = L"Zjednoczona si³a ludzkoœci po kryzysie energetycznym.\\nDominuj¹ w solarnej technologii, dronach i precyzyjnej in¿ynierii.";
const sf::String TXT_VOID_DESC = L"Pó³-wymiarowa rasa istniej¹ca na granicy czasu i przestrzeni.\\nOperuj¹ technologi¹ rezonansow¹ i wymiarow¹.";

// === NOWE STAŁE DLA GRY ===
const int MAP_WIDTH = 2000;
const int MAP_HEIGHT = 2000;
const int MAX_SUPPLY = 250;
const int START_SUPPLY = 8;

const sf::Vector2f START_POS_NORTH = { 1000, 300 };
const sf::Vector2f START_POS_NE = { 1400, 400 };
const sf::Vector2f START_POS_EAST = { 1700, 1000 };
const sf::Vector2f START_POS_SE = { 1400, 1600 };
const sf::Vector2f START_POS_SOUTH = { 1000, 1700 };
const sf::Vector2f START_POS_SW = { 600, 1600 };
const sf::Vector2f START_POS_WEST = { 300, 1000 };
const sf::Vector2f START_POS_NW = { 600, 400 };