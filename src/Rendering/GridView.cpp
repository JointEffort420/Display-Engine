//
// Created by natha on 9/3/2026.
//

#include "Rendering/GridView.h"
#include "Logic/GridModel.h"

namespace eng {
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

    //----------------------------------------------------------------------------------------------------------------------
    // View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------
    void GridView::draw() const {
        if (!isVisible()) {
            return;
        }

        // Grid squares
        const std::pair<unsigned int, unsigned int> position = getCamera().worldToWindowPosition(grid.getPosition());
        const std::pair<unsigned int, unsigned int> size = getCamera().worldToWindowSize(grid.getSize());
        const auto [columns, rows] = grid.getColRowCount();
        if (columns == 0 || rows == 0) {
            return;
        }

        const float cellWidth  = size.first / static_cast<float>(columns);
        const float cellHeight = size.second / static_cast<float>(rows);

        for (unsigned int column = 0; column < columns; ++column) {
            for (unsigned int row = 0; row < rows; ++row) {
                sf::Vector2f cellPosition = {
                    position.first + column * cellWidth,
                    position.second + row * cellHeight
                };

                sf::RectangleShape cell;
                cell.setPosition(cellPosition);
                cell.setSize({cellWidth, cellHeight});
                cell.setFillColor(deadColor);
                cell.setOutlineThickness(lineWidth);

                getWindow().draw(cell);
            }
        }

        //individual cells
         for (const auto& cell : grid.getConstCells()) {
            if (cell == nullptr) {
                continue;
            }
            cell->drawView();
        }
    }
}