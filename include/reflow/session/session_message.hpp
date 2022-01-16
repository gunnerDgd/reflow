#pragma once
#include <cstdint>
#include <cstddef>

namespace reflow {
	enum class session_message
	{
		failure = 0,
		
		startup  = 1,
		shutdown = 2
	};
}