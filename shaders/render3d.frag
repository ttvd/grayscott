varying vec2 tex_coord;

uniform int display_mode;
uniform sampler2D tex0U;

uniform int enable_discard;
uniform float discard_limit;

void main()
{
	float conc = texture2D(tex0U, tex_coord).r;

	// [rad] Do we want to discard bright pixels?
	if(enable_discard == 1)
	{
		if(conc > discard_limit)
		{
			discard;
		}
	}

	gl_FragColor = vec4(conc, conc, conc, 1.0);
}
