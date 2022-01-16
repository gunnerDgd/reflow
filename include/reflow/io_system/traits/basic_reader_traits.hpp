#pragma once
#include <reflow/io_system/define.hpp>
#include <string>

namespace reflow {
	template <typename ReadType, typename ReadMethod>
	class basic_reader_traits
	{
	public:
		typedef ReadType				read_type;
		typedef ReadMethod				method_type;
		typedef ReadMethod::handle_type method_handle;

	public:
		template <typename... InitArgs>
		basic_reader_traits	  (InitArgs&&...) requires std::is_constructible_v<typename ReadMethod::handle_type, InitArgs...>;
		std::size_t read_block(read_type*, std::size_t);

	private:
		method_handle __M_traits_handle;
	};
}

template <typename ReadType, typename ReadMethod>
template <typename... InitArgs>
reflow::basic_reader_traits<ReadType, ReadMethod>::basic_reader_traits(InitArgs&&... init_args) requires std::is_constructible_v<typename ReadMethod::handle_type, InitArgs...>
	: __M_traits_handle(std::forward<InitArgs>(init_args)...) {  }

template <typename ReadType, typename ReadMethod>
std::size_t reflow::basic_reader_traits<ReadType, ReadMethod>::read_block(read_type* read_vector, std::size_t read_count)
{
	return method_type::read(__M_traits_handle, (uint8_t*)read_vector, read_count * sizeof(read_type));
}