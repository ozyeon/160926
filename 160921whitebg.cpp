﻿#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#define _USE_MATH_DEFINES
#include <math.h>

//glfw
const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];
GLFWwindow* window;
void drawPixel(const int& i, const int& j, const float& red, const float&green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}


/*
void getMousePoint(GLFWwindow* window) {
double xpose, ypose;
glfwGetCursorPos(window, &xpos, &ypos);

}
*/
// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
bool isInsideCircle(const double x, const double y, const double x_c, const double y_c, const double r) {

	const double f = (x - x_c)*(x - x_c) + (y - y_c)*(y - y_c) - r*r;
	if (f > 0.0) return false;
	else {
		printf("1\n");
		return true;
	}
}
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawnline(const int& in0, const int& jn1, const int& jn2, const float& red, const float& green, const float& blue)
{
	for (int j = jn1; j <= jn2; j++)
	{
		drawPixel(in0, j, red, green, blue);
	}
}

void drawThicknerLine(const int& thickness, const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue) {
	/*
	for (int i = i0; i <= i1; i++)
	{
	const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

	for (int k = 0; k < thickness; k++) {
	drawPixel(i + k, j, red, green, blue);
	}
	}
	*/
	for (int i = 0; i < thickness; i++)
		drawLine(i0 + i, j0, i1 + i, j1, 0.0f, 1.0f, 0.0f);
}
void drawSquare(int thickness, const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue) {
	int i_center = (i0 + i1) / 2;
	int j_center = (j0 + j1) / 2;

	for (int j = j_center - thickness; j < j_center + thickness; j++) {
		for (int i = i_center - thickness; i < i_center + thickness; i++) {
			drawPixel(i, j, red, green, blue);
		}
	}
}
void drawPolygon() {
	/*
	//ø¿∞¢«¸
	int i_center = 120;
	int j_center = 130;
	int size = 10;
	int j_start = j_center - size;
	int j_end = j_center + size;
	for (int j = j_start; j <= j_end + size; j++) {
	int i_start = i_center - size + (j / 5);
	int i_end = i_center + size - (j / 5);
	for (int i = i_start; i <= i_end; i++) {
	//if(j == j_start || j == j_end || i == i_start || i == i_end)
	drawPixel(i, j, 1.0f, 0.0f, 0.0f);
	}
	}
	*/
	drawLine(500, 200, 550, 200, 0.0f, 0.0f, 0.0f);
	drawLine(480, 250, 525, 290, 0.0f, 0.0f, 0.0f);
	drawLine(525, 290, 570, 250, 0.0f, 0.0f, 0.0f);

	drawLine(480, 250, 500, 200, 0.0f, 0.0f, 0.0f);
	drawLine(480, 251, 500, 201, 0.0f, 0.0f, 0.0f);

	drawLine(550, 200, 570, 250, 0.0f, 0.0f, 0.0f);
	drawLine(550, 201, 570, 251, 0.0f, 0.0f, 0.0f);
}

void drawCircle(double xpos, double ypos, double rad, const int& i0, const int& j0, float red, float green, float blue) {
	bool color = isInsideCircle(xpos, 500 - ypos, i0, j0, rad);
	if (color == true)
	{
		red = 0.0f;
		blue = 1.0f;
	}
	for (int i = 0; i<20; i++)
	{
		rad = rad + i*0.01;
		for (double i = 0.0; i < 360.0; i += 0.1)
		{
			double angle = i *  M_PI / 180;

			int x = (int)(i0 + rad * cos(angle));
			int y = (int)(j0 + rad * sin(angle));

			drawPixel(x, y, red, green, blue);
		}
	}

}

