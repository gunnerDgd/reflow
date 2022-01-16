#pragma once
#include <Windows.h>

namespace reflow {
	class winevent_traits
	{
	public:
		typedef HANDLE handle_type;
		winevent_traits ();
		~winevent_traits();

		void event_raise();
		void event_wait ();

	public:
		handle_type __M_evt_handle;
	};
}