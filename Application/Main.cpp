#include "Engine.h" 
#include <iostream> 

int main(int argc, char** argv)
{
	neu::InitializeMemory();

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();

	neu::g_renderer.CreateWindow("Neumont", 800, 600);

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		neu::g_renderer.BeginFrame();
		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.5f, -0.5f);

		glEnd();
		neu::g_renderer.EndFrame();
	}

	neu::Engine::Instance().Shutdown();
	return 0;
}