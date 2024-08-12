//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GraphicsObject_FlatTexture.h"
#include "TextureMan.h"
#include "Mesh.h"
#include "Camera.h"

using namespace Azul;

extern Camera *pCam;

GraphicsObject_FlatTexture::GraphicsObject_FlatTexture(const Mesh *const _pMesh, const ShaderObject *const _pShaderObj, Texture::Name _name)
	: GraphicsObject(_pMesh, _pShaderObj), textName(_name)
{
	// check the base class
	assert(this->pMesh);
	assert(this->pShaderObj);
	assert(this->poWorld);
}

void GraphicsObject_FlatTexture::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	GLuint textureID = TextureMan::FindID(this->textName);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphicsObject_FlatTexture::SetDataGPU()
{
	// use this shader
	this->pShaderObj->SetActive();

	// set the vao
	glBindVertexArray(this->GetMesh()->vao);

	Mat4 world = this->GetWorld();
	Mat4 view = pCam->getViewMatrix();
	Mat4 proj = pCam->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *) &view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *) &world);
}

void GraphicsObject_FlatTexture::Draw()
{
	//The starting point of the IBO index buffer object
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_FlatTexture::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

//--- End of File -------------------------------------------------------------

