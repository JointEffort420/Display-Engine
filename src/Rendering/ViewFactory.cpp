//
// Created by natha on 9/4/2026.
//

#include <iostream>
#include <type_traits>
#include <variant>

#include "Rendering/ViewFactory.h"
#include "Rendering/PolygonView.h"
#include "Rendering/TextView.h"
#include "Rendering/SpriteView.h"
#include "Rendering/GridView.h"
#include "Rendering/ButtonView.h"

#include "Logic/Model.h"
#include "Logic/GridModel.h"
#include "Logic/ButtonModel.h"

std::unique_ptr<View> ViewFactory::createView(
    EngineContext& ctx,
    const Model& model,
    const ViewConfig& config
) {
    return std::visit(
        [&](const auto& viewConfig) -> std::unique_ptr<View> {
            using T = std::decay_t<decltype(viewConfig)>;

            //------------------------------------------------------------------------------------------------
            // Polygon
            //------------------------------------------------------------------------------------------------
            if constexpr (std::is_same_v<T, PolygonViewConfig>) {
                return std::make_unique<PolygonView>(
                    Key(), model, ctx.window, ctx.camera, viewConfig
                );
            }

            //------------------------------------------------------------------------------------------------
            // Text
            //------------------------------------------------------------------------------------------------
            else if constexpr (std::is_same_v<T, TextViewConfig>) {
                return std::make_unique<TextView>(
                    Key(), model, ctx.window, ctx.camera, viewConfig
                );
            }

            //------------------------------------------------------------------------------------------------
            // Sprite
            //------------------------------------------------------------------------------------------------
            else if constexpr (std::is_same_v<T, SpriteViewConfig>) {
                return std::make_unique<SpriteView>(
                    Key(), model, ctx.window, ctx.camera, viewConfig
                );
            }

            //------------------------------------------------------------------------------------------------
            // Grid
            //------------------------------------------------------------------------------------------------
            else if constexpr (std::is_same_v<T, GridViewConfig>) {
                const auto* grid = dynamic_cast<const GridModel*>(&model);

                if (grid == nullptr) {
                    std::cerr << "ViewFactory::createView(): GridViewConfig requires a GridModel.\n";
                    return nullptr;
                }

                return std::make_unique<GridView>(
                    Key(), *grid, ctx.window, ctx.camera, viewConfig
                );
            }

            //------------------------------------------------------------------------------------------------
            // Button
            //------------------------------------------------------------------------------------------------
            else if constexpr (std::is_same_v<T, ButtonViewConfig>) {
                const auto* button = dynamic_cast<const ButtonModel*>(&model);

                if (button == nullptr) {
                    std::cerr << "ViewFactory::createView(): ButtonViewConfig requires a ButtonModel.\n";
                    return nullptr;
                }

                auto background = std::make_unique<PolygonView>(
                    Key(), model, ctx.window, ctx.camera, viewConfig.polygonConfig
                );
                auto text = std::make_unique<TextView>(
                    Key(), model, ctx.window, ctx.camera, viewConfig.textConfig
                );
                auto icon = std::make_unique<SpriteView>(
                    Key(), model, ctx.window, ctx.camera, viewConfig.spriteConfig
                );

                return std::make_unique<ButtonView>(
                    Key(), *button, ctx.window, ctx.camera,
                    std::move(background), std::move(text), std::move(icon)
                );
            }

            //------------------------------------------------------------------------------------------------
            // Unknown
            //------------------------------------------------------------------------------------------------
            else {
                std::cerr << "ViewFactory::createView(): unknown ViewConfig alternative.\n";
                return nullptr;
            }
        },
        config
    );
}