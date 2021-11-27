#ifndef BUTTON_H
#define BUTTON_H

/* ====== KOMPILACJA ====== */
#ifdef _WIN32
    #include <SDL.h>
#endif
#ifdef __linux
    #include <SDL2/SDL.h>
#endif
/* ======================== */

class Texture;

/** class Button
 *  brief klasa reprezentująca przycisk
 *  details Reprezentuje obszar ekranu z którym można integrować
 */ 
class Button 
{
public:
    Button();
    ~Button();
    void setPoint(int,int);
    bool insideButton(int,int);
    void render(int);
    int getButtonPointX();
    int getButtonPointY();

private:
    SDL_Point buttonPoint;
};

#endif /* BUTTON_H */
