#include "Faction.h"
#include "Constants.h"

Faction::Faction(FactionType t) : type(t)
{
    if (t == FactionType::SolarisDominion)
    {
        name = "Solaris Dominion";
        shortName = "SOLARIS";
        primaryColor = SOLARIS_COLOR;
        accentColor = sf::Color(255, 178, 0);        // pomarańczowy
        description = TXT_SOLARIS_DESC;
    }
    else // Voidborn
    {
        name = "Voidborn Ascendancy";
        shortName = "VOIDBORN";
        primaryColor = VOIDBORN_COLOR;
        accentColor = sf::Color(56, 243, 224);       // neon turkus
        description = TXT_VOID_DESC;
    }
}

void Faction::applyToGame()
{
    // Tu później będziemy zmieniać kolory całego interfejsu, tła mapy itp.
}

sf::String Faction::getFlagSymbol() const
{
    return (type == FactionType::SolarisDominion) ? L"SOL" : L"VOID";
}