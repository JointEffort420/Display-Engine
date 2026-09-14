//
// Created by natha on 9/4/2026.
//

#ifndef DISPLAYENGINE_CAMERA_H
#define DISPLAYENGINE_CAMERA_H

#include <utility>
#include <algorithm>

class Camera {
    std::pair<unsigned int, unsigned int> windowSize;
    std::pair<float, float> worldSize;

    float uniformScale;
    std::pair<float, float> offset;

public:
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    Camera() = delete;
    Camera(const std::pair<float, float>& worldSize, const std::pair<unsigned int, unsigned int>& windowSize);

    //----------------------------------------------------------------------------------------------------------------------
    //Setters
    //----------------------------------------------------------------------------------------------------------------------
    void setWindowDimensions(std::pair<unsigned int, unsigned int> dimensions);
    void setWorldDimensions(std::pair<float, float> dimensions);

    //----------------------------------------------------------------------------------------------------------------------
    //Getters
    //----------------------------------------------------------------------------------------------------------------------
    Camera* get();
    [[nodiscard]] std::pair<float, float> getWorldDimensions() const;
    [[nodiscard]] std::pair<unsigned int, unsigned int> getWindowDimensions() const;

    [[nodiscard]] float getUniformScale() const { return uniformScale; }
    [[nodiscard]] std::pair<float, float> getOffset() const { return offset; }

    //----------------------------------------------------------------------------------------------------------------------
    //Logic
    //----------------------------------------------------------------------------------------------------------------------
    void calculateScale();
    [[nodiscard]] std::pair<float, float> worldToWindowPosition(std::pair<float, float> worldPosition) const;
    [[nodiscard]] std::pair<float, float> worldToWindowSize(std::pair<float, float> worldPosition) const;
    [[nodiscard]] std::pair<float, float> windowToWorldPosition(std::pair<unsigned int, unsigned int> windowPosition) const;
    [[nodiscard]] std::pair<float, float> windowToWorldSize(std::pair<unsigned int, unsigned int> windowPosition) const;

    //----------------------------------------------------------------------------------------------------------------------
    //Subscribtions
    //----------------------------------------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------------------------------------
    //View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------
};

#endif //DISPLAYENGINE_CAMERA_H