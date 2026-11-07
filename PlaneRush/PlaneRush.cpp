// ============================================================
//  JUEGO: AVION ESQUIVA-ROCAS CON NITRO
//  PARTE COMUN DEL GRUPO: ventana, shader y bucle principal
// ============================================================
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <ctime>

#include "src/Shader.h"
#include "src/Juego.h"
#include "src/Parte1_Avion.h"
#include "src/Parte2_Movimiento.h"
#include "src/Parte3_Nitro.h"
#include "src/Parte4_Rocas.h"
#include "src/Parte5_Colisiones.h"
#include "src/Parte6_Fondo.h"

void responsive(GLFWwindow* window, int width, int height);
void userInput(GLFWwindow* window);

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(VENTANA_ANCHO, VENTANA_ALTO, "PlaneRush", NULL, NULL);

	if (!window)
	{
		std::cout << "Error en la inicializacion de la ventana\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, responsive);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error en la inicializacion del GLEW\n";
		glfwTerminate();
		return -1;
	}

	std::srand((unsigned int)std::time(NULL));

	Shader miShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

	// Cada integrante prepara sus formas (VAO + VBO)
	crearAvion();      // Parte 1
	crearNitro();      // Parte 3
	crearRocas();      // Parte 4
	crearVidas();      // Parte 5
	crearFondo();      // Parte 6

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - ultimoCuadro;
		ultimoCuadro = currentFrame;
		if (deltaTime > 0.1f)
			deltaTime = 0.1f;

		userInput(window);
		revisarReinicio(window);

		// ---- Actualizar el juego ----
		if (!juegoTerminado)
		{
			actualizarMovimiento(window);
			actualizarRocas();
			actualizarColisiones();
			actualizarFondo();
		}

		// ---- Dibujar ----
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		miShader.use();

		dibujarFondo(miShader);
		dibujarRocas(miShader);
		dibujarNitro(miShader);
		dibujarAvion(miShader);
		dibujarVidas(miShader);

		if (juegoTerminado)
			dibujarGameOver(miShader);

		actualizarTitulo(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void responsive(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
