#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

static unsigned int compileShader(const std::string& source, unsigned int shaderType) {
	unsigned int shader = glCreateShader(shaderType);
	const char* src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	return shader;
}

static unsigned int createProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
	
	unsigned int program = glCreateProgram();

	unsigned int vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

  glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
  glLinkProgram(program);
	glValidateProgram(program);

	return program;
}

int glmain(float* vertices, int n, float* color) {
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

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * n, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	using namespace std::string_literals;
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
      color = vec4()"s
			+ std::to_string(color[0]) + ','
			+ std::to_string(color[1]) + ','
			+ std::to_string(color[2]) + ','
			+ std::to_string(color[3]) + R"();
		}
	)");
	glUseProgram(program);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 2 * n);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}