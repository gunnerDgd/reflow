#pragma once
#include <reflow/session/event/basic_session_event.hpp>
#include <reflow/session/event/winevent.hpp>
#include <reflow/session/operation.hpp>

#include <unordered_map>

namespace reflow {
	template <typename SessionDevice, typename SessionEntity>
	class basic_session_manager
	{
	public:
		typedef SessionDevice									   device_type;
		typedef SessionEntity									   entity_type;

		typedef SessionEntity::message							   message_type;
		typedef SessionEntity::session_type						   session_type;
		typedef basic_session_event<message_type, winevent_traits> event_type  ;
		
	public:
		entity_type& start_session(device_type&) requires std::is_constructible_v<entity_type, device_type&>;
		message_type watch_session();
		void		 end_session  (entity_type&);

	private:
		event_type									   __M_session_event ;
		std::unordered_map<session_type, entity_type*> __M_session_online;
	};
}

template <typename T, typename U>
reflow::basic_session_manager<T, U>::entity_type& reflow::basic_session_manager<T, U>::start_session(device_type& device) requires std::is_constructible_v<entity_type, device_type&>
{
	entity_type* session_entity = new entity_type(device);
	if (!session_entity->__start_session(__M_session_event))
		throw 1;

	__M_session_online.insert( { session_entity->__M_session_id, session_entity } );
	return					    *session_entity;
}

template <typename T, typename U>
reflow::basic_session_manager<T, U>::message_type reflow::basic_session_manager<T, U>::watch_session()
{
	return __M_session_event.wait_for();
}

template <typename T, typename U>
void reflow::basic_session_manager<T, U>::end_session(entity_type& entity)
{
	entity.__end_session(__M_session_event);
	
	__M_session_online.erase(entity.__M_session_id);
	delete					&entity;
}