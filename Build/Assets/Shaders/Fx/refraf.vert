#version 430 core 

in layout(location = 0) vec3 vposition;

in layout(location = 2) vec3 vnormal;

out vec3 refrac_dir;

out vec3 reflec_dir;

uniform mat4 model;

uniform mat4 view;

uniform mat4 projection;

uniform float ri = 1;

void main(){

	vec3 position = vec3(model * vec4(vposition,1));

	vec3 normal = normalize(mat3(model) * vnormal);

	vec3 camera_position = vec3(inverse(view)[3]);

	vec3 view_dir = normalize(position - camera_position);

	refrac_dir = refract(view_dir, normal, 1/ri);

	reflec_dir = reflect(view_dir, normal);

	mat4 mvp = projection * view * model;

	gl_Position = mvp * vec4(vposition, 1.0);

}
