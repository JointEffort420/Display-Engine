//
// Created by natha on 9/4/2026.
//

#ifndef DISPLAYENGINE_BUTTON_H
#define DISPLAYENGINE_BUTTON_H

#include <iostream>
#include <ostream>

#include "../Input/IInputObserver.h"
#include "Model.h"


class Factory;
class ButtonView;

class ButtonModel: public Model {
private:
    bool hovered = false;
    bool beenPressed = false;
    bool beingPressed = false;

public:
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    ButtonModel() = delete;
    ButtonModel(ModelFactory::Key key, const std::pair<float, float>& position, const std::pair<float, float>& size, Anchor anchor = Anchor::Center);
    ~ButtonModel() = default;

    //----------------------------------------------------------------------------------------------------------------------
    //Setters
    //----------------------------------------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------------------------------------
    //Getters
    //----------------------------------------------------------------------------------------------------------------------
    [[nodiscard]] bool hasBeenPressed() const;
    [[nodiscard]] bool isBeingPressed() const;
    [[nodiscard]] bool isHovered() const;
    [[nodiscard]] bool contains(const std::pair<float, float>& worldCoordinates) const;

    //----------------------------------------------------------------------------------------------------------------------
    //Logic
    //----------------------------------------------------------------------------------------------------------------------
    void updateModel();
    void onMouseMoved(const std::pair<float, float>& worldCoordinates);
    void onMousePressed(const std::pair<float, float>& worldCoordinates);
    void onMouseReleased(const std::pair<float, float>& worldCoordinates);
    void reset();


    //----------------------------------------------------------------------------------------------------------------------
    //View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------

};
#endif //GAMEOFLIFE_BUTTON_H