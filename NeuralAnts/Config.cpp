#include "pch.h"

#include <Shlwapi.h>

#include "Config.h"


Config::Config()
{
}


Config::~Config()
{
}

const std::wstring Config::GetFileResourcePath(const char *name) const
{
	auto filename = std::wstring(Utils::ToWide(name));
	std::wstring full_name;
	for(auto it : m_resource_paths)
	{
		full_name = Utils::ToWide(it) + filename;
		auto exists = PathFileExists(full_name.c_str());
		if(exists)
		{
			return(full_name);
		}
	}

	assert(full_name.empty());
	return(std::wstring(L""));
}

void Config::Startup()
{
	/* load the configuration */
	m_window_size.cx = 800;
	m_window_size.cy = 600;
	m_is_fullscreen = false;

	m_resource_paths.push_back(std::string("assets/textures/"));
	m_resource_paths.push_back(std::string("assets/textures/dds/"));
	m_resource_paths.push_back(std::string("assets/models/cmo/"));
}