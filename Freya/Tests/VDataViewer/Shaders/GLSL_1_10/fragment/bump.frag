varying	vec3 lt;
varying	vec3 ht;
varying vec3 norm;

uniform sampler2D bump;
uniform sampler2D diffuse;
uniform sampler2D specular;


void main (void)
{
	vec3	n    = texture2D ( bump, gl_TexCoord [0].xy ).rgb;		// get normal perturbation
	vec3	nt   = normalize ( 2.0*n - 1.0 )*1.0;
			//nt	   = vec3(0.0,1.0,0.0);
	vec3	l2   = normalize ( lt );
	vec3	h2   = normalize ( ht );
	float	diff = max ( dot ( nt, l2 ), 0.0 );
	float	spec = pow ( max ( dot ( nt, h2 ), 0.0 ), 30.0 );

	gl_FragColor = diff * texture2D ( diffuse, gl_TexCoord [0].xy ) + spec * texture2D ( specular, gl_TexCoord [0].xy );

	//gl_FragColor = gl_Color;
}

