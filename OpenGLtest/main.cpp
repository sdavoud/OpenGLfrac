#include <iostream>
#include <cmath>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <math.h>
// GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include "Shader.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void create_quad(GLuint *quad_vao, int n);
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "SherwinGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);


	Shader fractshad("C:\\Users\\sdavoud\\Documents\\Visual Studio 2015\\Projects\\OpenGLtest\\OpenGLtest\\vertex.vs", "C:\\Users\\sdavoud\\Documents\\Visual Studio 2015\\Projects\\OpenGLtest\\OpenGLtest\\fragment.frag");
	glEnable(GL_DEPTH_TEST);
	
	GLfloat vertices[] = {
		-0.9f, -0.9f, -0.9f,  0.0f, 0.0f,
		0.9f, -0.9f, -0.9f,  1.0f, 0.0f,
		0.9f,  0.9f, -0.9f,  1.0f, 1.0f,
		0.9f,  0.9f, -0.9f,  1.0f, 1.0f,
		-0.9f,  0.9f, -0.9f,  0.0f, 1.0f,
		-0.9f, -0.9f, -0.9f,  0.0f, 0.0f,

		-0.9f, -0.9f,  0.9f,  0.0f, 0.0f,
		0.9f, -0.9f,  0.9f,  1.0f, 0.0f,
		0.9f,  0.9f,  0.9f,  1.0f, 1.0f,
		0.9f,  0.9f,  0.9f,  1.0f, 1.0f,
		-0.9f,  0.9f,  0.9f,  0.0f, 1.0f,
		-0.9f, -0.9f,  0.9f,  0.0f, 0.0f,

		-0.9f,  0.9f,  0.9f,  1.0f, 0.0f,
		-0.9f,  0.9f, -0.9f,  1.0f, 1.0f,
		-0.9f, -0.9f, -0.9f,  0.0f, 1.0f,
		-0.9f, -0.9f, -0.9f,  0.0f, 1.0f,
		-0.9f, -0.9f,  0.9f,  0.0f, 0.0f,
		-0.9f,  0.9f,  0.9f,  1.0f, 0.0f,

		0.9f,  0.9f,  0.9f,  1.0f, 0.0f,
		0.9f,  0.9f, -0.9f,  1.0f, 1.0f,
		0.9f, -0.9f, -0.9f,  0.0f, 1.0f,
		0.9f, -0.9f, -0.9f,  0.0f, 1.0f,
		0.9f, -0.9f,  0.9f,  0.0f, 0.0f,
		0.9f,  0.9f,  0.9f,  1.0f, 0.0f,

		-0.9f, -0.9f, -0.9f,  0.0f, 1.0f,
		0.9f, -0.9f, -0.9f,  1.0f, 1.0f,
		0.9f, -0.9f,  0.9f,  1.0f, 0.0f,
		0.9f, -0.9f,  0.9f,  1.0f, 0.0f,
		-0.9f, -0.9f,  0.9f,  0.0f, 0.0f,
		-0.9f, -0.9f, -0.9f,  0.0f, 1.0f,

		-0.9f,  0.9f, -0.9f,  0.0f, 1.0f,
		0.9f,  0.9f, -0.9f,  1.0f, 1.0f,
		0.9f,  0.9f,  0.9f,  1.0f, 0.0f,
		0.9f,  0.9f,  0.9f,  1.0f, 0.0f,
		-0.9f,  0.9f,  0.9f,  0.0f, 0.0f,
		-0.9f,  0.9f, -0.9f,  0.0f, 1.0f
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	//GLfloat vertices[] = {
	//	0.9f,  0.9f, 0.0f,  // Top Right
	//	0.9f, -0.9f, 0.0f,  // Bottom Right
	//	-0.9f, -0.9f, 0.0f,  // Bottom Left
	//	-0.9f,  0.9f, 0.0f   // Top Left 
	//};
	//GLuint indices[] = {  
	//	0, 1, 3,  
	//	1, 2, 3   
	//};
	//GLuint VBO, VAO, EBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); 

	//glBindVertexArray(0);

						  // Game loop
	//GLuint quad_vao;
	//glGenVertexArrays(1, &quad_vao);
	//glBindVertexArray(quad_vao);
	////// Position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//// Color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);

	//glBindVertexArray(0); // Unbind VAO
	//create_quad(&quad_vao, 6);
	// World space positions of our cubes
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		fractshad.Use();
		glBindVertexArray(VAO);
		//glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		//model = glm::rotate(model, 55.1f*0.01f*(GLfloat)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		GLint modelLoc = glGetUniformLocation(fractshad.Program, "model");
		GLint viewLoc = glGetUniformLocation(fractshad.Program, "view");
		GLint projLoc = glGetUniformLocation(fractshad.Program, "projection");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//glDrawArrays(GL_TRIANGLES, 0,36);
		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++)
		{
			// Calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			if (i % 3 == 0)  // Every 3rd iteration (including the first) we set the angle using GLFW's time function.
				angle = glfwGetTime() * .01*25.0f;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		glBindVertexArray(0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glfwSwapBuffers(window);
		GLfloat timeValue = glfwGetTime();
		glUniform1f(glGetUniformLocation(fractshad.Program, "sherwintime"), (float)timeValue);
		
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
void create_quad(GLuint *quad_vao, int n)
{
	glm::vec4 *vertices = (glm::vec4 *)malloc(6 * n * n * sizeof(glm::vec4));
	float vert_inc = 2.0 / n;
	int index = 0;
	for (float x = -1.0; x < 1.0; x += vert_inc)
	{
		for (float y = -1.0; y < 1.0; y += vert_inc)
		{
			glm::vec4 v1 = glm::vec4(x, y, 0.0f, 1.0f);
			glm::vec4 v2 = glm::vec4(x, y + vert_inc, 0.0f, 1.0f);
			glm::vec4 v3 = glm::vec4(x + vert_inc, y + vert_inc, 0.0f, 1.0f);

			glm::vec4 v4 = glm::vec4(x, y, 0.0f, 1.0f);
			glm::vec4 v5 = glm::vec4(x + vert_inc, y, 0.0f, 1.0f);
			glm::vec4 v6 = glm::vec4(x + vert_inc, y + vert_inc, 0.0f, 1.0f);

			vertices[index++] = v1;
			vertices[index++] = v2;
			vertices[index++] = v3;

			vertices[index++] = v4;
			vertices[index++] = v5;
			vertices[index++] = v6;
		}
	}
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, quad_vao);
	glBindVertexArray(*quad_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * n * n * sizeof(glm::vec4), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, false, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

