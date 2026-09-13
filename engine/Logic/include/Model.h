//
// Created by natha on 9/4/2026.
//

#ifndef GAMEOFLIFE_MODEL_H
#define GAMEOFLIFE_MODEL_H
#include <memory>
#include <utility>

#include "Factory.h"
#include "../../Utils/Anchor.h"

class View;
class Factory;

//Logic-driven basis for entities
class Model {
private:
    std::unique_ptr<View> view;
    std::pair<float, float> position;//World-space
    std::pair<float, float> size;

public:
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    Model() = delete;
    Model(Factory::Key key, const std::pair<float, float>& position, const std::pair<float, float>& size, Anchor anchor = Anchor::Center);
    virtual ~Model();

    //----------------------------------------------------------------------------------------------------------------------
    //Setters
    //----------------------------------------------------------------------------------------------------------------------
    void setView(Factory::Key key, std::unique_ptr<View> newView);
    void setPosition(const std::pair<float, float>& position);
    void setSize(const std::pair<float, float>& size);

    //----------------------------------------------------------------------------------------------------------------------
    //Getters
    //----------------------------------------------------------------------------------------------------------------------
    Model* get();
    View* getView();
    [[nodiscard]] std::pair<float, float> getPosition() const;
    [[nodiscard]] std::pair<float, float> getSize() const;
    [[nodiscard]] bool isAt(const std::pair<float, float>& worldCoordinates) const;

    //----------------------------------------------------------------------------------------------------------------------
    //Subscribtions
    //----------------------------------------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------------------------------------
    //View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------
    virtual void updateView();
    void drawView();
};
#endif //GAMEOFLIFE_MODEL_H