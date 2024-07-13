#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;
uniform mat4 MVP;
uniform vec2 repeatFactor;

void main()
{
   TexCoords = texCoords * repeatFactor; // Apply the repeat factor
   gl_Position = MVP * vec4(position, 1.0);
}