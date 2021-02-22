#version 330 core

in vec3 ourColour;
in vec2 texCoord;

out vec4 fragColour;

uniform sampler2D texture1;

uniform vec3 addedColour;

void main()
{
	fragColour = texture(texture1, texCoord) * vec4(ourColour + addedColour, 1.0);
}