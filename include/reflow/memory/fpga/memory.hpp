#pragma once
#include <reflow/device/fpga/fpga.hpp>

namespace reflow {
	class fpga_memory
	{
	public:
		template <typename FpgaConnection>
		class local;

		template <typename FpgaConnection>
		class logic;
	};

	template <>
	class fpga_memory::local<fpga::uart>
	{
	public:
		class   accessor;

		typedef protocol::fpga::header			 protocol_header;
		typedef protocol::fpga::memory_operation protocol_memory;

		typedef basic_reader <protocol_memory, basic_reader_traits<protocol_memory, uart_read_method>> read_type ;
		typedef basic_writer <protocol_memory, basic_reader_traits<protocol_memory, uart_read_method>> write_type;

	public:
		local (fpga::uart&);
		~local();

		accessor allocate  (std::uint32_t);
		void     deallocate(accessor&);

	private:
		fpga::uart& __M_local_memory_device;
		read_type   __M_local_memory_read  ;
		write_type  __M_local_memory_write ;
	};

	class fpga_memory::local<fpga::uart>::accessor
	{
	private:
		

	public:
	};
}

reflow::fpga_memory::local<reflow::fpga::uart>::local(fpga::uart& device) : __M_local_memory_device(device),
																			__M_local_memory_read  (__M_local_memory_device.__M_uart_device),
																			__M_local_memory_write (__M_local_memory_device.__M_uart_device) {  }

reflow::fpga_memory::local<reflow::fpga::uart>::accessor reflow::fpga_memory::local<reflow::fpga::uart>::allocate(std::uint32_t size)
{
	protocol::fpga::header alloc_header;
	alloc_header.hdr_opcode  = protocol::fpga::major_opcode::memory;
	alloc_header.hdr_session = __M_local_memory_device.__M_uart_device_session;

	__M_local_memory_device.__M_uart_device_write.write(alloc_header);

	protocol::fpga::memory_operation alloc_memory;
	alloc_memory.mem_opcode = protocol::fpga::memory_operation::memory_opcode::create;
	alloc_memory.mem_size   = size;

	alloc_memory.mem_handle = 0;
	alloc_memory.mem_type   = protocol::fpga::memory_operation::memory_type::local;

	__M_local_memory

}