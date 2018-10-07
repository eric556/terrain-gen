#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(model) * aNormal;

	gl_Position = projection * view * vec4(FragPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;

void main() {
	FragColor = vec4(normalize(Normal), 1.0);
}