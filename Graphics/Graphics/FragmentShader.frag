#version 110 


uniform sampler2D tex;

uniform vec4 lightPosition;	//light source


varying vec4 fragNormal;
varying vec4 fragColor;
varying vec4 fragPosition;
varying vec4 fragCameraPosition;
varying vec2 fragTexCoord;
varying vec4 fragOutLine;

float testInt() {
	return 1.0;
}

void main() {

	vec4 L = lightPosition - fragPosition;
	vec4 V = fragCameraPosition - fragPosition;
	vec4 N = fragNormal;
	
	L.w = 0.0;
	V.w = 0.0;
	N.w = 0.0;
	
	L = normalize(L);
	V = normalize(V);
	N = normalize(N);

	float ambient = 1.0;
	float diffusion = max(0.0, dot(L, N));
	float specular = 0.0;
	if(dot(L, N) > 0.0)	specular = max(0.0, dot(((2.0 * dot(L, N) * N) - L), V));
	float shiness = 10.0;
	specular = max(0.0, pow(specular, shiness));
	
	float ac = 0.5;
	float dc = 0.6;
	float sc = 1.0;

	vec2 coord = vec2(0.0, 0.0);
	
	vec4 outLine = fragOutLine;
	outLine.w = 0.0;
	//outLine = normalize(outLine);

	vec4 virt = outLine;

	vec4 texColor = texture2D(tex, fragTexCoord);
	vec4 phongColor = fragColor * (ac * ambient + dc * diffusion + sc * specular);

	gl_FragColor = phongColor * texColor;

}