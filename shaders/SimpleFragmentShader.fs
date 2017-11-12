#version 330 core

in vec3 fragmentColor;
in vec2 texCoord;

//Output data
out vec4 color;

uniform sampler2D ourTexture;

void main()
{
	
	//color = vec4(fragmentColor,1);
	color = texture(ourTexture, texCoord);
}