// Logic/CellBuilder.h — new file
#ifndef DISPLAYENGINE_CELLBUILDER_H
#define DISPLAYENGINE_CELLBUILDER_H

#include <functional>
#include <memory>
#include <utility>

#include "Utils/Anchor.h"

namespace eng {
    class CellModel;
    class EngineContext;

    using CellBuilder = std::function<std::unique_ptr<CellModel>(
        EngineContext&, const std::pair<float, float>&, const std::pair<float, float>&, Anchor)>;

    CellBuilder defaultCellBuilder();
}

#endif