// GridModel.cpp
#include "Logic/GridModel.h"
#include "Logic/CellModel.h"
#include "Core/EngineContext.h"

#include <cstdlib>
#include <iostream>

namespace eng {
    GridModel::GridModel(
        ModelFactory::Key key,
        EngineContext& ctx,
        const std::pair<float, float>& position,
        const std::pair<float, float>& size,
        const std::pair<unsigned int, unsigned int>& dimensions,
        CellBuilder cellBuilder,
        Anchor anchor)
        : Model(key, position, size, anchor), ctx(ctx), cellBuilder(std::move(cellBuilder)), colRowCount(dimensions)
    {
        resizeCells();
    }

    GridModel::~GridModel() = default;

    void GridModel::resizeCells() {
        cells.clear();
        cells.resize(static_cast<std::size_t>(colRowCount.first) * colRowCount.second);
    }

    std::optional<std::size_t> GridModel::resolveIndex(int x, int y) const {
        const int width  = static_cast<int>(colRowCount.first);
        const int height = static_cast<int>(colRowCount.second);
        if (width <= 0 || height <= 0) return std::nullopt;

        if (!walls) {
            x = (x % width  + width)  % width;
            y = (y % height + height) % height;
        } else if (x < 0 || x >= width || y < 0 || y >= height) {
            return std::nullopt;
        }
        return static_cast<std::size_t>(y) * static_cast<std::size_t>(width) + static_cast<std::size_t>(x);
    }

    std::optional<std::size_t> GridModel::resolveIndex(std::pair<unsigned int, unsigned int> cellCoordinate) const {
        return resolveIndex(static_cast<int>(cellCoordinate.first), static_cast<int>(cellCoordinate.second));
    }

    std::pair<float, float> GridModel::cellPositionFor(const std::pair<unsigned int, unsigned int>& cellCoordinate) const {
        const auto cellSize = getCellSize();
        return {
            getPosition().first  + static_cast<float>(cellCoordinate.first)  * cellSize.first,
            getPosition().second + static_cast<float>(cellCoordinate.second) * cellSize.second
        };
    }

    std::optional<std::size_t> GridModel::getCellIndex(const std::pair<unsigned int, unsigned int>& cellCoordinate) const {
        return resolveIndex(cellCoordinate);
    }

    std::pair<unsigned int, unsigned int> GridModel::getCellCoordinate(const std::pair<float, float>& cellWorldPosition) const {
        const std::pair<float, float> worldPosition = getPosition();
        const float relativeX = cellWorldPosition.first  - worldPosition.first;
        const float relativeY = cellWorldPosition.second - worldPosition.second;

        if (relativeX < 0.0f || relativeY < 0.0f ||
            relativeX >= getSize().first || relativeY >= getSize().second) {
            std::cerr << "GridModel::getCellCoordinate(): position outside grid bounds\n";
            return {0, 0};
        }

        const auto cellSize = getCellSize();
        return {
            static_cast<unsigned int>(relativeX / cellSize.first),
            static_cast<unsigned int>(relativeY / cellSize.second)
        };
    }

    std::pair<unsigned int, unsigned int> GridModel::getRandomCellCoordinate() const {
        return {
            static_cast<unsigned int>(std::rand()) % colRowCount.first,
            static_cast<unsigned int>(std::rand()) % colRowCount.second
        };
    }

    CellModel* GridModel::getMutableCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) {
        auto index = resolveIndex(cellCoordinate);
        if (!index) {
            std::cerr << "GridModel::getMutableCell(): coordinate out of bounds\n";
            return nullptr;
        }
        return cells[*index].get();
    }

    const CellModel* GridModel::getConstCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) const {
        auto index = resolveIndex(cellCoordinate);
        if (!index) {
            std::cerr << "GridModel::getConstCell(): coordinate out of bounds\n";
            return nullptr;
        }
        return cells[*index].get();
    }

    std::pair<unsigned int, unsigned int> GridModel::getColRowCount() const { return colRowCount; }

    std::pair<float, float> GridModel::getCellSize() const {
        return { getSize().first / colRowCount.first, getSize().second / colRowCount.second };
    }

    const std::vector<std::unique_ptr<CellModel>>& GridModel::getConstCells() const { return cells; }

    bool GridModel::isInBounds(const std::pair<unsigned int, unsigned int>& gridCoordinate) const {
        return gridCoordinate.first < colRowCount.first && gridCoordinate.second < colRowCount.second;
    }

    bool GridModel::isOn() const { return on; }
    bool GridModel::hasWalls() const { return walls; }

    unsigned int GridModel::getNeighbourCount(const std::pair<unsigned int, unsigned int>& cellCoordinate) const {
        unsigned int count = 0;
        const int col = static_cast<int>(cellCoordinate.first);
        const int row = static_cast<int>(cellCoordinate.second);

        for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
            for (int colOffset = -1; colOffset <= 1; ++colOffset) {
                if (rowOffset == 0 && colOffset == 0) continue;
                auto index = resolveIndex(col + colOffset, row + rowOffset);
                if (index && cells[*index]) ++count;
            }
        }
        return count;
    }

    void GridModel::setRowColCount(const std::pair<unsigned int, unsigned int>& rowColCount) {
        colRowCount = rowColCount;
        resizeCells();
    }

    void GridModel::toggle() { on = !on; }
    void GridModel::play()   { on = true; }
    void GridModel::pause()  { on = false; }
    void GridModel::setWalls(bool ws) { walls = ws; }

    void GridModel::addCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) {
        auto index = resolveIndex(cellCoordinate);
        if (!index) {
            std::cerr << "GridModel::addCell(): coordinate out of bounds\n";
            return;
        }
        if (!cellBuilder) {
            std::cerr << "GridModel::addCell(): no cellBuilder set\n";
            return;
        }
        cells[*index] = cellBuilder(ctx, cellPositionFor(cellCoordinate), getCellSize(), Anchor::TopLeft);
    }

    void GridModel::removeCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) {
        auto index = resolveIndex(cellCoordinate);
        if (!index) {
            std::cerr << "GridModel::removeCell(): coordinate out of bounds\n";
            return;
        }
        cells[*index].reset();
    }

    void GridModel::toggleCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) {
        auto index = resolveIndex(cellCoordinate);
        if (!index) {
            std::cerr << "GridModel::toggleCell(): coordinate out of bounds\n";
            return;
        }
        if (cells[*index]) {
            cells[*index].reset();
        } else {
            addCell(cellCoordinate);
        }
    }

    void GridModel::fill() {
        for (unsigned int row = 0; row < colRowCount.second; ++row) {
            for (unsigned int col = 0; col < colRowCount.first; ++col) {
                addCell({col, row});
            }
        }
    }

    void GridModel::empty() {
        for (auto& cell : cells) cell.reset();
    }

    void GridModel::updateModel() {
        if (!on) return;
        step();
    }

    void GridModel::calibrateView() {
        for (auto& cell : cells) {
            if (!cell) continue;
            cell->calibrateView();
        }
    }

    bool GridModel::onClick(const std::pair<float, float>& worldCoordinates) {
        if (isAt(worldCoordinates)) {
            toggleCell(getCellCoordinate(worldCoordinates));
            return true;
        }
        return false;
    }
}