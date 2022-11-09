#version 430 core

in vec3 position;

in vec3 normal;

in vec2 textcoord;

out vec4 fcolor; // pixel to draw

struct Light{

	vec3 color;

	vec3 ambient;

	vec4 position;

};

struct Material{

	vec3 color;

	float shinnyness;

};

uniform Light light;

uniform Material material;

uniform vec3 tint;

uniform sampler2D textureSampler;

void main(){

	//AMBIENT

	vec3 ambient = light.ambient * material.color;

	//DIFFUSE

	vec3 lightDir = normalize(vec3(light.position) - position);

	//calculate light intensity with dit product (normal * light direction)

	float intensity = max(dot(lightDir, normal), 0);

	vec3 diffuse = light.color * material.color * intensity;

	//SPECULAR

	vec3 specular = vec3(0);
	
	if(intensity > 0){

		vec3 reflection = reflect(-lightDir, normal);

		vec3 viewDir = normalize(-vec3(position));

		intensity = max(dot(reflection, viewDir), 0);

		intensity = pow(intensity, 32.0);

		specular = light.color * intensity;

	}

	//color = vec3(0.2) + diffuse + specular;

	fcolor = vec4(ambient + diffuse, 1) * texture(textureSampler, textcoord) + vec4(specular, 1);

}
