#pragma once
#include <reflow/session/protocol/fpga/protocol.hpp>
#include <reflow/session/event/basic_session_event.hpp>
#include <reflow/session/session_message.hpp>

#include <reflow/io_system/forward/uart.hpp>

namespace reflow {
	template <typename FpgaDevice>
	class fpga_session;

	template <>
	class fpga_session<uart>
	{
	public:
		typedef uart							   device_type;
		typedef protocol::fpga::header::session_id session_type;

	public:
		fpga_session(uart& device) : __M_session_device(device) {  }

	public:
		template <typename EventTraits>
		bool start_session(basic_session_event<session_message, EventTraits>&);

		template <typename EventTraits>
		void end_session  (basic_session_event<session_message, EventTraits>&);

	private:
		device_type& __M_session_device;
		session_type __M_session_id;

		uart_reader& __M_session_istream;
		uart_writer& __M_session_ostream;
	};
}

template <typename EventTraits>
bool reflow::fpga_session<reflow::uart>::start_session(basic_session_event<session_message, EventTraits>& session_event)
{
	protocol::fpga::header st_header;
	st_header.hdr_opcode  = protocol::fpga::major_opcode::startup;
	st_header.hdr_session = 0;

	__M_session_ostream.write_blocks(reinterpret_cast<uint8_t*>(&st_header), sizeof(protocol::fpga::header));
	__M_session_istream.read_blocks (reinterpret_cast<uint8_t*>(&st_header), sizeof(protocol::fpga::header));

	if (st_header.hdr_opcode == protocol::fpga::major_opcode::startup &&
		st_header.hdr_session != 0)
	{
		session_event.raise(session_message::startup);
		__M_session_id = st_header.hdr_session;
	}
	else
		session_event.raise(session_message::failure);

	return (st_header.hdr_opcode != protocol::fpga::major_opcode::startup) ? false : true;
}

template <typename EventTraits>
void reflow::fpga_session<reflow::uart>::end_session(basic_session_event<session_message, EventTraits>& session_event)
{
	uart_reader uart_istream;
	uart_writer uart_ostream;

	protocol::fpga::header sh_header;
	sh_header.hdr_opcode  = protocol::fpga::major_opcode::shutdown;
	sh_header.hdr_session = __M_session_id;

	__M_session_ostream.write_blocks(reinterpret_cast<uint8_t*>(&sh_header), sizeof(protocol::fpga::header));
	__M_session_istream.read_blocks (reinterpret_cast<uint8_t*>(&sh_header), sizeof(protocol::fpga::header));

	session_event.raise(session_message::shutdown);
}