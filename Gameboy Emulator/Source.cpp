#include <SFML/Graphics.hpp>
#include "GameBoy.h"

int main() 
{
    GameBoy gameBoy("GameBoy Menu", 800, 600);
    gameBoy.start();

    return 0;
}
