//
// Created by natha on 9/14/2026.
//

#ifndef DISPLAYENGINE_TESTSTATE_H
#define DISPLAYENGINE_TESTSTATE_H

#include <Controller/Space.h>

class TestState : public State {
public:
    using State::State;
    void onEnter() override;
    void onExit() override{}
};

#endif //DISPLAYENGINE_TESTSTATE_H