// fragment shader

#version 150
#pragma include "../../shaders/ShaderTest/Functions.frag"

#define MAX_STEPS 100
#define MAX_DIST 100.
#define SURF_DIST .01

uniform float time;
uniform float w;
uniform float h;
out vec4 outputColor;

float kSphere(vec3 p)
{
	vec4 s = vec4(0,1,6,1); // sphere with radius 1 as 4th coord
	return length(p-s.xyz)-s.w; // distance from p to sphere center - radius
}

float kPlane(vec3 p)
{
	return 1;
}

float kCapsule(vec3 p, vec3 a, vec3 b, float r)
{
	vec3 ab = b - a;
	vec3 ap = p - a;
	float t  = dot(ab, ap) / dot(ab, ab);
	t = clamp(t, 0., 1.);
	vec3 c = a + t*ab;
	return length(p-c) - r;
}

float kCylinder(vec3 p, vec3 a, vec3 b, float r) {
	vec3 ab = b-a;
    vec3 ap = p-a;
    
    float t = dot(ab, ap) / dot(ab, ab);
    //t = clamp(t, 0., 1.);
    
    vec3 c = a + t*ab;
    
    float x = length(p-c)-r;
    float y = (abs(t-.5)-.5)*length(ab);
    float e = length(max(vec2(x, y), 0.));
    float i = min(max(x, y), 0.);
    
    return e+i;
}

float kTorus(vec3 p, vec3 a, vec2 r)
{
	// r are both circles radiuses, the circle main, and the circle taht goes around it
	float x = length(p.xz - a.xz)-r.x;
    return length(vec2(x, p.y - a.y))-r.y;
}

float kBox(vec3 p, vec3 a, vec3 s) // s is size of box
{
	return length(max(abs(p-a)-s,0.));
}

float kJulia(vec3 pos)
{
    float t = time / 3.0;
    
	vec4 c = 0.5*vec4(cos(t),cos(t*1.1),cos(t*2.3),cos(t*3.1));
    vec4 z = vec4( pos, 0.0 );
	vec4 nz;
    
	float md2 = 1.0;
	float mz2 = dot(z,z);

	for(int i=0;i<10;i++)
	{
		md2*=4.0*mz2;
	    nz.x=z.x*z.x-dot(z.yzw,z.yzw);
		nz.yzw=2.0*z.x*z.yzw;
		z=nz+c;

		mz2 = dot(z,z);
		if(mz2>4.0)
        {
			break;
        }
	}

	return 0.25*sqrt(mz2/md2)*log(mz2);
}


float GetDist(vec3 p)
{
	float sphereDist = kSphere(p);
	float planeDist = p.y;

	float julia = kJulia(p);
	float box = kBox(p, vec3(1), vec3(.2));

	//float d = min(julia, planeDist);
	//float d2 = min(d, box);
	return julia;
}

float RayMarch(vec3 ro, vec3 rd)
{
	float d0 = 0.;
	for(int i=0; i < MAX_STEPS; i++)
	{
		vec3 p = ro + rd * d0; // current marching location // start at ray origin and march in ray direction * d0
		float dS = GetDist(p); // get distance to the scene
		d0 += dS; // add that to distance from origin
		if(d0 > MAX_DIST || dS < SURF_DIST) break;
	}
	return d0; // it then outputs a height map (distance field) that I may have to divide to actually see right
}

// lights are just dot products between light ray and normal vector
// light vector is normalize(light pos to surface pos)

vec3 GetNormal(vec3 p) {
	float d = GetDist(p); // take distance at point P
    vec2 e = vec2(.01, 0);
    
    vec3 n = d - vec3(
        GetDist(p-e.xyy),
        GetDist(p-e.yxy),
        GetDist(p-e.yyx));
    
    return normalize(n);
}

float GetLight(vec3 p) {
    vec3 lightPos = vec3(0, 5, 6); // initial light pos
    lightPos.xz += vec2(sin(time), cos(time))*2.; // rotate light
    vec3 l = normalize(lightPos-p); // get light vector, light point - surface point
    vec3 n = GetNormal(p);
    
    float dif = clamp(dot(n, l), 0., 1.);
    float d = RayMarch(p+n*SURF_DIST*2., l); // get shadows using reverse raymarching
    if(d<length(lightPos-p)) dif *= .1;
    
    return dif;
}


//vec3 GetNormal // sample two points, and trace perpidicular 


void main()
{
	vec2 uv = gl_FragCoord.xy / vec2(w,h); // 0 <> 1 // normalizing the coordinates
	uv -= 0.5; // -0.5 <> 0.5 remap to center
	uv.x *= w/h; // adapt it to our screen ratio
	vec3 col = vec3(0);
    
    vec3 ro = vec3(0, 1, -5);
    vec3 rd = normalize(vec3(uv.x, uv.y-.2, 1));

	float d = RayMarch(ro, rd);
	// d /= 6 to actually see height map, maybe i could make a small function to map all values between 0 and 1 ?

	vec3 p = ro + rd * d; // grab all points in 3D space that come back to the camera
	float dif = GetLight(p);// diffuse lighting

    col = vec3(dif);

	outputColor = vec4(col,1);
}

