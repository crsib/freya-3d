uniform sampler2D guiTex;

void main()
{
	gl_FragColor = gl_Color * texture2D(guiTex, gl_TexCoord[0].xy);
}
