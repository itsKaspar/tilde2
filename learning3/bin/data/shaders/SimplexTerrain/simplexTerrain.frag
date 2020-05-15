#version 150
#pragma include "../../shaders/noise/perlin.glsl"

/*
uniform vec4 globalColor;
out vec4 outputColor;
uniform float time;
in vec2 varyingtexcoord;



float fbm( in vec2 x, in float H )
{    
    float G = exp2(-H);
    float f = 1.0;
    float a = 1.0;
    float t = 0.0;
    for( int i=0; i<8; i++ )
    {
        t += a*perlin(f*x,2);
        f *= 2.0;
        a *= G;
    }
    return t;
}

float pattern (in vec2 p)
{
    vec2 q = vec2( fbm( p + vec2(time/100,0.0),1 ),
                   fbm( p + vec2(5.2,1.3),1 ) );

    return fbm( p + 4.0*q, 1 );
}

void main()
{
	float windowWidth = 1024.0;
	float windowHeight = 768.0;

	float x = ((varyingtexcoord.x - 0.5* windowWidth)/ windowHeight)* 2.5;
	float y = ((varyingtexcoord.y - 0.5* windowHeight)/ windowHeight) * 2.5;

	vec3 col = vec3(0,0,0);
	col = mix(col, vec3(0.2,0.5,0.85), exp(pattern(vec2(x,y))));
	col = mix( col, vec3(0.85,0.45,0.90), dot(pattern(vec2(x,y)),pattern(vec2(x,y))));


	outputColor = vec4(col, 1);
}
*/