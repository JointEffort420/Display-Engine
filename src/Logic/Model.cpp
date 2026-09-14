//
// Created by natha on 9/4/2026.
//

#include "Logic/Model.h"
#include "Rendering/View.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
Model::Model(ModelFactory::Key key, const std::pair<float, float>& position, const std::pair<float, float>& size, Anchor anchor): position(position), size(size) {
    if (anchor == Anchor::Center) {
        std::pair<float, float> newPosition = position;
        newPosition.first -= getSize().first/2.0f;
        newPosition.second -= getSize().second/2.0f;

        setPosition(newPosition);
    }
}

Model::~Model() = default;


//----------------------------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------------------------
[[nodiscard]] Model* Model::get() {return this;}
[[nodiscard]] View* Model::getView() {return this->view.get();}
[[nodiscard]] std::pair<float, float> Model::getPosition() const {return this->position;}
[[nodiscard]] std::pair<float, float> Model::getSize() const {return this->size;}

//----------------------------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------------------------
void Model::setView(ModelFactory::Key key, std::unique_ptr<View> newView) {
    view = std::move(newView);
}
void Model::setPosition(const std::pair<float, float>& ps) {
    this->position = ps;
}

void Model::setSize(const std::pair<float, float>& size) {
    this->size = size;
}

//----------------------------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------------------------
[[nodiscard]]bool Model::isAt(const std::pair<float, float>& worldPoint) const {
    float leftMost = getPosition().first;
    float rightMost = getPosition().first + getSize().first;
    float upperMost = getPosition().second;
    float lowerMost = getPosition().second + getSize().second;

    return worldPoint.first > leftMost &&
           worldPoint.first < rightMost &&
           worldPoint.second > upperMost &&
           worldPoint.second < lowerMost;
}

//----------------------------------------------------------------------------------------------------------------------
//Logic
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//View, Draw, Print & Debug
//----------------------------------------------------------------------------------------------------------------------
void Model::updateView() {
    view->update();
}

void Model::drawView() {
    view->draw();
}