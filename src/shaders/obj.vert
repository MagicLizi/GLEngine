#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 nPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 NormalPos;
out vec3 FragPos;

void main()
{
	gl_Position =  proj * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    NormalPos = mat3(transpose(inverse(model))) * nPos; //基于model 变换的法线矩阵，最好用CPU先算 因为逆矩阵消耗比较大
}