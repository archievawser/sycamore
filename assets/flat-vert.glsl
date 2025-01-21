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