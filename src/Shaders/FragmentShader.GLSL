#version 330 core

in vec2 texCoord;

out vec4 fragColour;

uniform sampler2D sampler1;
uniform vec3 addedColour;
uniform vec2 textureCoordinates;

void main()
{
	fragColour = texture(sampler1, texCoord) * vec4(vec3(1.0, 1.0, 1.0) + addedColour, 1.0);
}