//
// Created by natha on 9/9/2026.
//

#ifndef DISPLAYENGINE_COMPOSITEVIEW_H
#define DISPLAYENGINE_COMPOSITEVIEW_H

#include <memory>
#include <vector>
#include <type_traits>

#include "View.h"

namespace eng {
    class SpriteView;
    class TextView;
    class PolygonView;

    class CompositeView : public View {
    private:
        std::vector<std::unique_ptr<View>> views;

    public:
        //----------------------------------------------------------------------------------------------------------------------
        //Constructors & Destructor
        //----------------------------------------------------------------------------------------------------------------------
        CompositeView() = delete;
        CompositeView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera);

        //----------------------------------------------------------------------------------------------------------------------
        //Setters
        //----------------------------------------------------------------------------------------------------------------------
        void addView(std::unique_ptr<View> view);
        void removeView(View* view);
        void clearViews();

        template<typename T, typename... Args>
        T& addView(Args&&... args) {
            static_assert(std::is_base_of_v<View, T>,
                          "T must derive from View");

            auto view = std::make_unique<T>(std::forward<Args>(args)...);
            T& reference = *view;

            views.push_back(std::move(view));

            return reference;
        }

        //----------------------------------------------------------------------------------------------------------------------
        //Getters
        //----------------------------------------------------------------------------------------------------------------------
        [[nodiscard]] std::size_t getViewCount() const;
        [[nodiscard]] View& getView(std::size_t index);
        [[nodiscard]] const View& getView(std::size_t index) const;

        //----------------------------------------------------------------------------------------------------------------------
        //Logic
        //----------------------------------------------------------------------------------------------------------------------
        void update() override;
        void calibrate() override;

        //----------------------------------------------------------------------------------------------------------------------
        //View, Draw, Print & Debug
        //----------------------------------------------------------------------------------------------------------------------
        void draw() override;
    };
}

#endif //DISPLAYENGINE_COMPOSITEVIEW_H