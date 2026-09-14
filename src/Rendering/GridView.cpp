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
// Logic
//----------------------------------------------------------------------------------------------------------------------
void GridView::calibrate() {
    const auto [columns, rows] = grid.getColRowCount();
    if (columns == 0 || rows == 0) {
        cellShapes.clear();
        return;
    }

    cellShapes.resize(columns * rows);

    const auto gridPosition = grid.getPosition();
    const auto gridSize = grid.getSize();

    const float colWidth = gridSize.first / static_cast<float>(columns);
    const float rowHeight = gridSize.second / static_cast<float>(rows);

    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int column = 0; column < columns; ++column) {
            const float leftWorld = gridPosition.first + (static_cast<float>(column) * colWidth);
            const float rightWorld = leftWorld + colWidth;
            const float topWorld = gridPosition.second + (static_cast<float>(row) * rowHeight);
            const float bottomWorld = topWorld + rowHeight;

            const auto topLeft = getCamera().worldToWindowPosition({leftWorld, topWorld});
            const auto bottomRight = getCamera().worldToWindowPosition({rightWorld, bottomWorld});

            const float cellWidth = (bottomRight.first - topLeft.first) - (2.0f * lineWidth);
            const float cellHeight = (bottomRight.second - topLeft.second) - (2.0f * lineWidth);

            std::size_t index = row * columns + column;
            sf::RectangleShape& shape = cellShapes[index];

            shape.setPosition({topLeft.first + lineWidth, topLeft.second + lineWidth});
            shape.setSize({cellWidth > 0.0f ? cellWidth : 0.0f, cellHeight > 0.0f ? cellHeight : 0.0f});
            shape.setOutlineThickness(lineWidth);
            shape.setOutlineColor(gridLineColor);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
// View, Draw, Print & Debug
//----------------------------------------------------------------------------------------------------------------------
void GridView::draw() {
    if (!isVisible()) {
        return;
    }

    const auto [columns, rows] = grid.getColRowCount();
    if (cellShapes.size() != columns * rows) {
        calibrate();
    }

    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int column = 0; column < columns; ++column) {
            const Cell* cell = grid.getConstCell({column, row});
            std::size_t index = row * columns + column;

            sf::RectangleShape& shape = cellShapes[index];
            shape.setFillColor(cell->alive ? aliveColor : deadColor);

            getWindow().draw(shape);
        }
    }
}