/*
void drawTriangle( {

int i_center = 100;
int j_center = 100;
int size = 70;
int j_start = j_center - size;
int j_end = j_center + size;

for (int j = j_start; j <= j_end; j++) {
int i_start = i_center - size + (j / 2);
int i_end = i_center + size - (j / 2);

for (int i = i_start; i <= i_end; i++) {
if (j == j_start || j == j_end || i == i_start || i == i_end)
drawPixel(i, j, 1.0f, 0.0f, 0.0f);
}
}
}
*/
void drawEmptySquare(int size, const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue) {
	int i_center = (i0 + i1) / 2;
	int j_center = (j0 + j1) / 2;

	for (int j = j_center - size; j <= j_center + size; j++) {
		//for (int i = i_center - thickness; i < i_center + thickness; i++) {
		for (int i = i_center - size; i <= i_center + size; i = i + size * 2)
			drawPixel(i, j, red, green, blue);

	}
	//for (int j = j_center - thickness; j < j_center + thickness; j++) {
	for (int i = i_center - size; i <= i_center + size; i++) {
		for (int j = j_center - size; j <= j_center + size; j = j + size * 2)
			drawPixel(i, j, red, green, blue);
	}
}
void heightLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue) {
	//for (int i = i0; i <= i1; i++)
	//
	for (int i = 0; i<50; i++)
	{

		drawPixel(i0, j0 - i, red, green, blue);
	}
}
void drawOnPixelBuffer(double xpos, double ypos)
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	//std::fill_n(pixels, width*height * 3, 1.0f);	// white background

	for (int i = 0; i<width*height; i++) {
		pixels[i * 3 + 0] = 1.0f; // red 
		pixels[i * 3 + 1] = 1.0f; // green
		pixels[i * 3 + 2] = 1.0f; // blue
	}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	//drawLine
	const int i0 = 60, i1 = 110;
	const int j0 = 310, j1 = 360;
	const int thickness = 10;
	const int size = 20;

	drawLine(58, 330, 104, 370, 1.0f, 0.0f, 0.0f);
	drawLine(59, 330, 105, 370, 1.0f, 0.0f, 0.0f);
	drawLine(60, 330, 106, 370, 1.0f, 0.0f, 0.0f);
	drawLine(61, 330, 107, 370, 1.0f, 0.0f, 0.0f);
	drawLine(62, 330, 108, 370, 1.0f, 0.0f, 0.0f);

	//drawCircle
	drawCircle(0, 0, 15, 200, 350, 1.0f, 0.0f, 0.0f);
	drawCircle(0, 0, 13, 200, 350, 1.0f, 0.0f, 0.0f);
	
	for (int i = 0; i<5; i++)
		drawCircle(xpos, ypos, 50, 80 + i * 120, 350, 1.0f, 0.0f, 0.0f);

	for (int i = 0; i<5; i++)
		drawCircle(xpos, ypos, 50, 80 + i * 120, 150, 1.0f, 0.0f, 0.0f);

	//drawSquare
	drawLine(300, 330, 340, 330, 1.0f, 0.0f, 0.0f);
	drawLine(300, 370, 340, 370, 1.0f, 0.0f, 0.0f);
	drawnline(300, 330, 370, 1.0f, 0.0f, 0.0f);
	drawnline(340, 330, 370, 1.0f, 0.0f, 0.0f);

	//drawX
	drawLine(420, 330, 460, 370, 1.0f, 0.0f, 0.0f);
	drawLine(420, 370, 460, 330, 1.0f, 0.0f, 0.0f);

	//drawarrow1
	drawnline(560, 330, 380, 1.0f, 0.0f, 0.0f);
	drawLine(545, 345, 560, 330, 1.0f, 0.0f, 0.0f);
	drawLine(560, 330, 575, 345, 1.0f, 0.0f, 0.0f);

	//drawrrow2
	drawLine(55, 145, 105, 145, 1.0f, 0.0f, 0.0f);
	drawLine(90, 160, 105, 145, 1.0f, 0.0f, 0.0f);
	drawLine(90, 130, 105, 145, 1.0f, 0.0f, 0.0f);

	//drawA
	drawLine(185, 145, 215, 145, 1.0f, 0.0f, 0.0f);
	drawLine(185, 144, 215, 144, 1.0f, 0.0f, 0.0f);
	drawLine(175, 125, 200, 177, 1.0f, 0.0f, 0.0f);
	drawLine(200, 177, 225, 125, 1.0f, 0.0f, 0.0f);
	drawLine(176, 125, 201, 177, 1.0f, 0.0f, 0.0f);
	drawLine(201, 177, 226, 125, 1.0f, 0.0f, 0.0f);

	//draw|
	drawnline(320, 120, 180, 1.0f, 0.0f, 0.0f);

	//drawarrow3
	drawLine(410, 145, 470, 145, 1.0f, 0.0f, 0.0f);
	drawLine(410, 145, 425, 160, 1.0f, 0.0f, 0.0f);
	drawLine(410, 145, 425, 130, 1.0f, 0.0f, 0.0f);

	//drawarrow4
	drawnline(560, 125, 175, 1.0f, 0.0f, 0.0f);
	drawLine(545, 160, 560, 175, 1.0f, 0.0f, 0.0f);
	drawLine(560, 175, 575, 160, 1.0f, 0.0f, 0.0f);

	//TODO: try moving object
}
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background
	bool inside = false;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* get Cursor pos */
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		printf("%04.1lf\t%04.1lf\n", xpos, ypos);

		/* ALL Drawing Function is here */
		drawOnPixelBuffer(xpos, ypos);

		/* Drawing Buffer on window */
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}