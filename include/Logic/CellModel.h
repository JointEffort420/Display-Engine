#ifndef DISPLAYENGINE_CELLMODEL_H
#define DISPLAYENGINE_CELLMODEL_H

#include "Model.h"

namespace eng {
    class CellModel : public Model {
    public:
        using Model::Model;   // inherits Model(ModelFactory::Key, position, size, anchor)
        ~CellModel() override = default;
    };
}

#endif //DISPLAYENGINE_CELLMODEL_H