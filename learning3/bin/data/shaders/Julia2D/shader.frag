// fragment shader

#version 150
#define MAX_ITER 150

uniform float scale;
uniform int iter;
uniform float time;

out vec4 outputColor;

void main()
{
	float windowWidth = 1024.0;
	float windowHeight = 768.0;

	vec2 c = vec2(0.);
	vec2 z = vec2(0.);

	z.x = ((gl_FragCoord.x - 0.5* windowWidth)/ windowHeight)* 2.5;
	z.y = ((gl_FragCoord.y - 0.5* windowHeight)/ windowHeight) * 2.5;

	// This line was taken from https://www.shadertoy.com/view/4d23WG to find a good rotation basis for c
	c = 0.51*cos( vec2(0.0,1.5708) + 0.1*time ) - 0.25*cos( vec2(0.0,1.5708) + 0.2*time );

	float i;
	float dist = 1e20f;

	for(i = 0.; i < MAX_ITER; i++) {

		float x = (z.x * z.x - z.y * z.y) + c.x;
		float y = (z.y * z.x + z.x * z.y) + c.y;

		if((x * x + y * y) > 4.0) break;
		z.x = x;
		z.y = y;

		dist = min(dist, dot(z,z));


	}
	float f = 1.0+log(dist)/16.0;

	vec3 col = vec3(1-dist);
	outputColor = vec4(col,1-f);
}