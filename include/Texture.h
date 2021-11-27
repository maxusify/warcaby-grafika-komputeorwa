#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
#endif
#ifdef __linux
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#endif

#include "Engine.h"

/** \class AI
 *  \brief klasa reprezentująca teksturę
 */ 
class Texture
{
public:
    Texture();
    ~Texture();

    bool loadFromFile(std::string);
    void render(int, int, SDL_Rect*);
    void free();
    int getWidth();
    int getHeight();

private:
    SDL_Texture *currentTexture;
    int width;
    int height;
};

#endif /* TEXTURE_H */
