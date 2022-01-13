#include <reflow/device/protocol/fpga/write_encapsulate.hpp>

reflow::basic_writer_traits<reflow::protocol::fpga::device_operation, reflow::uart_write_method>::basic_writer_traits(fpga::uart& device)
	: __M_traits_handle(device) {  }

std::size_t reflow::basic_writer_traits<reflow::protocol::fpga::device_operation, reflow::uart_write_method>::write_block(write_type* read_vector, std::size_t read_size)
{
	protocol::fpga::header wr_header;
	method_type::write(__M_traits_handle.__M_uart_device, (uint8_t*)&wr_header, sizeof(protocol::fpga::header));

	if (wr_header.hdr_session != __M_traits_handle.__M_uart_device_session)
		return 0;

	return method_type::write(__M_traits_handle.__M_uart_device, (uint8_t*)read_vector, sizeof(write_type));
}


reflow::basic_writer_traits<reflow::protocol::fpga::memory_operation, reflow::uart_write_method>::basic_writer_traits(fpga::uart& device)
	: __M_traits_handle(device) {  }

std::size_t reflow::basic_writer_traits<reflow::protocol::fpga::memory_operation, reflow::uart_write_method>::write_block(write_type* read_vector, std::size_t read_size)
{
	protocol::fpga::header wr_header;
	method_type::write(__M_traits_handle.__M_uart_device, (uint8_t*)&wr_header, sizeof(protocol::fpga::header));

	if (wr_header.hdr_session != __M_traits_handle.__M_uart_device_session)
		return 0;

	return method_type::write(__M_traits_handle.__M_uart_device, (uint8_t*)read_vector, sizeof(write_type));
}