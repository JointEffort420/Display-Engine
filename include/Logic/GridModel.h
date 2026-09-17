#ifndef DISPLAYENGINE_GRIDMODEL_H
#define DISPLAYENGINE_GRIDMODEL_H

#include <vector>
#include <iostream>
#include <ostream>

#include "Model.h"
#include <Logic/CellModel.h>

namespace eng {
  class GridView;
  class ModelFactory;

  class GridModel : public Model {
  private:
   std::vector<std::unique_ptr<CellModel>> cells;
   std::pair<unsigned int, unsigned int> colRowCount;//Determines amount of rows and columns

   bool on = false;
   // !toroidal topology (wrap-around/teleport behavior)
   bool walls = true;

  protected:
   CellModel* getMutableCell(const std::pair<unsigned int, unsigned int>& cellCoordinate);

  public:
   //----------------------------------------------------------------------------------------------------------------------
   //Constructors & Destructor
   //----------------------------------------------------------------------------------------------------------------------
   GridModel() = delete;
   GridModel(ModelFactory::Key key, const std::pair<float, float>& position, const std::pair<float, float>& size, const std::pair<unsigned int,unsigned int>& dimensions, Anchor anchor = Anchor::Center);
   ~GridModel() override;

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
   [[nodiscard]] const CellModel* getConstCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) const;
   [[nodiscard]] std::pair<unsigned int, unsigned int> getColRowCount() const;
   [[nodiscard]] std::pair<float, float> getCellSize() const;
   [[nodiscard]] const std::vector<std::unique_ptr<CellModel>>& getConstCells() const;
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
   void calibrateView() override;//Also take into account the cells
   void drawCells();
   virtual void step(){}

   void onClick(const std::pair<float, float> & worldCoordinates);
  };
}

#endif //DISPLAYENGINE_GRIDMODEL_H