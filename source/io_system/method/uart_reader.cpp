#include <reflow/io_system/method/uart/uart_reader.hpp>

std::size_t reflow::uart_read_method::read(handle_type& handle, uint8_t* read_vector, std::size_t read_size)
{
	DWORD read_bytes = 0;
	BOOL  read_reply = ::ReadFile(handle.__M_device_handle, read_vector, read_size, &read_bytes, NULL);

	return read_bytes;
}