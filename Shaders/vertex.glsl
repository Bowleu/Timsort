#version 460

layout (location = 0) in vec3 position;

uniform float shift;
uniform float shiftup;
uniform float index;

void main() {
	if (position.y == -1.0){
		if (position.x == -0.95){
			gl_Position = vec4(position.x + shift * index, position.y, position.z, 1.0);
		} 
		else {
			gl_Position = vec4(position.x + shift * (index + 1), position.y, position.z, 1.0);
		}
	} 
	else {
		if (position.x == -0.95){
			gl_Position = vec4(position.x + shift * index, position.y + shiftup, position.z, 1.0);
		} 
		else {
			gl_Position = vec4(position.x + shift * (index + 1), position.y + shiftup, position.z, 1.0);
		}
	}
}