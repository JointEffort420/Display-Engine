//
// Created by natha on 9/17/2026.
//

#ifndef DISPLAYENGINE_CELL_H
#define DISPLAYENGINE_CELL_H

#include <Logic/Model.h>

namespace eng {
    class CellModel : public Model {
    private:
        bool alive;

    public:
        CellModel();

        bool isAlive() const {return alive;}

        void setAlive(bool a = true) {alive = a;}
        void toggleAlive() {
            alive = !alive;
        }
    };
}

#endif //DISPLAYENGINE_CELL_H