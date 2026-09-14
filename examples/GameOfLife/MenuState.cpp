//
// Created by natha on 9/14/2026.
//

#include "MenuState.h"

#include "Logic/ModelFactory.h"
#include "Rendering/ViewConfig.h"
#include "Utils/Anchor.h"

void MenuState::onEnter() {
    TextViewConfig config;
    config.string = "Menu";
    addModel(ModelFactory::createModel(getCtx(), {0.02, 0}, {0.1f, 0.05f}, config));
}
