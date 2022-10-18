#include "Engine.h" 
#include <iostream> 

float points[] = {
  -0.5f, -0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
   0.5f, -0.5f,  0.5f,

  0.5f,  0.5f,  -0.5f,
   -0.5f,  -0.5f, -0.5f,
  -0.5f,  0.5f,  -0.5f
};

const char* vertex_shader =
"#version 430 core\n"
"in vec3 position;"
"void main() {"
"  gl_Position = vec4(position, 1.0);"
"}";



const char* fragment_shader =
"#version 430 core\n"
"out vec4 color;"
"void main() {"
"  color = vec4(1.0, 1.0, 0.0, 1.0);"
"}";

int main(int argc, char** argv)
{
	LOG("Application started...");
	
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();

	neu::g_renderer.CreateWindow("Neumont", 800, 600);

	LOG("Window created...");

	// create vertex buffer
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader
	//GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vs, 1, &vertex_shader, NULL);
	//glCompileShader(vs);
	//GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fs, 1, &fragment_shader, NULL);
	//glCompileShader(fs);

	// create program
	//std::shared_ptr<neu::Program> program = neu::g_resources.Get<neu::Program>("shaders/basic.prog");
	//program->Link();
	//program->Use();

	// create Texture
	//std::shared_ptr<neu::Texture> texture1 = neu::g_resources.Get<neu::Texture>("textures/llama.jpg"); 
	//std::shared_ptr<neu::Texture> texture2 = neu::g_resources.Get<neu::Texture>("textures/wood.png"); 
	//texture1->Bind();

	// create material 
	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("materials/box.mtrl");
	material->Bind();
	material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
	material->GetProgram()->SetUniform("scale", 0.5f);

	material->GetProgram()->SetUniform("scale", std::sin(neu::g_time.time * 3));
	glm::mat4 mx{ 1 };
	material->GetProgram()->SetUniform("transform", mx);

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		neu::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		neu::g_renderer.EndFrame();
	}

	neu::Engine::Instance().Shutdown();
	return 0;
}