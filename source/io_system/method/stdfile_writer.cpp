#include <reflow/io_system/method/system/stdfile_writer.hpp>

std::size_t reflow::standard_file_writer::write(handle_type& handle, uint8_t* write_vector, std::size_t write_size)
{
	DWORD write_bytes = 0;
	BOOL  write_reply = ::WriteFile(handle.__M_stdfile_handle, write_vector, write_size, &write_bytes, NULL);

	return write_bytes;
}