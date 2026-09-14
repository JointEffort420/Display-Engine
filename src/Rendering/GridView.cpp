//
// Created by natha on 9/3/2026.
//

#include "Rendering/GridView.h"
#include "Logic/GridModel.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
GridView::GridView(ViewFactory::Key key, const GridModel &grid, Window& window, Camera& camera, const GridViewConfig& config):
    View(key, grid, window, camera),
    grid(grid),
    lineWidth(config.lineWidth),
    aliveColor(config.aliveColor),
    deadColor(config.deadColor),
    gridLineColor(config.gridLineColor)
{}

//----------------------------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------------------------
void GridView::setColors(const sf::Color& ac, const sf::Color& dc, const sf::Color& glc) {
    aliveColor = ac;
    deadColor = dc;
    gridLineColor = glc;
}

//----------------------------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//Subscribtions
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//View, Draw, Print & Debug
//----------------------------------------------------------------------------------------------------------------------
void GridView::draw() {
    //most calculations here should be outsourced to GridView::calibrate()
    const auto [columns, rows] = grid.getColRowCount();

    const auto gridPosition = grid.getPosition();
    const auto gridSize = grid.getSize();

    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int column = 0; column < columns; ++column) {

            const float leftWorld = gridPosition.first + (static_cast<float>(column) / columns) * gridSize.first;
            const float rightWorld = gridPosition.first + (static_cast<float>(column + 1) / columns) * gridSize.first;
            const float topWorld = gridPosition.second + (static_cast<float>(row) / rows) * gridSize.second;
            const float bottomWorld = gridPosition.second + (static_cast<float>(row + 1) / rows) * gridSize.second;
            const auto topLeft = getCamera().worldToWindowPosition({leftWorld, topWorld});
            const auto bottomRight = getCamera().worldToWindowPosition( {rightWorld, bottomWorld});

            sf::RectangleShape shape;

            shape.setPosition({topLeft.first + lineWidth, topLeft.second + lineWidth});
            shape.setSize( {bottomRight.first - topLeft.first - 2 * lineWidth, bottomRight.second - topLeft.second - 2 * lineWidth});

            const Cell* cell = grid.getConstCell({column, row});

            shape.setFillColor(cell->alive ? aliveColor : deadColor);

            shape.setOutlineThickness(lineWidth);
            shape.setOutlineColor(gridLineColor);

            getWindow().draw(shape);
        }
    }
}