#pragma once
#include <reflow/io_system/device/disk/standard_file.hpp>
#include <string>

namespace reflow {
	class os_reader_method
	{
	public:
		typedef standard_file handle_type;

	public:
		static std::size_t read (handle_type&, uint8_t*, std::size_t);
	};
}