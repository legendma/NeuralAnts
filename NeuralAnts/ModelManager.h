#pragma once

typedef struct
{
	std::unique_ptr<DirectX::Model> model;
} ModelRecord;

typedef std::map<std::string, ModelRecord> ModelMap;

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	void SetModel(const char *name);
	void Shutdown();
	void Startup();


private:
	ModelMap               m_models;

	void LoadModel(const char *name);
};

