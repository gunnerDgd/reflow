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
		basic_writer_traits(std::string);

	public:
		bool		open();
		bool		close();
		std::size_t write_block(write_type*, std::size_t);

	private:
		method_handle __M_traits_handle;
		std::string   __M_traits_string;
	};
}

template <typename WriteType, typename WriteMethod>
reflow::basic_writer_traits<WriteType, WriteMethod>::basic_writer_traits(std::string file_name)
	: __M_traits_string(std::move(file_name)) {  }

template <typename WriteType, typename WriteMethod>
bool reflow::basic_writer_traits<WriteType, WriteMethod>::open()
{
	return method_type::open(__M_traits_handle, __M_traits_string);
}

template <typename WriteType, typename WriteMethod>
bool reflow::basic_writer_traits<WriteType, WriteMethod>::close()
{
	return method_type::close(__M_traits_handle);
}

template <typename WriteType, typename WriteMethod>
std::size_t reflow::basic_writer_traits<WriteType, WriteMethod>::write_block(write_type* read_vector, std::size_t read_count)
{
	return method_type::write(__M_traits_handle, read_vector, read_count * sizeof(read_type));
}