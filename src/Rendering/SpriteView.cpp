//
// Created by natha on 9/9/2026.
//

#include "Rendering/SpriteView.h"
#include "Logic/Model.h"

#include <algorithm>

namespace eng {
    //----------------------------------------------------------------------------------------------------------------------
    // Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    SpriteView::SpriteView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera,
                           const SpriteViewConfig& config)
        : View(key, model, window, camera),
        origin(sf::Vector2f(config.origin.first, config.origin.second)),
        rotation(config.rotation),
        textureRect(config.textureRect),
        useTextureRect(config.useTextureRect),
        color(config.color)
    {
        if (config.texture) {
            sprite.emplace(*config.texture);
            sprite->setOrigin(origin);
            sprite->setRotation(sf::degrees(rotation));//Angle member seems inaccesible
            sprite->setColor(color);
            if (useTextureRect) sprite->setTextureRect(textureRect);

        }
        calibrate();
    }

    //----------------------------------------------------------------------------------------------------------------------
    // Setters
    //----------------------------------------------------------------------------------------------------------------------

    void SpriteView::setTexture(const sf::Texture& texture, bool resetRect) {
        sprite->setTexture(texture, resetRect);
        calibrate();
    }

    void SpriteView::setTextureRect(const sf::IntRect& rectangle) {
        sprite->setTextureRect(rectangle);
        calibrate();
    }

    void SpriteView::setRotation(float angle) {
        rotation = angle;
        if (sprite) sprite->setRotation(sf::degrees(angle));
    }

    void SpriteView::setOrigin(float x, float y) {
        origin.x = x;
        origin.y = y;
        if (sprite) sprite->setOrigin(sf::Vector2f(x, y));
    }

    void SpriteView::setOrigin(const sf::Vector2f& org) {
        origin = org;
        if (sprite) sprite->setOrigin(org);
    }

    void SpriteView::setColor(const sf::Color& c) {
        color = c;
        if (sprite) sprite->setColor(c);
    }

    //----------------------------------------------------------------------------------------------------------------------
    // Getters
    //----------------------------------------------------------------------------------------------------------------------

    float SpriteView::getRotation() const {return rotation;}
    sf::Vector2f SpriteView::getOrigin() const {return origin;}
    sf::Color SpriteView::getColor() const {return color;}
    sf::IntRect SpriteView::getTextureRect() const {return textureRect;}

    //----------------------------------------------------------------------------------------------------------------------
    // Logic
    //----------------------------------------------------------------------------------------------------------------------

    void SpriteView::calibrate() {
        if (!sprite) {
            return;
        }

        const auto [x, y] = getCamera().worldToWindowPosition(getModel().getPosition());
        const auto [width, height] = getCamera().worldToWindowSize(getModel().getSize());

        const sf::FloatRect bounds = sprite->getLocalBounds();

        if (bounds.size.x <= 0.0f || bounds.size.y <= 0.0f) {
            return;
        }

        const float scaleX = width / bounds.size.x;
        const float scaleY = height / bounds.size.y;

        // Preserve aspect ratio.
        const float scale = std::min(scaleX, scaleY);

        sprite->setScale(sf::Vector2f(scale, scale));

        sprite->setOrigin(
            bounds.position +
            bounds.size / 2.0f
        );

        sprite->setPosition(
            sf::Vector2f(
                x + width / 2.0f,
                y + height / 2.0f
            )
        );
    }

    //----------------------------------------------------------------------------------------------------------------------
    // View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------

    void SpriteView::draw() {
        if (!isVisible()) {
            return;
        }
        if (!sprite) {
            return;
        }

        getWindow().draw(*sprite);
    }
}