#include <reflow/session/event/winevent.hpp>

reflow::winevent_traits::winevent_traits() : __M_evt_handle(::CreateEvent(NULL, FALSE, FALSE, NULL))
{

}

reflow::winevent_traits::~winevent_traits()
{
	::CloseHandle(__M_evt_handle);
}

void reflow::winevent_traits::event_raise()
{
	::SetEvent(__M_evt_handle);
}

void reflow::winevent_traits::event_wait()
{
	::WaitForSingleObject(__M_evt_handle, INFINITE);
}