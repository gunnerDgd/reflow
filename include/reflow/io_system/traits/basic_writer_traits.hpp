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
		basic_writer_traits	   (method_handle&);
		std::size_t write_block(write_type*, std::size_t);

	private:
		method_handle& __M_traits_handle;
	};
}

template <typename WriteType, typename WriteMethod>
reflow::basic_writer_traits<WriteType, WriteMethod>::basic_writer_traits(method_handle& init_args) : __M_traits_handle(init_args) 
{

}

template <typename WriteType, typename WriteMethod>
std::size_t reflow::basic_writer_traits<WriteType, WriteMethod>::write_block(write_type* write_vector, std::size_t write_count)
{
	return method_type::write(__M_traits_handle, (uint8_t*)write_vector, write_count * sizeof(write_type));
}