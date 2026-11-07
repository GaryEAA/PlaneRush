// ============================================================
//  PARTE 6 - FONDO, PUNTAJE Y REINICIO
//  Responsable: 
//
//  QUE HACER
//   1. crearFondo():
//        - Cielo: un rectangulo que cubra toda la pantalla (-1 a 1) con degradado
//          (rectanguloDegradado). Azul oscuro arriba, azul claro abajo.
//        - Nubes: varias nubes (3 circulos cada una) con y entre -0.85 y 0.85.
//        - Cartel de GAME OVER: una franja roja en el centro de la pantalla.
//   2. actualizarFondo(): hacer bajar las nubes (scrollFondo += velocidad * deltaTime).
//      Con nitro (factorNitro) deben bajar mas rapido.
//   3. dibujarFondo(): cielo y nubes. Las nubes se dibujan DOS veces,
//      en y = desplazamiento y en y = desplazamiento + 2, con
//      desplazamiento = -std::fmod(scrollFondo, 2.0f), para que no haya huecos.
//   4. dibujarGameOver(): dibuja la franja (se llama solo si juegoTerminado).
//   5. actualizarTitulo(window): mostrar en el titulo de la ventana el puntaje,
//      las vidas y si hay nitro (glfwSetWindowTitle). En game over: mensaje con
//      el puntaje final y "Presiona R para reiniciar".
//   6. reiniciarJuego(): dejar todas las variables compartidas como al inicio
//   7. revisarReinicio(window): si juegoTerminado y se presiona R -> reiniciarJuego().
// ============================================================
#pragma once

#include <string>
#include <cstdio>
#include "Juego.h"

// Declaracion de los VAO / VBO / contadores de cielo, nubes y cartel

void crearFondo()
{

}

void actualizarFondo()
{

}

void dibujarFondo(Shader& shader)
{

}

void dibujarGameOver(Shader& shader)
{

}

void actualizarTitulo(GLFWwindow* window)
{

}

void reiniciarJuego()
{
	// dejar todas las variables compartidas como al inicio
}

void revisarReinicio(GLFWwindow* window)
{

}
