#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform float xOffset;   // desplazamiento horizontal
uniform float yOffset;   // desplazamiento vertical
uniform float escala;    // tamano (1.0 = normal)
uniform float angulo;    // giro en radianes (0.0 = sin girar)

void main()
{
	// 1) Girar  2) Escalar  3) Mover a su posicion
	float c = cos(angulo);
	float s = sin(angulo);

	vec2 p = vec2(aPos.x * c - aPos.y * s,
	              aPos.x * s + aPos.y * c) * escala;

	gl_Position = vec4(p.x + xOffset, p.y + yOffset, aPos.z, 1.0);
	vertexColor = aColor;
}
