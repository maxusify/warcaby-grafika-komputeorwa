#include "../include/Button.h"
#include "../include/GameState.h"
#include "../include/Engine.h"

/**
 * Konstruktor klasy Button
 */
Button::Button()
{
    buttonPoint.x = 0;
    buttonPoint.y = 0;
}

/**
 * Destruktor klasy Button
 */
Button::~Button()
{
    buttonPoint.x = NULL;
    buttonPoint.y = NULL;
}

/**
 * Ustawia współrzędne punktu przycisku
 */
void Button::setPoint(int x, int y)
{
    buttonPoint.x = x;
    buttonPoint.y = y;
}

/**
 * Renderuje przycisk
 */
void Button::render(int sprite)
{
    spritesTexture.render(
        buttonPoint.x, 
        buttonPoint.y, 
        &spritesDims[sprite]
    );
}

/**
 * Sprawdza czy kursor znajduje się na obszarze przycisku
 * @return prawda jeśli znajduje się, nie w przeciwnym przypadku
 */
bool Button::insideButton(int buttonWidth, int buttonHeight)
{
    int x, y;
    bool isInsideButton = true;

    SDL_GetMouseState(&x,&y);
    
    // NAD przyciskiem
    if (y < buttonPoint.y)
    {
        isInsideButton = false;
    }

    // POD przyciskiem
    else if (y > buttonPoint.y + buttonHeight)
    {
        isInsideButton = false;
    }

    // NA LEWO od przycisku
    else if (x < buttonPoint.x) 
    {
        isInsideButton = false;
    }

    // NA PRAWO od przycisku
    else if (x > buttonPoint.x + buttonWidth)
    {
        isInsideButton = false;
    }

    return isInsideButton;
}

/**
 * Getter buttonPoint.x
 */
int Button::getButtonPointX()
{
    return buttonPoint.x;
}

/**
 * Getter buttonPoint.y
 */
int Button::getButtonPointY()
{
    return buttonPoint.y;
}