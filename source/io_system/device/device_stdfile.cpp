#include <reflow/io_system/device/disk/standard_file.hpp>

reflow::standard_file::standard_file(std::string fname, config fconfig)
{
	__M_stdfile_handle = ::CreateFileA(fname.c_str(), 
									  (std::underlying_type_t<config::access_mode>)fconfig.__M_config_access, 0, 0, 
									  (std::underlying_type_t<config::access_mode>)fconfig.__M_config_create, 0, 0);
}

reflow::standard_file::~standard_file()
{
	::CloseHandle(__M_stdfile_handle);
}

reflow::standard_file::config::config(creation_mode cmode, access_mode amode)
	: __M_config_access(amode),
	  __M_config_create(cmode) {  }