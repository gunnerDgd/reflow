#pragma once

namespace reflow {
	template <typename SessionDevice, typename SessionEntity>
	class basic_session_manager
	{
	public:
		typedef SessionDevice device_type;
		typedef SessionEntity entity_type;
		
	public:
		entity_type start_session(device_type&);
		void		end_session  (entity_type&);

	public:
		

	private:
	};
}