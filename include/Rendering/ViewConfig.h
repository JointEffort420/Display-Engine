//
// Created by natha on 9/9/2026.
//

#ifndef DISPLAYENGINE_VIEWCONFIG_H
#define DISPLAYENGINE_VIEWCONFIG_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "Resources/FontManager.h"
#include "Resources/TextureManager.h"

namespace eng {
    //----------------------------------------------------------------------------------------------------------------------
    // Polygon
    //----------------------------------------------------------------------------------------------------------------------
    struct PolygonViewConfig {
        std::vector<std::pair<float, float>> relativePoints = {
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f}
        };

        bool fill = true;
        bool edge = false;
        float edgeThickness = 2.f;

        sf::Color fillColor = sf::Color::Black;
        sf::Color edgeColor = sf::Color::White;
    };

    inline const PolygonViewConfig defaultPolygonConfig = {};

    //----------------------------------------------------------------------------------------------------------------------
    // Ellipse
    //----------------------------------------------------------------------------------------------------------------------

    struct EllipseViewConfig {
        bool fill = true;
        bool edge = true;

        sf::Color fillColor = sf::Color::White;
        sf::Color edgeColor = sf::Color::Black;

        unsigned int pointCount = 64;
    };

    inline const EllipseViewConfig defaultEllipseConfig = {};

    //----------------------------------------------------------------------------------------------------------------------
    // Grid
    //----------------------------------------------------------------------------------------------------------------------

    struct GridViewConfig {
        sf::Color aliveColor = sf::Color::Red;
        sf::Color deadColor = sf::Color::Black;
        sf::Color gridLineColor = sf::Color::Red;

        float lineWidth = 1.0f;
    };

    inline const GridViewConfig defaultGridViewConfig = {};

    //----------------------------------------------------------------------------------------------------------------------
    // Text
    //----------------------------------------------------------------------------------------------------------------------

    struct TextViewConfig {
        const sf::Font* font = FontManager::getDefaultFont();

        std::string string = "Lorem ipsum";

        unsigned int characterSize = 20;

        bool fill = true;
        bool edge = false;

        sf::Color fillColor = sf::Color::White;
        sf::Color edgeColor = sf::Color::Black;

        float edgeThickness = 1.0f;
    };

    inline const TextViewConfig defaultTextConfig = {};

    //----------------------------------------------------------------------------------------------------------------------
    // Sprite
    //----------------------------------------------------------------------------------------------------------------------

    struct SpriteViewConfig {
        std::pair<float, float> origin = {0.f, 0.f};
        float rotation = 0.0f;

        const sf::Texture* texture = TextureManager::getDefaultTexture();

        sf::IntRect textureRect = sf::IntRect();

        bool useTextureRect = false;

        sf::Color color = sf::Color::White;
    };
    inline const SpriteViewConfig defaultSpriteConfig = {};

    //----------------------------------------------------------------------------------------------------------------------
    // Button
    //----------------------------------------------------------------------------------------------------------------------
    struct ButtonViewConfig {
        //Window-space
        PolygonViewConfig polygonConfig = defaultPolygonConfig;
        TextViewConfig textConfig = defaultTextConfig;
        SpriteViewConfig spriteConfig = defaultSpriteConfig;
    };

    inline const ButtonViewConfig defaultButtonConfig = {};

    //----------------------------------------------------------------------------------------------------------------------
    // Variant
    //----------------------------------------------------------------------------------------------------------------------
    using ViewConfig = std::variant<
        PolygonViewConfig,
        EllipseViewConfig,
        GridViewConfig,
        TextViewConfig,
        SpriteViewConfig,
        ButtonViewConfig
    >;
}

#endif //DISPLAYENGINE_VIEWCONFIG_H