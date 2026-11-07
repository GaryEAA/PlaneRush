// ============================================================
//  PARTE 2 - MOVIMIENTO LATERAL DEL AVION
//  Responsable:
//
//  QUE HACER
//   El avion solo se mueve de lado a lado con A / D o con las flechas
//   izquierda / derecha. Nunca se mueve hacia arriba o abajo.
//
//  En actualizarMovimiento(window) hay que:
//   1. Leer las teclas y calcular 'direccion': -1 izquierda, 0 quieto, 1 derecha.
//   2. Guardarla en direccionAvion.
//   3. Llamar a actualizarNitro(window, direccion)   <- la escribe la Parte 3 asi que no hay que implementarla, solo llamarla
//   4. Mover:  avionX += direccion * VELOCIDAD_AVION * factorNitro * deltaTime;
//   5. Limitar avionX entre -LIMITE_X y +LIMITE_X.
// ============================================================
#pragma once

#include "Juego.h"

void actualizarMovimiento(GLFWwindow* window)
{
	// Código de la parte 2: movimiento lateral del avion

	// Mientras no esté terminada la Parte 3 usa esta linea para evitar errores al compilar:
	actualizarNitro(window, 0);
}
