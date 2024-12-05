#version 330 core

out vec4 FragColor;
uniform vec3 uColor;
void main()
{
    vec3 gradientColor = mix(vec3(0.1f, 0.1f, 0.1f), vec3(0.8f, 0.8f, 0.8f), 0.1);

    FragColor = vec4(gradientColor, 1.0); // Output the interpolated color
}
