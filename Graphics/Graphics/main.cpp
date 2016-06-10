
#include "GameObjectManager.h"

GameObjectManager* manager;

Time time;

void render();
void idle();
void changeSize(int width, int height);
void myGLInit();
void update();
void draw();

void checkError();



void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	update();
	draw();
	glutSwapBuffers();
}

void update() {
	if(manager != nullptr)	manager->update(time.deltaTime);
}

void draw() {	
	if (manager != nullptr)
		manager->render();
}

void KeyBoard(unsigned char key, int x, int y) {

	switch (key) {
	case 'w':
		if(manager->myChar != nullptr)manager->myChar->input.up = true;
		//manager->myChar->transform.SetPosition(manager->myChar->transform.position.x, manager->myChar->transform.position.y + 0.1f, manager->myChar->transform.position.z + 0.1f * 0.3f);
		break;
	case 'a':
		if (manager->myChar != nullptr)manager->myChar->input.left = true;
		//manager->myChar->transform.SetPosition(manager->myChar->transform.position.x - 0.1f, manager->myChar->transform.position.y, manager->myChar->transform.position.z);
		break;
	case 's':
		if (manager->myChar != nullptr)manager->myChar->input.down = true;
		//manager->myChar->transform.SetPosition(manager->myChar->transform.position.x, manager->myChar->transform.position.y - 0.1f, manager->myChar->transform.position.z - 0.1f * 0.3f);
		break;
	case 'd':
		if (manager->myChar != nullptr)manager->myChar->input.right = true;
		//manager->myChar->transform.SetPosition(manager->myChar->transform.position.x + 0.1f, manager->myChar->transform.position.y, manager->myChar->transform.position.z);
		break;
	case 'r':
		manager->shakingCamera();
		//manager->myChar->transform.SetPosition(manager->myChar->transform.position.x, manager->myChar->transform.position.y, manager->myChar->transform.position.z + 0.1f);
		break;
	case 'f':
		//manager->myChar->transform.SetPosition(manager->myChar->transform.position.x, manager->myChar->transform.position.y, manager->myChar->transform.position.z - 0.1f);
		break;

	case 'q'://카메라의 y 축 회전
			 //Camera::Rotation(0, 0.1f, 0);
		break;

	case 'e':
		//Camera::Rotation(0, -0.1f, 0);
		break;
	case ' ':
		//스페이스바를 누르면 총알을 만들어서 오브젝트 리스트에 추가하자.
		if (manager != nullptr)	manager->addBullet();
		break;
	}
	//printf("cam pos x, y, z : %.6f, %.6f, %.6f\n", Camera::pos.x, Camera::pos.y, Camera::pos.z);
}

void KeyBoardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		if (manager->myChar != nullptr)manager->myChar->input.up = false;
		//manager->myChar->transform.SetPosition(manager->myChar->transform.position.x, manager->myChar->transform.position.y + 0.1f, manager->myChar->transform.position.z + 0.1f * 0.3f);
		break;
	case 'a':
		if (manager->myChar != nullptr)manager->myChar->input.left = false;
		//manager->myChar->transform.SetPosition(manager->myChar->transform.position.x - 0.1f, manager->myChar->transform.position.y, manager->myChar->transform.position.z);
		break;
	case 's':
		if (manager->myChar != nullptr)manager->myChar->input.down = false;
		//manager->myChar->transform.SetPosition(manager->myChar->transform.position.x, manager->myChar->transform.position.y - 0.1f, manager->myChar->transform.position.z - 0.1f * 0.3f);
		break;
	case 'd':
		if (manager->myChar != nullptr)manager->myChar->input.right = false;
		//manager->myChar->transform.SetPosition(manager->myChar->transform.position.x + 0.1f, manager->myChar->transform.position.y, manager->myChar->transform.position.z);
		break;
	}
}

void main(int argc, char* argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Grapics");
	
	myGLInit();

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
	time = Time();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	int glewtest = glewInit();
	if (glewtest != GLEW_OK)		printf("asdf");
	glutKeyboardFunc(KeyBoard);
	glutKeyboardUpFunc(KeyBoardUp);
	manager = new GameObjectManager();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);  
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

void idle() {
	time.update();
	glutPostRedisplay();
}

void changeSize(int width, int height) {
	GLfloat aspectRatio = (GLfloat)height / (GLfloat)width;
	glViewport(0, 0, width, height);
	//obj->setAspect(aspectRatio);
}