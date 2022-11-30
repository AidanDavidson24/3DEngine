#pragma once
#include "Framework/Component.h"

namespace neu {

	class Program;

	class LightComponent : public Component {

	public:

		CLASS_DECLARATION(LightComponent);

		enum class lightTypes {

			Point, Directional, Spot

		};

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

		void SetProgram(std::shared_ptr<Program> program, int index);

	public:

		glm::vec3 color{ 0 };

		lightTypes type = lightTypes::Point;

		float cutoff = 45.0f;

		float exponent = 50.0f;

	};

}