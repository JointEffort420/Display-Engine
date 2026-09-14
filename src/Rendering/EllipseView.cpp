//
// Created by natha on 9/9/2026.
//

#include "Rendering/EllipseView.h"
#include "Logic/Model.h"

namespace eng {
    //----------------------------------------------------------------------------------------------------------------------
    // Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    EllipseView::EllipseView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera,
                             const EllipseViewConfig& config)
        : View(key, model, window, camera),
        fill(config.fill),
        edge(config.edge),
        fillColor(config.fillColor),
        edgeColor(config.edgeColor)
        {
            ellipse->setPointCount(24);
            calibrate();
        }

    //----------------------------------------------------------------------------------------------------------------------
    // Setters
    //----------------------------------------------------------------------------------------------------------------------
    void EllipseView::setFill(bool fill) {
        this->fill = fill;
    }

    void EllipseView::setEdge(bool edge) {
        this->edge = edge;
    }

    void EllipseView::setFillColor(const sf::Color& color) {
        fillColor = color;
    }

    void EllipseView::setEdgeColor(const sf::Color& color) {
        edgeColor = color;
    }

    void EllipseView::setColors(const sf::Color& fillColor, const sf::Color& edgeColor) {
        this->fillColor = fillColor;
        this->edgeColor = edgeColor;
    }

    void EllipseView::setPointCount(std::size_t count) {
        ellipse->setPointCount(count);
    }

    //----------------------------------------------------------------------------------------------------------------------
    // Getters
    //----------------------------------------------------------------------------------------------------------------------

    float EllipseView::getRadiusX() const {
        return ellipse->getRadius() * ellipse->getScale().x;
    }

    float EllipseView::getRadiusY() const {
        return ellipse->getRadius() * ellipse->getScale().y;
    }

    bool EllipseView::getFill() const {
        return fill;
    }

    bool EllipseView::getEdge() const {
        return edge;
    }

    sf::Color EllipseView::getFillColor() const {
        return fillColor;
    }

    sf::Color EllipseView::getEdgeColor() const {
        return edgeColor;
    }

    //----------------------------------------------------------------------------------------------------------------------
    // Logic
    //----------------------------------------------------------------------------------------------------------------------

    void EllipseView::calibrate() {
        const auto [x, y] = getCamera().worldToWindowPosition(getModel().getPosition());
        const auto [width, height] = getCamera().worldToWindowSize(getModel().getSize());

        // sf::CircleShape has a radius of 1.
        // Scaling it by width / height therefore gives the desired bounding box.
        ellipse->setRadius(1.0f);
        ellipse->setScale(sf::Vector2f(width, height));
        ellipse->setPosition(sf::Vector2f(x, y));
    }

    //----------------------------------------------------------------------------------------------------------------------
    // View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------

    void EllipseView::draw() {
        if (!isVisible()) {
            return;
        }

        ellipse->setFillColor(fill ? fillColor : sf::Color::Transparent);
        ellipse->setOutlineColor(edge ? edgeColor : sf::Color::Transparent);
        ellipse->setOutlineThickness(edge ? 1.0f : 0.0f);

        getWindow().draw(*ellipse);
    }
}