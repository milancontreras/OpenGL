#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  


void main()
{
	FragColor = vec4(0.3, 1.0, 1.0, 1.0);
}