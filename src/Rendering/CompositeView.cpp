//
// Created by natha on 9/9/2026.
//

#include "Rendering/CompositeView.h"

#include <algorithm>

namespace eng {
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    CompositeView::CompositeView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera)
        : View(key, model, window, camera) {}

    //----------------------------------------------------------------------------------------------------------------------
    //Setters
    //----------------------------------------------------------------------------------------------------------------------
    void CompositeView::addView(std::unique_ptr<View> view) {
        this->views.push_back(std::move(view));
    }

    void CompositeView::removeView(View *view) {
        auto it = std::find_if(views.begin(), views.end(),
            [view](const std::unique_ptr<View>& existingView) {
                return existingView.get() == view;
            });

        if (it != views.end()) {
            views.erase(it);
        }
    }


    void CompositeView::clearViews() {
        views.clear();
    }

    //----------------------------------------------------------------------------------------------------------------------
    //Getters
    //----------------------------------------------------------------------------------------------------------------------

    std::size_t CompositeView::getViewCount() const {
        return views.size();
    }

    View& CompositeView::getView(std::size_t index) {
        return *views.at(index);
    }

    const View& CompositeView::getView(std::size_t index) const {
        return *views.at(index);
    }

    //----------------------------------------------------------------------------------------------------------------------
    //Logic
    //----------------------------------------------------------------------------------------------------------------------

    void CompositeView::update() {
        //First erase nullptrs
        views.erase(
            std::remove(views.begin(), views.end(), nullptr),
            views.end()
        );

        for (const auto& view : views) {
            view->update();
        }
    }

    void CompositeView::calibrate() {
        for (const auto& view : views) {
            view->update();
        }
    }


    //----------------------------------------------------------------------------------------------------------------------
    //View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------

    void CompositeView::draw() {
        if (!isVisible()) {
            return;
        }

        for (const auto& view : views) {
            view->draw();
        }
    }
}