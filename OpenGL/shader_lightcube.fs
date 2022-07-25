#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;

void main()
{
    //FragColor = vec4(1.0, 1.0, 1.0, 0.3); // set alle 4 vector values to 1.0
    FragColor = vec4(objectColor, 0.3);
}