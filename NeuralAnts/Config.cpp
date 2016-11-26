#include "pch.h"
#include "Config.h"


Config::Config()
{
}


Config::~Config()
{
}

void Config::Startup()
{
	/* load the configuration */
	m_window_size.cx = 800;
	m_window_size.cy = 600;
	m_is_fullscreen = false;

	m_resource_paths.push_back(std::string("assets/textures/dds"));
	m_resource_paths.push_back(std::string("assets/models/cmo"));
}