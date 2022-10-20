#version 430 core 
layout (location = 0) in vec3 vposition;
layout (location = 1) in vec3 vcolor;
layout (location = 2) in vec2 vtexcoord;

out vec3 color;
out vec2 texcoord;

uniform float scale;
uniform mat4 mvp;

void main()
{
	color = vcolor;
	texcoord = vtexcoord;

	vec4 tposition = mvp * vec4(vposition * scale, 1.0);
	gl_Position = tposition;
}
