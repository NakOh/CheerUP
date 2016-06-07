#version 110 

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 xAxisRotationMatrixID;
uniform mat4 yAxisRotationMatrixID;
uniform mat4 zAxisRotationMatrixID;
uniform vec4 centerPosition;
uniform mat4 projectionMatrix;
uniform vec4 cameraPosition;
uniform mat4 scaleMatrix;
uniform mat4 camXRot;
uniform mat4 camYRot;
uniform mat4 camZRot;

uniform vec4 lightPosition;	//light source

attribute vec4 vertexPosition;
attribute vec4 vertexColor;
attribute vec4 vertexNormal;
attribute vec2 vertexTexture;

varying vec4 fragColor;
varying vec4 fragNormal;
varying vec4 fragPosition;
varying vec4 fragCameraPosition;
varying vec2 fragTexCoord;
varying vec4 fragOutLine;

void main () {
	mat4 rotation = xAxisRotationMatrixID *yAxisRotationMatrixID *zAxisRotationMatrixID;
	fragCameraPosition = cameraPosition;
	fragColor = vertexColor;
	fragNormal = rotation * vertexNormal;
	vec4 center = centerPosition;
	center.w = 0.0;
	fragOutLine = (vertexPosition - center);
	fragPosition = camXRot * camYRot * camZRot * (rotation * scaleMatrix * (vertexPosition - center) + center + cameraPosition);
	gl_Position  = projectionMatrix * viewMatrix * modelMatrix * fragPosition;

	fragTexCoord = vertexTexture;

}