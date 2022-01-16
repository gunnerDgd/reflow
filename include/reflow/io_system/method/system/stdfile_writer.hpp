#pragma once
#include <reflow/io_system/device/disk/standard_file.hpp>
#include <string>

namespace reflow {
	class standard_file_writer
	{
	public:
		typedef standard_file handle_type;
		static std::size_t write(handle_type&, uint8_t*, std::size_t);
	};
}