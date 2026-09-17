//
// Created by natha on 9/17/2026.
//

#ifndef DISPLAYENGINE_GRIDSCENE_H
#define DISPLAYENGINE_GRIDSCENE_H

#include <Controller/Space.h>

class GridScene  : public eng::Scene{
public:
    using Scene::Scene;
    void onEnter() override;
    void onExit() override{}
};


#endif //DISPLAYENGINE_GRIDSCENE_H