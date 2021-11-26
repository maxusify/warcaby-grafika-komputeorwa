#include "../include/GameState.h"

int TOTAL_BUTTONS = 32;

/**
 * Konstruktor klasy GameState.
 */
GameState::GameState()
{
    BUTTON_WIDTH = 80;
    BUTTON_HEIGHT = 80;
    currState = GAME_STATE;
    nextState = GAME_STATE;
    Board = new CheckersBoard;
    boardButtons = new Button[TOTAL_BUTTONS];
    userQuit = false;
    setGameMode();
}

/**
 * Destruktor klasy GameState.
 */
GameState::~GameState(){
    delete Board;
    Board = NULL;
    delete [] boardButtons;
    boardButtons = NULL;
    delete Player1;
    Player1 = NULL;
    delete Player2;
    Player2 = NULL;
    spritesDims.clear();
}

/**
 * Ustawia tryb gry który został wybrany przez gracza.
 */
void GameState::setGameMode()
{
    switch (GAMEMODE) {
        // Gracz vs. Gracz
        case 0:
            Player1 = new RealPlayer(true, Board, boardButtons);
            Player2 = new RealPlayer(false, Board, boardButtons);
            break;
        // Gracz vs. Komputer
        case 1:
            Player1 = new AI(true, Board, boardButtons);
            Player2 = new RealPlayer(false, Board, boardButtons);
            break;
        // Komputer vs. Komputer
        case 2:
            Player1 = new AI(true, Board, boardButtons);
            Player2 = new AI(false, Board, boardButtons);
            break;
        // Brak wyboru
        default:
            userQuit = true;
            break;
    }
}

/**
 * Komunikuje stan inicjalizacji potrzebnych zasobów dla stanu.
 */
void GameState::stateEnter()
{
    if (!loadMedia()) {
        cout << "ERROR: Nie można rozpocząć gry." << endl;
    }
}

/**
 * Odpowiedzialna za pętlę rozgrywki.
 */
void GameState::stateEvent()
{
    SDL_Event event;

    // Pętla zdarzeń
    while (SDL_PollEvent(&event) != 0) {

        // Wyjście
        if (event.type == SDL_QUIT)
        {
            userQuit = true;
        }

        if (!gameOver()) 
        {
            // Gdy tura należy do gracza pierwszego
            if (Player1->turn) 
            {
                if (Player1->makeMove(&event))
                {
                    Player1->updateKings();
                    Player1->turn = false;
                    Player2->turn = true;
                    Player2->updateTeam();
                    cout << *Board << endl;
                    break;
                }
            }
            // Gdy tura należy do gracza drugiego
            else 
            {
                if (Player2->makeMove(&event))
                {
                    Player2->updateKings();
                    Player2->turn = false;
                    Player1->turn = true;
                    Player1->updateTeam();
                    cout << *Board << endl;
                    break;
                }
            }
        }
        // Ustawienie następnego stanu aplikacji na GAME_OVER_STATE
        else
        {
            nextState = GAME_OVER_STATE;
        }
    }
}

/**
 * Ładuje media związane z pionkami.
 * @return status załadowania mediów 
 */
bool GameState::loadMedia()
{
    bool isMediaLoaded = true;

    /* ====== SPRAWDZENIE CZY SPRITE ISTNIEJE ====== */
    if (!spritesTexture.loadFromFile("data/CheckerSprites.png")) {
        cout << "ERROR: Nie można załadować sprite'ów!" << endl;
        isMediaLoaded = false;
        return isMediaLoaded;
    }

    /* ====== INICJALIZACJA PIONKÓW DO GRY ====== */
    // Czerwony pionek
    SDL_Rect redPiece = {
        0,
        0, 
        BUTTON_WIDTH, 
        BUTTON_HEIGHT
    };
    spritesDims.push_back(redPiece);

    // Czarny pionek
    SDL_Rect blackPiece = {
        BUTTON_WIDTH, 
        0, 
        BUTTON_WIDTH, 
        BUTTON_HEIGHT
    };
    spritesDims.push_back(blackPiece);

    // Czerwony król
    SDL_Rect redKing = {
        BUTTON_WIDTH*2, 
        0, 
        BUTTON_WIDTH, 
        BUTTON_HEIGHT
    };
    spritesDims.push_back(redKing);

    // Czarny król
    SDL_Rect blackKing = {
        BUTTON_WIDTH*3, 
        0, 
        BUTTON_WIDTH, 
        BUTTON_HEIGHT
    };
    spritesDims.push_back(blackKing);

    int index = 0;
    bool indent = true;
    int xPointStart;

    // Ustawia punkty dla przycisków pionków (lewy góry róg przycisku)
    for (int y = 0; y < SCREEN_HEIGHT; y += BUTTON_HEIGHT) 
    {
        if (indent) 
        {
            xPointStart = BUTTON_WIDTH;
            indent = false;
        }
        else 
        {
            xPointStart = 0;
            indent = true;
        }

        for (int x = xPointStart; x < SCREEN_WIDTH; x += 2*BUTTON_WIDTH)
        {
            boardButtons[index].setPoint(x, y);
            index++;
        }
    }

    return isMediaLoaded;
}

/**
 * Sprawdza czy można zakończyć grę.
 * @return prawdę jeśli można zakończyć, fałsz w przeciwnym wypadku.
 */
bool GameState::gameOver(){
    if (Player1->team.size() == 0 || Player2->team.size() == 0)
    {
        return true;
    }

    return false;
}

/**
 * Aktualizuje stan aplikacji.
 * @return następny stan aplikacji.
 */
States GameState::stateUpdate(){
    if (currState != nextState) {
        return nextState;
    }

    return currState;
}

/**
 * Renderuje aktualny stan gry.
 */
void GameState::stateRender()
{
    int index = 0;

    // Kolor parzystych pól planszy
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    Board->drawBoard();

    // Renderowanie pionków...
    for (int y = 0; y < 8; y++) 
    {
        for (int x = 0; x < 8; x++) 
        {
            // ...na polach parzystych
            if( (y + x) % 2 == 1) 
            {
                Board->drawBoardPeices(x, y, &boardButtons[index]);
                index++;
            }
        }
    }
}

/**
 * Zwraca status wyjścia przez gracza
 * @return status wyjścia
 */
bool GameState::stateExit()
{
    return userQuit;
}
