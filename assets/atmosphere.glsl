#frag
#version 100
precision highp float;
varying vec3 vpos;
varying vec3 vnormal;
varying vec2 vuv;

uniform vec3 color;


void main()
{
	vec3 skyColor = vec3(38.0, 50.0, 122.0) / vec3(255.0);
	vec3 horizonColor = vec3(114.0, 130.0, 224.0) / vec3(255.0);

	float distFromHorizon = abs(vpos.y - 0.0);

	gl_FragColor = vec4(mix(horizonColor, skyColor, min(distFromHorizon * 3.0, 1.0)), 1.0);
}

#vert
#version 100
precision highp float;
attribute vec3 position;
attribute vec3 normal;
attribute vec2 uv;
uniform mat4 mvp;
varying vec3 vpos;
varying vec3 vnormal;
varying vec2 vuv;


void main()
{
	vnormal = normal;
	vpos = position;
	vuv = uv;
	gl_Position = mvp * vec4(position, 1.0);
}