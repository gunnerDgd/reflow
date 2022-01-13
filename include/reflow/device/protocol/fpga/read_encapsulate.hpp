#pragma once
#include <reflow/device/fpga/fpga.hpp>

namespace reflow {
	typedef basic_reader_traits<protocol::fpga::device_operation, uart_read_method> fpga_device_read;
	typedef basic_reader_traits<protocol::fpga::memory_operation, uart_read_method> fpga_memory_read;

	class basic_reader_traits<protocol::fpga::device_operation, uart_read_method>
	{
	public:
		typedef protocol::fpga::device_operation read_type;
		typedef uart_read_method				 method_type;
		typedef uart_read_method::handle_type    method_handle;
		
	public:
		basic_reader_traits   (fpga::uart&);
		std::size_t read_block(read_type*, std::size_t);

	private:
		fpga::uart&	__M_traits_handle;
	};

	class basic_reader_traits<protocol::fpga::memory_operation, uart_read_method>
	{
	public:
		typedef protocol::fpga::memory_operation read_type;
		typedef uart_read_method				 method_type;
		typedef uart_read_method::handle_type    method_handle;

	public:
		basic_reader_traits   (fpga::uart&);
		std::size_t read_block(read_type*, std::size_t);

	private:
		fpga::uart& __M_traits_handle;
	};
}