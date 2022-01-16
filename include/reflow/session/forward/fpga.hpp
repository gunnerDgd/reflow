#pragma once
#include <reflow/session/basic_session_manager.hpp>
#include <reflow/session/traits/fpga/session.hpp>

namespace reflow {
namespace fpga   {
	typedef basic_session_manager<uart, fpga_session<uart>> uart_session;
}
}