//
// Created by natha on 9/4/2026.
//

#include "Window/Camera.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
Camera::Camera(const std::pair<unsigned int, unsigned int>& windowDimensions):
    windowDimensions(windowDimensions){
    calculateScale();
}

//----------------------------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------------------------
void Camera::setWindowDimensions(std::pair<unsigned int, unsigned int> dimensions) {
    this->windowDimensions = dimensions;
    calculateScale();
}
void Camera::setWorldDimensions(std::pair<float, float> dimensions) {
    this->worldDimensions = dimensions;
    calculateScale();
}

//----------------------------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------------------------
Camera* Camera::get(){return this;}

std::pair<float, float> Camera::getWorldDimensions() const {
    return worldDimensions;
}
std::pair<unsigned int, unsigned int> Camera::getWindowDimensions() const {
    return windowDimensions;
}

//----------------------------------------------------------------------------------------------------------------------
//Logic
//----------------------------------------------------------------------------------------------------------------------
void Camera::calculateScale() {
    float scaleX = windowDimensions.first  / worldDimensions.first;
    float scaleY = windowDimensions.second / worldDimensions.second;

    uniformScale = std::min(scaleX, scaleY);   // <-- the actual fix: one shared scale, not two

    float contentWidth  = worldDimensions.first  * uniformScale;
    float contentHeight = worldDimensions.second * uniformScale;

    offset = {
        (static_cast<float>(windowDimensions.first)  - contentWidth)  / 2.f,
        (static_cast<float>(windowDimensions.second) - contentHeight) / 2.f
    };
}

std::pair<float, float> Camera::worldToWindowPosition(std::pair<float, float> worldPosition) const {
    return {
        worldPosition.first  * uniformScale + offset.first,
        worldPosition.second * uniformScale + offset.second
    };
}

std::pair<float, float> Camera::worldToWindowSize(std::pair<float, float> worldPosition) const {
    return {
        worldPosition.first  * uniformScale,
        worldPosition.second * uniformScale
    };
}


std::pair<float, float> Camera::windowToWorldPosition(std::pair<unsigned int, unsigned int> windowPosition) const {
    return {
        (static_cast<float>(windowPosition.first)  - offset.first)  / uniformScale,
        (static_cast<float>(windowPosition.second) - offset.second) / uniformScale
    };
}

std::pair<float, float> Camera::windowToWorldSize(std::pair<unsigned int, unsigned int> windowPosition) const {
    return {
        static_cast<float>(windowPosition.first)  / uniformScale,
        static_cast<float>(windowPosition.second) / uniformScale
    };
}

//----------------------------------------------------------------------------------------------------------------------
//Subscribtions
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//View, Draw, Print & Debug
//----------------------------------------------------------------------------------------------------------------------