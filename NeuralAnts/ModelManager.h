#pragma once

typedef struct
{
	std::shared_ptr<DirectX::Model> model;
} ModelRecord;

typedef std::map<std::string, ModelRecord> ModelMap;

class ModelManager : public Singleton<ModelManager>
{
	friend class Singleton < ModelManager > ;
public:
	ModelManager();
	~ModelManager();

	void DrawModel(SimpleMath::Vector3 position, float scale, float x_rotation, float y_rotation, float z_rotation);
	void SetModel(const char *name);
	void Shutdown();
	void Startup();


private:
	ModelMap                          m_models;
	std::shared_ptr<DirectX::Model>   m_current_model;

	void LoadModel(const char *name);
};

