#include <reflow/io_system/device/peripheral/uart_device.hpp>

reflow::uart_device::uart_device(std::string device, config uart_config)
{
	__M_device_config.BaudRate = (std::underlying_type_t<config::baud_rate>)uart_config.__M_config_baud_rate ; 
	__M_device_config.ByteSize = (std::underlying_type_t<config::byte_size>)uart_config.__M_config_byte_size ;
	__M_device_config.StopBits = (std::underlying_type_t<config::stop_bit>) uart_config.__M_config_stop_bit  ;
	__M_device_config.Parity   = (std::underlying_type_t<config::baud_rate>)uart_config.__M_config_parity_bit;

	__M_device_handle = ::CreateFileA (device.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL);
						  SetCommState(__M_device_handle, &__M_device_config);
}

reflow::uart_device::~uart_device()
{
	CloseHandle(__M_device_handle);
} 

reflow::uart_device::config::config(baud_rate brate, byte_size bsize, stop_bit sbit, parity bparity) 
									: __M_config_baud_rate (brate)  ,
									  __M_config_byte_size (bsize)  ,
									  __M_config_parity_bit(bparity),
									  __M_config_stop_bit  (sbit)	{  }