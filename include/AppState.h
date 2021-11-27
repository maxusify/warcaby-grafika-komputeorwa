#ifndef APPSTATE_H
#define APPSTATE_H

enum States {
    MENU_STATE,
    GAME_STATE,
    GAME_OVER_STATE
};

/** class AppState
 *  brief klasa abstrakcyjna reprezentująca stan programu
 */ 
class AppState {
public:
    virtual ~AppState();
    virtual void stateEnter() = 0;
    virtual void stateEvent() = 0;
    virtual States stateUpdate() = 0;
    virtual void stateRender() = 0;
    virtual bool stateExit() = 0;

protected:
    virtual bool loadMedia() = 0;
    States currState;
    States nextState;
};

#endif /* APPSTATE_H */
