#include "pch.h"
#include "Camera.h"
#include "Config.h"
#include "Graphics.h"
#include "ModelManager.h"


ModelManager::ModelManager()
{
}


ModelManager::~ModelManager()
{
}

void ModelManager::DrawModel(SimpleMath::Vector3 position, float scale, float x_rotation, float y_rotation, float z_rotation)
{
	auto &graphics = Graphics::Instance();
	auto &camera = Camera::Instance();

	auto uniform_scale = SimpleMath::Matrix::CreateScale(scale);
	
	auto x_rot = SimpleMath::Matrix::CreateRotationY(x_rotation);
	auto y_rot = SimpleMath::Matrix::CreateRotationY(y_rotation);
	auto z_rot = SimpleMath::Matrix::CreateRotationY(z_rotation);
	auto rotation = x_rot * z_rot * y_rot;

	auto translate = SimpleMath::Matrix::CreateTranslation(position);

	auto world = translate * rotation * uniform_scale;

	m_current_model->UpdateEffects(Graphics::UpdateEffects);
	m_current_model->Draw(graphics.GetContext().Get(), graphics.GetRenderStates(), world, camera.GetView(), camera.GetProjection());
}

void ModelManager::SetModel(const char *name)
{
	auto search = m_models.find(std::string(name));
	if(search == m_models.end())
	{
		LoadModel(name);
	}

	search = m_models.find(std::string(name));
	m_current_model = search->second.model;
}

void ModelManager::Shutdown()
{
	m_current_model.reset();
	for(auto &it : m_models)
	{
		it.second.model.reset();
	}

}

void ModelManager::Startup()
{
}

void ModelManager::LoadModel(const char *name)
{
	using namespace DirectX;
	using namespace Microsoft::WRL;

	auto &filename = Config::Instance().GetFileResourcePath(name);
	assert(Utils::GetFileExtension(filename.c_str()) == std::wstring(L".cmo"));

	/* load the model */
	auto model = Model::CreateFromCMO(Graphics::Instance().GetDevice().Get(), filename.c_str(), Graphics::Instance().GetEffectsFactory());

	/* create the record and add to our loaded list */
	ModelRecord record;
	record.model = std::move(model);

	m_models.insert(std::make_pair(std::string(name), record));
}