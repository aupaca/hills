#version 320 es

precision mediump float;

in vec4 vertColor;
out vec4 fragColor;

void main()
{
    fragColor = vertColor;
}

