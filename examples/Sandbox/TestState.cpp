//
// Created by natha on 9/14/2026.
//

#include "TestState.h"

void TestState::onEnter() {
    PolygonViewConfig config1;
    PolygonViewConfig config2;
    PolygonViewConfig config3;
    PolygonViewConfig config4;
    PolygonViewConfig config5;

    std::pair<float, float> spaceSize = getSpaceSize();

    std::pair<float, float> position1 = {0, 0};
    std::pair<float, float> position2 = {spaceSize.first ,0};
    std::pair<float, float> position3 = {0,spaceSize.second};
    std::pair<float, float> position4 = spaceSize;
    std::pair<float, float> position5 = {spaceSize.first/2,spaceSize.second/2};

    std::pair<float, float> size = {spaceSize.first/2, spaceSize.first/2};

    config1.fillColor = sf::Color::Red;
    config2.fillColor = sf::Color::Red;
    config3.fillColor = sf::Color::Red;
    config4.fillColor = sf::Color::Red;
    config5.fillColor = sf::Color::Yellow;

    Anchor anchor = Anchor::Center;

    after(1.0f,
    [this, position1, size, config1, anchor]{
        auto model = ModelFactory::createModel(getCtx(), position1, size,config1, anchor);
        addModel(std::move(model));
    });

    after(2.0f,
    [this, position2, size, config2, anchor]{
        auto model = ModelFactory::createModel(getCtx(), position2, size,config2, anchor);
        addModel(std::move(model));
    });

    after(3.0f,
    [this, position3, size, config3, anchor]{
        auto model = ModelFactory::createModel(getCtx(), position3, size,config3, anchor);
        addModel(std::move(model));
    });

    after(4.0f,
    [this, position4, size, config4, anchor]{
        auto model = ModelFactory::createModel(getCtx(), position4, size,config4, anchor);
        addModel(std::move(model));
    });

    after(5.0f,
    [this, position5, size, config5, anchor]{
        auto model = ModelFactory::createModel(getCtx(), position5, size,config5, anchor);
        addModel(std::move(model));
    });
}