#include "../include/Engine.h"

/**
 * Punkt wejściowy programu. Tworzy obiekt klasy Engine
 * oraz przekazuje mu kontrolę.
 */ 
int main(int argc, char* argv[])
{
    // Utworzenie obiektu klasy Engine
    Engine game;

    // Przekazanie kontroli aplikacji obiektowi klasy Engine.
    return game.start();
}
