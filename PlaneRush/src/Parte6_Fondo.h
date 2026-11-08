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

// Declaración de los VAO / VBO / contadores gráficos para cielo, nubes y cartel
static unsigned int VAOCielo = 0, VBOCielo = 0;
static int verticesCielo = 0;

static unsigned int VAONubes = 0, VBONubes = 0;
static int verticesNubes = 0;

static unsigned int VAOGameOver = 0, VBOGameOver = 0;
static int verticesGameOver = 0;

static float scrollFondo = 0.0f;
static float velocidad = 0.5f;


void crearFondo()
{
    // - Cielo: un rectángulo que cubra toda la pantalla (-1 a 1) con degradado (rectanguloDegradado).
    //   Azul oscuro arriba, azul claro abajo.
    std::vector<float> vc;
    Color azulOscuro = { 0.10f, 0.20f, 0.35f };
    Color azulClaro = { 0.40f, 0.60f, 0.90f };
    rectanguloDegradado(vc, -1.0f, -1.0f, 1.0f, 1.0f, azulClaro, azulOscuro);
    verticesCielo = static_cast<int>(vc.size() / 6);
    crearBuffer(vc, VAOCielo, VBOCielo);

    // - Nubes: varias nubes (3 círculos cada una) con Y entre -0.85 y 0.85.
    std::vector<float> vn;
    Color blancoCentro = { 0.95f, 0.95f, 0.95f };
    Color blancoBorde = { 0.80f, 0.80f, 0.80f };

    // Nube 1
    circulo(vn, -0.5f, 0.4f, 0.12f, blancoCentro, blancoBorde);
    circulo(vn, -0.4f, 0.45f, 0.15f, blancoCentro, blancoBorde);
    circulo(vn, -0.3f, 0.4f, 0.1f, blancoCentro, blancoBorde);

    // Nube 2
    circulo(vn, 0.4f, -0.2f, 0.14f, blancoCentro, blancoBorde);
    circulo(vn, 0.52f, -0.16f, 0.18f, blancoCentro, blancoBorde);
    circulo(vn, 0.65f, -0.2f, 0.12f, blancoCentro, blancoBorde);

    // Nube 3
    circulo(vn, -0.2f, -0.6f, 0.15f, blancoCentro, blancoBorde);
    circulo(vn, -0.08f, -0.55f, 0.2f, blancoCentro, blancoBorde);
    circulo(vn, 0.05f, -0.6f, 0.13f, blancoCentro, blancoBorde);

    verticesNubes = static_cast<int>(vn.size() / 6);
    crearBuffer(vn, VAONubes, VBONubes);

    // - Cartel de GAME OVER: una franja roja en el centro de la pantalla.
    std::vector<float> vg;
    Color rojoFranja = { 0.85f, 0.15f, 0.15f };
    rectangulo(vg, -1.0f, -0.15f, 1.0f, 0.15f, rojoFranja);
    verticesGameOver = static_cast<int>(vg.size() / 6);
    crearBuffer(vg, VAOGameOver, VBOGameOver);
}

void actualizarFondo()
{
    // Hacer bajar las nubes (scrollFondo += velocidad * deltaTime).
    // Con nitro (factorNitro) deben bajar más rápido.
    if (!juegoTerminado)
    {
        scrollFondo += velocidad * factorNitro * deltaTime;
    }
}

void dibujarFondo(Shader& shader)
{
    // Cielo y nubes. Las nubes se dibujan DOS veces,
    // en y = desplazamiento y en y = desplazamiento + 2, con
    // desplazamiento = -std::fmod(scrollFondo, 2.0f), para que no haya huecos.

    // Dibujar cielo estático
    dibujarObjeto(shader, VAOCielo, GL_TRIANGLES, 0, verticesCielo, 0.0f, 0.0f);

    float desplazamiento = -std::fmod(scrollFondo, 2.0f);

    // Dibujar nubes primera pasada
    dibujarObjeto(shader, VAONubes, GL_TRIANGLES, 0, verticesNubes, 0.0f, desplazamiento);
    // Dibujar nubes segunda pasada (desplazamiento + 2.0f)
    dibujarObjeto(shader, VAONubes, GL_TRIANGLES, 0, verticesNubes, 0.0f, desplazamiento + 2.0f);
}


void dibujarGameOver(Shader& shader)
{
    if (juegoTerminado)
    {
        dibujarObjeto(shader, VAOGameOver, GL_TRIANGLES, 0, verticesGameOver, 0.0f, 0.0f);
    }
}



void actualizarTitulo(GLFWwindow* window)
{
    std::stringstream ss;
    if (juegoTerminado)
    {
        ss << "PlaneRush | GAME OVER - Puntaje Final: " << puntaje << " | Presiona R para reiniciar";
    }
    else
    {
        ss << "PlaneRush | Puntaje: " << puntaje << " | Vidas: " << vidas << " | Nitro: " << (nitroActivo ? "ACTIVO" : "OFF");
    }
    glfwSetWindowTitle(window, ss.str().c_str());
}

void reiniciarJuego()
{
    // Dejar todas las variables compartidas como al inicio
    puntaje = 0;
    vidas = VIDAS_INICIALES;
    juegoTerminado = false;
    scrollFondo = 0.0f;
    tiempoJuego = 0.0f;
    tiempoSpawn = 0.0f;
    rocas.clear();
    tiempoInvulnerable = 0.0f;
    avionVisible = true;
    avionX = 0.0f;
}


void revisarReinicio(GLFWwindow* window)
{
    if (juegoTerminado && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        reiniciarJuego();
    }
}
