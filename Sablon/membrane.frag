#version 330 core

out vec4 outCol;
uniform int uW;
uniform int uH;

void main()
{
	outCol = vec4(0.2f, 0.2f, 0.2f, 0.5);
	
    bool horizontalLine = mod(gl_FragCoord.y, 5) < 1;

    bool verticalLine = mod(gl_FragCoord.x, 5) < 1;

    if (!(horizontalLine || verticalLine))
    {
        discard;
    }

}