//
// Created by natha on 9/4/2026.
//

#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

//----------------------------------------------------------------------------------------------------------------------
// Models
//----------------------------------------------------------------------------------------------------------------------

#include "../../Logic/include/VirtualGridModel.h"
#include "../../Logic/include/ConwayGridModel.h"
#include "../../Logic/include/RandomGridModel.h"
#include "../../Logic/include/ButtonModel.h"

//----------------------------------------------------------------------------------------------------------------------
// Views
//----------------------------------------------------------------------------------------------------------------------

#include "../../Representation/include/View.h"
#include "../../Representation/include/GridView.h"
#include "../../Representation/include/ButtonView.h"
#include "../../Representation/include/PolygonView.h"
#include "../../Representation/include/EllipseView.h"
#include "../../Representation/include/TextView.h"
#include "../../Representation/include/SpriteView.h"

//----------------------------------------------------------------------------------------------------------------------
// States
//----------------------------------------------------------------------------------------------------------------------

#include "../../States/include/State.h"
#include "../../States/include/StateManager.h"
#include "../../States/include/ConwayState.h"
#include "../../States/include/MenuState.h"

//----------------------------------------------------------------------------------------------------------------------
// Factory
//----------------------------------------------------------------------------------------------------------------------

#include "../include/Factory.h"


//======================================================================================================================
// Models
//======================================================================================================================

std::unique_ptr<Model> Factory::createModel(EngineContext &ctx, const std::pair<float, float> &position, const std::pair<float, float> &size, const ViewConfig &config, Anchor anchor) {
    std::unique_ptr<Model> model = std::make_unique<Model>(Key(), position, size, anchor);
    std::unique_ptr<View> view = createView(ctx, *model, config);
    model->setView(Key(), std::move(view));

    return model;
}

std::unique_ptr<VirtualGridModel> Factory::createGrid(
    EngineContext& ctx,
    GridType gridType,
    const std::pair<float, float>& position,
    const std::pair<float, float>& size,
    const std::pair<unsigned int, unsigned int>& cellDimensions,
    const GridViewConfig& config,
    Anchor anchor
) {
    std::unique_ptr<VirtualGridModel> model = nullptr;

    switch (gridType) {

        case ConwayGrid: {
            model = std::make_unique<ConwayGridModel>(
                Key(),
                position,
                size,
                cellDimensions,
                anchor
            );
            break;
        }

        case RandomGrid: {
            model = std::make_unique<RandomGridModel>(
                Key(),
                position,
                size,
                cellDimensions,
                anchor
            );
            break;
        }

        default: {
            std::cerr
                << "Factory::createGrid(): unknown GridType: "
                << static_cast<int>(gridType)
                << std::endl;

            return nullptr;
        }
    }

    //----------------------------------------------------------------------------------------------------------
    // Create the GridView through the universal View factory
    //----------------------------------------------------------------------------------------------------------

    auto view = createView(
        ctx,
        *model,
        config
    );

    if (view == nullptr) {
        std::cerr
            << "Factory::createGrid(): failed to create GridView."
            << std::endl;

        return nullptr;
    }

    model->setView(
        Key(),
        std::move(view)
    );

    return model;
}


std::unique_ptr<ButtonModel> Factory::createButton(
    EngineContext& ctx,
    ButtonType buttonType,
    const std::pair<float, float>& position,
    const std::pair<float, float>& size,
    const ButtonViewConfig& config,
    Anchor anchor
) {
    auto model = std::make_unique<ButtonModel>(
        Key(),
        position,
        size,
        anchor
    );

    //------------------------------------------------------------------------------------------------------------------
    // Create ButtonView through the universal View factory
    //------------------------------------------------------------------------------------------------------------------

    auto view = createView(
        ctx,
        *model,
        config
    );

    if (view == nullptr) {
        std::cerr
            << "Factory::createButton(): failed to create ButtonView."
            << std::endl;

        return nullptr;
    }

    model->setView(
        Key(),
        std::move(view)
    );

    return model;
}


//======================================================================================================================
// States
//======================================================================================================================

std::unique_ptr<State> Factory::createState(
    EngineContext& ctx,
    StateType stateType
) {
    switch (stateType) {

        case MenuStateType: {
            return std::make_unique<MenuState>(
                Key(),
                ctx
            );
        }

        case ConwayStateType: {
            return std::make_unique<ConwayState>(
                Key(),
                ctx
            );
        }

        default: {
            std::cerr
                << "Factory::createState(): unknown StateType: "
                << static_cast<int>(stateType)
                << std::endl;

            return nullptr;
        }
    }
}


