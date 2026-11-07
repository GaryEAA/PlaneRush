// ============================================================
//  PARTE 5 - COLISIONES Y VIDAS
//  Responsable: 
//
//  QUE HACER
//   1. colisionCirculoRectangulo(...): decide si una roca (circulo) toca al
//      avion (rectangulo). Truco: buscar el punto del rectangulo mas cercano
//      al centro del circulo y ver si esta a menos de 'radio' de distancia
//   2. actualizarColisiones():
//        - Si tiempoInvulnerable > 0: restarle deltaTime, hacer parpadear al
//          avion (avionVisible true/false) y NO revisar choques
//        - Si no: revisar cada roca contra el avion
//            (avionX, AVION_Y, AVION_MEDIO_ANCHO, AVION_MEDIO_ALTO)
//          Si choca: borrar esa roca, vidas--, tiempoInvulnerable = TIEMPO_INVULNERABLE.
//          Si vidas llega a 0: juegoTerminado = true (y avionVisible = true)
//   3. crearVidas() / dibujarVidas(): dibujar un corazon (u otra figura) por cada
//      vida restante, arriba a la izquierda
// ============================================================
#pragma once

#include "Juego.h"

// Declaracion de VAOVida, VBOVida y verticesVida

void crearVidas()
{

}

bool colisionCirculoRectangulo(float cx, float cy, float radio,
	float rx, float ry, float mitadAncho, float mitadAlto)
{

	return false;
}

void actualizarColisiones()
{

}

void dibujarVidas(Shader& shader)
{

}
