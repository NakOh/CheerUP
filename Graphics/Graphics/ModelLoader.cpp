

#include "ModelLoader.h"

Vertex::Vertex() {
	pos = Vec4();
	normal = Vec4();
	sum_normal = Vec4();
	color = Vec4(1, 1, 1, 1);
}

Model* copyModel(Model* model) {
	Model* ret = new Model();
	ret->model.faceCount = model->model.faceCount;
	ret->model.textureCount = model->model.textureCount;
	ret->model.vertexCount = model->model.vertexCount;

	//*
	ret->model.coorddata = new Vec4[model->model.textureCount];
	for (int i = 0; i < model->model.textureCount; i++) {
		ret->model.coorddata[i].x = model->model.coorddata[i].x;
		ret->model.coorddata[i].y = model->model.coorddata[i].y;
		ret->model.coorddata[i].z = model->model.coorddata[i].z;
		ret->model.coorddata[i].w = model->model.coorddata[i].w;
	}
	//*/

	//*
	ret->model.coords = new Point4[model->model.faceCount];
	for (int i = 0; i < model->model.faceCount; i++) {
		ret->model.coords[i].p[0] = model->model.coords[i].p[0];
		ret->model.coords[i].p[1] = model->model.coords[i].p[1];
		ret->model.coords[i].p[2] = model->model.coords[i].p[2];
		ret->model.coords[i].p[3] = model->model.coords[i].p[3];
	}
	//*/

	ret->model.vertices = new Vertex[model->model.vertexCount];
	for (int i = 0; i < model->model.vertexCount; i++) {
		ret->model.vertices[i].pos.x = model->model.vertices[i].pos.x;
		ret->model.vertices[i].pos.y = model->model.vertices[i].pos.y;
		ret->model.vertices[i].pos.z = model->model.vertices[i].pos.z;
		ret->model.vertices[i].pos.w = model->model.vertices[i].pos.w;

		ret->model.vertices[i].color.x = model->model.vertices[i].color.x;
		ret->model.vertices[i].color.y = model->model.vertices[i].color.y;
		ret->model.vertices[i].color.z = model->model.vertices[i].color.z;
		ret->model.vertices[i].color.w = model->model.vertices[i].color.w;

		ret->model.vertices[i].normal.x = model->model.vertices[i].normal.x;
		ret->model.vertices[i].normal.y = model->model.vertices[i].normal.y;
		ret->model.vertices[i].normal.z = model->model.vertices[i].normal.z;
		ret->model.vertices[i].normal.w = model->model.vertices[i].normal.w;

		ret->model.vertices[i].sum_normal.x = model->model.vertices[i].sum_normal.x;
		ret->model.vertices[i].sum_normal.y = model->model.vertices[i].sum_normal.y;
		ret->model.vertices[i].sum_normal.z = model->model.vertices[i].sum_normal.z;
		ret->model.vertices[i].sum_normal.w = model->model.vertices[i].sum_normal.w;
	}

	ret->model.faces = new Point4[model->model.faceCount];
	for (int i = 0; i < model->model.faceCount; i++) {
		for (int j = 0; j < 3; j++) {
			ret->model.faces[i].p[j] = model->model.faces[i].p[j];
		}
	}

	ret->model.colordata = new GLfloat[model->model.vertexCount * 4 * 10];
	for (int i = 0; i < model->model.vertexCount * 4 * 10; i++) {
		ret->model.colordata[i] = 1.0f;
	}

	int count = model->model.faceCount * 3 * 4;
	ret->arrays.vertexPositionArray = new GLfloat[count];
	ret->arrays.vertexNormalArray = new GLfloat[count];
	ret->arrays.vertexCoordArray = new GLfloat[count];

	for (int i = 0; i < count; i++) {
		ret->arrays.vertexPositionArray[i] = model->arrays.vertexPositionArray[i];
		ret->arrays.vertexNormalArray[i] = model->arrays.vertexNormalArray[i];
		ret->arrays.vertexCoordArray[i] = model->arrays.vertexCoordArray[i];
	}
	return ret;
}

