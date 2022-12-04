#version 430 core 
  
in vec2 texcoord; 
  
out vec4 fcolor; 

uniform sampler2D textureMap; 
  
void main(){ 

 vec3 color = texture(textureMap, texcoord).rgb; 
  
 // invert 

 fcolor = vec4(1.0 - color, 1); 

} 
