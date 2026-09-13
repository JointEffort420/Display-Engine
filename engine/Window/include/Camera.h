//
// Created by natha on 9/4/2026.
//

#ifndef GAMEOFLIFE_CAMERA_H
#define GAMEOFLIFE_CAMERA_H

#include <utility>

class Camera {
    std::pair<unsigned int, unsigned int> windowDimensions;
    std::pair<float, float> worldDimensions = std::make_pair(1,1);

    float uniformScale = 1.0f;
    std::pair<float, float> offset = std::make_pair(0.f, 0.f);

public:
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    Camera() = delete;
    Camera(const std::pair<unsigned int, unsigned int>& windowDimensions);

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

#endif //GAMEOFLIFE_CAMERA_H