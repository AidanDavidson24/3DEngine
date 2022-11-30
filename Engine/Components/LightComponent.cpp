#include "LightComponent.h"

#include "Engine.h"

#include <iostream>

namespace neu {

	void LightComponent::Update() {



	}

	bool LightComponent::Write(const rapidjson::Value& value) const {

		return true;

	}

	bool LightComponent::Read(const rapidjson::Value& value) {

		READ_DATA(value, color);

		READ_DATA(value, cutoff);

		READ_DATA(value, exponent);

		std::string type_name;

		READ_DATA(value, type_name);

		if (CompareIgnoreCase(type_name, "directional")) {

			type = lightTypes::Directional;

		}
		else if (CompareIgnoreCase(type_name, "spot")) {

			type = lightTypes::Spot;

		}
		else {

			type = lightTypes::Point;

		}

		return true;

	}

	void LightComponent::SetProgram(std::shared_ptr<Program> program, int index) {

		// transform the light position by the view, puts light in model view space

		glm::vec4 position = g_renderer.GetView() * glm::vec4(m_owner->m_transform.position, 1);

		//Set the direction from the transform forward at the top of the method (after getting the position) & returns a vector pointing in the forward direction of the light

		glm::vec3 direction = m_owner->m_transform.getForward();

		// create array light name from index (lights[0], ...) 

		std::string lightName = "lights[" + std::to_string(index) + "]";


		// get all programs in the resource system

		auto programs = g_resources.Get<Program>();

		// set programs light properties

		program->Use();

		program->SetUniform(lightName + ".type", (int)type);

		program->SetUniform(lightName + ".color", color);

		program->SetUniform(lightName + ".position", position);

		program->SetUniform(lightName + ".direction", direction);

		program->SetUniform(lightName + ".cutoff", glm::radians(cutoff));

		program->SetUniform(lightName + ".exponent", exponent);

	}

}