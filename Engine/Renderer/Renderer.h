#pragma once

#include "Math/Color.h"

#include "Math/Matrix3X3.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <SDL.h> 

struct SDL_Renderer;

struct SDL_Window;

namespace neu {

	struct Transform;

	struct Rect;

	class Texture;

	class Renderer {

	public:

		Renderer() = default;

		~Renderer() = default;

		void Initialize();

		void Shutdown();

		void CreateWindow(const std::string& name, int width, int height, bool fullscreen = false);

		void BeginFrame();

		void EndFrame();

		void Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle = 0, const Vector2& scale = Vector2{ 1,1 }, const Vector2& registration = Vector2{ 0.5f,0.5f });

		void Draw(std::shared_ptr<Texture> texture, const Transform& transform, const Vector2& registration = Vector2(0.5f, 0.5f));

		void Draw(std::shared_ptr<Texture> texture, const Rect& source, const Transform& transform, const Vector2& registration = Vector2(0.5f, 0.5f), bool flipH = false);

		void DrawLine(float x1, float y1, float x2, float y2);

		void DrawLine(const Vector2& v1, const Vector2& v2, const Color& color);

		void DrawPoint(float x1, float y1);

		void DrawPoint(const Vector2& v, const Color& color);

		void SetViewport(int x, int y, int width, int height);

		void RestoreViewport();

		const glm::mat4& GetView() { return m_view; }

		void SetView(const glm::mat4& view) { m_view = view; }

		const glm::mat4& GetProjection() { return m_projection; }

		void SetProjection(const glm::mat4& projection) { m_projection = projection; }

		void SetClearColor(const Color& color) { clear_color = glm::vec3(color.r, color.g, color.b); }

		int GetWidth() { return width; }

		int GetHeight() { return height; }

		friend class Text;

		friend class Texture;

		friend class GUI;

		glm::vec3 ambient_color{ 0.3, 0, 0.3 };

		glm::vec3 clear_color{ 0, 0, 0 };

		int width = 800;

		int height = 600;

		bool fullscreen = false;

	private:

		glm::mat4 m_view{ 1 };

		glm::mat4 m_projection{ 1 };

		SDL_Renderer* m_renderer = nullptr;

		SDL_Window* m_window = nullptr;

		SDL_GLContext m_context;

	};

}