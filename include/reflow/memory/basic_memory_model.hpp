#pragma once
#include <reflow/memory/define.hpp>

namespace reflow {
	template <typename MemoryType, typename MemoryTraits>
	class basic_memory_model
	{
	public:
		typedef MemoryType				   memory_type;
		typedef MemoryTraits			   traits_type;
		typedef MemoryTraits::pointer_type pointer_type;

	public:
		template <typename... InitArgs>
		basic_memory_model (InitArgs&&...);
		~basic_memory_model();
		
	public:

	private:
		traits_type __M_mmodel_traits;
	};
}