#pragma once
#include <reflow/io_system/define.hpp>
#include <string>

namespace reflow {
	class fpga_writer_uart
	{
	public:
		struct  handle;
		typedef handle handle_type;

	public:
		static bool		   open (handle_type&, std::string, std::uint32_t);
		static bool		   close(handle_type&);
		static std::size_t write(handle_type&, uint8_t*, std::size_t);

	private:
		std::string __M_uart_device;
	};

	struct fpga_writer_uart::handle
	{
		friend class fpga_writer_uart;
	private:
		HANDLE __M_fpga_uart_handle;
		DCB	   __M_fpga_uart_config;
	};
}

bool reflow::fpga_writer_uart::open(handle_type& handle, std::string name, std::uint32_t brate)
{
	handle.__M_fpga_uart_handle			 = REFLOW_DEVICE_OPEN(name.c_str());
	handle.__M_fpga_uart_config.BaudRate = brate;

	if (handle.__M_fpga_uart_handle == INVALID_HANDLE_VALUE)
		return false;

	return SetCommState(handle.__M_fpga_uart_handle, &handle.__M_fpga_uart_config);
}

bool reflow::fpga_writer_uart::close(handle_type& handle)
{
	return ::CloseHandle(handle.__M_fpga_uart_handle);
}

std::size_t reflow::fpga_writer_uart::write(handle_type& handle, uint8_t* write_vector, std::size_t write_size)
{
	DWORD  write_bytes = 0;
	BOOL   write_reply = ::WriteFile(handle.__M_fpga_uart_handle, write_vector, write_size, &write_bytes, NULL);

	return write_bytes;
}