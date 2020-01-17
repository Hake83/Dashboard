#include "helper.h"
#include "Buffer.h"


int main()
{
	init_log();

	GLFWwindow* window;
	//Initialize glfw
	if (!glfwInit())
	{
		std::cout << "There was an error initializing GLFW\n";
		//TODO: add error reporting feature
		return -1;
	}

	//Window hints
	glfwWindowHint(GLFW_SAMPLES, 4);


	//Create a window
	window = glfwCreateWindow(640, 480, "Main Screen", NULL, NULL);
	if (!window)
	{
		std::cout << "There was an error initializing the window\n";
		//TODO: add error reporting feature
		glfwTerminate();
		return -1;
	}

	//Make the window's context current, must have valid rendering context to initialize GLEW
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	GLenum GLerr = glewInit();
	if (GLEW_OK != GLerr)
	{
		gl_log("GLEW failed to initialize, Error: ", glewGetErrorString(GLerr));
	}

	//Output a few things to the log file, I can probably clean this up some
	gl_log("Status: Using Glew ", glewGetString(GLEW_VERSION));
	gl_log("Renderer: ", glGetString(GL_RENDERER));
	gl_log("OpenGL version supported: ", glGetString(GL_VERSION));

	//triangle indices for a square, including texture coords
	float positions[] = {
		-0.15f, -0.15f,
		 0.15F, -0.15F,
		 0.15f,  0.75f,
		-0.15f,  0.75f
	};

	float tex_coords[] = {
		 0.0f, 0.0f,
		 1.0f, 0.0f,
		 1.0f, 1.0f,
		-1.0f, 1.0f
	}


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Create the vertex buffer
	VertexBuffer vb(positions, 2 * 2 * sizeof(float));
													

	/*************************************************************
	|
	|
	|				Render Loop
	|
	|
	**************************************************************/

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		glfwSwapBuffers(window);

		glfwPollEvents();
		processInput(window);
	}
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}