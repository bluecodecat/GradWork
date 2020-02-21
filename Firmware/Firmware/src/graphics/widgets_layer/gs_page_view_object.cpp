#include "gs_page_view_object.hpp"

#include "ih/gs_events.hpp"

#include "widgets/battery/gs_battery_widget.hpp"
#include "widgets/battery/gs_battery_handler.hpp"

#include <algorithm>

namespace Graphics::Views
{

PageViewObject::PageViewObject( std::weak_ptr<Theme::IThemeController> _themeController )
    :   m_pThemeController{ _themeController }
    ,   m_isPageVisible{ false }
{
}

void PageViewObject::addWidget(
    const std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget
)
{
    m_pWidgetsStorage.push_back( _pWidget );
}

void PageViewObject::show()
{
    executeForEachWidget(
        []( std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget )
        {
                _pWidget->show();
        }
    );
}

void PageViewObject::hide()
{
    executeForEachWidget(
        []( std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget )
        {
                _pWidget->hide();
        }
    );
}

bool PageViewObject::isVisible() const
{
    return m_isPageVisible;
}

std::shared_ptr<Theme::IThemeController> PageViewObject::getThemeController()
{
    return m_pThemeController.lock();
}

void PageViewObject::executeForEachWidget(
    std::function<void(std::shared_ptr<Graphics::Widgets::IWidgetObject>&)> _toCall
)
{
    std::for_each(
            m_pWidgetsStorage.begin()
        ,   m_pWidgetsStorage.end()
        ,   _toCall
    );
}

};
