#pragma once
#include <reflow/session/protocol/fpga/protocol.hpp>
#include <reflow/session/event/basic_session_event.hpp>
#include <reflow/session/operation.hpp>

#include <reflow/io_system/forward/uart.hpp>

namespace reflow {
	template <typename FpgaDevice>
	class fpga_session;

	template <>
	class fpga_session<uart>
	{
		template <typename T, typename U>
		friend class basic_session_manager;

		template <typename T>
		friend class fpga_memory;

	public:
		typedef uart							   device_type;
		typedef protocol::fpga::header::session_id session_type;

	public:
		struct  message
		{
			session_operation session_operation;
			session_type      session_handle   ;
		};

	private:
		fpga_session(uart& device) : __M_session_device(device) {  }

	private:
		template <typename EventTraits>
		bool __start_session(basic_session_event<message, EventTraits>&);

		template <typename EventTraits>
		void __end_session  (basic_session_event<message, EventTraits>&);

	private:
		device_type& __M_session_device;
		session_type __M_session_id;

		uart_reader& __M_session_istream;
		uart_writer& __M_session_ostream;
	};
}

template <typename EventTraits>
bool reflow::fpga_session<reflow::uart>::__start_session(basic_session_event<message, EventTraits>& session_event)
{
	protocol::fpga::header st_header;
	message				   st_message;

	st_header.hdr_opcode		 = protocol::fpga::major_opcode::startup;
	st_header.hdr_session		 = 0;
	st_message.session_operation = session_operation::startup;

	__M_session_ostream.write_blocks(reinterpret_cast<uint8_t*>(&st_header), sizeof(protocol::fpga::header));
	__M_session_istream.read_blocks (reinterpret_cast<uint8_t*>(&st_header), sizeof(protocol::fpga::header));

	if (st_header.hdr_opcode == protocol::fpga::major_opcode::startup &&
		st_header.hdr_session != 0)
	{
		st_message.session_handle = st_header.hdr_session;
		session_event.raise		   (st_message);
		
		__M_session_id = st_header.hdr_session;
	}
	else
		session_event.raise(session_message::failure);

	return (st_header.hdr_opcode != protocol::fpga::major_opcode::startup) ? false : true;
}

template <typename EventTraits>
void reflow::fpga_session<reflow::uart>::__end_session(basic_session_event<message, EventTraits>& session_event)
{
	protocol::fpga::header sh_header;
	message				   sh_message { session_operation::shutdown, __M_session_id };

	sh_header.hdr_opcode		 = protocol::fpga::major_opcode::shutdown;
	sh_header.hdr_session		 = __M_session_id;

	__M_session_ostream.write_blocks(reinterpret_cast<uint8_t*>(&sh_header), sizeof(protocol::fpga::header));
	__M_session_istream.read_blocks (reinterpret_cast<uint8_t*>(&sh_header), sizeof(protocol::fpga::header));

	session_event.raise(sh_message);
}