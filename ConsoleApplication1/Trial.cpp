#include <windows.h>

#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>

//#include "olcConsoleGameEngine.h"
#include <fstream>
#include <strstream>
#include <algorithm>
#include<sstream>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include<glut.h>
#include<glu.h>
#include<gl.h>
#include<glfw3.h>
//#include <glm.hpp>
//#include <matrix_transform.hpp>
#include <type_ptr.hpp>

using namespace std;

//using namespace __unnamed_struct_001e_3;
#define EXPORT extern "C" _declspec(dllexport)
//#include <Game.cpp>
using namespace std;

HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);
COORD screen;

void putpixel(int x, int y, int color, char m = '*') {
	POINT cursorPosition;
	GetCursorPos(&cursorPosition);
	screen.X = x;
	screen.Y = y;
	
	SetConsoleCursorPosition(hdl, screen);
	SetConsoleTextAttribute(hdl, color);
	cout << m;
}

class vec3d
{
public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1; // Need a 4th term to perform sensible matrix vector multiplication
};
class mat4x4
	
{
public:
		float m[4][4] = { 0 };
};
class mat4x4a

{
public:
	float a[4][4] = { 0 };
};
int Sign(double x) {
	if (x < 0)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

void drawLine(double xPrev, double yPrev, double x, double y, char(&map)[20][79])
{
	double x1 = xPrev;
	double y1 = yPrev;
	double x2 = x;
	double y2 = y;
	double dy = y2 - y1;
	double dx = x2 - x1;

	if (fabs(dy) > fabs(dx))
	{
		for (y = y1; y != y2; y += Sign(dy))
		{
			x = x1 + (y - y1) * dx / dy;
			map[(int)y][(int)x] = '.';

		}
	}

	else
	{
		for (x = x1; x != x2; x += Sign(dx))
		{
			y = y1 + (x - x1) * dy / dx;
			map[(int)y][(int)x] = '.';
		}
	}

	// draw the last point
	map[(int)y2][(int)x2] = '.';
}
//vector<vec3d> verts;
mat4x4 Matrix_MakeRotationX(float fAngleRad)
{
	mat4x4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = cosf(fAngleRad);
	matrix.m[1][2] = sinf(fAngleRad);
	matrix.m[2][1] = -sinf(fAngleRad);
	matrix.m[2][2] = cosf(fAngleRad);
	matrix.m[3][3] = 1.0f;
	return matrix;
}
mat4x4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
{
	float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
	mat4x4 matrix;
	matrix.m[0][0] = fAspectRatio * fFovRad;
	matrix.m[1][1] = fFovRad;
	matrix.m[2][2] = fFar / (fFar - fNear);
	matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matrix.m[2][3] = 1.0f;
	matrix.m[3][3] = 0.0f;
	return matrix;
}
mat4x4 Matrix_MakeRotationZ(float fAngleRad)
{
	mat4x4 matrix;
	matrix.m[0][0] = cosf(fAngleRad);
	matrix.m[0][1] = sinf(fAngleRad);
	matrix.m[1][0] = -sinf(fAngleRad);
	matrix.m[1][1] = cosf(fAngleRad);
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
}
mat4x4 Matrix_MultiplyMatrix(mat4x4& m1, mat4x4& m2)
{
	mat4x4 matrix;
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
	return matrix;
}

void DrawParabola(int a, int xb){
	a = a * a;
		xb = xb;
		
}
int getRemainder(int num, int divisor)
{
	return (num - divisor * (num / divisor));
}
void DrawLine(int xA, int yA, int xB, int yB) {
	int dx = abs((xB - xA) + 50), dy = (yB - yA), color = 4;

	float steps = abs(dx);
	float xinc = dx/steps ;
	float yinc = dy / steps;
	float x = xA, y = yA;
	putpixel(xinc,  yinc,color,'*');
}
void DrawLineDDA(int xA, int yA, int xB, int yB) {
	int dx = abs((xB -xA)), dy = (yB - yA), color = 4;

	float steps =max(abs(dx),abs(dy));
	float xinc = dx / steps;
	float yinc = dy /steps;
	float x = xA, y = yA;
	float x2 = xB, y2 = yB;
	int p1 = 0;
	int p2 = 0;
	steps = 300;
	
	while (steps ) {
		
		


		mat4x4 matrix2;
		matrix2.m[0][0] = cosf(x);
		matrix2.m[0][1] = sinf(x);
		matrix2.m[1][0] = -sinf(x);
		matrix2.m[1][1] = cosf(x);
		matrix2.m[2][2] = 1.0f;
		matrix2.m[3][3] = 1.0f;
		
		struct sKeyState
		{
			bool bPressed;
			bool bReleased;
			bool bHeld;
		} m_keys[256], m_mouse[5];

		int m_mousePosX;
		int m_mousePosY;



		


		mat4x4 matrix;
		float fAngleRad = x;
		matrix.m[0][0] = x;
		matrix.m[1][1] = cosf(fAngleRad);
		matrix.m[1][2] = sinf(fAngleRad);
		matrix.m[2][1] = -sinf(fAngleRad);
		matrix.m[2][2] = cosf(fAngleRad);
		matrix.m[3][3] = 1.0f;
		//Matrix_MakeRotationX();

		//mat4x4 matrix;
		for (int c = 0; c < 4; c++){
			for (int r = 0; r < 4; r++){
				matrix.m[r][c] = matrix.m[r][0] * matrix2.m[0][c] + matrix.m[r][1] * matrix2.m[1][c] + matrix.m[r][2] * matrix2.m[2][c] + matrix.m[r][3] * matrix2.m[3][c];
				
				{//do something}
					{
						//sKeyState
							//getKeyState;
						//WM_SYSKEYDOWN
						int i = 1;
						if (GetKeyState(VK_UP) == 0) {
							if (x < 80) {

								/*
								putpixel(((x) / 20) + 25, y, 0, '*');
								putpixel(((x) / 20) + 30, y, 0, '*');
								putpixel(((x) / 20) + 45, y, 0, '*');

								putpixel(((x) * 30) + 25, y, 0, '*');
								putpixel(((x) * 30) + 30, y, 0, '*');*/


								//std::cout << (steps);
								if (x > 2) {



									x = 0;


									for (int i = 0; i < 20; i++) {
										//putpixel(((x)), i , color, '*');

									}



								}


								for (int i = 0; i < 20; i++) {
									//putpixel(((x)), i , color, '*');

								}






								xinc = dx / steps;
								while (GetKeyState(49) == 1) {
									if (steps < -300 or steps>700) {
										steps = 300;
									}
									steps = (steps++);
									//steps = steps * -1;


								}
								while (GetKeyState(50) == 1) {
									if (steps > -21 or steps < -700) {
										steps = -50;
									}
									steps = (steps--);
									steps = steps * -1;

								}
								/*if (steps > -21 or steps < -700) {
									steps = -50;
								}*/
							}
							else {
								//x = 0;
								//xinc=dx / steps;
							}
							if (GetKeyState(57) == 1) {

								//xinc = dx;

							}



						}
						else if (GetKeyState(48) == 1) {

							//float angle = atan2(p1 - p2, p1 - p2);

								//while true
							//putpixel(x, y, 3);
							int remainder = getRemainder(y, 50);

							int wavex = (cos(x / 10)) * 15 + (50);
							int wavey = (sin(y / 10)) * 15 - (y / 3) + (10);
							
								//float angle = (atan2(wavey - y2, wavex - x2))*180/3.14159;
								//putpixel(x2, angle, 2);
							
							//angle = atan2(wavey - wavex, wavex - wavey);
							//	std::cout << (angle);

							putpixel(wavex, wavey, color);
							putpixel(x2, wavey, 3);
							
							

							
								
							

							//putpixel(wavex, wavey, 3);





						}

						
						//if(GetKey)
						//putpixel(abs(sin(x / 10)) * 50 , y, color);

					}
					
				}
					
		}
			}
			//matrix.m[i][i] = Matrix_MakeRotationX(x);
					
			
		x += xinc;
		y += yinc;
		Sleep(10);
		
		steps++;
		
		
	}
	

}
void drawRegularLine(int x, int y) {
	POINT cursorPosition;
	GetCursorPos(&cursorPosition);
	putpixel(x, y,4);

}

void keyboard(unsigned char c, int x, int y);
float random = 0;
struct sKeyState
{
	bool bPressed;
	bool bReleased;
	bool bHeld;
} m_keys[256], m_mouse[5];
GLfloat b = 0;
GLfloat a = 0;
bool test = true;
sKeyState GetKey(int nKeyID) { return m_keys[nKeyID]; }
void DisplayFunction(void) {
	
		
	int start = clock();
		
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_LINES);
			
			if (true) {
				random=random +0.05;
				Sleep(2);
			}
			if (random >= 50) {
				random = 0;
			}
			if (test == true) {
					/*b += 0.1;
					

					a += 0.1;
					Sleep(20);*/
					/* 
					}*/
					

				}
			if (test == false) {
				/*
				b =cos(random/2);


				a = sin(random/2);
				Sleep(1);*/

			}
			/*glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
			trans = glm::rotate(trans, (float)random, glm::vec3(0.0f, 0.0f, 1.0f));*/
			
			//std::cout << random << endl;
				//front face
				glVertex3f(0+cos(random)+(1-cos(random))/20-20, (1-cos(random)) - sin(random)/20-20, 0);
				glVertex3f(1-cos(random)+sin(random )/20, 0+cos(random )+(1-cos(random))/20, 0);

				glVertex3f(0 + cos(random) + (1 - cos(random)) / 20-20, (1 - cos(random)) - sin(random) / 20-20, 0);
				glVertex3f(1 - cos(random) + sin(random) / 20+160, 0 + cos(random) + (1 - cos(random)) / 20+160, 0);


				glVertex3f(sin(random + 160), 0 + cos(random + 160), 0);
				glVertex3f(0 + cos(random+160), 0 - sin(random+160), 0);

				glVertex3f(0 + cos(random + 160), 0 - sin(random + 160), 0);
				glVertex3f(sin(random ), 0 + cos(random  ), 0);

				//back face
				glVertex3f(0 , 0.5, 0.5 );
				glVertex3f(0.5 , 0.5, 0.5 );

				glVertex3f(0  , 0, 0.5 );
				glVertex3f(0.5 , 0, 0.5);


				glVertex3f(0 , 0.5, 0.5 );
				glVertex3f(0 , 0, 0.5 );

				glVertex3f(0.5, 0.5, 0.5 );
				glVertex3f(0.5 , 0, 0.5 );
				
				;


			glEnd();
			//glutKeyboardFunc(keyboard);
			glFlush();
			glutPostRedisplay();
		
		
		
	
}
//void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv) {
	int start=clock();
	POINT cursorPosition;
	GetCursorPos(&cursorPosition);
	{
		if (cursorPosition.x > 200) {
			//drawRegularLine(cursorPosition.x, cursorPosition.y);
		}
	}

	/*glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;*/
	//std::cout << vec.x << vec.y << vec.z << std::endl;
	//int start = clock();




	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("GraphicsTestApp");
	if (GetKeyState(VK_UP) == 1) {
		//a = 0.4;
		glutDisplayFunc(DisplayFunction);
		//xinc = dx;
		
		
	}
	if (GetKeyState(VK_DOWN) == 1) {
	//	a = 0.4;
		glutDisplayFunc(DisplayFunction);
		//xinc = dx;
		
		
	}
	
		
	
		
	
	glutDisplayFunc(DisplayFunction);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	

	//HDC hdc = GetDC(hWnd);

	int Count;

	//HDC hdc;
	//HWND hwnd;

	//HDC hdc=GetDC(NULL);
	//SetPixel(hdc, 240, 240, 3);
	//Setpixel(255, 555, 3, 'M');
	
	for (Count = 0; Count < 10; Count++) {
		cout << char(219);
		if (Count) {
		//	Sleep(100);
		}
		
	}

	std::cout << cursorPosition.x << endl;
	while (true) {
		
		
		//drawRegularLine(cursorPosition.x, cursorPosition.y);
		DrawLineDDA(155,155, 55, 55);

				//change y1
	}
	
	return 0;
	//PrintWindow;
	//DrawLineDDA(55, 5, 250, 250);
	//initwindow(500, 500);
}

void keyboard(unsigned char c, int x, int y) {


	if (c=='a') {
		test = false;

		//exit(0);
	}
	if (c == 's') {
		test = true;

		//exit(0);
	}

}

	//Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	/* Register the window class
	const char* CLASS_NAME = "myWin32WindowClass";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);*/

	/*// Create the window
	CreateWindow(CLASS_NAME, "Win32 Drawing with GDI+ Tutorial",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,            // Window style
		CW_USEDEFAULT, CW_USEDEFAULT,                // Window initial position
		800, 600,                                    // Window size
		nullptr, nullptr, nullptr, nullptr);

	// Window loop
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;*/


/*class vec3d
{
public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1; // Need a 4th term to perform sensible matrix vector multiplication
};*/