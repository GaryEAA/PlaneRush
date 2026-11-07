#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#include "Shader.h"

// ------------------------------------------------------------
//  CONSTANTES
// ------------------------------------------------------------
const int   VENTANA_ANCHO = 800;     // ventana cuadrada
const int   VENTANA_ALTO = 800;
const float PI = 3.1415926f;

// Avion
const float AVION_Y = -0.75f;              // altura fija del avion (solo se mueve de lado a lado)
const float LIMITE_X = 0.86f;              // el avion no puede pasar de -LIMITE_X a +LIMITE_X
const float VELOCIDAD_AVION = 1.2f;        // unidades por segundo
const float FACTOR_NITRO = 2.2f;           // para el nitro la velocidad se deberá multiplicar por este factor
const float AVION_MEDIO_ANCHO = 0.10f;     // caja de colision del avion (mitad del ancho)
const float AVION_MEDIO_ALTO = 0.11f;      // caja de colision del avion (mitad del alto)

// Juego
const int   VIDAS_INICIALES = 3;
const float TIEMPO_INVULNERABLE = 1.5f;    // segundos sin recibir danio despues de un golpe

// ------------------------------------------------------------
//  TIPOS
// ------------------------------------------------------------
struct Color
{
	float r, g, b;
};

struct Roca
{
	float x, y;          // posicion del centro
	float radio;         // tamanio
	float velocidad;     // unidades por segundo hacia abajo
	float angulo;        // giro actual (en radianes)
	float giro;          // velocidad de giro (en radianes por segundo)
};

// ------------------------------------------------------------
//  VARIABLES COMPARTIDAS (las pueden cambiar segun se avance cada parte)
// ------------------------------------------------------------
float deltaTime = 0.0f;          // segundos que duro el ultimo cuadro
float ultimoCuadro = 0.0f;

float avionX = 0.0f;             // posicion horizontal del avion
int   direccionAvion = 0;        // -1 izquierda, 0 quieto, 1 derecha
bool  nitroActivo = false;       // true si Shift + tecla de movimiento
float factorNitro = 1.0f;        // 1.0 normal, FACTOR_NITRO con nitro

std::vector<Roca> rocas;         // rocas que estan cayendo
float tiempoSpawn = 0.0f;        // cronometro para crear la siguiente roca
float tiempoJuego = 0.0f;        // segundos jugados

int   puntaje = 0;               // rocas esquivadas
int   vidas = VIDAS_INICIALES;   // 
bool  juegoTerminado = false;    // 
float tiempoInvulnerable = 0.0f; // 
bool  avionVisible = true;       // false = el avion parpadea

// ------------------------------------------------------------
//  FUNCIONES DE CADA PARTE (cada una se escribe en su archivo)
// ------------------------------------------------------------
// Parte 1 - Avion
void crearAvion();
void dibujarAvion(Shader& shader);
// Parte 2 - Movimiento lateral
void actualizarMovimiento(GLFWwindow* window);
// Parte 3 - Nitro
void crearNitro();
void actualizarNitro(GLFWwindow* window, int direccion);
void dibujarNitro(Shader& shader);
// Parte 4 - Rocas
void crearRocas();
void actualizarRocas();
void dibujarRocas(Shader& shader);
// Parte 5 - Colisiones y vidas
void crearVidas();
void actualizarColisiones();
void dibujarVidas(Shader& shader);
// Parte 6 - Fondo, puntaje y reinicio
void crearFondo();
void actualizarFondo();
void dibujarFondo(Shader& shader);
void dibujarGameOver(Shader& shader);
void actualizarTitulo(GLFWwindow* window);
void revisarReinicio(GLFWwindow* window);
void reiniciarJuego();

// ------------------------------------------------------------
//  FUNCIONES DE AYUDA PARA ARMAR LAS FORMAS
//  Cada vertice son 6 numeros: x, y, z, r, g, b
// ------------------------------------------------------------
void vertice(std::vector<float>& v, float x, float y, Color c)
{
	v.push_back(x);
	v.push_back(y);
	v.push_back(0.0f);
	v.push_back(c.r);
	v.push_back(c.g);
	v.push_back(c.b);
}

// Triangulo de un solo color
void triangulo(std::vector<float>& v, float x1, float y1, float x2, float y2, float x3, float y3, Color c)
{
	vertice(v, x1, y1, c);
	vertice(v, x2, y2, c);
	vertice(v, x3, y3, c);
}

// Cuadrilatero (4 puntos en orden) = 2 triangulos
void cuadrilatero(std::vector<float>& v, float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4, Color c)
{
	triangulo(v, x1, y1, x2, y2, x3, y3, c);
	triangulo(v, x1, y1, x3, y3, x4, y4, c);
}

// Rectangulo: esquina inferior izquierda (x1,y1) y superior derecha (x2,y2)
void rectangulo(std::vector<float>& v, float x1, float y1, float x2, float y2, Color c)
{
	cuadrilatero(v, x1, y1, x2, y1, x2, y2, x1, y2, c);
}

// Rectangulo con degradado
void rectanguloDegradado(std::vector<float>& v, float x1, float y1, float x2, float y2, Color abajo, Color arriba)
{
	vertice(v, x1, y1, abajo);
	vertice(v, x2, y1, abajo);
	vertice(v, x2, y2, arriba);

	vertice(v, x1, y1, abajo);
	vertice(v, x1, y2, arriba);
	vertice(v, x2, y2, arriba);
}

// Circulo hecho de triangulos
void circulo(std::vector<float>& v, float cx, float cy, float radio, Color centro, Color borde)
{
	const int SEGMENTOS = 24;
	for (int i = 0; i < SEGMENTOS; i++)
	{
		float a1 = i * 2.0f * PI / SEGMENTOS;
		float a2 = (i + 1) * 2.0f * PI / SEGMENTOS;

		vertice(v, cx, cy, centro);
		vertice(v, cx + std::cos(a1) * radio, cy + std::sin(a1) * radio, borde);
		vertice(v, cx + std::cos(a2) * radio, cy + std::sin(a2) * radio, borde);
	}
}

// ------------------------------------------------------------
//  BUFFERS Y DIBUJO
// ------------------------------------------------------------

void crearBuffer(const std::vector<float>& datos, unsigned int& VAO, unsigned int& VBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, datos.size() * sizeof(float), datos.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void dibujarObjeto(Shader& shader, unsigned int VAO, GLenum modo, int primero, int cantidad,
	float x, float y, float escala = 1.0f, float angulo = 0.0f)
{
	shader.setFloat("xOffset", x);
	shader.setFloat("yOffset", y);
	shader.setFloat("escala", escala);
	shader.setFloat("angulo", angulo);

	glBindVertexArray(VAO);
	glDrawArrays(modo, primero, cantidad);
}

float aleatorio(float minimo, float maximo)
{
	return minimo + (maximo - minimo) * ((float)std::rand() / (float)RAND_MAX);
}
