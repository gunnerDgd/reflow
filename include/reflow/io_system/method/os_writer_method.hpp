#pragma once
#include <reflow/io_system/define.hpp>
#include <string>

namespace reflow {
	class os_writer_method
	{
	public:
		struct  handle;
		typedef handle handle_type;

	public:
		static bool		   open (handle_type&, std::string);
		static bool		   close(handle_type&);
		static std::size_t write(handle_type&, uint8_t*, std::size_t);
	};

	struct os_writer_method::handle
	{
		friend class os_writer_method;
	private:
		HANDLE	   __M_os_handle;
		OVERLAPPED __M_os_overlapped;
	};
}

bool reflow::os_writer_method::open(handle_type& handle, std::string name)
{
	handle.__M_os_handle = REFLOW_FORMAT_FILE_OPEN(name.c_str());

	if (handle.__M_os_handle != INVALID_HANDLE_VALUE)
		return true;

	DWORD   open_err = GetLastError();
	switch (open_err)
	{
	case ERROR_FILE_NOT_FOUND:
		handle.__M_os_handle = REFLOW_FORMAT_FILE_CREATE(name.c_str());
		break;

	case ERROR_PATH_NOT_FOUND:
		return false;
	}

	return true;
}

bool reflow::os_writer_method::close(handle_type& handle)
{
	return CloseHandle(handle.__M_os_handle);
}

std::size_t reflow::os_writer_method::write(handle_type& handle, uint8_t* write_vector, std::size_t write_size)
{
	DWORD write_bytes = 0;
	BOOL  write_reply = ::WriteFile(handle.__M_os_handle, write_vector, write_size, &write_bytes, NULL);

	return write_bytes;
}