#include <reflow/device/fpga/fpga.hpp>

reflow::fpga::uart::uart(device_type& device) : __M_uart_device	     (device),
												__M_uart_device_read (device),
												__M_uart_device_write(device) {  }

bool reflow::fpga::uart::initialize()
{
	protocol_type::header init_header;

	init_header.hdr_opcode  = protocol_type::major_opcode::startup;
	init_header.hdr_session = 0;

	if (__M_uart_device_write.write(init_header) != sizeof(protocol_type::header))
		return false;

	if (__M_uart_device_read .read (init_header) != sizeof(protocol_type::header))
		return false;

	__M_uart_device_session = init_header.hdr_session;
	return true;
}

bool reflow::fpga::uart::shutdown()
{
	protocol_type::header init_header;

	init_header.hdr_opcode  = protocol_type::major_opcode::shutdown;
	init_header.hdr_session = __M_uart_device_session;

	if (__M_uart_device_write.write(init_header) != sizeof(protocol_type::header))
		return false;

	if (__M_uart_device_read.read(init_header)   != sizeof(protocol_type::header))
		return false;

	__M_uart_device_session = init_header.hdr_session;
	return true;
}