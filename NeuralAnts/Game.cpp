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

    // TODO: Add your rendering code here.

    graphics.Present();
}

void Game::ResetElapsedTime()
{
	m_timer.ResetElapsedTime();
}

void Game::Startup()
{
}

void Game::Shutdown()
{
}