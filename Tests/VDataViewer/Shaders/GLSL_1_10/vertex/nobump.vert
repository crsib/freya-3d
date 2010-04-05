varying	vec3 lt;
varying	vec3 ht;
varying  vec3 norm;
uniform	vec3	lightPos;
uniform vec3	eyePos;

attribute vec3 tangent,binormal;

void main(void)
{
	vec3	p = vec3      ( gl_ModelViewMatrix * gl_Vertex );			// transformed point to world space
	vec3	lp= vec3     ( gl_ModelViewMatrix * vec4(lightPos,1.0) );
	        lp = lightPos;
	vec3	l = normalize ( lp  - p );					// vector to light source
	vec3	v = normalize ( eyePos - p );					// vector to the eye
	vec3	h = normalize ( l + v );

	vec3	n = gl_NormalMatrix * gl_Normal;							// transformed n

	vec3 t = gl_NormalMatrix * gl_MultiTexCoord1.xyz;			// transformed t
	vec3 b = gl_NormalMatrix * gl_MultiTexCoord2.xyz;			// transformed b
																// now remap l, and h into tangent space
	lt = l;
	ht = h;
	norm = n;

	gl_Position     = gl_ProjectionMatrix * gl_TextureMatrix[0] * gl_ModelViewMatrix * gl_Vertex;
	gl_TexCoord [0] = gl_MultiTexCoord0;
}

