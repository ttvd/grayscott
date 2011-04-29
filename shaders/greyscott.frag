uniform float step_width;
uniform float step_height;

uniform float du;
uniform float dv;

uniform float distance;
uniform float timestep;

uniform float k;
uniform float f;

uniform sampler2D tex0U;

void main()
{
    // [rad] Store original concentrations for both U and V.
    float oldU = texture2D(tex0U, gl_TexCoord[0].xy).r;				
    float oldV = texture2D(tex0U, gl_TexCoord[0].xy).g;	

    // [rad] Compute approximation of Laplacian for both V and U.
    float otherU = -4.0 * oldU;
    float otherV = -4.0 * oldV;

    otherU += texture2D(tex0U, gl_TexCoord[0].xy + vec2(-step_width, 0)).r;
    otherU += texture2D(tex0U, gl_TexCoord[0].xy + vec2(step_width, 0)).r;
    otherU += texture2D(tex0U, gl_TexCoord[0].xy + vec2(0, -step_height)).r;
    otherU += texture2D(tex0U, gl_TexCoord[0].xy + vec2(0, step_height)).r;

    otherV += texture2D(tex0U, gl_TexCoord[0].xy + vec2(-step_width, 0)).g;
    otherV += texture2D(tex0U, gl_TexCoord[0].xy + vec2(step_width, 0)).g;
    otherV += texture2D(tex0U, gl_TexCoord[0].xy + vec2(0, -step_height)).g;
    otherV += texture2D(tex0U, gl_TexCoord[0].xy + vec2(0, step_height)).g;

    float distance_squared = distance * distance;
    
    // [rad] Compute greyscott equations.
    float newU = du * otherU / distance_squared - oldU * oldV * oldV + f * (1.0 - oldU);
    float newV = dv * otherV / distance_squared + oldU * oldV * oldV - (f + k ) * oldV;

    float scaledU = oldU + newU * timestep;
    float scaledV = oldV + newV * timestep;

    gl_FragColor = vec4(clamp(scaledU, 0.0, 1.0), clamp(scaledV, 0.0, 1.0), clamp(newU, 0.0, 1.0), 1.0);
}
