//
// Created by natha on 9/4/2026.
//

#ifndef DISPLAYENGINE_CAMERA_H
#define DISPLAYENGINE_CAMERA_H

#include <utility>
#include <algorithm>

namespace eng {
    struct ViewportRect {
        int x;
        int y;
        int width;
        int height;
    };

    class Camera {
        std::pair<unsigned int, unsigned int> windowSize{800, 600};
        std::pair<float, float> worldSize{1.0f, 1.0f};

        float uniformScale{1.0f};
        std::pair<float, float> offset{0.0f, 0.0f};

    public:
        //----------------------------------------------------------------------------------------------------------------------
        // Constructors
        //----------------------------------------------------------------------------------------------------------------------
        Camera() = default;
        Camera(const std::pair<float, float>& worldSize, const std::pair<unsigned int, unsigned int>& windowSize);

        //----------------------------------------------------------------------------------------------------------------------
        // Setters
        //----------------------------------------------------------------------------------------------------------------------
        void setWindowDimensions(std::pair<unsigned int, unsigned int> dimensions);
        void setWorldDimensions(std::pair<float, float> dimensions);

        //----------------------------------------------------------------------------------------------------------------------
        // Getters
        //----------------------------------------------------------------------------------------------------------------------
        [[nodiscard]] std::pair<float, float> getWorldDimensions() const { return worldSize; }
        [[nodiscard]] std::pair<unsigned int, unsigned int> getWindowDimensions() const { return windowSize; }
        [[nodiscard]] float getUniformScale() const { return uniformScale; }
        [[nodiscard]] std::pair<float, float> getOffset() const { return offset; }

        // Returns the exact pixel region (X, Y, Width, Height) occupied by the letterboxed world on screen.
        [[nodiscard]] ViewportRect getViewport() const;

        //----------------------------------------------------------------------------------------------------------------------
        // Coordinate Transformations
        //----------------------------------------------------------------------------------------------------------------------
        [[nodiscard]] std::pair<float, float> worldToWindowPosition(std::pair<float, float> worldPos, bool flipY = false) const;
        [[nodiscard]] std::pair<float, float> worldToWindowSize(std::pair<float, float> worldSize) const;

        [[nodiscard]] std::pair<float, float> windowToWorldPosition(std::pair<unsigned int, unsigned int> windowPos, bool flipY = false) const;
        [[nodiscard]] std::pair<float, float> windowToWorldSize(std::pair<unsigned int, unsigned int> windowSize) const;

    private:
        void calculateScale();
    };
}

#endif //DISPLAYENGINE_CAMERA_H