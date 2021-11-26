#ifndef APPSTATEMANAGER_H
#define APPSTATEMANAGER_H

#include "AppState.h"
#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"

class AppStateManager {
public:
    AppStateManager();
    ~AppStateManager();
    void stateEvent();
    States stateUpdate();
    void stateRender();
    bool stateExit();
    States getCurrentStateEnum();
    void setCurrentStateEnum(States);
    void changeStates();
    
private:
    AppState *currentState;
    States currentStateEnum;
};
#endif /* APPSTATEMANAGER_H */
