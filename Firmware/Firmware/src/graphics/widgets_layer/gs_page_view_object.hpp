#pragma once

#include "ih/gs_ipage_view_object.hpp"

#include <vector>
#include <functional>

namespace Graphics::Events
{
    struct TEvent;
}

namespace Graphics::Views
{

class PageViewObject
    :   public IPageViewObject
{

public:

    PageViewObject() = default;

    void addWidget( const std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget ) override;

    IEventHandler& getEventHandler() override;

    IEventHandler& getEventHandler() const override;

    void show() override;

    void hide() override;

    ~PageViewObject() = default;

private:

private:

    void executeForEachWidget(  std::function<void(std::shared_ptr<Graphics::Widgets::IWidgetObject>&)> _toCall );

    using TWidgetsStorage = std::vector<std::shared_ptr<Graphics::Widgets::IWidgetObject> >;
    TWidgetsStorage m_pWidgetsStorage;
};

};
