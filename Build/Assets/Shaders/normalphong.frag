#version 430 core

in vec3 position;

//in vec3 normal;

in vec2 texcoord;

in mat3 tbn;

out vec4 fcolor; // pixel to draw

struct Light{

	vec3 color;

	vec3 ambient;

	vec4 position;

};

struct Material{

	vec3 color;

	float shinnyness;

	vec2 uv_tiling;
	vec2 uv_offset;

};

uniform Light light;

uniform Material material;

uniform vec3 tint;

layout (binding = 0) uniform sampler2D diffuseMap; 
layout (binding = 1) uniform sampler2D normalMap;

void phong (vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
 	//AMBIENT

	ambient = light.ambient * material.color;

	//DIFFUSE

	vec3 lightDir = normalize(vec3(light.position) - position);

	//calculate light intensity with dit product (normal * light direction)

	float intensity = max(dot(lightDir, normal), 0);

	diffuse = light.color * material.color * intensity;

	//SPECULAR

	specular = vec3(0,0,0);

	if(intensity > 0){

		vec3 reflection = reflect(-lightDir, normal);

		vec3 viewDir = normalize(-vec3(position));

		intensity = max(dot(reflection, viewDir), 0);

		intensity = pow(intensity, 32.0);

		specular = light.color * intensity;
}
}

void main()
{
	vec2 ttexcoord = (texcoord * material.uv_tiling) + material.uv_offset;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 normal = texture(normalMap, texcoord).rgb;

	normal = (normal * 2) - vec3(1);
	normal = normalize(tbn * normal);

	phong(position, normal, ambient, diffuse, specular);
	
	//vec2 ttexcoord = (texcoord * material.uv_tiling) + material.uv_offset;

	//vec4 diffuseColor = texture(diffuseMap, ttexcoord);
	//vec4 specularColor = texture(specularMap, ttexcoord);
	//vec4 emissiveColor = texture(emissiveMap, ttexcoord);

	vec4 texture_color = texture(diffuseMap, texcoord);
	//vec4 texture_color = texture(diffuseMap, ttexcoord);

	//color = vec3(0.2) + diffuse + specular;

	vec4 color = vec4(ambient + diffuse, 1) * texture_color + (vec4(specular, 1));

	fcolor = color;

	//fcolor = texture_color;

}
