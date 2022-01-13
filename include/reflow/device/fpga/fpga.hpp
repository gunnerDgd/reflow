#pragma once
#include <reflow/io_system/device/peripheral/uart_device.hpp>

#include <reflow/io_system/basic_reader.hpp>
#include <reflow/io_system/basic_writer.hpp>

#include <reflow/io_system/traits/basic_reader_traits.hpp>
#include <reflow/io_system/traits/basic_writer_traits.hpp>

#include <reflow/io_system/method/uart/uart_reader.hpp>
#include <reflow/io_system/method/uart/uart_writer.hpp>

#include <reflow/device/protocol/fpga/protocol.hpp>

namespace reflow {
	class fpga
	{
	public:
		class uart;
	};

	class fpga::uart
	{
		friend class fpga_memory;
	public:
		typedef protocol::fpga protocol_type;
		typedef uart_device	   device_type;

		typedef basic_reader<protocol_type::header, basic_reader_traits<protocol_type::header, uart_read_method>>  read_type;
		typedef basic_writer<protocol_type::header, basic_writer_traits<protocol_type::header, uart_write_method>> write_type;

	public:
		uart (device_type&);
		~uart()			   { shutdown(); }

	public:
		bool initialize();
		bool shutdown  ();

	public:
		read_type						  __M_uart_device_read ;
		write_type						  __M_uart_device_write;
		
		device_type&					  __M_uart_device	     ;
		protocol_type::header::session_id __M_uart_device_session;
	};
}