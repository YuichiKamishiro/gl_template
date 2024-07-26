#version 330 core

in vec4 gl_FragCoord;
out vec3 color;
 
// big thanks to https://www.youtube.com/watch?v=f4s1h2YETNY

uniform vec2 iMouse;
uniform vec2 iResolution;
uniform float iTime;

vec3 palette( float t ) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263,0.416,0.557);

    return a + b*cos( 6.28318*(c*t+d) );
}

out vec4 fragColor;
in vec4 gl_FragCoord;

void main() {
    vec4 fragCoord = gl_FragCoord;
    vec2 uv = ((fragCoord * 2.0).xy - iResolution.xy) / iResolution.y;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0, 0.0, 0.0);
    
    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;

        float d = length(uv) * exp(-length(uv0));

        vec3 col = palette(length(uv0) + i*.4 + iTime*.4);

        d = sin(d*8. + iTime * 3)/8.;
        d = abs(d);

        d = pow(0.01 / d, 1.2);

        finalColor += col * d;
    }
        
    fragColor = vec4(finalColor, 1.0);
}