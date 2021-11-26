#include "../include/AppStateManager.h"

/**
 * Konstruktor klasy AppStateManager
 */
AppStateManager::AppStateManager()
{
    currentState = new MenuState();
    currentState->stateEnter();
}

/**
 * Destruktor klasy AppStateManager
 */
AppStateManager::~AppStateManager()
{
    delete currentState;
    currentState = NULL;
}

/**
 * Wywołuje metodę stateEvent() obecnego stanu aplikacji.
 */
void AppStateManager::stateEvent()
{
    currentState->stateEvent();
}

/**
 * Zwraca odwołanie do metody stateUpdate() aktualnego stanu
 */
States AppStateManager::stateUpdate()
{
    return currentState->stateUpdate();
}

/**
 * Wywołuje metodę stateRender() obecnego stanu aplikacji.
 */
void AppStateManager::stateRender()
{
    currentState->stateRender();
}

/**
 * Zwraca odwołanie do metody stateExit() aktualnego stanu
 */
bool AppStateManager::stateExit()
{
    return currentState->stateExit();
}

/**
 * Ustawia obecny stan aplikacji.
 */
void AppStateManager::setCurrentStateEnum(States current)
{
    currentStateEnum = current;
}

/**
 * Getter dla currentStateEnum
 */
States AppStateManager::getCurrentStateEnum(){
    return currentStateEnum;
}

/**
 * Zmienia obecny stan aplikacji i wywołuje jego metodę stateEnter()
 */
void AppStateManager::changeStates()
{
    delete currentState;
    currentState = NULL;
    
    switch (currentStateEnum) {
        // Stan menu głównego
        case MENU_STATE:
            currentState = new MenuState;
            break;
        // Stan gry
        case GAME_STATE:
            currentState = new GameState;
            break;
        // Stan końca gry
        case GAME_OVER_STATE:
            currentState = new GameOverState;
            break;
        default:
            break;
    }

    currentState->stateEnter();
}