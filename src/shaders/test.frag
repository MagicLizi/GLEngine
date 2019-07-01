#version 330 core
in vec3 vetexColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(vetexColor,1.0f);
}