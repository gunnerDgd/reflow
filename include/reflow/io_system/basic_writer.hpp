#pragma once
#include <reflow/io_system/define.hpp>
#include <type_traits>

namespace reflow {
	template <typename WriteType, typename WriteTraits>
	class basic_writer
	{
	public:
		typedef			 basic_writer<WriteType, WriteTraits> writer_type;
		typedef		     WriteType			  				  write_type;
		typedef			 WriteTraits					      traits_type;

	public:
		template <typename... OpenArgument>
		basic_writer (OpenArgument&&...);
		~basic_writer();

	public:
		std::size_t write		(write_type&);
		template <std::size_t WriteCount>
		std::size_t write_blocks(write_type(&)[WriteCount]);
		std::size_t write_blocks(write_type*, std::size_t);

	private:
		traits_type __M_write_handle;
	};
}

template <typename WriteType, typename WriteTraits>
template <typename... OpenArgument>
reflow::basic_writer<WriteType, WriteTraits>::basic_writer(OpenArgument&&... open_args)
	: __M_write_handle(traits_type(std::forward<OpenArgument>(open_args)...)) {  }

template <typename WriteType, typename WriteTraits>
reflow::basic_writer<WriteType, WriteTraits>::~basic_writer() {  }

template <typename WriteType, typename WriteTraits>
std::size_t reflow::basic_writer<WriteType, WriteTraits>::write(write_type& write_block)
{
	return __M_write_handle.write_block(&write_block, 1);
}

template <typename WriteType, typename WriteTraits>
template <std::size_t WriteCount>
std::size_t reflow::basic_writer<WriteType, WriteTraits>::write_blocks(write_type(&write_vector)[WriteCount])
{
	return __M_write_handle.write_block(&write_vector, WriteCount);
}

template <typename WriteType, typename WriteTraits>
std::size_t reflow::basic_writer<WriteType, WriteTraits>::write_blocks(write_type* write_vector, std::size_t write_count)
{
	return __M_write_handle.write_block(write_vector, write_count);
}