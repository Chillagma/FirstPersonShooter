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
						//DrawVerTri((-0.5) + x1, (0) + x2, (0) + y1, (0) + y2, 0, 0.5);
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

struct mat {

	double x1ab[4] = { -0.5,-0.5,-0.5,-0.5};
	double y1ab[4] = { 0,0,0, 0 };
	double x2ab[4] = { 0, -0.5,-0.5, 0};
	double y2ab[4] = { 0, 0.5,0,0};

	double x3ab[4] = { 0, 0,-0.5 , -0.5 };
	double y3ab[4] = { 0.5, 0.5,0.5, 0 };
};

void DrawVerTri(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glVertex3f(x1, y1, 0);
	glVertex3f(x2, y2,0);


	glVertex3f(x2, y2, 0);
	glVertex3f( x3, y3, 0);




	glVertex3f(x3, y3, 0);
	glVertex3f( x1, y1,0);


}

void DrawVerSquare(float x1, float y1, float x2, float y2, float x3, float y3,float x4, float y4)
{
	glVertex3f(x1, y1, 0);
	glVertex3f(x2, y2, 0);


	glVertex3f(x2, y2, 0);
	glVertex3f(x3, y3, 0);




	glVertex3f(x3, y3, 0);
	glVertex3f(x4, y4, 0);

	glVertex3f(x4, y4, 0);
	glVertex3f(x1, y1, 0);



}
void matfunc(int x1, int y1, int x2, int y2, int x3, int y3) {

	
}
mat idea;
float random = 0;
int i = 0;
void  square() {

	//random = 0;
	if (true) {
		random = random + 0.05;
		Sleep(2);
	}
	/*float x1 = (0 + cos(random) + (1 - cos(random)) - 20) / 15;
	float y1 = ((1 - cos(random)) - sin(random) - 20)/15;
	float x2 = 1 - cos(random) + sin(random);
	float y2 = (0 + cos(random) + (1 - cos(random)));*/
	/**/
	/*
	///East connect
	glVertex3f((x1 + 2 * 10) / 15, (y1 + 1 * 10) / 15, 0);
	glVertex3f((x1 + 2 * 10) / 15, (y1 + 2 * 10) / 15, 0);

	//North connect
	glVertex3f(x2 / 15, (y2 - 1 * 10) / 15, 0);
	glVertex3f(x2 / 15, y2 / 15, 0);

	//diagonal bottom
	glVertex3f(x2 / 15, (y2 - 1 * 10) / 15, 0);
	glVertex3f((x1 + 2 * 10) / 15, (y1 + 1 * 10) / 15, 0);

	//diagonal top
	glVertex3f((x1 + 2 * 10) / 15, (y1 + 2 * 10) / 15, 0);
	glVertex3f(x2 / 15, y2 / 15, 0);*/


//	glutPostRedisplay();


}



void keyboard(unsigned char c, int x, int y);

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
/*
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
*/

