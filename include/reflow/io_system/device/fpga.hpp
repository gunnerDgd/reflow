#pragma once
#include <reflow/io_system/define.hpp>
#include <reflow/io_system/protocol/fpga/protocol.hpp>

#include <string>

namespace reflow {
	class fpga_device
	{
	public:
		typedef HANDLE handle_type;
		typedef DCB    config_type;

	private:
		bool __M_device_startup ();
		bool __M_device_shutdown();
		
	public:
		fpga_device (std::string, uint16_t);
		~fpga_device();

	private:
		handle_type __M_device_handle;
		config_type __M_device_config;
		
	};
}

reflow::fpga_device::fpga_device(std::string device, uint16_t baud_rate)
{
	__M_device_config.BaudRate = baud_rate;
	__M_device_handle		   = ::CreateFileA(device.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL);

	__M_device_startup();
}

reflow::fpga_device::~fpga_device()
{

}

bool reflow::fpga_device::__M_device_startup()
{
	if (__M_device_handle == INVALID_HANDLE_VALUE)
		return false;

	fpga_uart_protocol::header st_header;
	st_header.hdr_opcode  = fpga_uart_protocol::major_opcode::startup;
	st_header.hdr_session = 0;

	DWORD st_req_byte = 0;
	BOOL  st_req_res  = ::WriteFile(__M_device_handle, &st_header, sizeof(fpga_uart_protocol::header), &st_req_byte, NULL);
	
	if (!st_req_res || !st_req_byte) 
		return false;

	st_req_byte = 0;
	st_req_res  = ::ReadFile(__M_device_handle, &st_header, sizeof(fpga_uart_protocol::header), &st_req_byte, NULL);

	if (!st_req_res || !st_req_byte) 
		return false;
	if (st_header.hdr_opcode == fpga_uart_protocol::major_opcode::error)
		return false;
	
	return true ;
}

bool reflow::fpga_device::__M_device_shutdown()
{
	fpga_uart_protocol::header st_header;
	st_header.hdr_opcode
}