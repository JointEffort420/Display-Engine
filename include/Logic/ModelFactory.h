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
    class CellModel;
    class Model;
    class GridModel;
    class ButtonModel;

    // Sole responsibility: construct a Model (concrete or, for GridModel,
    // caller-specified subclass) and wire it to its View via ViewFactory.
    // This is the ONLY class permitted to call ViewFactory::createView.
    class ModelFactory {
    public:

        class Key {
            friend class ModelFactory;
        private:
            Key() = default;
        };

        static std::unique_ptr<Model> createModel(
            EngineContext& ctx,
            const std::pair<float, float>& position,
            const std::pair<float, float>& size,
            const ViewConfig& config = defaultPolygonConfig,
            Anchor anchor = Anchor::TopLeft
        );

        template<typename CellT>
    static std::unique_ptr<CellT> createCell(
        EngineContext& ctx,
        const std::pair<float, float>& position,
        const std::pair<float, float>& size,
        const ViewConfig& viewConfig,
        Anchor anchor = Anchor::TopLeft)
        {
            static_assert(std::is_base_of_v<CellModel, CellT>, "CellT must derive from CellModel");
            auto cell = std::make_unique<CellT>(Key(), position, size, anchor);
            auto view = ViewFactory::createView(ctx, *cell, viewConfig);
            cell->setView(Key(), std::move(view));   // matches the pattern already used in createGrid
            return cell;
        }
    };
}

#endif //DISPLAYENGINE_MODELFACTORY_H