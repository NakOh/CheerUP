
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
		//obj->transform.SetPosition(obj->transform.position.x, obj->transform.position.y + 0.1f, obj->transform.position.z );
		//Camera::pos.z += 0.1f;
		break;
	case 'a':
		//obj->transform.SetPosition(obj->transform.position.x - 0.1f, obj->transform.position.y, obj->transform.position.z);
		//Camera::pos.x -= 0.1f;
		break;
	case 's':
		//obj->transform.SetPosition(obj->transform.position.x, obj->transform.position.y - 0.1f, obj->transform.position.z);
		//Camera::pos.z -= 0.1f;
		break;
	case 'd':
		//obj->transform.SetPosition(obj->transform.position.x + 0.1f, obj->transform.position.y, obj->transform.position.z);
		//Camera::pos.x += 0.1f;
		break;
	case 'r':
		//obj->transform.SetPosition(obj->transform.position.x, obj->transform.position.y, obj->transform.position.z + 0.1f);
		//Camera::pos.y += 0.1f;
		break;
	case 'f':
		//obj->transform.SetPosition(obj->transform.position.x, obj->transform.position.y, obj->transform.position.z - 0.1f);
		//Camera::pos.y -= 0.1f;
		break;

	case 'q'://ī�޶��� y �� ȸ��
		//Camera::Rotation(0, 0.1f, 0);
		break;

	case 'e':
		//Camera::Rotation(0, -0.1f, 0);
		break;
	case ' ':
		//�����̽��ٸ� ������ �Ѿ��� ���� ������Ʈ ����Ʈ�� �߰�����.
		if (manager != nullptr)	manager->addBullet();
		break;
	}
	//printf("cam pos x, y, z : %.6f, %.6f, %.6f\n", Camera::pos.x, Camera::pos.y, Camera::pos.z);
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

	manager = new GameObjectManager();

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