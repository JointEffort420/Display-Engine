//
// Created by natha on 9/14/2026.
//

#ifndef DISPLAYENGINE_MENUSTATE_H
#define DISPLAYENGINE_MENUSTATE_H

#include <Controller/Space.h>

class MenuState : public State {
public:
    using State::State;
    void onEnter() override;
    void onExit() override{}
};


#endif //DISPLAYENGINE_MENUSTATE_H