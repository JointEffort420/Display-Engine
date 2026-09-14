//
// Created by natha on 9/9/2026.
//

#ifndef DISPLAYENGINE_POLYGONVIEW_H
#define DISPLAYENGINE_POLYGONVIEW_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "View.h"

class PolygonView : public View {
private:
    std::unique_ptr<sf::ConvexShape> polygon;

    //Points in a ([0;1],[0;1])space
    std::vector<std::pair<float, float>> relativePoints;

    bool fill = true;
    bool edge = true;
    float edgeThickness;

    sf::Color fillColor;
    sf::Color edgeColor;

public:
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    PolygonView() = delete;
    PolygonView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera, const PolygonViewConfig& config);

    //----------------------------------------------------------------------------------------------------------------------
    //Setters
    //----------------------------------------------------------------------------------------------------------------------
    void setPoints(const std::vector<std::pair<float, float>>& points);

    void setFill(bool fill);
    void setEdge(bool edge);
    void setEdgeThickness(float thickness);

    void setFillColor(const sf::Color& color);
    void setEdgeColor(const sf::Color& color);

    void setColors(const sf::Color& fillColor, const sf::Color& edgeColor);

    //----------------------------------------------------------------------------------------------------------------------
    //Getters
    //----------------------------------------------------------------------------------------------------------------------
    [[nodiscard]] bool getFill() const;
    [[nodiscard]] bool getEdge() const;

    [[nodiscard]] sf::Color getFillColor() const;
    [[nodiscard]] sf::Color getEdgeColor() const;

    [[nodiscard]] std::size_t getPointCount() const;
    [[nodiscard]] sf::Vector2f getPoint(int index) const;
    [[nodiscard]] std::pair<float, float> getRelativePoint(int index) const;

    //----------------------------------------------------------------------------------------------------------------------
    //Logic
    //----------------------------------------------------------------------------------------------------------------------
    void calibrate();//Calculate the sf::ConvexShape based on the relativePoints

    //----------------------------------------------------------------------------------------------------------------------
    //View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------
    void draw() override;
};

#endif //DISPLAYENGINE_POLYGONVIEW_H