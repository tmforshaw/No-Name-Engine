#shader vertex
#version 460 core
layout( location = 0 ) in vec3 a_pos;
layout( location = 1 ) in vec2 a_uvCoords;
layout( location = 2 ) in uint a_texID;

invariant out vec2	uvCoords;
invariant out float displayTexture;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

// Constants to do with the textureAtlas
uniform float u_atlasTexWidth;	// Width of the textures in images
uniform float u_atlasTexHeight; // Height of the textures in images
uniform uint  u_atlasPixWidth;	// Width in pixels

vec2 GetUV_Coords( uint p_textureId, vec2 p_uvCoords )
{
	uint i = ( p_textureId - 1 ) / u_atlasPixWidth;
	uint j = ( p_textureId - 1 ) % u_atlasPixWidth;

	return vec2( ( float( j ) + p_uvCoords.x ) / u_atlasTexWidth, ( float( i ) + p_uvCoords.y ) / u_atlasTexHeight );
}

void main()
{
	gl_Position = u_proj * u_view * u_model * vec4( a_pos, 1.0 );
	uvCoords	= GetUV_Coords( a_texID, a_uvCoords );

	displayTexture = float( a_texID > 0 );
}

#shader fragment
#version 460 core
layout( location = 0 ) in vec2 uvCoords;

in float displayTexture;

out vec4 o_fragColour;

uniform vec4	  u_colour;
uniform sampler2D u_textureAtlas;

void main()
{
	if ( displayTexture > 0.5 ) // Display a texture
		o_fragColour = texture( u_textureAtlas, uvCoords ) + u_colour;
	else
		o_fragColour = vec4( 0.0 );
}