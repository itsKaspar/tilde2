// fragment shader

#version 150
#define MAX_ITER 150

uniform float scale;
uniform int iter;
uniform float time;

out vec4 outputColor;

float remap01(float a, float b, float t) // remap between 0 and 1
{
	return clamp((t - a) / (b - a), 0., 1.);
}
float remap(float a, float b, float c, float d, float t ) // remap t that is between a and b to be between c and d
{
	return ((t - a) / (b - a))* (d - c) + c;
}

// ##### 3D Tutorial

float DistLine(vec3 ro, vec3 rd, vec3 p)
{
	return length(cross(p - ro, rd))/length(rd);
}

float DrawPoint(vec3 ro, vec3 rd, vec3 p)
{
	float d = DistLine(ro, rd, p);
	d = smoothstep(.06, .05, d);
	return d;
}

void main()
{
	float windowWidth = 1024.0;
	float windowHeight = 768.0;

	vec2 uv = gl_FragCoord.xy / vec2(windowWidth,windowHeight); // 0 <> 1 // normalizing the coordinates
	uv -= 0.5; // -0.5 <> 0.5 remap to center
	uv.x *= windowWidth/windowHeight; // adapt it to our screen ratio
	vec3 col = vec3(0); //initialize color

	// Raycasting is about casting each ray from camera to screen.
	// a ray is defined by two points : 
	// 1. ray origin (camera) [vec3 ro]
	// 2. ray intersection with viewing plane
	// these points make up the direction vector [vec3 rd]
	// vector math says direction =  vec3(x2 - x1, y2 - y1, z2 - z1)

	//vec3 ro = vec3(3*sin(time),2.,-3*cos(time)); // ray origin // camera position
	vec3 ro = vec3(0);

	vec3 lookat = vec3(0); // lookat point
	float zoom = 1.;

	vec3 f = normalize(lookat-ro); // forward vector
	vec3 r = cross(vec3(0., 1.0, 0.), f); // right vector
	vec3 u = cross(vec3(f), r); // up vector

	vec3 c = ro + f * zoom;// center of screen
	vec3 i = c + uv.x*r + uv.y*u;// intersection point of the screen

	//vec3 rd = i - ro; // ray direction
	vec3 rd = normalize(vec3(uv.x, uv.y, 1));

	// ##### Drawing Sphere

	vec3 s = vec3(0,0,4); // sphere center
	float rad = 1.; // sphere radius

	float t = dot(s-ro, rd);
	vec3 p = ro + rd*t;
	float y = length(s-p);
	if(y<rad){ //so it doesnt cast anything out of the sphere
		float x = sqrt(rad*rad - y*y);
		float t1 = t-x;
		float t2 = t+x;

		float c = remap01(s.z,s.z-rad,t1);
		col = vec3(c);
	}

	// ##### Drawing Cube
	//float d = 0;
	//d += DrawPoint(ro, rd, vec3(0.,0.,0.));
	//d += DrawPoint(ro, rd, vec3(0.,0.,1.));
	//d += DrawPoint(ro, rd, vec3(0.,1.,0.));
	//d += DrawPoint(ro, rd, vec3(0.,1.,1.));
	//d += DrawPoint(ro, rd, vec3(1.,0.,0.));
	//d += DrawPoint(ro, rd, vec3(1.,0.,1.));
	//d += DrawPoint(ro, rd, vec3(1.,1.,0.));
	//d += DrawPoint(ro, rd, vec3(1.,1.,1.));
	//vec3 col = vec3(d);

	outputColor = vec4(col,1);
}