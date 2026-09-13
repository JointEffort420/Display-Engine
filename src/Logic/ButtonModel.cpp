//
// Created by natha on 9/4/2026.
//

#include "../include/ButtonModel.h"
#include "../../Representation/include/ButtonView.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
ButtonModel::ButtonModel(Factory::Key key, const std::pair<float, float>& position, const std::pair<float, float>& size, Anchor anchor): Model(key, position, size, anchor) {}

//----------------------------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------------------------
bool ButtonModel::isHovered() const {return hovered;}
bool ButtonModel::hasBeenPressed() const {return beenPressed;}
bool ButtonModel::isBeingPressed() const {return beingPressed;}

//----------------------------------------------------------------------------------------------------------------------
//Logic
//----------------------------------------------------------------------------------------------------------------------
void ButtonModel::updateModel() {
    reset();
}
bool ButtonModel::contains(const std::pair<float, float>& worldCoordinates) const {return isAt(worldCoordinates);}
void ButtonModel::onMouseMoved(const std::pair<float, float>& worldCoordinates) {hovered = contains(worldCoordinates);}
void ButtonModel::onMouseReleased(const std::pair<float, float>& worldCoordinates) {
    if (!beingPressed)
        return;
    beenPressed = contains(worldCoordinates) && beingPressed;
    beingPressed = false;
}
void ButtonModel::onMousePressed(const std::pair<float, float>& worldCoordinates) {
    beingPressed = contains(worldCoordinates);
}

void ButtonModel::reset() {
    beenPressed = false;
}


//----------------------------------------------------------------------------------------------------------------------
//View, Draw, Print & Debug
//----------------------------------------------------------------------------------------------------------------------