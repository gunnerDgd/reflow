#include <reflow/memory/fpga/memory_traits.hpp>

reflow::fpga_memory<reflow::fpga::uart_session>::fpga_memory(std::size_t mem_size, entity_type& session)
	: __M_memory_size   (mem_size),
	  __M_memory_session(session)
{
	protocol::fpga::header			 al_header { protocol::fpga::major_opcode::memory, __M_memory_session.__M_session_id };
	protocol::fpga::memory_operation al_memory;

	al_memory.mem_handle = 0;
	
	al_memory.mem_opcode = protocol::fpga::memory_operation::memory_opcode::create;
	al_memory.mem_type   = protocol::fpga::memory_operation::memory_type::local;
	
	al_memory.mem_offset = 0;
	al_memory.mem_size   = mem_size;
	
	__M_memory_session.__M_session_ostream.write_blocks(reinterpret_cast<uint8_t*>(&al_header), sizeof(protocol::fpga::header));
	__M_memory_session.__M_session_ostream.write_blocks(reinterpret_cast<uint8_t*>(&al_memory), sizeof(protocol::fpga::memory_operation));

	__M_memory_session.__M_session_istream.read_blocks (reinterpret_cast<uint8_t*>(&al_header), sizeof(protocol::fpga::header));
	__M_memory_session.__M_session_istream.read_blocks (reinterpret_cast<uint8_t*>(&al_memory), sizeof(protocol::fpga::memory_operation));

	
}

reflow::fpga_memory<reflow::fpga::uart_session>::~fpga_memory()
{
	
}