#frag
#version 100
precision highp float;
varying vec3 vpos;
varying vec3 vnormal;
varying vec2 vuv;

uniform vec3 color;


void main()
{
	gl_FragColor = vec4(1.0);
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