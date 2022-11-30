#version 430 core

in vec3 refrac_dir;

in vec3 reflec_dir;

out vec4 fcolor;

uniform samplerCube cubeMap;

uniform float e = 1;

void main(){

	vec3 refrac_color = texture(cubeMap, refrac_dir).rgb;

	vec3 reflec_color =  texture(cubeMap, reflec_dir).rgb;

	vec3 color = mix(reflec_color, refrac_color, e);

	//set fragment color
	
	fcolor = texture(cubeMap, color);

}
