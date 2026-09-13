//
// Created by natha on 9/7/2026.
//

#ifndef GAMEOFLIFE_RANDOMGRID_H
#define GAMEOFLIFE_RANDOMGRID_H

#include "VirtualGridModel.h"
#include "Factory.h"

class RandomGridModel : public VirtualGridModel {
private:

public:
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    RandomGridModel() = delete;
    RandomGridModel(Factory::Key key, const std::pair<float, float>& position, const std::pair<float, float>& size, const std::pair<unsigned int,unsigned int>& dimensions, Anchor anchor = Anchor::Center);
    ~RandomGridModel() override = default;

    //----------------------------------------------------------------------------------------------------------------------
    //Logic
    //----------------------------------------------------------------------------------------------------------------------
    void step() override;

    //----------------------------------------------------------------------------------------------------------------------
    //Subscribtions
    //----------------------------------------------------------------------------------------------------------------------
};

#endif //GAMEOFLIFE_RANDOMGRID_H