//======================================================================================================================
// Views
//======================================================================================================================

std::unique_ptr<View> Factory::createView(
    EngineContext& ctx,
    const Model& model,
    const ViewConfig& config
) {
    return std::visit(
        [&](const auto& viewConfig) -> std::unique_ptr<View> {

            using T = std::decay_t<decltype(viewConfig)>;

            //----------------------------------------------------------------------------------------------------------
            // Polygon
            //----------------------------------------------------------------------------------------------------------

            if constexpr (std::is_same_v<T, PolygonViewConfig>) {
                auto view = std::make_unique<PolygonView>(
                    Key(),
                    model,
                    ctx.window,
                    ctx.camera,
                    viewConfig
                );

                return view;
            }

            //----------------------------------------------------------------------------------------------------------
            // Ellipse
            //----------------------------------------------------------------------------------------------------------

            else if constexpr (std::is_same_v<T, EllipseViewConfig>) {

                auto view = std::make_unique<EllipseView>(
                    Key(),
                    model,
                    ctx.window,
                    ctx.camera,
                    viewConfig
                );

                return view;
            }

            //----------------------------------------------------------------------------------------------------------
            // Text
            //----------------------------------------------------------------------------------------------------------

            else if constexpr (std::is_same_v<T, TextViewConfig>) {
                auto view = std::make_unique<TextView>(
                    Key(),
                    model,
                    ctx.window,
                    ctx.camera,
                    viewConfig
                );

                return view;
            }

            //----------------------------------------------------------------------------------------------------------
            // Sprite
            //----------------------------------------------------------------------------------------------------------

            else if constexpr (std::is_same_v<T, SpriteViewConfig>) {
                auto view = std::make_unique<SpriteView>(
                    Key(),
                    model,
                    ctx.window,
                    ctx.camera,
                    viewConfig
                );

                return view;
            }

            //----------------------------------------------------------------------------------------------------------
            // Grid
            //----------------------------------------------------------------------------------------------------------

            else if constexpr (std::is_same_v<T, GridViewConfig>) {

                const auto* grid =
                    dynamic_cast<const VirtualGridModel*>(&model);

                if (grid == nullptr) {
                    std::cerr
                        << "Factory::createView(): "
                        << "GridConfig requires a VirtualGridModel."
                        << std::endl;

                    return nullptr;
                }

                auto view = std::make_unique<GridView>(
                    Key(),
                    *grid,
                    ctx.window,
                    ctx.camera,
                    viewConfig
                );

                return view;
            }

            //----------------------------------------------------------------------------------------------------------
            // Button
            //----------------------------------------------------------------------------------------------------------

            else if constexpr (std::is_same_v<T, ButtonViewConfig>) {

                const auto* button =
                    dynamic_cast<const ButtonModel*>(&model);

                if (button == nullptr) {
                    std::cerr
                        << "Factory::createView(): "
                        << "ButtonConfig requires a ButtonModel."
                        << std::endl;

                    return nullptr;
                }

                //----------------------------------------------------------------------------------------------
                // Background
                //----------------------------------------------------------------------------------------------

                auto background = std::make_unique<PolygonView>(
                    Key(),
                    model,
                    ctx.window,
                    ctx.camera,
                    viewConfig.polygonConfig
                );

                //----------------------------------------------------------------------------------------------
                // Text
                //----------------------------------------------------------------------------------------------
                std::unique_ptr<TextView> text = std::make_unique<TextView>(
                    Key(),
                    model,
                    ctx.window,
                    ctx.camera,
                    viewConfig.textConfig
                );

                //----------------------------------------------------------------------------------------------
                // Icon (if texture)
                //----------------------------------------------------------------------------------------------
                std::unique_ptr<SpriteView> icon = std::make_unique<SpriteView>(
                        Key(),
                        model,
                        ctx.window,
                        ctx.camera,
                        viewConfig.spriteConfig
                    );

                //----------------------------------------------------------------------------------------------
                // Button
                //----------------------------------------------------------------------------------------------
                return std::make_unique<ButtonView>(
                    Key(),
                    *button,
                    ctx.window,
                    ctx.camera,
                    std::move(background),
                    std::move(text),
                    std::move(icon)
                );
            }

            //----------------------------------------------------------------------------------------------------------
            // Unknown
            //----------------------------------------------------------------------------------------------------------

            else {
                std::cerr
                    << "Factory::createView(): unknown ViewConfig type."
                    << std::endl;

                return nullptr;
            }
        },
        config
    );
}