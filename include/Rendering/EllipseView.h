//
// Created by natha on 9/9/2026.
//

#ifndef DISPLAYENGINE_ELLIPSEVIEW_H
#define DISPLAYENGINE_ELLIPSEVIEW_H

#include <SFML/Graphics.hpp>
#include "View.h"

namespace eng {
    class EllipseView : public View {
    private:
        std::unique_ptr<sf::CircleShape> ellipse;

        bool fill = true;
        bool edge = true;

        sf::Color fillColor = sf::Color::White;
        sf::Color edgeColor = sf::Color::Black;

    public:
        //----------------------------------------------------------------------------------------------------------------------
        //Constructors & Destructor
        //----------------------------------------------------------------------------------------------------------------------
        EllipseView() = delete;
        EllipseView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera);
        EllipseView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera,
                    const EllipseViewConfig& config);

        //----------------------------------------------------------------------------------------------------------------------
        //Setters
        //----------------------------------------------------------------------------------------------------------------------
        void setFill(bool fill);
        void setEdge(bool edge);

        void setFillColor(const sf::Color& color);
        void setEdgeColor(const sf::Color& color);

        void setColors(const sf::Color& fillColor, const sf::Color& edgeColor);

        void setPointCount(std::size_t count);

        //----------------------------------------------------------------------------------------------------------------------
        //Getters
        //----------------------------------------------------------------------------------------------------------------------
        //Returns scale, not the actual radius
        [[nodiscard]] float getRadiusX() const;
        [[nodiscard]] float getRadiusY() const;

        [[nodiscard]] bool getFill() const;
        [[nodiscard]] bool getEdge() const;

        [[nodiscard]] sf::Color getFillColor() const;
        [[nodiscard]] sf::Color getEdgeColor() const;

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

#endif //DISPLAYENGINE_ELLIPSEVIEW_H