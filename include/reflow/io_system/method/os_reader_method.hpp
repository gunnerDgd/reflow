#pragma once
#include <reflow/io_system/define.hpp>
#include <string>

namespace reflow {
	class os_reader_method
	{
	public:
		struct  handle;
		typedef handle handle_type;

	public:
		static bool		   open (handle_type&, std::string);
		static bool		   close(handle_type&);
		static std::size_t read (handle_type&, uint8_t*, std::size_t);
	};

	struct os_reader_method::handle
	{
		friend class os_reader_method;
	private:
		HANDLE	   __M_os_handle;
		OVERLAPPED __M_os_overlapped;
	};
}

bool reflow::os_reader_method::open(handle_type& handle, std::string name)
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

bool reflow::os_reader_method::close(handle_type& handle)
{
	return CloseHandle(handle.__M_os_handle);
}

std::size_t reflow::os_reader_method::read(handle_type& handle, uint8_t* read_vector, std::size_t read_size)
{
	DWORD read_bytes = 0;
	BOOL  read_reply = ::ReadFile(handle.__M_os_handle, read_vector, read_size, &read_bytes, NULL);

	return read_bytes;
}