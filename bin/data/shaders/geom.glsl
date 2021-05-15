/***********************************************
 Geometry shader to convert lines into triangle strips
 Memo Akten
 www.memo.tv

************************************************/

#version 120
#extension GL_EXT_geometry_shader4 : enable

uniform float thickness;

void main() {
	vec3 p0 = gl_PositionIn[0].xyz;
	vec3 p1 = gl_PositionIn[1].xyz;
	
	vec3 up = vec3(0, 0, 1);	// arbitrary up vector
	
	vec3 dir = normalize(p1 - p0);			// normalized direction vector from p0 to p1
	vec3 right = normalize(cross(dir, up))*20;	// right vector
	
	gl_Position = gl_ModelViewProjectionMatrix * vec4(p0 - right, 1.0);
	gl_FrontColor = vec4(1.0, 0.0, 0.0, 1.0);
	EmitVertex();
	
	gl_Position = gl_ModelViewProjectionMatrix * vec4(p0 + right, 1.0);
	gl_FrontColor = vec4(0.0, 1.0, 0.0, 1.0);
	EmitVertex();
	
	gl_Position = gl_ModelViewProjectionMatrix * vec4(p1 - right, 1.0);
	gl_FrontColor = vec4(0.0, 0.0, 1.0, 1.0);
	EmitVertex();

	gl_Position = gl_ModelViewProjectionMatrix * vec4(p1 + right, 1.0);
	gl_FrontColor = vec4(0.0, 1.0, 1.0, 1.0);
	EmitVertex();

}