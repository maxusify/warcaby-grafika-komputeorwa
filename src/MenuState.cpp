#include "../include/MenuState.h"

/**
 * Konstruktor klasy MenuState
 */ 
MenuState::MenuState()
{
    BUTTON_WIDTH = 346;
    BUTTON_HEIGHT = 40;
    currState = MENU_STATE;
    nextState = MENU_STATE;
    boardButtons = new Button[FULL_MENU];
    userQuit = false;
}

/**
 * Destruktor klasy MenuState
 */
MenuState::~MenuState()
{
    delete [] boardButtons;
    boardButtons = NULL;
    spritesTexture.free();
    spritesDims.clear();
}

/**
 * Komunikuje o dostępności zasobów potrzebnych dla stanu
 */
void MenuState::stateEnter()
{
    if (!loadMedia()) 
    {
        cout << "ERROR: Nie można załadować zasobów!" << endl;
    }
}
/**
 * Pętla zdarzeń dla ekranu menu głównego.
 */
void MenuState::stateEvent()
{
    SDL_Event event;
    
    while (SDL_PollEvent(&event) != 0)
    {
        // Wyjście
        if (event.type == SDL_QUIT)
        {
            userQuit=true;
        }
        
        if (event.type == SDL_MOUSEMOTION) 
        {
            // Sprawdzenie czy kursor najeżdza na któryś z przycisków
            for (int index = 0; index < 3; index ++) 
            {
                if (boardButtons[index].insideButton(346, 40)) 
                {
                    hover[index] = true;
                }
                else 
                {
                    hover[index] = false;
                }
            }
        }
        
        // Sprawdzenie czy któryś z przycisków został przyciśnięty
        if (event.type == SDL_MOUSEBUTTONDOWN) 
        {
            for (int index = 0; index < 3; index++) 
            {
                if (hover[index]) 
                {
                    // Ustawienie następnego stanu aplikacji na GAME_STATE
                    nextState = GAME_STATE;
                    // GAMEMODE to indeks wciśniętego przycisku
                    GAMEMODE = index;
                }
            }
        }

    }
}

/**
 * Aktualizacja stanu aplikacji.
 * @return stan aplikacji
 */
States MenuState::stateUpdate()
{
    if (currState != nextState) 
    {
        return nextState;
    }

    return currState;
}

/**
 * Renderuje przyciski w menu głównym
 */
void MenuState::stateRender()
{
    // Kolor tła
    SDL_SetRenderDrawColor(renderer, 0xCB, 0xBE, 0xB5, 0xFF);
    SDL_RenderClear(renderer);
    drawMenu();

    for (int index = 0; index < 3; index++) 
    {
        currentSprite = index;

        if (hover[index])
        {
            // Zmiana przycisku na jego wariant HOVER
            currentSprite += 3;
        }

        // Renderowanie przycisku
        boardButtons[index].render(currentSprite);
    }
}

/**
 * Zwraca status wyjścia
 * @return status wyjścia
 */
bool MenuState::stateExit()
{
    return userQuit;
}

/**
 * Ładuje tekstury menu i inicjalizuje jego przyciski
 */
bool MenuState::loadMedia()
{
    bool isMediaLoaded = true;
    
    if (!spritesTexture.loadFromFile("data/MenuState.png")) {
        cout << "ERROR: Nie można załadować tekstury menu!" << endl;
        return !isMediaLoaded;
    }
    
    /* ========= INICJALIZACJA PRZYCISKÓW MENU ========= */
    // Dwóch graczy - Normalny
    SDL_Rect twoPlayers = {
        0, 
        0, 
        346, 
        40
    };
    spritesDims.push_back(twoPlayers);

    // Pojedynczy gracz - Normalny
    SDL_Rect singlePlayer = {
        0, 
        40, 
        346, 
        40
    };
    spritesDims.push_back(singlePlayer);

    // Komputer vs Komputer - Normalny
    SDL_Rect aiVsAi = {
        0, 
        80, 
        346, 
        40
    };
    spritesDims.push_back(aiVsAi);

    // Dwóch graczy - Najechano
    SDL_Rect twoPlayersHover = {
        346, 
        0, 
        346, 
        40
    };
    spritesDims.push_back(twoPlayersHover);

    // Pojedynczy gracz - Najechano
    SDL_Rect singlePlayerHover = {
        346, 
        40, 
        346, 
        40
    };
    spritesDims.push_back(singlePlayerHover);

    // Komputer vs Komputer - Najechano
    SDL_Rect aiVsAiHover = {
        346, 
        80, 
        346, 
        40
    };
    spritesDims.push_back(aiVsAiHover);

    // Menu
    SDL_Rect fullMenu = {
        0, 
        120, 
        640, 
        640
    };
    spritesDims.push_back(fullMenu);
    
    boardButtons[TWO_PLAYERS].setPoint(148, 210);
    boardButtons[SINGLE_PLAYER].setPoint(148, 280);
    boardButtons[AI_VS_AI].setPoint(148, 350);
    
    return isMediaLoaded;
}

/**
 * Rystuje tekstury menu.
 */
void MenuState::drawMenu() 
{
    spritesTexture.render(0, 0, &spritesDims[FULL_MENU]);
}




