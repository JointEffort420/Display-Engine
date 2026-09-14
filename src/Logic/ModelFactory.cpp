//
// Created by natha on 9/4/2026.
//

#include <iostream>

#include "Logic/Model.h"
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
        auto model = std::make_unique<Model>(Key(), position, size, anchor);

        auto view = ViewFactory::createView(ctx, *model, config);
        if (!view) {
            std::cerr << "ModelFactory::createModel(): failed to create View.\n";
            return nullptr;
        }

        model->setView(Key(), std::move(view));
        return model;
    }

    std::unique_ptr<ButtonModel> ModelFactory::createButton(
        EngineContext& ctx,
        const std::pair<float, float>& position,
        const std::pair<float, float>& size,
        const ButtonViewConfig& config,
        Anchor anchor
    ) {
        auto model = std::make_unique<ButtonModel>(Key(), position, size, anchor);

        auto view = ViewFactory::createView(ctx, *model, config);
        if (!view) {
            std::cerr << "ModelFactory::createButton(): failed to create ButtonView.\n";
            return nullptr;
        }

        model->setView(Key(), std::move(view));
        return model;
    }
}