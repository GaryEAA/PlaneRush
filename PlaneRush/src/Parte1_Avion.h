// ============================================================
//  PARTE 1 - AVION (dibujo con triangulos)
//  Responsable:
//
//  QUE HACER
//   1. Dibujar el avion con triangulos y rectangulos, CENTRADO en (0, 0),
//      de unos 0.26 de ancho y 0.25 de alto (ver AVION_MEDIO_ANCHO y
//      AVION_MEDIO_ALTO en Juego.h). La punta mira hacia ARRIBA.
//   2. crearAvion(): arma los vertices y los guarda con crearBuffer().
//   3. dibujarAvion(): lo dibuja en la posicion (avionX, AVION_Y).
// ============================================================
#pragma once

#include "Juego.h"

unsigned int VAOAvion, VBOAvion;
int verticesAvion = 0;

void crearAvion()
{
	std::vector<float> v;

	Color gris = { 0.85f, 0.88f, 0.92f };
	Color rojo = { 0.90f, 0.15f, 0.15f };
	Color azul = { 0.20f, 0.40f, 0.90f };
	Color azulOscuro = { 0.10f, 0.25f, 0.65f };
	Color celeste = { 0.55f, 0.85f, 1.00f };

	rectangulo(v, -0.025f, -0.11f, 0.025f, 0.07f, gris);
	triangulo(v, -0.025f, 0.07f, 0.025f, 0.07f, 0.0f, 0.13f, rojo);

	triangulo(v, -0.025f, 0.03f, -0.13f, -0.07f, -0.025f, -0.03f, azul);
	triangulo(v, 0.025f, 0.03f, 0.13f, -0.07f, 0.025f, -0.03f, azul);

	triangulo(v, -0.025f, -0.08f, -0.07f, -0.12f, -0.025f, -0.11f, azulOscuro);
	triangulo(v, 0.025f, -0.08f, 0.07f, -0.12f, 0.025f, -0.11f, azulOscuro);

	rectangulo(v, -0.014f, 0.0f, 0.014f, 0.05f, celeste);

	verticesAvion = (int)(v.size() / 6);
	crearBuffer(v, VAOAvion, VBOAvion);
}

void dibujarAvion(Shader& shader)
{
	if (!avionVisible)
		return;

	dibujarObjeto(shader, VAOAvion, GL_TRIANGLES, 0, verticesAvion, avionX, AVION_Y);
}