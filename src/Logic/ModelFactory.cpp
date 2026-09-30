//
// Created by natha on 9/4/2026.
//

#include <iostream>

#include "Logic/Model.h"
#include <Logic/GridModel.h>
#include "Logic/ButtonModel.h"
#include "Logic/ModelFactory.h"
#include "Rendering/View.h"

namespace eng {
    std::unique_ptr<Model> ModelFactory::createModel(
        EngineContext& ctx,
        const std::pair<float, float>& position,
        const std::pair<float, float>& size,
        const ViewConfig& config,
        Anchor anchor
    ) {
        return std::visit(
    [&](const auto& viewConfig) -> std::unique_ptr<Model> {
            using T = std::decay_t<decltype(viewConfig)>;

            //------------------------------------------------------------------------------------------------
            // Button
            //------------------------------------------------------------------------------------------------
            if constexpr (std::is_same_v<T, ButtonViewConfig>) {
                auto model = std::make_unique<ButtonModel>(Key(), position, size, anchor);

                auto view = ViewFactory::createView(ctx, *model, config);
                if (!view) {
                    std::cerr << "ModelFactory::createButton(): failed to create ButtonView.\n";
                    return nullptr;
                }

                model->setView(Key(), std::move(view));
                return model;
            }
            //------------------------------------------------------------------------------------------------
            // Grid
            //------------------------------------------------------------------------------------------------
            else if constexpr (std::is_same_v<T, GridViewConfig>) {
                auto model = std::make_unique<GridModel>(
                    Key(), ctx, position, size, viewConfig.gridDimensions, viewConfig.cellBuilder, viewConfig.cellConfig, anchor
                );

                auto view = ViewFactory::createView(ctx, *model, config);
                if (!view) return nullptr;

                model->setView(Key(), std::move(view));
                return model;
            }
            //------------------------------------------------------------------------------------------------
            // Basic model
            //------------------------------------------------------------------------------------------------
            else {
                auto model = std::make_unique<Model>(Key(),  position, size, anchor);

                auto view = ViewFactory::createView(ctx, *model, config);
                if (!view) {
                    std::cerr << "ModelFactory::createModel(): failed to create View.\n";
                    return nullptr;
                }

                model->setView(Key(), std::move(view));
                return model;
            }
        }, config);
    }
}