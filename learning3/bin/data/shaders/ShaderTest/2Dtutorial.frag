// fragment shader

#version 150
#define MAX_ITER 150


uniform float scale;
uniform int iter;
uniform float time;

out vec4 outputColor;

float Circle(vec2 uv, vec2 p, float r, float blur)
{
	float d = length(uv-p);
	float c = smoothstep(r, r-blur, d);
	return c;
}

float Band(float t, float start, float end, float blur)
{
	float step1 = smoothstep(start-blur, start+blur, t);
	float step2 = smoothstep(end+blur, end-blur, t);
	return step2*step1;
}

float Rect(vec2 uv, float left, float right, float bottom, float top, float blur)
{
	float band1 = Band(uv.x, left, right, blur);
	float band2 = Band(uv.y, top, bottom, blur);
	return band1*band2;
}

float Smiley(vec2 uv, vec2 p, float size)
{
	uv -= p;
	uv /= size;

	float mask = Circle(uv, vec2(0,0), 0.4, 0.01); // first circle
	mask -= Circle(uv, vec2(.13,.15),.05, .01); // substract second circle
	mask -= Circle(uv, vec2(-.13,.15),.05, .01); // substract second circle

	float mouth = Circle(uv, vec2(0., 0.), .3, .02);
	mouth -= Circle(uv, vec2(0., 0.1), .3, .02);

	mask -= mouth;
	return mask;
}

float remap01(float a, float b, float t) // remap between 0 and 1
{
	return clamp((t - a) / (b - a), 0., 1.);
}
float remap(float a, float b, float c, float d, float t ) // remap t that is between a and b to be between c and d
{
	return ((t - a) / (b - a))* (d - c) + c;
}

void main()
{
	float windowWidth = 1024.0;
	float windowHeight = 768.0;

	vec2 uv = gl_FragCoord.xy / vec2(windowWidth,windowHeight); // 0 <> 1 // normalizing the coordinates
	uv -= 0.5; // -0.5 <> 0.5 remap to center
	uv.x *= windowWidth/windowHeight; // adapt it to our screen ratio

	vec3 col = vec3(0.);

	float mask = 0;

	//float mask = Smiley(uv, vec2(0.,0.), 1.5);



	float x = uv.x;

	float m = sin((x+time/5)*8)*.1;

	float y = uv.y-m;

	float blur = remap(-.5, .5, .01, .25, x); //remap value 
	blur *= blur; // make it less linear

	mask = Rect(vec2(x,y), -.5, .5, .1, -.1, blur);

	col = vec3(1., 1.,1.)*mask;

	outputColor = vec4(vec3(col),1);
}