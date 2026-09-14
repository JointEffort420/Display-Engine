//
// Created by natha on 9/6/2026.
//

#include "Rendering/ButtonView.h"
#include "Rendering/PolygonView.h"
#include "Rendering/SpriteView.h"
#include "Rendering/TextView.h"
#include "Logic/ButtonModel.h"

namespace eng {
    //----------------------------------------------------------------------------------------------------------------------
    // Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    ButtonView::ButtonView(
        ViewFactory::Key key,
        const ButtonModel& model,
        Window& window,
        Camera& camera,
        std::unique_ptr<PolygonView> backgroundView,
        std::unique_ptr<TextView> textView,
        std::unique_ptr<SpriteView> iconView
    )
        : CompositeView(
            key,
            model,
            window,
            camera
        ),
          model(model),
          background(*backgroundView),
          text(*textView),
          icon(*iconView)
    {
        // CompositeView becomes the owner of the three components.
        addView(std::move(backgroundView));
        addView(std::move(textView));
        addView(std::move(iconView));

        pressedColor = text.getFillColor();
        hoveredColor = background.getEdgeColor();
    }


    //----------------------------------------------------------------------------------------------------------------------
    // Setters
    //----------------------------------------------------------------------------------------------------------------------

    void ButtonView::setColors(
        const sf::Color& buttonColor,
        const sf::Color& lineColor,
        const sf::Color& textColor
    ) {
        background.setFillColor(buttonColor);
        background.setEdgeColor(lineColor);
        text.setFillColor(textColor);
        baseColor = buttonColor;
        hoveredColor = lineColor;
        pressedColor = textColor;
    }
    void ButtonView::setColors(
        const sf::Color& buttonColor,
        const sf::Color& lineColor,
        const sf::Color& textColor,
        const sf::Color& hoverColor,
        const sf::Color& pressColor
    ) {
        background.setFillColor(buttonColor);
        background.setEdgeColor(lineColor);
        text.setFillColor(textColor);
        baseColor = buttonColor;
        hoveredColor = hoverColor;
        pressedColor = pressColor;
    }


    void ButtonView::setText(const std::string& string) {
        text.setString(string);
    }

    void ButtonView::setFont(const sf::Font* font) {
        text.setFont(font);
    }


    //----------------------------------------------------------------------------------------------------------------------
    // Getters
    //----------------------------------------------------------------------------------------------------------------------

    std::string ButtonView::getText() const {
        return text.getString();
    }


    //----------------------------------------------------------------------------------------------------------------------

    sf::Color ButtonView::getCurrentColor() const {
        if (model.isBeingPressed()) {
            return background.getEdgeColor();
        }

        if (model.isHovered()) {
            return text.getFillColor();
        }

        return background.getFillColor();
    }


    //----------------------------------------------------------------------------------------------------------------------
    // Logic
    //----------------------------------------------------------------------------------------------------------------------

    void ButtonView::update() {
        // First update all child views.
        CompositeView::update();

        //--------------------------------------------------------------------------------------------------------------
        // Visual state
        //--------------------------------------------------------------------------------------------------------------

        background.setFillColor(baseColor);
        if (model.isHovered()) {
            background.setFillColor(hoveredColor);
        }
        if (model.isBeingPressed()) {
            background.setFillColor(pressedColor);
        }
    }

    void ButtonView::calibrate() {
        CompositeView::calibrate();
    }



    //----------------------------------------------------------------------------------------------------------------------
    // View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------

    void ButtonView::draw() {
        if (!isVisible()) {
            return;
        }

        CompositeView::draw();
    }
}