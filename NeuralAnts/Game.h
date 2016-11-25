//
// Game.h
//

#pragma once

#include "StepTimer.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public Singleton<Game>
{
	friend class Singleton < Game > ;
    Game();
public:


    // Initialization and management
	void Startup();
	void Shutdown();
	void ResetElapsedTime();

    // Basic game loop
    void DoFrame();


private:

    void Update(DX::StepTimer const& timer);
    void Render();

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
};