//
// Created by natha on 9/14/2026.
//

#include "TestState.h"

#include <Resources/Font.h>

void TestState::onEnter() {
    eng::PolygonViewConfig config1;
    eng::PolygonViewConfig config2;
    eng::PolygonViewConfig config3;
    eng::PolygonViewConfig config4;
    eng::PolygonViewConfig config5;

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

    eng::Anchor anchor = eng::Anchor::Center;

    after(1.0f,
    [this, position1, size, config1, anchor]{addModel(position1, size,config1, anchor);});
    after(2.0f,
    [this, position2, size, config2, anchor]{addModel(position2, size,config2, anchor);});
    after(3.0f,
    [this, position3, size, config3, anchor]{addModel(position3, size,config3, anchor);});
    after(4.0f,
    [this, position4, size, config4, anchor]{addModel(position4, size,config4, anchor);});
    after(5.0f,
    [this, position5, size, config5, anchor]{addModel(position5, size,config5, anchor);});


    //text tests
    eng::TextViewConfig textConfig;
    textConfig.font = eng::Font::fromFile("../examples/Sandbox/assets/custom_font.ttf");

    addModel({5, 5}, {10, 10}, textConfig);

    eng::TextViewConfig textConfigTwo;

    addModel({55, 5}, {10, 10}, textConfigTwo);

    //texture tests
    eng::SpriteViewConfig spriteConfig;
    spriteConfig.texture = eng::Texture::fromFile("../examples/Sandbox/assets/rook.png");
    addModel({50, 50}, {30, 30}, spriteConfig);
}