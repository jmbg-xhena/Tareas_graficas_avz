#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = vec4(ourColor, 1.0)*mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.4);
	//FragColor = mix(texture(texture3, TexCoord), texture(texture4, TexCoord), 0.9);
}