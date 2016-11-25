#pragma once

typedef std::list<std::string> ResourcePaths;
class Config : public Singleton<Config>
{
	friend class Singleton < Config >;
	Config();
public:
	~Config();

	void Startup();
	const ResourcePaths & GetResourcePaths() const { return(m_resource_paths); }
	SIZE GetDefaultWindowSize() const { return(m_window_size); }
	bool GetFullscreen() const { return(m_is_fullscreen); }

private:
	ResourcePaths          m_resource_paths;
	bool                   m_is_fullscreen;
	SIZE                   m_window_size;
};

