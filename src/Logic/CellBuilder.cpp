//
// Created by natha on 9/26/2026.
//
#include "Logic/CellBuilder.h"
#include "Logic/CellModel.h"
#include "Logic/ModelFactory.h"
#include "Rendering/ViewConfig.h"
#include "Rendering/View.h"

namespace eng {
    CellBuilder defaultCellBuilder(PolygonViewConfig cellConfig) {
        return [cellConfig](EngineContext& ctx, const std::pair<float, float>& position,
                  const std::pair<float, float>& size, Anchor anchor) {
            return ModelFactory::createCell<CellModel>(ctx, position, size, cellConfig, anchor);
        };
    }
}