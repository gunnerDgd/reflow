#pragma once
#include <reflow/io_system/define.hpp>
#include <type_traits>

namespace reflow {
	template <typename ReadType, typename ReadTraits>
	class basic_reader
	{
	public:
		typedef basic_reader<ReadType, ReadTraits> reader_type;
		typedef ReadType						   read_type;
		typedef ReadTraits						   traits_type;

	public:
		template <typename... OpenArgument>
		basic_reader (OpenArgument&&...);
		~basic_reader();

	public:
		std::size_t read	   (read_type&);
		template <std::size_t ReadCount>
		std::size_t read_blocks(read_type(&)[ReadCount]);
		std::size_t read_blocks(read_type*, std::size_t);

	private:
		traits_type __M_reader_handle;
	};
}

template <typename ReadType, typename ReadTraits>
template <typename... OpenArgument>
reflow::basic_reader<ReadType, ReadTraits>::basic_reader(OpenArgument&&... open_args)
	: __M_reader_handle(traits_type(std::forward<OpenArgument>(open_args)...)) {  }

template <typename ReadType, typename ReadTraits>
reflow::basic_reader<ReadType, ReadTraits>::~basic_reader() {  }

template <typename ReadType, typename ReadTraits>
std::size_t reflow::basic_reader<ReadType, ReadTraits>::read(read_type& read_block)
{
	return __M_reader_handle.read_block(&read_block, 1);
}

template <typename ReadType, typename ReadTraits>
template <std::size_t ReadCount>
std::size_t reflow::basic_reader<ReadType, ReadTraits>::read_blocks(read_type(&read_vector)[ReadCount])
{
	return __M_reader_handle.read_block(&read_vector, ReadCount);
}

template <typename ReadType, typename ReadTraits>
std::size_t reflow::basic_reader<ReadType, ReadTraits>::read_blocks(read_type* read_vector, std::size_t read_count)
{
	return __M_reader_handle.read_block(read_vector, read_count);
}