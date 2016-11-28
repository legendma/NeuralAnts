//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Graphics.h"

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game()
{
}

// Executes the basic game loop.
void Game::DoFrame()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;
}

// TESTING REMOVE //////////
	#include "TextureManager.h"
    #include "ModelManager.h"
	#include "Camera.h"
// TESTING REMOVE //////////
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

	auto &graphics = Graphics::Instance();
	
	graphics.Clear();

    //testing REMOVE
	auto &camera = Camera::Instance();
	camera.SetPosition(SimpleMath::Vector3(2.0f, 3.0f, 2.0f));
	camera.LookAt(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));

	//auto &textures = TextureManager::Instance();
	//textures.SetTexture("grass.dds");

	auto &models = ModelManager::Instance();
	models.SetModel("woodencup.cmo");

	//graphics.PushRaster();
	//graphics.SetWireframe();
	models.DrawModel(SimpleMath::Vector3(-0.5f, 0.0f, 0.0f), 1.0f, 0.0f, 0.0f, 0.0f);
	//graphics.PopRaster();

	models.SetModel("cup.cmo");
	models.DrawModel(SimpleMath::Vector3(0.5f, -0.5f, 0.0f), 2.0f, 0.0f, 0.0f, 0.0f);

	// testing END
    graphics.Present();
}

void Game::ResetElapsedTime()
{
	m_timer.ResetElapsedTime();
}
void Game::Startup()
{
	//testing REMOVE
	//TextureManager::Instance().SetTexture("grass.dds");
	Graphics::Instance().SetMSAA(true, 8);
}

void Game::Shutdown()
{
}