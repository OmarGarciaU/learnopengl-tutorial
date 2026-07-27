#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main() 
{
    //Flip horizontal
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
    //mix texture
    FragColor = vec4(lightColor * objectColor, 1.0);
}
