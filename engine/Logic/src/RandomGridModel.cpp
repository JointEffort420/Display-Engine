//
// Created by natha on 9/7/2026.
//

#include "../include/RandomGridModel.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
RandomGridModel::RandomGridModel(Factory::Key key, const std::pair<float, float>& position, const std::pair<float, float>& size, const std::pair<unsigned int,unsigned int>& dimensions, Anchor anchor): VirtualGridModel(key, position, size, dimensions, anchor) {
    setWalls(false);
}

//----------------------------------------------------------------------------------------------------------------------
//Logic
//----------------------------------------------------------------------------------------------------------------------
void RandomGridModel::step() {
    getMutableCell(getRandomCellCoordinate())-> switchState();
}

//----------------------------------------------------------------------------------------------------------------------
//Subscribtions
//----------------------------------------------------------------------------------------------------------------------

