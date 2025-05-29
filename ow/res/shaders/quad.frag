#version 450

in vec2 fragTex;
out vec4 fragColor;

uniform sampler2D tex;

void main()
{

    
    vec3 color = texture(tex, fragTex).rgb;
    
    fragColor = vec4(color, 1.0);
}