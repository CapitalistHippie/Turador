#ifndef LIBTURADOR_TURA_GAME_H_INCLUDED
#define LIBTURADOR_TURA_GAME_H_INCLUDED

#include "gameconfiguration.h"

namespace tura
{
class Game
{
private:
    GameConfiguration gameConfiguration;

public:
    Game(GameConfiguration gameConfiguration) :
        gameConfiguration(gameConfiguration)
    {
    }
};
}

#endif // LIBTURADOR_TURA_GAME_H_INCLUDED
