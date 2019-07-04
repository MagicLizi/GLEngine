#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 objColor;
void main()
{
	FragColor = vec4(1.0);
}