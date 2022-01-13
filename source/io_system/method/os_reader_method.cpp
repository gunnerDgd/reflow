#include <reflow/io_system/method/os_reader_method.hpp>

std::size_t reflow::os_reader_method::read(handle_type& handle, uint8_t* read_vector, std::size_t read_size)
{
	DWORD read_bytes = 0;
	BOOL  read_reply = ::ReadFile(handle.__M_stdfile_handle, read_vector, read_size, &read_bytes, NULL);

	return read_bytes;
}