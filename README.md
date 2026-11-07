# Juego: Avion esquiva-rocas con nitro

Un avion que se mueve solo de lado a lado
mientras caen rocas. Hay que esquivarlas; con **Shift + tecla de movimiento** se activa el **nitro**.

## Controles
| Tecla | Accion |
|---|---|
| A / D o flechas | Mover el avion |
| Shift + A / D | Nitro (mas velocidad) |
| R | Reiniciar (cuando termina el juego) |
| ESC | Salir |

## Reparto de partes
Cada integrante trabaja **solo en su archivo** de `src/`. Asi casi no hay conflictos al unir el trabajo.

| Parte | Archivo | Responsable | Que hace |
|---|---|---|---|
| 1 | `src/Parte1_Avion.h` | Gary Añanga | Dibujo del avion con triangulos |
| 2 | `src/Parte2_Movimiento.h` | Alejandra Galvez | Movimiento lateral con teclado y limites |
| 3 | `src/Parte3_Nitro.h` | Jadhe Sotelo | Nitro con Shift, llama y lineas de velocidad |
| 4 | `src/Parte4_Rocas.h` | Miguel Clavo | Rocas: aparicion, caida y puntaje |
| 5 | `src/Parte5_Colisiones.h` | Alexander Gabino | Choques, vidas y corazones |
| 6 | `src/Parte6_Fondo.h` | Jhon Velasquez | Fondo, titulo con puntaje, game over y reinicio |

**Parte comun** (no se edita sin avisar al grupo): `main.cpp`, `src/Juego.h`, `src/Shader.*`, `res/Shader/*`.

Cada archivo `ParteN_...h` tiene arriba las instrucciones de lo que debe hacer su responsable.
Las funciones ya estan declaradas (vacias) para que el proyecto **compile desde el inicio**.

## Orden recomendado para unir
1 Avion, 2 Movimiento, 3 Nitro, 4 Rocas, 5 Colisiones, 6 Fondo.
Cuando todos esten unidos, comparar con el codigo completo de referencia.

## Como probar nuestros avances
- **Parte 1:** al terminar `crearAvion` / `dibujarAvion` ya debe verse el avion en la parte de abajo.
- **Parte 2:** con la Parte 1 lista, el avion debe moverse con A/D y no salirse de la pantalla.
- **Parte 3:** Shift + A/D debe mover al avion mas rapido y mostrar la llama.
- **Parte 4:** deben caer rocas y el puntaje sube al esquivarlas (se ve en el titulo cuando este la Parte 6).
- **Parte 5:** al chocar se pierde una vida y el avion parpadea.
- **Parte 6:** cielo, nubes, titulo con puntaje y reinicio con R.
