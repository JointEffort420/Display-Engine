//
// Created by natha on 9/9/2026.
//

#include "Rendering/PolygonView.h"
#include "Logic/Model.h"

#include <algorithm>
#include <limits>

//----------------------------------------------------------------------------------------------------------------------
// Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
PolygonView::PolygonView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera,
                         const PolygonViewConfig& config)
    : View(key, model, window, camera), relativePoints(config.relativePoints), edge(config.edge), fillColor(config.fillColor),edgeColor(config.edgeColor), edgeThickness(config.edgeThickness) {
    polygon = std::make_unique<sf::ConvexShape>();
    calibrate();
}

//----------------------------------------------------------------------------------------------------------------------
// Setters
//----------------------------------------------------------------------------------------------------------------------

void PolygonView::setPoints(const std::vector<std::pair<float, float>>& points) {
    relativePoints = points;
    calibrate();
}

void PolygonView::setFill(bool fill) {
    this->fill = fill;
}

void PolygonView::setEdge(bool edge) {
    this->edge = edge;
}

void PolygonView::setEdgeThickness(float thickness) {
    this->edgeThickness = thickness;
}

void PolygonView::setFillColor(const sf::Color& color) {
    fillColor = color;
}

void PolygonView::setEdgeColor(const sf::Color& color) {
    edgeColor = color;
}

void PolygonView::setColors(const sf::Color& fillColor, const sf::Color& edgeColor) {
    this->fillColor = fillColor;
    this->edgeColor = edgeColor;
}

//----------------------------------------------------------------------------------------------------------------------
// Getters
//----------------------------------------------------------------------------------------------------------------------

bool PolygonView::getFill() const {
    return fill;
}

bool PolygonView::getEdge() const {
    return edge;
}

sf::Color PolygonView::getFillColor() const {
    return fillColor;
}

sf::Color PolygonView::getEdgeColor() const {
    return edgeColor;
}

std::size_t PolygonView::getPointCount() const {
    return relativePoints.size();
}

sf::Vector2f PolygonView::getPoint(int index) const {
    return polygon->getPoint(index);
}

std::pair<float, float> PolygonView::getRelativePoint(int index) const {
    return relativePoints[index];
}

//----------------------------------------------------------------------------------------------------------------------
// Logic
//----------------------------------------------------------------------------------------------------------------------
void PolygonView::calibrate() {
    std::pair<unsigned int, unsigned int> windowPosition = getCamera().worldToWindowPosition(getModel().getPosition());
    std::pair<unsigned int, unsigned int> windowSize = getCamera().worldToWindowSize(getModel().getSize());

    polygon->setPointCount(relativePoints.size());

    int index = 0;
    for (const std::pair<float, float> relativePoint : relativePoints) {
        sf::Vector2f point;
        point.x = windowPosition.first + (relativePoint.first * windowSize.first);
        point.y = windowPosition.second + (relativePoint.second * windowSize.second);
        polygon->setPoint(index, point);
        index ++;
    }
}


//----------------------------------------------------------------------------------------------------------------------
// View, Draw, Print & Debug
//----------------------------------------------------------------------------------------------------------------------

void PolygonView::draw() {
    if (!isVisible()) {
        return;
    }

    //reset these values to SFML object in case there's been an update
    polygon->setFillColor(fill ? fillColor : sf::Color::Transparent);
    polygon->setOutlineColor(edge ? edgeColor : sf::Color::Transparent);
    polygon->setOutlineThickness(edge ? edgeThickness : 0.0f);

    getWindow().draw(*polygon);
}