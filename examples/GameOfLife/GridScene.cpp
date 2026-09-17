//
// Created by natha on 9/17/2026.
//

#include "GridScene.h"

#include "Logic/ModelFactory.h"
#include "Rendering/ViewConfig.h"

void GridScene::onEnter() {
    eng::GridViewConfig config;
    addModel({1, 1}, {98, 98}, config);
}