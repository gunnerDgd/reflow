#pragma once
#include <reflow/device/fpga/fpga.hpp>

#include <reflow/device/protocol/fpga/read_encapsulate.hpp>
#include <reflow/device/protocol/fpga/write_encapsulate.hpp>

#include <reflow/memory/define.hpp>

namespace reflow {
	class fpga_memory
	{
	public:
		template <typename FpgaConnection, typename AllocType>
		class local;

		template <typename FpgaConnection, typename AllocType>
		class logic;
	};

	template <typename AllocType>
	class fpga_memory::local<fpga::uart, AllocType>
	{
	public:
		class   accessor;
		typedef accessor  pointer_type;
		typedef AllocType alloc_type;

		typedef protocol::fpga::header			 protocol_header;
		typedef protocol::fpga::memory_operation protocol_memory;

		typedef fpga_memory_read  read_type ;
		typedef fpga_memory_write write_type;

		typedef decltype(protocol::fpga::memory_operation::mem_handle) handle_type;
		typedef decltype(protocol::fpga::memory_operation::mem_size)   size_type;

	public:
		local (fpga::uart&);
		~local();

		accessor allocate  (size_type);
		void     deallocate(accessor&);

	private:
		fpga::uart& __M_local_memory_device;
		read_type   __M_local_memory_read  ;
		write_type  __M_local_memory_write ;
	};

	
}