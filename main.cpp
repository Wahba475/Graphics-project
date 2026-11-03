#include<iostream>
#include<glad/glad.h> // de lel opengl functions
#include<GLFW/glfw3.h>  // de lel window w el input
#include <cmath> // de lel math functions e7na 3awzenha a4an el sin wel cos lel circle

// el vertex shader: by2ol kol no2ta tro7 fen 3al shasha  doool GLSL LANGUAGE FOR GPU PRORGRAM // GPU PROGRAM IS SHADER 
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform vec2 offset;\n"      
"uniform vec2 scale;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x * scale.x + offset.x,\n"
"                      aPos.y * scale.y + offset.y,\n"
"                      0.0, 1.0);\n"
"}\0";

// el fragment shader: by2ol kol pixel gowa el shakl lono eh (orange)
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec3 color;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(color, 1.0);\n"
"}\0";

GLuint TriangleVAO, RectangleVAO, TriangleVBO, RectangleVBO, CircleVAO, CircleVBO;

GLint offset, scale, colors;

// hn3ml function testahl 3lena bdl mn3ed kol 4ewaya hn3ml wa7d lel rectangle we wa7d lel circle we by5do inputes we bytl3o el shapes . bnendh 3lehom fel while loop


  void DrawingRectangles(float x, float y, float w, float h, float r, float g, float b) { //  (x,y) dol el offsets , (w,h) dool el scaling factors , (r,g,b) dool lel colors

	glBindVertexArray(RectangleVAO);              // bind means select  the rectangle
	glUniform3f(colors, r, g, b);
	glUniform2f(scale, w, h);            
	glUniform2f(offset, x, y);         
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}

  void DrawingCircle(float x, float y, float w, float h, float r, float g, float b) { //  (x,y) dol el offsets , (w,h) dool el scaling factors , (r,g,b) dool lel colors
	  
	  glBindVertexArray(CircleVAO);              // bind means select  the circle 
	  glUniform3f(colors, r, g, b);
	  glUniform2f(scale, w, h);
	  glUniform2f(offset, x, y);
	  glDrawArrays(GL_TRIANGLES, 0, 24);

  }

  void DrawingTriangles(float x, float y, float w, float h, float r, float g, float b) { //  (x,y) dol el offsets , (w,h) dool el scaling factors , (r,g,b) dool lel colors

	  glBindVertexArray(TriangleVAO);              
	  glUniform3f(colors, r, g, b);
	  glUniform2f(scale, w, h);
	  glUniform2f(offset, x, y);
	  glDrawArrays(GL_TRIANGLES, 0, 3);

  }

  void Teta(float x, float y) {
	  DrawingRectangles(x - 0.056f, y - 0.023f, 0.017f, 0.256f, 0.42, 0.26, 0.15);
	  DrawingRectangles(x - 0.006f, y - 0.05f, 0.119f, 0.031f, 0.42, 0.26, 0.15);
	  DrawingRectangles(x,y, 0.073, 0.108, 0.29, 0.17, 0.37);  // Body of teta
	  DrawingCircle(x, y + 0.093f, 0.062, 0.111, 0.96, 0.96, 0.96); // el hijab bt3 teta alah y5leha
	  DrawingCircle(x, y + 0.091f, 0.037, 0.067, 0.88, 0.71, 0.54); // we4 teta (face)
}
  void Mama(float x, float y) {
	  DrawingTriangles(x, y, 0.1f, 0.203f, 0.48, 0.31, 0.63 ); // dress (purple)
	  DrawingCircle(x, y + 0.149f, 0.062f, 0.111f, 0.95, 0.78, 0.29); // head / scarf (yellow)
	  DrawingRectangles(x + 0.073f, y + 0.132f, 0.034f, 0.117f, 0.23, 0.44, 0.82); // slipper
  }
  void Brother(float x, float y) {
	  DrawingRectangles(x, y - 0.096f, 0.058f, 0.069f, 0.14, 0.22, 0.36); // pants
	  DrawingRectangles(x, y, 0.069f, 0.122f, 0.16, 0.62, 0.56); // shirt
	  DrawingCircle(x, y + 0.1f, 0.053f, 0.094f, 0.88, 0.71, 0.54); // rasoo abyad
	  DrawingRectangles(x + 0.072f, y + 0.018f, 0.025f, 0.086f, 0.25, 0.64, 0.30); // spray can  Range(melee weapon)  green
  }

  void Namoosa(float x, float y) {
	  DrawingRectangles(x - 0.064f, y, 0.047f, 0.008f, 0.17, 0.17, 0.17); // stinger
	  DrawingCircle(x, y, 0.081f, 0.05f, 0.17, 0.17, 0.17); // body
	  DrawingCircle(x - 0.007f, y + 0.047f, 0.05f, 0.056f, 0.93, 0.93, 0.93); // head


  }

  void SorSar(float x, float y) {
	  DrawingCircle(x, y, 0.125f, 0.078f, 0.55, 0.17, 0.1); // body
	  DrawingCircle(x - 0.07f, y, 0.034f, 0.061f, 0.35, 0.12, 0.06); // head

  }
  void Cat(float x, float y) {
	  DrawingRectangles(x + 0.07f, y + 0.047f, 0.016f, 0.111f, 0.85f, 0.47f, 0.12f);   // tail (dark orange)
	  DrawingCircle(x, y, 0.141f, 0.117f, 0.91f, 0.54f, 0.17f);                         // body (orange)
	  DrawingTriangles(x - 0.11f, y + 0.12f, 0.028f, 0.05f, 0.91f, 0.54f, 0.17f);       // left ear
	  DrawingTriangles(x - 0.07f, y + 0.12f, 0.028f, 0.05f, 0.91f, 0.54f, 0.17f);       // right ear
	  DrawingCircle(x - 0.091f, y + 0.041f, 0.069f, 0.122f, 0.94f, 0.60f, 0.24f);       // head (light orange)
  }












