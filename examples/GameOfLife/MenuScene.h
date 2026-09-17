//
// Created by natha on 9/14/2026.
//

#ifndef DISPLAYENGINE_MENUSTATE_H
#define DISPLAYENGINE_MENUSTATE_H

#include <Controller/Space.h>

class MenuScene : public eng::Scene {
public:
    using Scene::Scene;
    void onEnter() override;
    void onExit() override{}
};


#endif //DISPLAYENGINE_MENUSTATE_H