void Model::makeModel(const char* path) {
	FILE* f = fopen(path, "rt");
	InitVertex(f);
	InitCoordData(f);
	InitFace(f);
	fclose(f);

	InitColor();
	InitCenter();
	//InitGPUId();

	InitData();
}

void Model::InitFace(FILE* f) {
	//의미없이 셋을 날림.
	char ssss[100];
	for (int i = 0; i < 3; i++)
		fscanf(f, "%s", &ssss);
	model.faceCount = ParseStringToInt(ssss);
	model.faces = new Point4[model.faceCount];
	model.coords = new Point4[model.faceCount];
	for (int i = 0; i < model.faceCount; i++) {
		fscanf(f, "%d/%d %d/%d %d/%d\n", &model.faces[i].p[0], &model.coords[i].p[0], &model.faces[i].p[1], &model.coords[i].p[1], &model.faces[i].p[2], &model.coords[i].p[2]);
		for (int j = 0; j < 3; j++) {
			model.faces[i].p[j] --;
			model.coords[i].p[j]--;
		}
	}
}

void Model::InitCoordData(FILE* f) {
	char ssss[100];
	for (int i = 0; i < 3; i++)
		fscanf(f, "%s", &ssss);
	model.textureCount = ParseStringToInt(ssss);
	model.coorddata = new Vec4[model.textureCount];
	int a, b, c;
	for (int i = 0; i < model.textureCount; i++) {
		fscanf(f, "%f %f %f\n", &model.coorddata[i].x, &model.coorddata[i].y, &model.coorddata[i].z);
		model.coorddata[i].w = 1;
	}
}

void Model::InitVertex(FILE* f) {
	double size = 0.005;
	fscanf(f, "VERTEX = %d", &model.vertexCount);
	model.vertices = new Vertex[model.vertexCount];
	for (int i = 0; i < model.vertexCount; i++) {
		fscanf(f, "%f %f %f", &model.vertices[i].pos.x, &model.vertices[i].pos.y, &model.vertices[i].pos.z);
		model.vertices[i].pos.Mul(size);
		float a = model.vertices[i].pos.x;
		float b = model.vertices[i].pos.y;
		float c = model.vertices[i].pos.z;
	}
}

float Model::ParseStringToFloat(const char *s) {
	int negative = 1;
	int startPos = 0;
	float ret = 0;
	int length = 0;
	bool isFindPoint = false;
	float point = 1;
	if (s == NULL || *s == '\0')	return 0;
	length = strlen(s);
	if (s[0] == '-')	negative = -1;
	if (s[0] == '+' || s[0] == '-')	startPos++;
	for (int i = startPos; i < length - 1; i++) {
		if ('0' <= s[i] && s[i] <= '9') {
			ret = ret * 10 + (s[i] - '0');
			if (isFindPoint) point *= 10;
		}
		else if (s[i] == '.') {
			if (isFindPoint)	return 0;
			else	isFindPoint = true;
		}
		else return 0;
	}
	return ret * negative / point;
}

int Model::ParseStringToInt(const char *s) {
	int negative = 1;
	int startPos = 0;
	int ret = 0;
	int length = 0;
	if (s == NULL || *s == '\0')	return 0;
	length = strlen(s);
	if (s[0] == '-')	negative = -1;
	if (s[0] == '+' || s[0] == '-')	startPos++;
	for (int i = startPos; i < length; i++) {
		if ('0' <= s[i] && s[i] <= '9')	ret = ret * 10 + (s[i] - '0');
		else return 0;
	}
	return ret * negative;
}


void Model::Setup_NormalVector() {
	Setup_FaceNormalVector();
	Setup_VertexNormalVector();
}