int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);


	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Shib-Shib Defense", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 1280, 720);

	// el 3 no2at bto3 el triangle: (x, y, z)
	GLfloat TriangleVertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	GLfloat RectangleVertices[] =  // hena da 2 trinagles a4an n3ml rectangle el mfrod 6 vertices bs fe 2 points by3mlo overlapping 3ala b3d
	{
		-0.5f, -0.5f, 0.0f, // ta7t 3al 4emal
		 0.5f, -0.5f, 0.0f, // ta7t 3al ymen
		 0.5f,  0.5f, 0.0f, // fo2 3al ymen
		-0.5f,  0.5f, 0.0f // fo2 3al 4emal
	};
	GLfloat CircleVertices[] =   // 8 triangles x 3 points = 24 points  el radius is 0.5, el center (0, 0, 0) 3al shasha a4an ageb el x le kol slice b3ml el cos w el y b3ml el sin, w el z = 0.0f 3al shasha
		
	{
		0.0f, 0.0f, 0.0f,    0.5f,    0.0f,   0.0f,    0.354f,  0.354f, 0.0f,   // 1: C, A, B   c here is the center thats why it repeats in every triangle
		0.0f, 0.0f, 0.0f,    0.354f,  0.354f, 0.0f,    0.0f,    0.5f,   0.0f,   // 2: C, B, D
		0.0f, 0.0f, 0.0f,    0.0f,    0.5f,   0.0f,   -0.354f,  0.354f, 0.0f,   // 3: C, D, E
		0.0f, 0.0f, 0.0f,   -0.354f,  0.354f, 0.0f,   -0.5f,    0.0f,   0.0f,   // 4: C, E, F
		0.0f, 0.0f, 0.0f,   -0.5f,    0.0f,   0.0f,   -0.354f, -0.354f, 0.0f,   // 5: C, F, G
		0.0f, 0.0f, 0.0f,   -0.354f, -0.354f, 0.0f,    0.0f,   -0.5f,   0.0f,   // 6: C, G, H
		0.0f, 0.0f, 0.0f,    0.0f,   -0.5f,   0.0f,    0.354f, -0.354f, 0.0f,   // 7: C, H, I
		0.0f, 0.0f, 0.0f,    0.354f, -0.354f, 0.0f,    0.5f,    0.0f,   0.0f    // 8: C, I, A
	};

	// 1) vertex shader: e3mel wa7ed fady, edilo el text, e3melo compile  1 to 3 dol same for everyshape they are just to create the shader program for the gpu (graphic pipline)
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 2) nafs el kalam lel fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 3) n7ot el etnen f program wa7ed w nerbothom ba3d
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// da hena a4an ne move el objects 
	 offset = glGetUniformLocation(shaderProgram, "offset");
	 scale = glGetUniformLocation(shaderProgram, "scale");
	 colors = glGetUniformLocation(shaderProgram, "color");
	// el program ma3ah nos5a, fa mesh me7tagenhom
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	// 4) VBO = sandoo2 f memory el graphics card fih el no2at
	//    VAO = wara2a bt2ol ezay ne2ra el sandoo2
	// 
	//GLuint TriangleVAO, RectangleVAO, TriangleVBO, RectangleVBO , CircleVAO, CircleVBO;
	glGenVertexArrays(1, &TriangleVAO);
	glGenVertexArrays(1, &RectangleVAO);
	glGenVertexArrays(1, &CircleVAO);
	glGenBuffers(1, &TriangleVBO);
	glGenBuffers(1, &RectangleVBO);
	glGenBuffers(1, &CircleVBO);

	//circle 

	glBindVertexArray(CircleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, CircleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CircleVertices), CircleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
	// triangle
	glBindVertexArray(TriangleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, TriangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleVertices), TriangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// rectangle
	glBindVertexArray(RectangleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, RectangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RectangleVertices), RectangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.95f, 0.89f, 0.78f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shaderProgram); // 3alashan ne use el program elly 3mlnah bta3 el shader el GLSL eli fo2

		// 5) ersem: esta5dem el program, el no2at, w ersem 3 no2at

		//static shapes first here is the lanes which are made of rectangles hn3ml 3 lanes 




		// lanes
		DrawingRectangles(0.125f, -0.03f, 1.75f, 0.39f, 0.79f, 0.51f, 0.31f);   // lane 1
		DrawingRectangles(0.125f, -0.42f, 1.75f, 0.39f, 0.78f, 0.56f, 0.40f);   // lane 2
		DrawingRectangles(0.125f, -0.81f, 1.75f, 0.39f, 0.79f, 0.51f, 0.31f);   // lane 3

		// coins
		DrawingCircle(-0.922f, 0.875f, 0.05f, 0.089f, 0.88f, 0.65f, 0.15f);   // coin 1
		DrawingCircle(-0.853f, 0.875f, 0.05f, 0.089f, 0.88f, 0.65f, 0.15f);   // coin 2
		DrawingCircle(-0.784f, 0.875f, 0.05f, 0.089f, 0.88f, 0.65f, 0.15f);   // coin 3
		// lane 1
		//glBindVertexArray(RectangleVAO);              // bind means select  the rectangle
		//glUniform3f(colors, 0.79f, 0.51f, 0.31f);     
		//glUniform2f(scale, 1.75f, 0.39f);             // width 1.75, height 0.39
		//glUniform2f(offset, 0.125f, -0.03f);          // move center to (0.125, -0.03)
		//glDrawArrays(GL_TRIANGLE_FAN, 0, 4);          // draw the 4 points


		//lane 2
		//glUniform3f(colors, 0.78f, 0.56f, 0.4f);
		//glUniform2f(scale, 1.75f, 0.39f);             // width (scale x = 1 − (−0.75) = 1.75) 1.75, height 0.39  scale y = −0.22 − (−0.61) = 0.39 same scale for all lanes
		//glUniform2f(offset, 0.125f, -0.42f);          // move center to (0.125, -0.45)
		//glDrawArrays(GL_TRIANGLE_FAN, 0, 4);          // draw the 4 points

		//lane 3 
		//glUniform3f(colors, 0.79f, 0.51f, 0.31f);
		//glUniform2f(scale, 1.75f, 0.39f);             
		//glUniform2f(offset, 0.125f, -0.81f);
		//glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


		// now the coins kolhom nafs el scale wel y offset 

		//glBindVertexArray(CircleVAO);
		// Coin 1
		//glUniform3f(colors, 0.88f, 0.65f, 0.15f);
		//glUniform2f(scale, 0.05f, 0.089f);
		//glUniform2f(offset, -0.922f, 0.875f);
		//glDrawArrays(GL_TRIANGLES, 0, 24);
		//// Coin 2
		//glUniform2f(offset, -0.853f, 0.875f);
		//glDrawArrays(GL_TRIANGLES, 0, 24);
		//// Coin 3
		//glUniform2f(offset, -0.784f, 0.875f);
		//glDrawArrays(GL_TRIANGLES, 0, 24);


		// triangle
		
		//glBindVertexArray(TriangleVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		 //lel rectangle

		//Our Team
		Teta(-0.607f, -0.799f);
		Mama(-0.603f, -0.074f);
		Brother(-0.603f, -0.433f);

		//The Opps
		Namoosa(0.409f, 0.039f);
		SorSar(0.609f, -0.528f);
		Cat(0.727f, -0.847f);
	
		
		

		glfwSwapBuffers(window);
	}

	// 6) emsa7 kol 7aga 3amalnaha
	glDeleteVertexArrays(1, &TriangleVAO);
	glDeleteVertexArrays(1, &RectangleVAO);
	glDeleteVertexArrays(1, &CircleVAO);


	glDeleteBuffers(1, &TriangleVBO);
	glDeleteBuffers(1, &RectangleVBO);
	glDeleteBuffers(1, &CircleVBO);



	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;

}