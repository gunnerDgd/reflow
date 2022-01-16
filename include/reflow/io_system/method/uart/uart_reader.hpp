#pragma once
#include <reflow/io_system/define.hpp>
#include <reflow/io_system/device/peripheral/uart.hpp>
#include <string>

namespace reflow {
	class uart_read_method
	{
	public:
		typedef uart handle_type;
		static std::size_t read(handle_type&, uint8_t*, std::size_t);
	};
}

