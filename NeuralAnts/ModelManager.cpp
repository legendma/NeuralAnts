#include "pch.h"
#include "Config.h"
#include "Graphics.h"
#include "ModelManager.h"


ModelManager::ModelManager()
{
}


ModelManager::~ModelManager()
{
}

void ModelManager::SetModel(const char *name)
{
	auto search = m_models.find(std::string(name));
	if(search == m_models.end())
	{
		LoadModel(name);
	}

}

void ModelManager::Shutdown()
{
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

	auto &paths = Config::Instance().GetResourcePaths();
	auto found_it = false;

	auto name_str = std::string(name);
	std::unique_ptr<DirectX::Model> model;
	std::unique_ptr<DirectX::IEffectFactory> effects;

	/* check if model is CMO */
	assert(Utils::GetFileExtension(name_str) == std::string("cmo"));

	for(auto it : paths)
	{
		auto full_name = Utils::ToWide(it + name_str);
		model = Model::CreateFromCMO(Graphics::Instance().GetDevice().Get(), full_name.c_str(), *effects);

		if(model)
		{
			found_it = true;
			break;
		}
	}

	if(!found_it)
	{
		throw std::exception();
	}

	model->UpdateEffects(Graphics::UpdateEffects);

	/* create the record and add to our loaded list */
	ModelRecord record;
	record.model = std::move(model);

	//m_models.insert(std::make_pair(std::string(name), record));
}