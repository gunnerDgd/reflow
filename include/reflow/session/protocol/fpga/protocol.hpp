#pragma once
#include <reflow/session/protocol/fpga/uart.hpp>

namespace reflow   {
namespace protocol {

	class fpga
	{
	public:
		enum major_opcode;
	public:
		struct header;
		struct memory_operation;
		struct device_operation;
	};

	enum fpga::major_opcode : std::uint8_t
	{
		error    = 0x00,
		startup  = 0x01,
		shutdown = 0x02,

		memory   = 0x03,
		device   = 0x04
	};

	struct fpga::header
	{
		typedef std::uint32_t session_id;

		major_opcode hdr_opcode;
		session_id   hdr_session;
		
	};

	struct fpga::memory_operation
	{
		typedef std::uint32_t memory_handle;
		enum				  memory_type   : std::uint8_t
		{
			local = 0x00,
			logic = 0x01
		};
		enum				  memory_opcode : std::uint8_t
		{
			create = 0x01,
			remove = 0x02,

			read   = 0x03,
			write  = 0x04
		};

		memory_opcode mem_opcode;
		memory_handle mem_handle;
		memory_type   mem_type  ;
		std::uint32_t mem_size  ;
		std::uint32_t mem_offset;
	};

	struct fpga::device_operation
	{
		typedef std::uint32_t device_enumerator_handle;
		typedef std::uint32_t device_handle;

		enum device_opcode
		{
			enumerate = 0x01,
			open	  = 0x02,
			close	  = 0x03,
			control   = 0x04,

			read	  = 0x05,
			write	  = 0x06
		};

		device_opcode			 dev_opcode;
		device_enumerator_handle dev_enumerator_handle;
		device_handle			 dev_handle;
		uint32_t				 dev_io_size;
	};
}
}