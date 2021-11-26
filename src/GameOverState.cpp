#include "../include/GameOverState.h"

/**
 * Konstruktor klasy GameOverState
 */
GameOverState::GameOverState()
{
    currState = GAME_OVER_STATE;
    nextState = GAME_OVER_STATE;
    userQuit = false;
}

/**
 * Destruktor klasy GameOverState
 */
GameOverState::~GameOverState() 
{
}

/**
 * Komunikuje o końcu gry
 */
void GameOverState::stateEnter()
{
    cout << "GRA SKOŃCZYŁA SIĘ" << endl;
}

/**
 * Pętla zdarzeń dla stanu końca gry
 */
void GameOverState::stateEvent()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            userQuit = true;
        }
    }
}

/**
 * Aktualizuje stan aplikacji
 * @return stan aplikacji
 */
States GameOverState::stateUpdate()
{
    if (currState != nextState) 
    {
        return nextState;
    }

    return currState;
}

/**
 * Renderuje ekran końca gry
 */
void GameOverState::stateRender()
{
    // Kolor tła
    SDL_SetRenderDrawColor(renderer, 0xD4, 0x9A, 0x6A, 0xFF);
    SDL_RenderClear(renderer);
}

/**
 * Zwraca status zakończenia
 * @return status zakończenia
 */
bool GameOverState::stateExit(){
    return userQuit;
}

/**
 * Ładuje zasoby i inicjuje elementy ekranu końcowego
 * @return stan załadowania zasobów
 */
bool GameOverState::loadMedia(){
    return false;
}
