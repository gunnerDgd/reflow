#pragma once
#include <reflow/io_system/define.hpp>
#include <string>

namespace reflow {
	class uart_device
	{
		friend class uart_read_method ;
		friend class uart_write_method;

		template <typename T, typename U>
		friend class basic_reader_traits;

		template <typename T, typename U>
		friend class basic_writer_traits;

	public:
		typedef HANDLE handle_type;
		typedef DCB    config_type;
		class		   config
		{
			friend class uart_device;
		public:
			enum class baud_rate : uint32_t
			{
				baud_9600   = BAUD_9600,
				baud_115200 = BAUD_115200
			};

			enum class byte_size : uint32_t
			{
				byte_8 = 8,
				byte_7 = 7
			};

			enum class stop_bit  : uint32_t { enable = 1, disable = 0 };
			enum class parity	 : uint32_t
			{
				disable = NOPARITY,
				even    = PARITY_EVEN,
				odd		= PARITY_ODD
			};

			config(baud_rate brate, byte_size bsize = byte_size::byte_8, stop_bit sbit = stop_bit::enable, parity bparity = parity::disable);

		private:
			baud_rate __M_config_baud_rate ;
			byte_size __M_config_byte_size ;
			stop_bit  __M_config_stop_bit  ;
			parity    __M_config_parity_bit;
		};
		
	public:
		uart_device (std::string, config);
		~uart_device();

	private:
		handle_type __M_device_handle;
		config_type __M_device_config;
	};
	
}