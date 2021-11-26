#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <stdio.h>
#include "AppState.h"
#include "Texture.h"

class GameOverState : public AppState {
public:
    GameOverState();
    ~GameOverState();
    void stateEnter();
    void stateEvent();
    States stateUpdate();
    void stateRender();
    bool stateExit();

private:
    bool loadMedia();
    bool userQuit;
};

#endif /* GAMEOVERSTATE_H */
