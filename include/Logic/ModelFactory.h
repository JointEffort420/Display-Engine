//
// Created by natha on 9/4/2026.
//

#ifndef DISPLAYENGINE_MODELFACTORY_H
#define DISPLAYENGINE_MODELFACTORY_H

#include <memory>
#include <type_traits>

#include "Utils/Anchor.h"
#include "Rendering/ViewConfig.h"
#include "Rendering/ViewFactory.h"
#include "Core/EngineContext.h"

namespace eng {
    class Model;
    class GridModel;
    class ButtonModel;

    // Sole responsibility: construct a Model (concrete or, for GridModel,
    // caller-specified subclass) and wire it to its View via ViewFactory.
    // This is the ONLY class permitted to call ViewFactory::createView.
    class ModelFactory {
    public:
        ModelFactory() = default;

        class Key {
            friend class ModelFactory;
        private:
            Key() = default;
        };

        //------------------------------------------------------------------------------------------------------------------
        // Plain Model (e.g. a static background panel — no logic of its own)
        //------------------------------------------------------------------------------------------------------------------
        static std::unique_ptr<Model> createModel(
            EngineContext& ctx,
            const std::pair<float, float>& position,
            const std::pair<float, float>& size,
            const ViewConfig& config = defaultPolygonConfig,
            Anchor anchor = Anchor::TopLeft
        );

        //------------------------------------------------------------------------------------------------------------------
        // Grid — templated: GridModel is abstract, the caller names the concrete
        // automaton subclass (e.g. createGrid<ConwayGridModel>(...)).
        // Args are forwarded to GridT's constructor after the standard grid args.
        //------------------------------------------------------------------------------------------------------------------
        template<typename GridT, typename... Args>
        static std::unique_ptr<GridT> createGrid(
            EngineContext& ctx,
            const std::pair<float, float>& position,
            const std::pair<float, float>& size,
            const std::pair<unsigned int, unsigned int>& cellDimensions,
            const GridViewConfig& config = defaultGridViewConfig,
            Anchor anchor = Anchor::TopLeft,
            Args&&... args
        ) {
            static_assert(std::is_base_of_v<GridModel, GridT>,
                          "GridT must derive from GridModel");

            auto model = std::make_unique<GridT>(
                Key(), position, size, cellDimensions, anchor,
                std::forward<Args>(args)...
            );

            auto view = ViewFactory::createView(ctx, *model, config);
            if (!view) return nullptr;

            model->setView(Key(), std::move(view));
            return model;
        }

        //------------------------------------------------------------------------------------------------------------------
        // Button
        //------------------------------------------------------------------------------------------------------------------
        static std::unique_ptr<ButtonModel> createButton(
            EngineContext& ctx,
            const std::pair<float, float>& position,
            const std::pair<float, float>& size,
            const ButtonViewConfig& config = defaultButtonConfig,
            Anchor anchor = Anchor::TopLeft
        );
    };
}

#endif //DISPLAYENGINE_MODELFACTORY_H