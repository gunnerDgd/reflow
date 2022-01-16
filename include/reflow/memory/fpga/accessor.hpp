#include <reflow/memory/fpga/memory.hpp>

namespace reflow {

	template <typename AllocType>
	class fpga_memory::local<fpga::uart, AllocType>::accessor
	{
		friend class fpga_memory::local<fpga::uart, AllocType>;

		typedef decltype(protocol::fpga::memory_operation::mem_handle) handle_type;
		typedef decltype(protocol::fpga::memory_operation::mem_size)   size_type  ;
		typedef AllocType											   alloc_type ;
	private:
		accessor (fpga_memory::local<fpga::uart, AllocType>&, handle_type, size_type);
		~accessor();

	public:
		alloc_type operator[](size_type);
		void	   operator= (alloc_type);

	private:
		fpga_memory::local<fpga::uart>& __M_accessor_allocator;
		handle_type						__M_accessor_handle   ;
		size_type						__M_accessor_size	  ;
	};
}

template <typename AllocType>
reflow::fpga_memory::local<reflow::fpga::uart, AllocType>::local(fpga::uart& device) : __M_local_memory_device(device),
																					   __M_local_memory_read  (device),
																					   __M_local_memory_write (device) {  }

template <typename AllocType>
reflow::fpga_memory::local<reflow::fpga::uart, AllocType>::accessor reflow::fpga_memory::local<reflow::fpga::uart, AllocType>::allocate(std::uint32_t count)
{
	protocol::fpga::memory_operation alloc_memory;
	
	alloc_memory.mem_opcode = protocol::fpga::memory_operation::memory_opcode::create;
	alloc_memory.mem_type   = protocol::fpga::memory_operation::memory_type::local;
	
	alloc_memory.mem_size   = count * sizeof(alloc_type);
	alloc_memory.mem_handle = 0;

	REFLOW_MEMORY_THROW_IF(__M_local_memory_write.write_block(&alloc_memory, sizeof(protocol::fpga::memory_operation)) != sizeof(protocol::fpga::memory_operation), 0)
	REFLOW_MEMORY_THROW_IF(__M_local_memory_write.read_block (&alloc_memory, sizeof(protocol::fpga::memory_operation)) != sizeof(protocol::fpga::memory_operation), 0)

	
}

template <typename AllocType>
reflow::fpga_memory::local<reflow::fpga::uart, AllocType>::accessor::accessor(fpga_memory::local<fpga::uart, AllocType>& acc_alloc, handle_type acc_handle, size_type acc_size)
	: __M_accessor_allocator(acc_alloc) ,
	  __M_accessor_handle   (acc_handle),
	  __M_accessor_size     (acc_size)  {  }

template <typename AllocType>
reflow::fpga_memory::local<reflow::fpga::uart, AllocType>::accessor::~accessor()
{
	__M_accessor_allocator.deallocate(*this);
}

template <typename AllocType>
reflow::fpga_memory::local<reflow::fpga::uart, AllocType>::accessor::alloc_type reflow::fpga_memory::local<reflow::fpga::uart, AllocType>::accessor::operator[](size_type index)
{
	protocol::fpga::memory_operation ref_memory;

	ref_memory.mem_handle = __M_accessor_handle;
	ref_memory.mem_opcode = protocol::fpga::memory_operation::memory_opcode::read;
	ref_memory.mem_type   = protocol::fpga::memory_operation::memory_type::local;
	ref_memory.mem_size   =			sizeof(alloc_type);
	ref_memory.mem_offset = index * sizeof(alloc_type);
	
	REFLOW_MEMORY_THROW_IF(__M_local_memory_write.write_block(&ref_memory, sizeof(protocol::fpga::memory_operation)) != sizeof(protocol::fpga::memory_operation), 0)
	REFLOW_MEMORY_THROW_IF(__M_local_memory_read .read_block (&ref_memory, sizeof(protocol::fpga::memory_operation)) != sizeof(protocol::fpga::memory_operation), 0)
	
	REFLOW_MEMORY_THROW_IF(ref_memory.mem_size != sizeof(alloc_type), 0)
	REFLOW_MEMORY_THROW_IF()
}

template <typename AllocType>
void reflow::fpga_memory::local<reflow::fpga::uart, AllocType>::accessor::operator= (alloc_type)
{

}