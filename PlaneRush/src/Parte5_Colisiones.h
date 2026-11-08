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
#include <cmath>
#include <algorithm>

static unsigned int VAOVida = 0;
static unsigned int VBOVida = 0;
static int verticesVida = 0;

void crearVidas()
{
    std::vector<float> v;
    Color rojoCorazon = { 0.95f, 0.2f, 0.3f };

    triangulo(v, 0.0f, 0.03f, -0.03f, -0.02f, 0.03f, -0.02f, rojoCorazon);

    verticesVida = (int)(v.size() / 6);
    crearBuffer(v, VAOVida, VBOVida);
}

bool colisionCirculoRectangulo(float cx, float cy, float radio, float rx, float ry, float mitadAncho, float mitadAlto)
{
    float puntoX = std::max(rx - mitadAncho, std::min(cx, rx + mitadAncho));
    float puntoY = std::max(ry - mitadAlto, std::min(cy, ry + mitadAlto));

    float distX = cx - puntoX;
    float distY = cy - puntoY;

    return (distX * distX + distY * distY) <= (radio * radio);
}

void actualizarColisiones()
{
    if (juegoTerminado) return;

    if (tiempoInvulnerable > 0.0f)
    {
        tiempoInvulnerable -= deltaTime;

        int parpadeo = static_cast<int>(tiempoInvulnerable * 10);
        avionVisible = (parpadeo % 2 == 0);
        return;
    }
    else
    {
        avionVisible = true;
    }

    for (int i = (int)rocas.size() - 1; i >= 0; i--)
    {
        if (colisionCirculoRectangulo(rocas[i].x, rocas[i].y, rocas[i].radio, avionX, AVION_Y, AVION_MEDIO_ANCHO, AVION_MEDIO_ALTO))
        {
            rocas.erase(rocas.begin() + i);

            vidas--;
            tiempoInvulnerable = 1.5f; // Valor directo para evitar conflictos de redefinición

            if (vidas <= 0)
            {
                vidas = 0;
                juegoTerminado = true;
                avionVisible = true;
            }
            break;
        }
    }
}

void dibujarVidas(Shader& shader)
{
    for (int i = 0; i < vidas; i++)
    {
        float posX = -0.9f + (i * 0.08f);
        float posY = 0.9f;
        dibujarObjeto(shader, VAOVida, GL_TRIANGLES, 0, verticesVida, posX, posY, 1.0f, 0.0f);
    }
}