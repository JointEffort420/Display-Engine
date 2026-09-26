//
// Created by natha on 9/17/2026.
//

#ifndef DISPLAYENGINE_GRIDSCENE_H
#define DISPLAYENGINE_GRIDSCENE_H

#include <Controller/Space.h>

#include "Logic/ButtonModel.h"
#include "Logic/GridModel.h"
#include "Rendering/TextView.h"

class GridScene  : public eng::Scene{
private:
    eng::GridModel* grid;
    eng::Model* text;
    eng::ButtonModel* button;

public:
    using Scene::Scene;
    void onEnter() override;
    void onExit() override{}

    bool onLeftPressed(const std::pair<unsigned int, unsigned int> &windowCoordinates) override;
};


#endif //DISPLAYENGINE_GRIDSCENE_H