#include "ModelOBJ.h"

ModelOBJ::ModelOBJ():position(0,0,0), orientation(0,0,0), model(0) {}
ModelOBJ::~ModelOBJ(){
	if(model){
		glmDelete(model);
	}
}

bool ModelOBJ::Load(char *filename, bool addForCollision)
{
	model = glmReadOBJ(filename);
	if(!model) return false;
    glmUnitize(model);
    glmFacetNormals(model);
    glmVertexNormals(model, 90.0);
	
	if (addForCollision)
		AddToCollisionEngine();

	return true;
}

void ModelOBJ::AddToCollisionEngine()
{
	UpdateTriangleBuffer();

	size_t size = triangles.size();
	for (size_t i=0; i<size; ++i){
		mvc::CollisionManager::get()->addTriangle(
			triangles[i]
		);
	}
}

void ModelOBJ::UpdateTriangleBuffer(){
	triangles.resize(0);
	if (model){
		unsigned int i;
		GLMgroup* group;
		GLMtriangle* triangle;

		group = model->groups;
		while (group) {
			for (i = 0; i < group->numtriangles; i++) {
				triangle = &(model->triangles[(group->triangles[i])]);
				float* pA = &model->vertices[3 * triangle->vindices[0]];
				float* pB = &model->vertices[3 * triangle->vindices[1]];
				float* pC = &model->vertices[3 * triangle->vindices[2]];
				triangles.push_back(
					mvc::Triangle(
					mvc::Point(pA[0], pA[1], pA[2]), 
					mvc::Point(pB[0], pB[1], pB[2]), 
					mvc::Point(pC[0], pC[1], pC[2])
					));
			}
			group = group->next;
		}
	}
}

void ModelOBJ::Scale(float factor)
{
	glmScale(model,factor);	
	UpdateTriangleBuffer();
}

void ModelOBJ::Render()
{
	glPushMatrix();
		glTranslatef( position.x, position.y, position.z );
		glRotatef(orientation.x, 1.0, 0.0, 0.0);
		glRotatef(orientation.y, 0.0, 1.0, 0.0);
		glRotatef(orientation.z, 0.0, 0.0, 1.0);
		glmDraw(model, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE );
	glPopMatrix();
}

void ModelOBJ::SetPosition(float x, float y, float z){
	position.x=x;
	position.y=y;
	position.z=z;
}


void ModelOBJ::SetOrientation(float angX, float angY, float angZ){
	orientation.x=angX;
	orientation.y=angY;
	orientation.z=angZ;
}
