//
// Created by natha on 9/4/2026.
//

#include "Window/Camera.h"

#include <iostream>

//----------------------------------------------------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------------------------------------------------
Camera::Camera(const std::pair<float, float>& worldSize, const std::pair<unsigned int, unsigned int>& windowSize)
    : windowSize(windowSize), worldSize(worldSize) {
    calculateScale();
}

//----------------------------------------------------------------------------------------------------------------------
// Setters
//----------------------------------------------------------------------------------------------------------------------
void Camera::setWindowDimensions(std::pair<unsigned int, unsigned int> dimensions) {
    this->windowSize = dimensions;
    calculateScale();
}

void Camera::setWorldDimensions(std::pair<float, float> dimensions) {
    this->worldSize = dimensions;
    calculateScale();
}

//----------------------------------------------------------------------------------------------------------------------
// Logic & Calculation
//----------------------------------------------------------------------------------------------------------------------
void Camera::calculateScale() {
    if (worldSize.first <= 0.0f || worldSize.second <= 0.0f ||
        windowSize.first == 0 || windowSize.second == 0) {
        uniformScale = 1.0f;
        offset = {0.0f, 0.0f};
        return;
    }

    const float scaleX = static_cast<float>(windowSize.first) / worldSize.first;
    const float scaleY = static_cast<float>(windowSize.second) / worldSize.second;

    // Letterbox/Pillarbox rule: fit whole world inside window while maximizing area
    uniformScale = std::min(scaleX, scaleY);

    const float contentWidth  = worldSize.first  * uniformScale;
    const float contentHeight = worldSize.second * uniformScale;

    // Center the rendering area in the window
    offset = {
        (static_cast<float>(windowSize.first)  - contentWidth)  * 0.5f,
        (static_cast<float>(windowSize.second) - contentHeight) * 0.5f
    };
}

ViewportRect Camera::getViewport() const {
    return {
        static_cast<int>(offset.first),
        static_cast<int>(offset.second),
        static_cast<int>(worldSize.first * uniformScale),
        static_cast<int>(worldSize.second * uniformScale)
    };
}

//----------------------------------------------------------------------------------------------------------------------
// Coordinate Transformations
//----------------------------------------------------------------------------------------------------------------------
std::pair<float, float> Camera::worldToWindowPosition(std::pair<float, float> worldPos, bool flipY) const {
    float posY = worldPos.second;
    if (flipY) {
        posY = worldSize.second - posY;
    }

    return {
        worldPos.first * uniformScale + offset.first,
        posY * uniformScale + offset.second
    };
}

std::pair<float, float> Camera::worldToWindowSize(std::pair<float, float> size) const {
    return {
        size.first * uniformScale,
        size.second * uniformScale
    };
}

std::pair<float, float> Camera::windowToWorldPosition(std::pair<unsigned int, unsigned int> windowPos, bool flipY) const {
    float wx = (static_cast<float>(windowPos.first) - offset.first) / uniformScale;
    float wy = (static_cast<float>(windowPos.second) - offset.second) / uniformScale;

    if (flipY) {
        wy = worldSize.second - wy;
    }

    return {wx, wy};
}

std::pair<float, float> Camera::windowToWorldSize(std::pair<unsigned int, unsigned int> size) const {
    return {
        static_cast<float>(size.first) / uniformScale,
        static_cast<float>(size.second) / uniformScale
    };
}