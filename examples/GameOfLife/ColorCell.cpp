//
// Created by s0243038 on 30/09/2026.
//

#include "ColorCell.h"

ColorCell::ColorCell() {
    eng::PolygonViewConfig config;
    config.fillColor = {static_cast<unsigned char>(getPosition().first/2), 0, 200};
    view = eng::ViewFactory::createView()
}
