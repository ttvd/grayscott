uniform int display_mode;

uniform sampler2D tex0U;

void main()
{
	if(display_mode == 0)
	{
		float valU = texture2D(tex0U, gl_TexCoord[0].xy).r;		
		gl_FragColor = vec4(valU, valU, valU, 1.0);
	}
	else if(display_mode == 1)
	{
		float valV = texture2D(tex0U, gl_TexCoord[0].xy).g;	
		gl_FragColor = vec4(valV, valV, valV, 1.0);
	}
	else if(display_mode == 2)
	{
		float changeU = texture2D(tex0U, gl_TexCoord[0].xy).b;	
		gl_FragColor = vec4(changeU, changeU, changeU, 1.0);
	}
}
