// ============================================================
//  PARTE 4 - ROCAS (son los obstáculos que aparecen desde arriba de la pantalla y caen)
//  Responsable: 
//
//  QUE HACER
//   1. crearRocas(): armar UNA forma de roca (poligono irregular) centrada en
//      (0,0) con radio 1.0. Se reutiliza para todas las rocas; el tamano
//      real se da con el parametro 'escala' al dibujar.
//        Idea: abanico (GL_TRIANGLE_FAN) con 9 lados y radios distintos.
//   2. generarRoca(): crea una Roca nueva y la agrega con rocas.push_back(r):
//        radio al azar (0.05 a 0.10), x al azar (-0.9 a 0.9),
//        y = 1.0 + radio (justo arriba de la pantalla),
//        velocidad al azar (0.5 a 0.9), giro al azar.
//      Usen aleatorio(minimo, maximo) de Juego.h.
//   3. actualizarRocas():
//        - sumar deltaTime a tiempoJuego y a tiempoSpawn
//        - cuando tiempoSpawn llegue al intervalo, generar una roca y reiniciar el cronometro
//        - bajar cada roca:  y -= velocidad * deltaTime;  y girarla
//        - si sale por abajo (y < -1 - radio): borrarla y hacer puntaje++
//        - dificultad: que aparezcan mas seguido y mas rapido con el tiempo
//   4. dibujarRocas(): dibujar cada roca con dibujarObjeto(..., x, y, radio, angulo)
// ============================================================
#pragma once

#include "Juego.h"

// Aqui declaren VAORoca, VBORoca y verticesRoca

void crearRocas()
{
	
}

void generarRoca()
{
	
}

void actualizarRocas()
{
	
}

void dibujarRocas(Shader& shader)
{
	
}
