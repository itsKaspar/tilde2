
float kCircle(vec2 uv, vec2 pos, float radius, float blur)
{
	float d = length(uv-pos);
	float c = smoothstep(radius, radius-.01, d);
	return c;
}


