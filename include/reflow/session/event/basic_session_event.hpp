#pragma once
#include <Windows.h>

#include <queue>
#include <type_traits>

namespace reflow {
	template <typename T, typename U>
	class basic_session_event;

	template <typename EventMessage, typename EventTraits>
	class basic_session_event
	{
	public:
		typedef EventMessage			 message_type;
		typedef EventTraits				 traits_type ;
		typedef std::queue<message_type> queue_type  ;

	public:
		template <typename... InitArgs>
		basic_session_event (InitArgs&&...) requires std::is_constructible_v<EventTraits, InitArgs...>;
		~basic_session_event();

	public:
		template <typename InputMessage>
		void		 raise	 (InputMessage&&) requires std::is_same_v<std::remove_cvref_t<InputMessage>, message_type>;
		message_type wait_for();

	private:
		traits_type __M_event_traits;
		queue_type  __M_event_message_queue;
	};

	template <typename EventTraits>
	class basic_session_event<void, EventTraits>
	{
	public:
		typedef EventTraits traits_type;
	public:
		template <typename... InitArgs>
		basic_session_event(InitArgs&&...) requires std::is_constructible_v<EventTraits, InitArgs...>;
		~basic_session_event();

	public:
		void raise   ();
		void wait_for();

	private:
		traits_type __M_event_traits;
	};
}

template <typename EventMessage, typename EventTraits>
template <typename... InitArgs>
reflow::basic_session_event<EventMessage, EventTraits>::basic_session_event(InitArgs&&... init_args) requires std::is_constructible_v<EventTraits, InitArgs...>
	: __M_event_traits(std::forward<InitArgs>(init_args)...)
{
	
}

template <typename EventMessage, typename EventTraits>
reflow::basic_session_event<EventMessage, EventTraits>::~basic_session_event()
{
	
}

template <typename EventMessage, typename EventTraits>
template <typename InputMessage>
void reflow::basic_session_event<EventMessage, EventTraits>::raise(InputMessage&& msg) requires std::is_same_v<std::remove_cvref_t<InputMessage>, message_type>
{
	__M_event_message_queue.push	   (msg);
	__M_event_traits	   .event_raise();
}

template <typename EventMessage, typename EventTraits>
EventMessage reflow::basic_session_event<EventMessage, EventTraits>::wait_for()
{
	__M_event_traits.event_wait();
	message_type wait_msg = __M_event_message_queue.front();
							__M_event_message_queue.pop  ();

	return wait_msg;
}

template < typename EventTraits>
template <typename... InitArgs>
reflow::basic_session_event<void, EventTraits>::basic_session_event(InitArgs&&... init_args) requires std::is_constructible_v<EventTraits, InitArgs...>
	: __M_event_traits(std::forward<InitArgs>(init_args)...)
{

}

template <typename EventTraits>
reflow::basic_session_event<void, EventTraits>::~basic_session_event()
{

}

template <typename EventTraits>
void reflow::basic_session_event<void, EventTraits>::raise()
{
	__M_event_traits.event_raise();
}

template <typename EventTraits>
void reflow::basic_session_event<void, EventTraits>::wait_for()
{
	__M_event_traits.event_wait();
}