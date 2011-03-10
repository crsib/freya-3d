varying	vec3 lt;
varying	vec3 ht;
varying vec3 norm;

uniform sampler2D diffuse;
uniform sampler2D specular;


void main (void)
{
	vec3	nt   = normalize(norm);
	vec3	l2   = normalize ( lt );
	vec3	h2   = normalize ( ht );
	float	diff = max ( dot ( nt, l2 ), 0.0 );
	float	spec = pow ( max ( dot ( nt, h2 ), 0.0 ), 30.0 );

	gl_FragColor = diff * texture2D ( diffuse, gl_TexCoord [0].xy ) + spec * texture2D ( specular, gl_TexCoord [0].xy );

	//gl_FragColor = gl_Color;
}

