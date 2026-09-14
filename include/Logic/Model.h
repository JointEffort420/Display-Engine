//
// Created by natha on 9/4/2026.
//

#ifndef DISPLAYENGINE_MODEL_H
#define DISPLAYENGINE_MODEL_H

#include <memory>
#include <utility>

#include "ModelFactory.h"
#include "Utils/Anchor.h"

namespace eng {
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
        Model(ModelFactory::Key key, const std::pair<float, float>& position, const std::pair<float, float>& size, Anchor anchor = Anchor::Center);
        virtual ~Model();

        //----------------------------------------------------------------------------------------------------------------------
        //Setters
        //----------------------------------------------------------------------------------------------------------------------
        void setView(ModelFactory::Key key, std::unique_ptr<View> newView);
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
        //Logic
        //----------------------------------------------------------------------------------------------------------------------
        virtual void update(){}

        //----------------------------------------------------------------------------------------------------------------------
        //View, Draw, Print & Debug
        //----------------------------------------------------------------------------------------------------------------------
        void calibrateView();
        virtual void updateView();
        void drawView();
    };
}

#endif //DISPLAYENGINE_MODEL_H