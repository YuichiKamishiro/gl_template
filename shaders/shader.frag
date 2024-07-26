#version 330 core

in vec4 gl_FragCoord;
out vec3 color;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = ((gl_FragCoord * 2.0).xy - iResolution.xy) / iResolution.y;

    float d = length(uv);

    vec3 col = vec3(0.0, 1., 1.);

    d = sin(d * 12. + iTime * 2)/12.;
    d = abs(d);

    d = 0.01 / d;

    col *= d;

    color = col;
}