void Model::Setup_FaceNormalVector() {
	Vec4** pos = (Vec4**)malloc(sizeof(Vec4*) * 3);
	for (int i = 0; i < 3; i++)	pos[i] = new Vec4();
	for (int i = 0; i < model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = model.faces[i].p[k];
			pos[k]->x = arrays.vertexPositionArray[(i * 3 + k) * 4 + 0];
			pos[k]->y = arrays.vertexPositionArray[(i * 3 + k) * 4 + 1];
			pos[k]->z = arrays.vertexPositionArray[(i * 3 + k) * 4 + 2];
		}
		pos[1]->Sub(*pos[0]);
		pos[2]->Sub(*pos[0]);

		arrays.faceNormalVector[i] = *Vec4::Cross(pos[1], pos[2]);
		arrays.faceNormalVector[i].Normalize();
	}
	for (int i = 0; i < 3; i++)	delete pos[i];
	free(pos);
}

void Model::Setup_VertexNormalVector() {
	for (int i = 0; i < model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = model.faces[i].p[k];
			model.vertices[vertIndex].sum_normal.Add(arrays.faceNormalVector[i]);
		}
	}

	for (int i = 0; i < model.vertexCount; i++) {
		model.vertices[i].sum_normal.Normalize();
	}

	for (int i = 0; i < model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = model.faces[i].p[k];
			arrays.vertexNormalArray[(i * 3 + k) * 4 + 0] = model.vertices[vertIndex].sum_normal.x;
			arrays.vertexNormalArray[(i * 3 + k) * 4 + 1] = model.vertices[vertIndex].sum_normal.y;
			arrays.vertexNormalArray[(i * 3 + k) * 4 + 2] = model.vertices[vertIndex].sum_normal.z;
			arrays.vertexNormalArray[(i * 3 + k) * 4 + 3] = 1;
		}
	}
}

void Model::InitData() {
	arrays.vertexPositionArray = new GLfloat[model.faceCount * 3 * 4];
	arrays.vertexNormalArray = new GLfloat[model.faceCount * 3 * 4];
	arrays.vertexCoordArray = new GLfloat[model.faceCount * 3 * 4];
	arrays.faceNormalVector = new Vec4[model.faceCount];
	Setup_VertexPositionToArray();
	Setup_CoordinationToArray();
	Setup_NormalVector();
}

void Model::Setup_VertexPositionToArray() {
	for (int i = 0; i < model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = model.faces[i].p[k];
			arrays.vertexPositionArray[(i * 3 + k) * 4 + 0] = model.vertices[vertIndex].pos.x;
			arrays.vertexPositionArray[(i * 3 + k) * 4 + 1] = model.vertices[vertIndex].pos.y;
			arrays.vertexPositionArray[(i * 3 + k) * 4 + 2] = model.vertices[vertIndex].pos.z;
			arrays.vertexPositionArray[(i * 3 + k) * 4 + 3] = 1;
		}
	}
}

void Model::Setup_CoordinationToArray() {
	for (int i = 0; i < model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int coordIndex = model.coords[i].p[k];
			arrays.vertexCoordArray[(i * 3 + k) * 2 + 0] = model.coorddata[coordIndex].x;
			arrays.vertexCoordArray[(i * 3 + k) * 2 + 1] = model.coorddata[coordIndex].y;
		}
	}
}



void Model::InitCenter() {
	Vec4 vec = Vec4();
	for (int i = 0; i < model.vertexCount; i++)	vec.Add(model.vertices[i].pos);
	vec.Divide(model.vertexCount);
	for (int i = 0; i < model.vertexCount; i++)	model.vertices[i].pos.Sub(vec);
}

void Model::InitColor() {
	model.colordata = new GLfloat[model.vertexCount * 4 * 10];
	for (int i = 0; i < model.vertexCount * 4 * 10; i++)	model.colordata[i] = 1.0f;
}


/*
void Model::InitGPUId() {
	//shaderID.Init();
	//gouraudID.Init();
}
*/