/*
    Borealis, a Nintendo Switch UI Library
    Copyright (C) 2020  natinusala

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <map>

#include "borealis/view.hpp"

namespace brls
{

// A "layout" that takes a list of views and takes care of all the plumbing
// The user is responsible for calling setBoundaries on all the child views
// as well as implementing navigation (getDefaultFocus(), getNextFocus())
//
// Override layout() and reposition your views here, then call the super method
class AbsoluteLayout : public View
{
    // TODO: rewrite some of the base views (AppletFrame, CrashFrame, PopupView...) using AbsoluteLayout

  private:
    std::vector<View*> children;

  public:
    ~AbsoluteLayout();

    void addView(View* view);

    // Plumbing
    void draw(NVGcontext* vg, int x, int y, unsigned width, unsigned height, Style* style, FrameContext* ctx) override;
    void layout(NVGcontext* vg, Style* style, FontStash* stash) override;
    void onWindowSizeChanged() override;
    void willAppear(bool resetState = false) override;
    void willDisappear(bool resetState = false) override;
};

// Allows users to define an entirely custom "navigation map"
// to define where the focus should go when pressing a navigation
// key from a view.
// Can be used anywhere a custom navigation map is wanted, not only
// in AbsoluteLayout.
class NavigationMap
{
  public:
    /**
     * Call this method from any view's getNextFocus() to use the
     * navigation map. Returns nullptr if there is no such known route.
     */
    View* getNextFocus(FocusDirection direction, View* currentView);

    /**
     * Add a route to the map from the two given views
     * using the given direction
     */
    void add(View* from, FocusDirection direction, View* to);

  private:
    std::map<std::pair<View*, FocusDirection>, View*> map;
};

} // namespace brls
