// fragment shader

#version 150
#define MAX_ITER 150

uniform float scale;
uniform int iter;
uniform float time;

out vec4 outputColor;

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
	float mask2 = 0;

	float x = uv.x;
	float m = sin((x+time/20)*25)*.02;
	float y = uv.y-m;

	float blur = remap(.003, .003, .003, .003, x); //remap value 
	//blur *= blur; // make it less linear

	mask = Rect(vec2(x,y+.035), -.12, .12, .015, -.015, blur);
	mask2 = Rect(vec2(x,y-.035), -.12, .12, .015, -.015, blur);

	mask += mask2;

	col = vec3(1,1,1)*mask;
	float alpha = mask;

	outputColor = vec4(vec3(col),alpha);
}