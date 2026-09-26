//
// Created by natha on 9/14/2026.
//

#include "MenuScene.h"

#include "Logic/ModelFactory.h"
#include "Rendering/ViewConfig.h"
#include "Utils/Anchor.h"

void MenuScene::onEnter() {
    eng::TextViewConfig config;
    config.string = "Menu";
    addModel({0.02, 0}, {0.1f, 0.05f}, config);
}
