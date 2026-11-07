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
unsigned int VAORoca, VBORoca;

int verticesRoca = 0;

const float INTERVALO_INICIAL = 1.0f;
const float INTERVALO_MINIMO = 0.35f;     
const float REDUCCION_INTERVALO = 0.015f;
const float AUMENTO_VELOCIDAD = 0.01f;
const float VELOCIDAD_EXTRA_MAX = 0.6f;

float intervaloRocas()
{
	return std::max(INTERVALO_MINIMO, INTERVALO_INICIAL - tiempoJuego * REDUCCION_INTERVALO);
}

float velocidadExtra()
{
	return std::min(VELOCIDAD_EXTRA_MAX, tiempoJuego * AUMENTO_VELOCIDAD);
}

void crearRocas()
{
	std::vector<float> v;

	Color centro = { 0.62f, 0.55f, 0.48f };
	Color borde = { 0.36f, 0.31f, 0.27f };

	const int LADOS = 9;
	const float radios[LADOS] = { 1.00f, 0.82f, 0.95f, 0.78f, 1.00f, 0.86f, 0.93f, 0.80f, 0.97f };

	vertice(v, 0.0f, 0.0f, centro);
	for (int i = 0; i <= LADOS; i++)
	{
		int k = i % LADOS;
		float a = k * 2.0f * PI / LADOS;
		vertice(v, std::cos(a) * radios[k], std::sin(a) * radios[k], borde);
	}

	verticesRoca = (int)(v.size() / 6);
	crearBuffer(v, VAORoca, VBORoca);
	
}

void generarRoca()
{
	Roca r;
	r.radio = aleatorio(0.05f, 0.10f);
	r.x = aleatorio(-0.9f, 0.9f);
	r.y = 1.0f + r.radio;
	r.velocidad = aleatorio(0.5f, 0.9f) + velocidadExtra();
	r.angulo = aleatorio(0.0f, 2.0f * PI);
	r.giro = aleatorio(-2.0f, 2.0f);

	rocas.push_back(r);
	
}

void actualizarRocas()
{
	tiempoJuego += deltaTime;
	tiempoSpawn += deltaTime;

	if (tiempoSpawn >= intervaloRocas())
	{
		generarRoca();
		tiempoSpawn = 0.0f;
	}

	for (int i = (int)rocas.size() - 1; i >= 0; i--)
	{
		rocas[i].y -= rocas[i].velocidad * deltaTime;
		rocas[i].angulo += rocas[i].giro * deltaTime;

		if (rocas[i].y < -1.0f - rocas[i].radio)
		{
			rocas.erase(rocas.begin() + i);
			puntaje++;
		}
	}
}

void dibujarRocas(Shader& shader)
{
	for (const Roca& r : rocas)
	{
		dibujarObjeto(shader, VAORoca, GL_TRIANGLE_FAN, 0, verticesRoca, r.x, r.y, r.radio, r.angulo);
	}
}
