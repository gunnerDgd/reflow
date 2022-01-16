#pragma once
#include <reflow/io_system/basic_reader.hpp>
#include <reflow/io_system/basic_writer.hpp>

#include <reflow/io_system/traits/basic_reader_traits.hpp>
#include <reflow/io_system/traits/basic_writer_traits.hpp>

#include <reflow/io_system/device/peripheral/uart.hpp>
#include <reflow/io_system/method/uart/uart_reader.hpp>
#include <reflow/io_system/method/uart/uart_writer.hpp>

namespace reflow {
	typedef basic_reader<uint8_t, basic_reader_traits<uint8_t, uart_read_method>>  uart_reader;
	typedef basic_writer<uint8_t, basic_writer_traits<uint8_t, uart_write_method>> uart_writer;
}