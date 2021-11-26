#include "../include/Engine.h"
#include "../include/AppState.h"
#include "../include/AppStateManager.h"
#include "../include/Texture.h"

/**
 * Obecnie używany sprite
 */
int currentSprite = 0;
/**
 * Wskaźnik na okno aplikacji
 */
SDL_Window *window;
/**
 * Renderer używany do rysowania obiektów
 */
SDL_Renderer *renderer;
/**
 * Szerokość okna
 */
const int SCREEN_WIDTH = 640;
/**
 * Wysokość okna
 */
const int SCREEN_HEIGHT = 640;
/**
 * Szerkość przycisku
 */
int BUTTON_WIDTH = 0;
/**
 * Wysokość przycisku
 */
int BUTTON_HEIGHT = 0;
/**
 * Tryb gry
 */
int GAMEMODE = 0;
/**
 * Wymiary sprite'ów do rysowania ich na ekranie
 */
vector<SDL_Rect> spritesDims;
/**
 * Obecnie używana tekstura dla zestawu sprite'ów
 */
Texture spritesTexture;

/**
 * Konstruktor klasy Engine
 */
Engine::Engine()
{
    window=NULL;
    renderer=NULL;

    // Checks if init was able to excute //
    if (!init())
    {
        cout << "ERROR: Nie można załadować aplikacji." << endl;
    }

    aps = new AppStateManager;
}

/**
 * Destruktor klasy Engine
 */
Engine::~Engine()
{
    delete aps;
    aps = NULL;

    SDL_DestroyWindow(window);
    window=NULL;

    SDL_DestroyRenderer(renderer);
    renderer=NULL;
}

/**
 * Inicjalizuje bibliotekę SDL oraz jej rozszerzenia i moduły.
 * @return true jeśli się powiedzie; false w przeciwnym wypadku
 */
bool Engine::init()
{
    bool isInitSuccessful = true;

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "ERROR: Inicjalizacja nie udała się. SDL_Error: %s\n" << SDL_GetError() << endl;
        isInitSuccessful = false;
    }
    else
    {
        if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ))
        {
            cout << "UWAGA: Liniowe filtorwanie tekstur jest wyłączone!" << endl;
        }

        window = SDL_CreateWindow(
            "Warcaby - Silnik 2D",
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if (window == NULL)
        {
            cout << "ERROR: Nie można stworzyć okna. SDL_Error: %s\n" << SDL_GetError() << endl;
            isInitSuccessful = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(
                window,
                -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
            );

            if (renderer == NULL)
            {
                cout << "ERROR: Nie można stworzyć renderera. SDL_Error: %s\n" << SDL_GetError() << endl;
                isInitSuccessful = false;
            }
            else
            {
                // Ustawienie początkowego koloru renderera
                SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);

                // Inicjalizacja bilbioteki SDL_Image
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags)&imgFlags))
                {
                    cout<<"ERROR: Nie można załadować biblioteki SDL_Image. SDl_Image_Error: %s\n" << IMG_GetError() << endl;
                    isInitSuccessful = false;
                }
            }
        }
    }

    return isInitSuccessful;
}

/**
 * Rozpoczyna główną pętle aplikacji
 * @return EXIT_SUCCESS
 */
int Engine::start()
{
    while (!aps->stateExit()) 
    {
        aps->stateEvent();
        aps->stateRender();

        if (aps->stateUpdate() != aps->getCurrentStateEnum()) 
        {
            aps->setCurrentStateEnum(aps->stateUpdate());
            aps->changeStates();
        }

        SDL_RenderPresent(renderer);

        if (aps->getCurrentStateEnum() == MENU_STATE) 
        {
            SDL_Delay(30);
        }
        else 
        {
            SDL_Delay(100);
        }
    }

    close();
    return EXIT_SUCCESS;

}

/**
 * Zakańcza działanie wszystkich bibliotek i ich rozszerzeń
 */
void Engine::close()
{
    IMG_Quit();
    SDL_Quit();
}