void load_obj(const char* filename, vector<glm::vec4>& vertices, vector<glm::vec3>& normals, vector<GLushort>& elements)
{
	
	ifstream in(filename, ios::in);
	if (!in)
	{
		cerr << "Cannot open " << filename << endl; exit(1);
	}

	string line;
	while (getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			istringstream s(line.substr(2));
			glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
			vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "f ")
		{
			istringstream s(line.substr(2));
			GLushort a, b, c;
			s >> a; s >> b; s >> c;
			a--; b--; c--;
			elements.push_back(a); elements.push_back(b); elements.push_back(c);
		}
		/* anything else is ignored */
	}


	vector<glm::vec4> suzanne_vertices;
	vector<glm::vec3> suzanne_normals;
	vector<GLushort> suzanne_elements;
	///[...]
	load_obj("teapot.obj", suzanne_vertices, suzanne_normals, suzanne_elements);

	normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
	for (int i = 0; i < elements.size(); i += 3)
	{
		GLushort ia = elements[i];
		GLushort ib = elements[i + 1];
		GLushort ic = elements[i + 2];
		glm::vec3 normal = glm::normalize(glm::cross(
			glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
			glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
		normals[ia] = normals[ib] = normals[ic] = normal;
	}
}


void DisplayFunction(void) {

	/*
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	const float radius = 10.0f;
	float camX = sin(random) * radius;
	float camZ = cos(random) * radius;
	

	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	*/
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
			vector<mat>mystructs;
			for (int i = 0; i < 3; i++) {
				mystructs.emplace_back(mat{});
				//x1ab=mystructs.at(i)={  2,2,2};
				
			}
			/*glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
			trans = glm::rotate(trans, (float)random, glm::vec3(0.0f, 0.0f, 1.0f));*/
			
			//std::cout << random << endl;
				//front face
				float x1 = 0 + cos(random) + (1 - cos(random))-1  ;
				float y1 = (1 - cos(random)) - sin(random) -2 ;
				float x2 = 1 - cos(random)  + sin(random)-1 ;
				float y2 = (0 + cos(random) + (1 - cos(random)))-2;

				
				//float z3=
				
				
				vec3d light_direction = { 0.0f, 0.0f, -1.0f };
				float l = sqrtf(light_direction.x * light_direction.x + light_direction.y * light_direction.y + light_direction.z * light_direction.z);
				light_direction.x /= l; light_direction.y /= l; light_direction.z /= l;

			/*
				// East
				glVertex3f((x1+2.5*10)/15, (y1+2*10)/15, 0);
				glVertex3f((x2+1*10) / 15 ,(y2+1*10)/15   , 0);

				glColor3f(255, 0, 0);
			
				
				//glutGetColor('red', 'red');
				//South
				glVertex3f((x2+2)/15 , y2/15 , 0);
				glVertex3f((x2 +1*10) / 15, (y2 + 1*10) / 15, 0);


				//upper
				for (int i = 0; i < 155; i++) {

					//North2
					glVertex3f((x2+2) / 15, (y2-1*10) / 15  , 0);
					glVertex3f((x2 + 1*10) / 15, (y2 + 1*10) / 15, 0);

					
			
					
					//East2
					glVertex3f((x1 +2.5*10) / 15, (y1 + 1*10) / 15 , 0);
					glVertex3f((x2 + 1*10) / 15, (y2 + 1*10) / 15, 0);
					

					
				}
				for (int i = 0; i < 3; i++) {
					
					//15 is scale
					//10 is strech

					//idea.ab[i][i];
					glVertex3f((x1 + idea.x1ab[i] * 10) / 15, (y1 + idea.y1ab[i] * 10) / 15, 0);
				}
				for (int i = 0; i <3; i++) {

					//idea.ab[i][i];
					glVertex3f((x2 + idea.x2ab[i] * 10) / 15, (y2 + idea.y2ab[i] * 10) / 15, 0);
					
				}
				
				*/
				for (int i = 0; i < 4; i++) {

					//idea.ab[i][i];
					//glVertex3f((x2 + idea.x2ab[i] * 10) / 15, (y2 + idea.y2ab[i] * 10) / 15, 0);
				//	DrawVerTri((idea.x1ab[i] + cos(random)), idea.y1ab[i] + sin(random), idea.x2ab[i] - sin(random), idea.y2ab[i] + cos(random), idea.x3ab[i] - sin(random), idea.y3ab[i] + cos(random));

				}


				glColor3f(255, 0, 0);
			for (int i = 0; i < 4; i++) {

				DrawVerTri((idea.x1ab[i]) + cos(random), (idea.y1ab[i]) + sin(random), (idea.x2ab[i]) - sin(random), (idea.y2ab[i]) + cos(random), (idea.x3ab[i]) - sin(random), (idea.y3ab[i]) + cos(random));
			
					//idea.ab[i][i];
					//idea=mystructs.at(1) = {4, 4, 4 };
				
				
				}
				/*
				DrawVerTri((-0.5) + cos(random), (0) + sin(random), (0) - sin(random), (0) + cos(random), 0 - sin(random), 0.5 + cos(random));

				DrawVerTri((-0.5)+cos(random), (0)+sin(random), (-0.5)-sin(random), (0.5)+cos(random), 0-sin(random), 0.5+cos(random));

				DrawVerTri((-0.5) + cos(random), (0) + sin(random), (-0.5) - sin(random), (0) + cos(random), -0.5 - sin(random), 0.5 + cos(random));

				DrawVerTri((-0.5) + cos(random), (0) + sin(random), (0) - sin(random), (0) + cos(random), -0.5 - sin(random), 0 + cos(random));
				
				*/
				//DrawVerSquare((-0.5) + cos(random), (0) + sin(random), (0) - sin(random), (0) + cos(random), 0 - sin(random), 0.5 + cos(random), -0.5 + cos(random), 0.5 + sin(random));









				//DrawVerTri((-0.5), (0.5), (0), (0.5), -0.5, 0.65);


				//DrawVerTri((-1 + x1), (0 + y1), (0.5 + x2), (0 + y2), 0, 0.5);
			;
				
				/*for (int i = 0; i < 2; i++) {
				
					//idea.ab[i][i];
					glVertex3f((x1 + idea.x1ab[i] * 10) / 15, (y1 + idea.y1ab[i] * 10) / 15, 0);
				}*/
				//
				/*
				//East connect
				glVertex3f((x1 + 2*10) / 15, (y1 + 1*10) / 15 , 0);
				glVertex3f((x1 + 2*10) / 15, (y1 + 2*10) / 15, 0);

				//North connect
				glVertex3f(x2 / 15, (y2-1*10) / 15, 0);
				glVertex3f(x2 / 15, y2 / 15, 0);

				//diagonal bottom
				glVertex3f(x2 / 15, (y2-1*10)/ 15 , 0);
				glVertex3f((x1 + 2*10) / 15, (y1 + 1*10) / 15 , 0);

				//diagonal top
				glVertex3f((x1 + 2*10) / 15, (y1 + 2*10) / 15, 0);
				glVertex3f(x2 / 15, y2 / 15, 0);

				*/

				
				



				/*
				glVertex3f(sin(random + 160), 0 + cos(random + 160), 0);
				glVertex3f(0 + cos(random+160), 0 - sin(random+160), 0);

				glVertex3f(0 + cos(random + 160), 0 - sin(random + 160), 0);
				glVertex3f(sin(random ), 0 + cos(random  ), 0);
				*/

				


				//back face
				/*glVertex3f(0, 0.5, 0.5);
				glVertex3f(0.5 , 0.5, 0.5 );

				glVertex3f(0  , 0, 0.5 );
				glVertex3f(0.5 , 0, 0.5);


				glVertex3f(0 , 0.5, 0.5 );
				glVertex3f(0 , 0, 0.5 );

				glVertex3f(0.5, 0.5, 0.5 );
				glVertex3f(0.5 , 0, 0.5 );
				
				;
				*/
				
			// square();
				
			 for (int i = 0; i < 4; i++) {
				 i++;
				 //idea.ab[i][i];
				
				// square();
			
			 }

			glEnd();
			//glutKeyboardFunc(keyboard);
			glFlush();
			glutPostRedisplay();
		
		
		
	
}
//void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv) {
	/*float x1 = 0 + cos(random) + (1 - cos(random)) - 20;
	float y1 = (1 - cos(random))  - sin(random)  - 20;
	float x2 = 1 - cos(random)  + sin(random) ;
	float y2 = (0 + cos(random)  + (1 - cos(random)) );*/
	int start=clock();
	POINT cursorPosition;
	GetCursorPos(&cursorPosition);
	{
		if (cursorPosition.x > 200) {
			//drawRegularLine(cursorPosition.x, cursorPosition.y);
		}
	}


	//initialized elsewhere

	square();


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