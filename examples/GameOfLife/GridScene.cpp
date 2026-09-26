//
// Created by natha on 9/17/2026.
//

#include "GridScene.h"

#include "Logic/ModelFactory.h"
#include "Rendering/ViewConfig.h"

void GridScene::onEnter() {
    eng::GridViewConfig gridConfig;
    eng::TextViewConfig textConfig;
    eng::ButtonViewConfig buttonConfig;

    grid = addModel({1, 1}, {98, 98}, gridConfig);
    text = addModel({50, 1}, {30, 10}, textConfig);
    button = addModel({50, 50}, {10, 10}, buttonConfig);

    grid->toggleCell({1, 1});
    grid->toggleCell({4, 1});
    grid->toggleCell({5, 2});
}
bool GridScene::onLeftPressed(const std::pair<unsigned int, unsigned int> &windowCoordinates) {
    return grid->onClick(getCtx().camera.windowToWorldPosition(windowCoordinates));
}
