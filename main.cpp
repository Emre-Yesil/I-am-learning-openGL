//------------------------------
//at least it is work
//------------------------------
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include<iostream>
#include"shader.h"

const int win_width(800);
const int win_height(600);

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(win_width, win_height, "window", NULL, NULL);
	if (window == NULL)
		std::cerr << "failed to make window" << std::endl;
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //initailize the glad to glfw
	{
		std::cerr << "failed to call glad" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	float verticesTri[] = {
		//possitions         colors             cordinates
		-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 0.13f,// left
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f,   0.9f, 0.193f,// right
		 0.0f,  0.5f, 0.0f,  0.0f,1.0f,1.0f,     0.45f, 0.9f // top
	};

	float vertices[] = {
		// positions			//color					// texture coords
		 1.0f,  1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f, // top right
		 1.0f, -1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f  // top left
	};

	unsigned int indices[] = {
	   0, 1, 3,  // first triangle
	   1, 2, 3   // second triangle
	};


	//object
	//-----------------------------
	unsigned int VAOs[2], VBOs[2];
	glGenBuffers(1, &VBOs[0]);
	glGenVertexArrays(1, &VAOs[0]);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTri), verticesTri, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//object2
	unsigned int EBO;
	glGenBuffers(1, &VBOs[1]);
	glGenVertexArrays(1, &VAOs[1]);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//textures
	//----------------------
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//repeat type
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("pyramid.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "failed to load texture" << std::endl;
		return -1;
	}
	stbi_image_free(data);

	//texture2
	//------------------------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	//repeat type
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	 data = stbi_load("flatEarth.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "failed to load texture" << std::endl;
		return -1;
	}
	stbi_image_free(data);

	glBindVertexArray(0);

	shader myShader("vShader.vert", "fShader.frag");
	shader myShader2("vShader.vert", "fShader2.frag");


	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		
		myShader2.use();
		glUniform1i(glGetUniformLocation(myShader.ID, "texture1"), 1); // Texture unit 1
		glBindVertexArray(VAOs[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		myShader.use();
		glUniform1i(glGetUniformLocation(myShader.ID, "texture1"), 0); // Texture unit 0
		glUniform1i(glGetUniformLocation(myShader.ID, "texture2"), 1); // Texture unit 1
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAOs[0]);
	glDeleteBuffers(1, &VBOs[0]);
	glDeleteVertexArrays(1, &VAOs[1]);
	glDeleteBuffers(1, &VBOs[1]);
	myShader.deletePrograme();
	myShader2.deletePrograme();

	glfwTerminate();
	return 0;
}
void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}