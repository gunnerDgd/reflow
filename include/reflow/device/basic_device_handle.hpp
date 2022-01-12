#pragma once

namespace reflow {
	template <typename DeviceTraits>
	class basic_device_handle
	{
	public:
		typedef DeviceTraits traits_type;

	public:
		template <typename... InitArgs>
		bool startup (InitArgs&&...);
		bool shutdown();

	private:
		traits_type __M_device_handle;
	};
}