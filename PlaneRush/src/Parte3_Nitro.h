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

// Aqui primero declarar sus VAO / VBO y contadores de vertices

void crearNitro()
{
	// Armar la llama y las lineas de velocidad con crearBuffer(...)
}

// Esta función se estará llamando desde la Parte 2 en cada cuadro. 'direccion' es -1, 0 o 1.
void actualizarNitro(GLFWwindow* window, int direccion)
{
	// Calcular nitroActivo y el factorNitro
}

void dibujarNitro(Shader& shader)
{
	// if (!nitroActivo) return;  y luego dibujar lineas y llama
}
