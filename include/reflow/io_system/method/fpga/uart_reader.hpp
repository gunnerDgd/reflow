#pragma once
#include <reflow/io_system/define.hpp>
#include <string>

namespace reflow {
	class fpga_reader_uart
	{
	public:
		struct  handle;
		typedef handle handle_type;

	public:
		static bool		   open (handle_type&, std::string, std::uint32_t);
		static bool		   close(handle_type&);
		static std::size_t read (handle_type&, uint8_t*, std::size_t);

	private:
		std::string __M_uart_device;
	};

	struct fpga_reader_uart::handle
	{
		friend class fpga_reader_uart;
	private:
		HANDLE __M_fpga_uart_handle;
		DCB	   __M_fpga_uart_config;
	};
}

bool reflow::fpga_reader_uart::open(handle_type& handle, std::string name, std::uint32_t brate)
{
	handle.__M_fpga_uart_handle			 = REFLOW_DEVICE_OPEN(name.c_str());
	handle.__M_fpga_uart_config.BaudRate = brate;

	if (handle.__M_fpga_uart_handle == INVALID_HANDLE_VALUE)
		return false;

	return SetCommState(handle.__M_fpga_uart_handle, &handle.__M_fpga_uart_config);
}

bool reflow::fpga_reader_uart::close(handle_type& handle)
{
	return ::CloseHandle(handle.__M_fpga_uart_handle);
}

std::size_t reflow::fpga_reader_uart::read(handle_type& handle, uint8_t* read_vector, std::size_t read_size)
{
	DWORD read_bytes = 0;
	BOOL  read_reply = ::ReadFile(handle.__M_fpga_uart_handle, read_vector, read_size, &read_bytes, NULL);

	return read_bytes;
}