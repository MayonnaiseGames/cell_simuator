#version 460 core

in vec2 TexCoords;
out vec4 FragColor;

uniform usampler2D canvasTex;

void main(){
    uint value = texture(canvasTex, TexCoords).r;

    if (value == 0u)
        discard;
    else if (value == 1u)
        FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    else if (value == 2u)
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    else
        FragColor = vec4(1.0, 1.0, 1.0, 1.0); // debug color
}