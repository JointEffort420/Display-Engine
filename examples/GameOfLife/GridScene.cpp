//
// Created by natha on 9/17/2026.
//

#include "GridScene.h"

#include "Logic/ModelFactory.h"
#include "Rendering/ViewConfig.h"

void GridScene::onEnter() {
    eng::PolygonViewConfig cellConfig;
    cellConfig.relativePoints = {
                    {0.5f, 0.0f},
                    {0.0f, 0.3f},
                    {1.0f, 0.3f},
                    {0.2f, 1.0f},
                    {0.8f, 1.0f}
    };
    cellConfig.edgeThickness = 5;

    eng::GridViewConfig gridConfig;
    gridConfig.cellConfig = cellConfig;
    gridConfig.cellBuilder = eng::defaultCellBuilder(cellConfig);

    grid = addModel({1, 1}, {98, 98}, gridConfig);
    every(0.1, [this] {grid->toggleCell(grid->getRandomCellCoordinate());});

}
bool GridScene::onLeftPressed(const std::pair<unsigned int, unsigned int> &windowCoordinates) {
    return grid->onClick(getCtx().camera.windowToWorldPosition(windowCoordinates));
}
