#include <iostream>
#include "BomberWave.hpp"

int main()
{
    try
    {
        BomberWave game;
        game.Launch();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 84;
    }
    return 0;
}