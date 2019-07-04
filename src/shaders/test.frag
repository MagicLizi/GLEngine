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
    //mix(texture(texture0, TexCoord),texture(texture1, TexCoord),0.2) * vec4(ourColor,1.0f);
	FragColor = vec4(lightColor * objColor , 1.0f);
}