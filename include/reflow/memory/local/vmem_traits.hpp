#pragma once
#include <reflow/memory/define.hpp>

namespace reflow {
	template <typename AllocType>
	class vmem_traits
	{
	public:
		typedef AllocType*				 pointer_type;
		typedef AllocType				 alloc_type;
		REFLOW_MEMORY_CONST(std::size_t) alloc_unit = REFLOW_MEMORY_FIT(sizeof(alloc_type));

	public:
		vmem_traits ();
		~vmem_traits();
	public:
		pointer_type allocate  (std::size_t);
		void		 deallocate(std::size_t, pointer_type);

	private:
		class __vmem_chunk	  ;
		class __vmem_reserved ;
		class __vmem_committed;

	private:
		void __vmem_alloc_reserve();
		void __vmem_alloc_commit ();

		void __vmem_alloc_lock   ();
		void __vmem_alloc_unlock ();
	};

	template <typename AllocType>
	class vmem_traits<AllocType>::__vmem_chunk
	{
	public:
		__vmem_chunk();
	};
}