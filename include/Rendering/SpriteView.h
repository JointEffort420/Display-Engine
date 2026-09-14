//
// Created by natha on 9/9/2026.
//

#ifndef DISPLAYENGINE_SPRITEVIEW_H
#define DISPLAYENGINE_SPRITEVIEW_H

#include <SFML/Graphics.hpp>

#include "View.h"
namespace eng {
    class SpriteView : public View {
    private:
        //Sprite may be empty upon construction or during runtime
        std::optional<sf::Sprite> sprite;

        //texture and thus sprite may be null
        //Therefore we establish a shadow-state
        sf::Vector2f origin;
        float rotation ;
        sf::IntRect textureRect;
        bool useTextureRect;
        sf::Color color;

    public:
        //----------------------------------------------------------------------------------------------------------------------
        //Constructors & Destructor
        //----------------------------------------------------------------------------------------------------------------------
        SpriteView() = delete;
        SpriteView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera,
                   const SpriteViewConfig& config);

        //----------------------------------------------------------------------------------------------------------------------
        //Setters
        //----------------------------------------------------------------------------------------------------------------------
        void setTexture(const sf::Texture& texture, bool resetRect = false);
        void setTextureRect(const sf::IntRect& rectangle);
        void setRotation(float angle);
        void setOrigin(float x, float y);
        void setOrigin(const sf::Vector2f& origin);
        void setColor(const sf::Color& color);

        //----------------------------------------------------------------------------------------------------------------------
        //Getters
        //----------------------------------------------------------------------------------------------------------------------
        [[nodiscard]] float getRotation() const;
        [[nodiscard]] sf::Vector2f getOrigin() const;
        [[nodiscard]] sf::Color getColor() const;
        [[nodiscard]] sf::IntRect getTextureRect() const;

        //----------------------------------------------------------------------------------------------------------------------
        //Logic
        //----------------------------------------------------------------------------------------------------------------------
        void calibrate();

        //----------------------------------------------------------------------------------------------------------------------
        //View, Draw, Print & Debug
        //----------------------------------------------------------------------------------------------------------------------
        void draw() override;
    };
}
#endif //GAMEOFLIFE_SPRITEVIEW_H