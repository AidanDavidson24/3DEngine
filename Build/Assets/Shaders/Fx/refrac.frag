#version 430 core

in vec3 refrac_dir;

out vec4 fcolor;

uniform samplerCube cubeMap;

void main(){

	fcolor = texture(cubeMap, refrac_dir);

}
