#include "../include/Texture.h"

/**
 * Konstruktor klasy Texture
 */
Texture::Texture()
{
    currentTexture = NULL;
    width = 0;
    height = 0;
}

/**
 * Destruktor klasy Texture
 */
Texture::~Texture()
{
    free();
}

/**
 * Ładuje teksturę z pliku.
 * @return status załadowania tekstury z pliku
 */
bool Texture::loadFromFile(std::string path)
{
    // Zwalnia obecnie używaną teksturę
    free();

    SDL_Texture *newTexture;
    SDL_Surface *surf = IMG_Load(path.c_str());

    if (surf == NULL)
    {
        cout 
        << "ERROR: Nie można załadować obrazu z " << path.c_str() 
        << "SDL_Error: " << IMG_GetError() 
        << endl;
        return false;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, surf);

        if (newTexture == NULL) 
        {
            cout 
            << "ERROR: Nie można stworzyć tekstury z " << path.c_str() 
            << "SDL_Error: " << IMG_GetError() 
            << endl;
            return false;
        }
        else
        {
            width = surf->w;
            height = surf->h;
        }

        SDL_FreeSurface(surf);
    }

    currentTexture = newTexture;
    return currentTexture != NULL;
}

/**
 * Renderuje obiekt na podstawie jego pozycji i rozmiarów
 */
void Texture::render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect renderSpace = {x, y, width, height};

    if (clip != NULL)
    {
        renderSpace.w = clip->w;
        renderSpace.h = clip->h;
    }

    SDL_RenderCopy(renderer, currentTexture, clip, &renderSpace);
}

/**
 * Zwalnia teksturę
 */
void Texture::free()
{
    if (currentTexture != NULL)
    {
        SDL_DestroyTexture(currentTexture);
        currentTexture = NULL;
        width = 0;
        height = 0;
    }
}

/**
 * Getter width
 */
int Texture::getWidth()
{
    return width;
}

/**
 * Getter height
 */
int Texture::getHeight()
{
    return height;
}
