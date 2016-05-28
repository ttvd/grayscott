varying vec2 tex_coord;
uniform int mapping_mode;

uniform int enable_displacement;
uniform float displace_size;

uniform sampler2D tex0U;

void main()
{
	vec4 vert = gl_Vertex;
	vec3 normal = gl_Normal;
	
	// [rad] Special mapping mode for sphere and torus (glut) - those do not have UV coordinates
	// and end up textured pretty badly.
	if(mapping_mode == 1)
	{
		float PI = 3.141592;

		// [rad] This is spherical mapping.
		tex_coord.t = asin(normal.x) / PI + 0.5;
		tex_coord.s = asin(normal.y) / PI + 0.5;
	}
	else
	{
		tex_coord = gl_MultiTexCoord0.st;
	}

	// [rad] We want to displace vertex.
	if(enable_displacement == 1)
	{
		float conc = texture2D(tex0U, tex_coord).r * displace_size;
		vec3 modified_normal = normal * conc;

		vert.x += modified_normal.x;
		vert.y += modified_normal.y;
		vert.z += modified_normal.z;
	}


	// [rad] Final vertex transformation.
	gl_Position = gl_ModelViewProjectionMatrix * vert;
}
