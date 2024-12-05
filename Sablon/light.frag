#version 330 core
out vec4 FragColor;

uniform float time; // Time variable to animate the light color
uniform bool isOn; // Time variable to animate the light color

void main() {
    if (isOn) {
        // Interpolate between white and orange
        vec3 white = vec3(1.0, 1.0, 1.0);
        vec3 orange = vec3(1.0, 0.5, 0.0);
        float factor = (sin(time) + 1.0) / 2.0; // Oscillates between 0 and 1
        vec3 lightColor = mix(white, orange, factor);

        FragColor = vec4(lightColor, 1.0);
    }else{
        FragColor = vec4(vec3(0.0f), 1.0);
    }
}