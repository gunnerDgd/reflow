#pragma once
#include <reflow/device/fpga/fpga.hpp>

namespace reflow {
	typedef basic_writer_traits<protocol::fpga::device_operation, uart_write_method> fpga_device_write;
	typedef basic_writer_traits<protocol::fpga::memory_operation, uart_write_method> fpga_memory_write;

	template <>
	class basic_writer_traits<protocol::fpga::device_operation, uart_write_method>
	{
	public:
		typedef protocol::fpga::device_operation write_type;
		typedef uart_write_method				 method_type;
		typedef uart_write_method::handle_type   method_handle;

	public:
		basic_writer_traits    (fpga::uart&);
		std::size_t write_block(write_type*, std::size_t);

	private:
		fpga::uart& __M_traits_handle;
	};

	template <>
	class basic_writer_traits<protocol::fpga::memory_operation, uart_write_method>
	{
	public:
		typedef protocol::fpga::memory_operation write_type;
		typedef uart_write_method				 method_type;
		typedef uart_write_method::handle_type   method_handle;

	public:
		basic_writer_traits    (fpga::uart&);
		std::size_t write_block(write_type*, std::size_t);

	private:
		fpga::uart& __M_traits_handle;
	};
}