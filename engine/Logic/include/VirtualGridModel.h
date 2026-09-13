//Grid class holds an array. Each entry represents a cell. These cells could be a class themselves or, for Arduino implementations, uint_8.
//Can grid find a cell based on it's coords?
//Should the array be ordened? Yes, this'll make finding a cell easier
//Does a cell know it's own location? For now that doesn't seem necessary

#pragma once
#include <vector>
#include <iostream>
#include <ostream>

#include "Model.h"

class GridView;
class Factory;

struct Cell {
 bool alive = false;

 void switchState() {
  alive = !alive;
 }
};

class VirtualGridModel : public Model {
private:
 std::vector<Cell> grid;
 std::pair<unsigned int, unsigned int> colRowCount;//Determines amount of rows and columns

 bool on = false;
 // !toroidal topology (wrap-around/teleport behavior)
 bool walls = true;

protected:
 Cell* getMutableCell(const std::pair<unsigned int, unsigned int>& cellCoordinate);

public:
 //----------------------------------------------------------------------------------------------------------------------
 //Constructors & Destructor
 //----------------------------------------------------------------------------------------------------------------------
 VirtualGridModel() = delete;
 VirtualGridModel(Factory::Key key, const std::pair<float, float>& position, const std::pair<float, float>& size, const std::pair<unsigned int,unsigned int>& dimensions, Anchor anchor = Anchor::Center);
 ~VirtualGridModel() override;

 //----------------------------------------------------------------------------------------------------------------------
 //Setters
 //----------------------------------------------------------------------------------------------------------------------
 void setRowColCount(const std::pair<unsigned int, unsigned int>& rowColCount);
 void toggle();
 void play();
 void pause();
 void setWalls(bool walls);

 //----------------------------------------------------------------------------------------------------------------------
 //Getters
 //----------------------------------------------------------------------------------------------------------------------
 [[nodiscard]] std::pair<unsigned int, unsigned int> getCellCoordinate(const std::pair<float, float>& cellWorldPosition) const;
 [[nodiscard]] std::pair<unsigned int, unsigned int> getRandomCellCoordinate() const;
 [[nodiscard]] const Cell* getConstCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) const;
 [[nodiscard]] std::pair<unsigned int, unsigned int> getColRowCount() const;
 [[nodiscard]] std::pair<float, float> getCellSize() const;
 [[nodiscard]] bool isInBounds(const std::pair<unsigned int, unsigned int>& gridCoordinate) const;//Checks if a world coordinate is still within grid
 [[nodiscard]] bool isOn() const;
 [[nodiscard]] bool hasWalls() const;
 [[nodiscard]] unsigned int getAliveNeighbourCount(const std::pair<unsigned int, unsigned int>& cellCoordinate) const;

 //----------------------------------------------------------------------------------------------------------------------
 //Logic
 //----------------------------------------------------------------------------------------------------------------------
 void allOn();
 void allOff();
 void doSomething();
 void toggleCell(const std::pair<unsigned int, unsigned int>& cellCoordinate);
 void setAlive(const std::pair<unsigned int, unsigned int>& cellCoordinate, bool alive);
 void updateModel();
 virtual void step() = 0;

 void onClick(const std::pair<float, float> & worldCoordinates);

 //----------------------------------------------------------------------------------------------------------------------
 //Subscribtions
 //----------------------------------------------------------------------------------------------------------------------

 //----------------------------------------------------------------------------------------------------------------------
 //View, Draw, Print & Debug
 //----------------------------------------------------------------------------------------------------------------------
};