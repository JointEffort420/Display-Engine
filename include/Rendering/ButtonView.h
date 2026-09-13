//
// Created by natha on 9/6/2026.
//

#ifndef GAMEOFLIFE_BUTTONVIEW_H
#define GAMEOFLIFE_BUTTONVIEW_H

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "CompositeView.h"
#include "Window.h"

class ButtonModel;
class PolygonView;
class TextView;
class SpriteView;

class ButtonView : public CompositeView {
private:
    const ButtonModel& model;

    PolygonView& background;
    TextView& text;
    SpriteView& icon;

    sf::Color baseColor;
    sf::Color hoveredColor;
    sf::Color pressedColor;

public:
    //----------------------------------------------------------------------------------------------------------------------
    // Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    ButtonView() = delete;

    ButtonView(
        Factory::Key key,
        const ButtonModel& model,
        Window& window,
        Camera& camera,
        std::unique_ptr<PolygonView> background,
        std::unique_ptr<TextView> text,
        std::unique_ptr<SpriteView> icon
    );

    //----------------------------------------------------------------------------------------------------------------------
    // Setters
    //----------------------------------------------------------------------------------------------------------------------
    void setColors(
        const sf::Color& buttonColor,
        const sf::Color& lineColor,
        const sf::Color& textColor
    );
    void setColors(
        const sf::Color& buttonColor,
        const sf::Color& lineColor,
        const sf::Color& textColor,
        const sf::Color& hoveredColor,
        const sf::Color& pressedColor
    );

    void setText(const std::string& text);
    void setFont(const sf::Font* font);

    //----------------------------------------------------------------------------------------------------------------------
    // Getters
    //----------------------------------------------------------------------------------------------------------------------
    [[nodiscard]] std::string getText() const;

    [[nodiscard]] sf::Color getCurrentColor() const;

    //----------------------------------------------------------------------------------------------------------------------
    // Logic
    //----------------------------------------------------------------------------------------------------------------------
    void update() override;

    //----------------------------------------------------------------------------------------------------------------------
    // View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------
    void draw() override;
};

#endif //GAMEOFLIFE_BUTTONVIEW_H