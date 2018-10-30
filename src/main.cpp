#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static unsigned int compileShader(const char* source, unsigned int shaderType) {
	unsigned int shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	return shader;
}

static unsigned int createProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
	
	unsigned int program = glCreateProgram();

	unsigned int vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

  glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
  glLinkProgram(program);
	glValidateProgram(program);

	return program;
}

int main() {
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		return -1;

	float vertices[] = {
		-0.5,  0.5,
		 0.0, -0.5,
		 0.5,  0.5,
		 
		0.8, 0.8,
		0.5, 0.6,
		0.6, 0.5,

		-0.8, 0.8,
		-0.5, 0.6,
		-0.6, 0.5,

		-0.08, -0.55,
		0.08, -0.55,
		0, -0.9,
		
		-0.08,  0.9,
		 0.0,  0.55,
		 0.08,  0.9,
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int program = createProgram(R"(
		#version 330 core
		layout(location = 0) in vec4 position;
		void main() {
      gl_Position = position;
		}
	)", R"(
		#version 330 core
		layout(location = 0) out vec4 color;
		void main() {
      color = vec4(0.1, 0.2, 0.3, 1.0);
		}
	)");
	glUseProgram(program);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float));

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}