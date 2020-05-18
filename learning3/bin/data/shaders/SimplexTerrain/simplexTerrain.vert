#version 150
#pragma include "../../shaders/noise/simplex.glsl"


uniform mat4 modelViewProjectionMatrix;

in vec4 position;

uniform float mouseRange;
uniform vec2 mousePos;
uniform vec4 mouseColor;
uniform float time;

uniform int octaves;
uniform float scale;
uniform float persistence;
uniform float lacunarity;
uniform float speed;
uniform float direction;

out vec2 varyingtexcoord;

// ##### Main

void main(){

    // copy position so we can work with it.
    vec4 pos = position;
	float frequency = 1.0;
	float amplitude = 1.0;
	float z = 0.0;

	for	(int i = 0 ; i < octaves ; ++i)
	{
		z += simplex((vec2(
			(pos.x + time * speed * cos(direction))* frequency * scale,
			(pos.y + time * speed * sin(direction))* frequency * scale 
			)) / 100.0) * 50 * amplitude;

		amplitude *= persistence;
		frequency *= lacunarity;
	}
    pos.z = z;
	
	varyingtexcoord = vec2(pos.x, pos.y);
    gl_Position = modelViewProjectionMatrix * pos;
}

