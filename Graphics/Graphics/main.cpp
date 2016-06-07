#define _CRT_SECURE_NO_WARNINGS


#include "GameObjectManager.h"

float rotddd = 0;
int g_timeDelta = 0, g_prevTime = 0;
GameObject* obj;

Light light;
Camera camera;

void render();
void idle();
void changeSize(int width, int height);
void dataLoad();
void myGLInit();

void checkError();

void dataLoad() {
	obj = new GameObject("models/sphere.dat", false);
	obj->transform.SetPosition(0, 0, 3);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	rotddd += 0.001;
	obj->Draw(camera, light);
	obj->transform.Rotation(0, -0.0001, 0);
	glutSwapBuffers();
}

void KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		//Camera::pos.z += 0.1f;
		break;
	case 'a':
		//Camera::pos.x -= 0.1f;
		break;
	case 's':
		//Camera::pos.z -= 0.1f;
		break;
	case 'd':
		//Camera::pos.x += 0.1f;
		break;
	case 'r':
		//Camera::pos.y += 0.1f;
		break;
	case 'f':
		//Camera::pos.y -= 0.1f;
		break;

	case 'q'://카메라의 y 축 회전
		//Camera::Rotation(0, 0.1f, 0);
		break;
	case 'e':
		//Camera::Rotation(0, -0.1f, 0);
		break;
	}
	//printf("cam pos x, y, z : %.6f, %.6f, %.6f\n", Camera::pos.x, Camera::pos.y, Camera::pos.z);
}

void main(int argc, char* argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Shader");
	

	myGLInit();
	dataLoad();

	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(changeSize);

	glutMainLoop();
}

void checkError() {
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		printf("Error. glError 0x%04X\n",err);
}

void myGLInit() {
	light = Light();
	camera = Camera();
	light.Init(8, 20, -15);
	camera.Init();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	int glewtest = glewInit();
	if (glewtest != GLEW_OK) {
		printf("asdf");
	}
	glutKeyboardFunc(KeyBoard);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

void idle() {
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	g_timeDelta = currentTime - g_prevTime;
	g_prevTime = currentTime;
	glutPostRedisplay();
}

void changeSize(int width, int height) {

	GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.f, aspectRatio, 10.f, 200.f);

}