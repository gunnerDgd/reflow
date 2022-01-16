#pragma once
#include <reflow/io_system/define.hpp>
#include <string>

namespace reflow {
	class standard_file
	{
		friend class standard_file_reader;
		friend class standard_file_writer;
	public:
		typedef HANDLE handle_type;
		class		   config;

	public:
		standard_file (std::string, config);
		~standard_file();

	private:
		handle_type __M_stdfile_handle;
	};

	class standard_file::config
	{
		friend class standard_file;
	public:
		enum class creation_mode : uint32_t
		{
			create = CREATE_NEW,
			open   = OPEN_EXISTING
		};

		enum class access_mode : uint32_t
		{
			read_only  = GENERIC_READ,
			write_only = GENERIC_WRITE,
			all		   = GENERIC_ALL
		};

	public:
		config(creation_mode cmode = creation_mode::create, access_mode amode = access_mode::all);

	private:
		creation_mode __M_config_create;
		access_mode   __M_config_access;
	};
}

