#version 430 core 

layout(location = 0) in vec3 vposition; // 0

layout(location = 1) in vec2 vtextcoord;

layout(location = 2) in vec3 vnormal;

layout(location = 3) in vec3 vtangent;

out vec3 position;

out vec2 textcoord;

out mat3 tbn;

uniform mat4 model;

uniform mat4 view;

uniform mat4 projection;

void main(){

	//create model view matrix

	mat4 modelView = view * model;

	//transform normals to view space

	vec3 normal = normalize(mat3(modelView) * vnormal);

	vec3 tangent = normalize(mat3(modelView) * vtangent);

	vec3 bitangent = cross(normal, tangent);

	tbn = mat3(tangent, bitangent, normal);

	//transform positions to view space

	position = vec3(modelView * vec4(vposition, 1));

	//pass trhough textcoord

	textcoord = vtextcoord;

	//calculate light direction (unit vector)

	mat4 mvp = projection * view * model;

	gl_Position = mvp * vec4(vposition, 1.0);

}