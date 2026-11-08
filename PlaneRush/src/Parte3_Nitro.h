// ============================================================
//  PARTE 3 - NITRO (Shift + tecla de movimiento)
//  Responsable:
//
//  QUE HACER
//   1. actualizarNitro(window, direccion): el nitro se activa cuando se
//      mantiene SHIFT mas una tecla de movimiento (direccion distinta de 0).
//        nitroActivo = shift && direccion != 0;
//        factorNitro = nitroActivo ? FACTOR_NITRO : 1.0f;
//   2. Efecto visual (solo cuando nitroActivo es true):
//        - Una llama detras del avion (triangulos naranja y amarillo).
//        - Lineas de velocidad verticales que bajan rapido (GL_LINES).
//   3. crearNitro(): arma las formas.  dibujarNitro(): las dibuja.
// ============================================================
#pragma once

#include "Juego.h"

//  VAO / VBO y contadores de vertices

unsigned int VAOLlama, VBOLlama;
int verticesLlama = 0;

unsigned int VAOLineasNitro, VBOLineasNitro;
int verticesLineasNitro = 0;

const int CANTIDAD_LINEAS_NITRO = 28;
const float VELOCIDAD_LINEAS_NITRO = 3.5f;   // unidades por segundo hacia abajo

void crearNitro()
{
	//  LLAMA 

	{
		std::vector<float> v;

		Color rojoNaranja = { 1.00f, 0.35f, 0.05f };
		Color naranja = { 1.00f, 0.60f, 0.10f };
		Color amarillo = { 1.00f, 0.95f, 0.30f };

		// Llama exterior (naranja), larga
		triangulo(v, -0.035f, -0.09f, 0.035f, -0.09f, 0.0f, -0.32f, naranja);

		// Llama media (rojo-naranja) en los costados, mas corta
		triangulo(v, -0.060f, -0.10f, -0.020f, -0.10f, -0.040f, -0.22f, rojoNaranja);
		triangulo(v, 0.020f, -0.10f, 0.060f, -0.10f, 0.040f, -0.22f, rojoNaranja);

		// Llama interior (amarilla)
		triangulo(v, -0.018f, -0.09f, 0.018f, -0.09f, 0.0f, -0.23f, amarillo);

		verticesLlama = (int)(v.size() / 6);
		crearBuffer(v, VAOLlama, VBOLlama);
	}

	//  LINEAS DE VELOCIDAD
	{
		std::vector<float> v;

		Color tenue = { 0.25f, 0.30f, 0.40f };
		Color claro = { 0.85f, 0.95f, 1.00f };

		for (int i = 0; i < CANTIDAD_LINEAS_NITRO; i++)
		{
			float x = aleatorio(-0.98f, 0.98f);
			float largo = aleatorio(0.15f, 0.30f);
			float yInicio = aleatorio(-1.0f, 1.0f - largo);

			vertice(v, x, yInicio + largo, tenue);   // extremo de arriba
			vertice(v, x, yInicio, claro);           // extremo de abajo
		}

		verticesLineasNitro = (int)(v.size() / 6);
		crearBuffer(v, VAOLineasNitro, VBOLineasNitro);
	}
}

// Se llama desde la Parte 2 en cada cuadro. 'direccion' es -1, 0 o 1.
void actualizarNitro(GLFWwindow* window, int direccion)
{
	bool shift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;

	nitroActivo = shift && direccion != 0;
	factorNitro = nitroActivo ? FACTOR_NITRO : 1.0f;
}

void dibujarNitro(Shader& shader)
{
	if (!nitroActivo)
		return;

	float t = (float)glfwGetTime();

	// Lineas de velocidad (bajan rapido y se repiten al salir)
	float k = std::fmod(t * VELOCIDAD_LINEAS_NITRO, 2.0f);

	glLineWidth(2.0f);   // en perfil core algunos drivers solo aceptan 1.0
	dibujarObjeto(shader, VAOLineasNitro, GL_LINES, 0, verticesLineasNitro, 0.0f, -k);
	dibujarObjeto(shader, VAOLineasNitro, GL_LINES, 0, verticesLineasNitro, 0.0f, 2.0f - k);

	// Llama detras del avion (parpadea cambiando el tamano)
	float parpadeo = 1.0f + 0.10f * std::sin(t * 50.0f);
	dibujarObjeto(shader, VAOLlama, GL_TRIANGLES, 0, verticesLlama, avionX, AVION_Y, parpadeo);
}
