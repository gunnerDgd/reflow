#include <reflow/device/protocol/fpga/read_encapsulate.hpp>

reflow::basic_reader_traits<reflow::protocol::fpga::device_operation, reflow::uart_read_method>::basic_reader_traits(fpga::uart& device)
	: __M_traits_handle(device) {  }

std::size_t reflow::basic_reader_traits<reflow::protocol::fpga::device_operation, reflow::uart_read_method>::read_block(read_type* read_vector, std::size_t read_size)
{
	protocol::fpga::header rd_header;
	method_type::read(__M_traits_handle.__M_uart_device, (uint8_t*)&rd_header, sizeof(protocol::fpga::header));

	if (rd_header.hdr_session != __M_traits_handle.__M_uart_device_session)
		return 0;

	return method_type::read(__M_traits_handle.__M_uart_device, (uint8_t*)read_vector, sizeof(read_type));
}


reflow::basic_reader_traits<reflow::protocol::fpga::memory_operation, reflow::uart_read_method>::basic_reader_traits(fpga::uart& device)
	: __M_traits_handle(device) {  }

std::size_t reflow::basic_reader_traits<reflow::protocol::fpga::memory_operation, reflow::uart_read_method>::read_block(read_type* read_vector, std::size_t read_size)
{
	protocol::fpga::header rd_header;
	method_type::read(__M_traits_handle.__M_uart_device, (uint8_t*)&rd_header, sizeof(protocol::fpga::header));

	if (rd_header.hdr_session != __M_traits_handle.__M_uart_device_session)
		return 0;

	return method_type::read(__M_traits_handle.__M_uart_device, (uint8_t*)read_vector, sizeof(read_type));
}