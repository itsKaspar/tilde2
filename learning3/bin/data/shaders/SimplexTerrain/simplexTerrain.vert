#version 150

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

// ##### Simplex 2D Noise taken from 
// https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83

vec3 permute(vec3 x) { return mod(((x*34.0)+1.0)*x, 289.0); }

float snoise(vec2 v){
	const vec4 C = vec4(0.211324865405187, 0.366025403784439,
           -0.577350269189626, 0.024390243902439);
	vec2 i  = floor(v + dot(v, C.yy) );
	vec2 x0 = v -   i + dot(i, C.xx);
	vec2 i1;
	i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
	vec4 x12 = x0.xyxy + C.xxzz;
	x12.xy -= i1;
	i = mod(i, 289.0);
	vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
	+ i.x + vec3(0.0, i1.x, 1.0 ));
	vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy),
    dot(x12.zw,x12.zw)), 0.0);
	m = m*m ;
	m = m*m ;
	vec3 x = 2.0 * fract(p * C.www) - 1.0;
	vec3 h = abs(x) - 0.5;
	vec3 ox = floor(x + 0.5);
	vec3 a0 = x - ox;
	m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
	vec3 g;
	g.x  = a0.x  * x0.x  + h.x  * x0.y;
	g.yz = a0.yz * x12.xz + h.yz * x12.yw;
	return 130.0 * dot(m, g);
}

// ##### Main

void main(){

    // copy position so we can work with it.
    vec4 pos = position;
	float frequency = 1.0;
	float amplitude = 1.0;
	float z = 0.0;

	for	(int i = 0 ; i < octaves ; ++i)
	{
		z += snoise((vec2(
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


