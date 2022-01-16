#pragma once
#include <reflow/io_system/define.hpp>
#include <string>

namespace reflow {
	template <typename WriteType, typename WriteMethod>
	class basic_writer_traits
	{
	public:
		typedef WriteType				 write_type;
		typedef WriteMethod				 method_type;
		typedef WriteMethod::handle_type method_handle;

	public:
		template <typename... InitArgs>
		basic_writer_traits	   (InitArgs&&...) requires std::is_constructible_v<typename WriteMethod::handle_type, InitArgs...>;
		std::size_t write_block(write_type*, std::size_t);

	private:
		method_handle __M_traits_handle;
	};
}

template <typename WriteType, typename WriteMethod>
template <typename... InitArgs>
reflow::basic_writer_traits<WriteType, WriteMethod>::basic_writer_traits(InitArgs&&... init_args) requires std::is_constructible_v<typename WriteMethod::handle_type, InitArgs...>
	: __M_traits_handle(std::forward<InitArgs>(init_args)...) {  }

template <typename WriteType, typename WriteMethod>
std::size_t reflow::basic_writer_traits<WriteType, WriteMethod>::write_block(write_type* write_vector, std::size_t write_count)
{
	return method_type::write(__M_traits_handle, (uint8_t*)write_vector, write_count * sizeof(write_type));
}