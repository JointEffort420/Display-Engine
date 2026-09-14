//
// Created by natha on 9/4/2026.
//

#ifndef DISPLAYENGINE_VIEWFACTORY_H
#define DISPLAYENGINE_VIEWFACTORY_H

#include <memory>

#include "Core/EngineContext.h"
#include "Rendering/ViewConfig.h"

namespace eng {
    class Model;
    class View;

    class ViewFactory {
    public:
        ViewFactory() = default;

        friend class ModelFactory;

        class Key {
            friend class ViewFactory;
        private:
            Key() = default;
        };

    private:
        static std::unique_ptr<View> createView(
            EngineContext& ctx,
            const Model& model,
            const ViewConfig& config
        );
    };
}

#endif //DISPLAYENGINE_VIEWFACTORY_H