//
// Created by natha on 9/4/2026.
//

#ifndef GAMEOFLIFE_FACTORY_H
#define GAMEOFLIFE_FACTORY_H

#include <memory>

#include <SFML/Graphics/Color.hpp>

#include "../../Utils/StateType.h"
#include "../../Utils/GridType.h"
#include "../../Utils/ButtonType.h"
#include "../../Utils/EngineContext.h"
#include "../../Utils/Anchor.h"
#include "../../Utils/ViewConfig.h"

// Models
class Model;
class VirtualGridModel;
class ButtonModel;

// Views
class View;
class ButtonView;

// States
class State;


//----------------------------------------------------------------------------------------------------------------------
// Color palette
//----------------------------------------------------------------------------------------------------------------------

inline sf::Color mainColor = sf::Color(120, 0, 0);
inline sf::Color sideColor = sf::Color(60, 0, 0);


//----------------------------------------------------------------------------------------------------------------------
// Factory
//----------------------------------------------------------------------------------------------------------------------

class Factory {
public:

    Factory() = default;

    class Key {
        friend class Factory;

    private:
        Key() = default;
    };


    //------------------------------------------------------------------------------------------------------------------
    // Models
    //------------------------------------------------------------------------------------------------------------------
    static std::unique_ptr<Model> createModel(
        EngineContext& ctx,
        const std::pair<float, float>& position,
        const std::pair<float, float>& size,
        const ViewConfig& config = defaultPolygonConfig,
        Anchor = Anchor::TopLeft
    );

    static std::unique_ptr<VirtualGridModel> createGrid(
        EngineContext& ctx,
        GridType gridType,
        const std::pair<float, float>& position,
        const std::pair<float, float>& size,
        const std::pair<unsigned int, unsigned int>& cellDimensions,
        const GridViewConfig& config = defaultGridViewConfig,
        Anchor anchor = Anchor::TopLeft
    );

    static std::unique_ptr<ButtonModel> createButton(
        EngineContext& ctx,
        ButtonType buttonType,
        const std::pair<float, float>& position,
        const std::pair<float, float>& size,
        const ButtonViewConfig& config = defaultButtonConfig,
        Anchor anchor = Anchor::TopLeft
    );



    //------------------------------------------------------------------------------------------------------------------
    // States
    //------------------------------------------------------------------------------------------------------------------

    static std::unique_ptr<State> createState(
        EngineContext& ctx,
        StateType stateType
    );

private:
    //------------------------------------------------------------------------------------------------------------------
    // Views
    //------------------------------------------------------------------------------------------------------------------

    static std::unique_ptr<View> createView(
        EngineContext& ctx,
        const Model& model,
        const ViewConfig& config
    );
};

#endif //GAMEOFLIFE_FACTORY_H