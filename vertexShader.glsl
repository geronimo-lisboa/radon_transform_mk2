#version 400
layout(location = 5) in vec3 vp;
layout(location = 10) in vec3 vc;
out vec3 outColor;
void main() {
  gl_Position = vec4(vp, 1.0);
  outColor = vc;
 }