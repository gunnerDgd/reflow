#pragma once
#include <reflow/session/forward/fpga.hpp>

#include <cstdint>
#include <cstddef>

namespace reflow {
	template <typename T>
	class fpga_memory;

	template <>
	class fpga_memory<fpga::uart_session>
	{
	public:
		typedef fpga::uart_session::entity_type						   entity_type;
		typedef decltype(protocol::fpga::memory_operation::mem_handle) handle_type;
	
	public:
		fpga_memory (std::size_t, entity_type&);
		~fpga_memory();

	private:
		entity_type& __M_memory_session;
		handle_type  __M_memory_handle ;
		std::size_t  __M_memory_size   ;
	};
}

