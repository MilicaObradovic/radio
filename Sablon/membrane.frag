#version 330 core

out vec4 outCol;
uniform int uW;
uniform int uH;

void main()
{
	outCol = vec4(0.2f, 0.2f, 0.2f, 0.5);
	
    // Add conditions for horizontal and vertical lines
    // Horizontal lines: Check if y modulo some value is within the line thickness
    bool horizontalLine = mod(gl_FragCoord.y, 5) < 1;

    // Vertical lines: Check if x modulo some value is within the line thickness
    bool verticalLine = mod(gl_FragCoord.x, 5) < 1;

    // Combine the conditions to create a grid pattern
    if (!(horizontalLine || verticalLine))
    {
        discard; // Skip drawing the fragment for the line
    }

}