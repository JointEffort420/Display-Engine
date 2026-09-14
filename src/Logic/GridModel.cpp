//
// Created by natha on 9/3/2026.
//

#include "Logic/GridModel.h"
#include "Rendering/GridView.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
GridModel::GridModel(
    ModelFactory::Key key,
    const std::pair<float, float>& position,
    const std::pair<float, float>& size,
    const std::pair<unsigned int, unsigned int>& dimensions,
    Anchor anchor):
Model(key, position, size, anchor)
{
    colRowCount = dimensions;
    grid = std::vector<Cell>(colRowCount.first * colRowCount.second);
}

GridModel::~GridModel() = default;

//----------------------------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------------------------
std::pair<unsigned int, unsigned int> GridModel::getCellCoordinate(const std::pair<float, float>& cellWorldPosition) const {
    std::pair<float, float> worldPosition = this->getPosition();
    float relativeX = cellWorldPosition.first - worldPosition.first;
    float relativeY = cellWorldPosition.second - worldPosition.second;

    // Check world-space bounds first
    if (relativeX < 0.0f || relativeY < 0.0f ||
        relativeX >= getSize().first ||
        relativeY >= getSize().second) {

        std::cerr << "Requesting grid index of cell outside of bounds"
                  << std::endl;

        // You may prefer throwing an exception or returning a sentinel value.
        return {0, 0};
        }

    float cellWidth =
        getSize().first / static_cast<float>(colRowCount.first);

    float cellHeight =
        getSize().second / static_cast<float>(colRowCount.second);

    auto x = static_cast<unsigned int>(relativeX / cellWidth);
    auto y = static_cast<unsigned int>(relativeY / cellHeight);

    return {x, y};
}

std::pair<unsigned int, unsigned int> GridModel::getRandomCellCoordinate() const {
    unsigned int x = rand() % colRowCount.first;
    unsigned int y = rand() % colRowCount.second;

    return std::make_pair(x, y);
}

Cell* GridModel::getMutableCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) {
    int x = static_cast<int>(cellCoordinate.first);
    int y = static_cast<int>(cellCoordinate.second);
    int width = static_cast<int>(colRowCount.first);
    int height = static_cast<int>(colRowCount.second);

    if (!walls) {
        // Safe mathematical modulo for wrap-around
        x = (x % width + width) % width;
        y = (y % height + height) % height;
    }

    unsigned int index = static_cast<unsigned int>(y * width + x);
    return &grid[index];
}

const Cell* GridModel::getConstCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) const {
    int x = static_cast<int>(cellCoordinate.first);
    int y = static_cast<int>(cellCoordinate.second);
    int width = static_cast<int>(colRowCount.first);
    int height = static_cast<int>(colRowCount.second);

    if (!walls) {
        // Safe mathematical modulo for wrap-around
        x = (x % width + width) % width;
        y = (y % height + height) % height;
    }

    unsigned int index = static_cast<unsigned int>(y * width + x);
    return &grid[index];
}

std::pair<unsigned int, unsigned int> GridModel::getColRowCount() const {return colRowCount;}
std::pair<float, float> GridModel::getCellSize() const {
    return std::make_pair(getSize().first/colRowCount.first, getSize().second/colRowCount.second);
}
bool GridModel::isInBounds(const std::pair<unsigned int, unsigned int>& gridCoordinate) const {
    const unsigned int x = gridCoordinate.first;
    const unsigned int y = gridCoordinate.second;
    const unsigned int gridWidth = colRowCount.first;
    const unsigned int gridHeight = colRowCount.second;

    return x < gridWidth && y < gridHeight;
}

bool GridModel::isOn() const {
    return on;
}

bool GridModel::hasWalls() const {
    return walls;
}


unsigned int GridModel::getAliveNeighbourCount(const std::pair<unsigned int, unsigned int>& cellCoordinate) const {
    const auto [col, row] = cellCoordinate;
    const int width = static_cast<int>(colRowCount.first);
    const int height = static_cast<int>(colRowCount.second);
    unsigned int count = 0;

    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
        for (int colOffset = -1; colOffset <= 1; ++colOffset) {

            // Don't count the cell itself
            if (rowOffset == 0 && colOffset == 0)
                continue;

            int neighbourRow = static_cast<int>(row) + rowOffset;
            int neighbourCol = static_cast<int>(col) + colOffset;

            if (walls) {
                // Ignore neighbours outside the grid when walls exist
                if (neighbourCol < 0 || neighbourCol >= width ||
                    neighbourRow < 0 || neighbourRow >= height) {
                    continue;
                    }
            } else {
                // Wrap around edges when walls do NOT exist
                neighbourCol = (neighbourCol % width + width) % width;
                neighbourRow = (neighbourRow % height + height) % height;
            }

            const auto index = static_cast<std::size_t>(neighbourRow) * width + static_cast<std::size_t>(neighbourCol);

            if (grid[index].alive)
                ++count;
        }
    }

    return count;
}

//----------------------------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------------------------
void GridModel::setRowColCount(const std::pair<unsigned int, unsigned int>& rcc) {this->colRowCount = rcc;}
void GridModel::toggle() {on = !on;}
void GridModel::play() {on = true;}
void GridModel::pause() {on = false;}
void GridModel::setWalls(bool ws) {this->walls = ws;}


//----------------------------------------------------------------------------------------------------------------------
//Logic
//----------------------------------------------------------------------------------------------------------------------
void GridModel::allOn() {
    for (Cell& cell : grid) {
        cell.alive = true;
    }
}

void GridModel::allOff() {
    for (Cell& cell : grid) {
        cell.alive = false;
    }
}

void GridModel::doSomething() {
    toggleCell(getRandomCellCoordinate());
}
void GridModel::toggleCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) {
    if (!isInBounds(cellCoordinate)) return; // silently ignore; caller (Game) is responsible for valid coords later
    Cell* cell = getMutableCell(cellCoordinate);
    cell->alive = !cell->alive;
}

void GridModel::setAlive(const std::pair<unsigned int, unsigned int>& cellCoordinate, bool alive) {
    if (!isInBounds(cellCoordinate)) return;
    Cell* cell = getMutableCell(cellCoordinate);
    cell->alive = alive;
}

void GridModel::updateModel() {
    if (on == false){return;}
    step();
}

void GridModel::onClick(const std::pair<float, float> & worldCoordinates){
    if (isAt(worldCoordinates)) {
        getMutableCell(getCellCoordinate(worldCoordinates))->switchState();
    }
}



