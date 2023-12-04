#include "Plane.h"

Plane::Plane(Shader* shader, Texture* diffuseTexture, Texture* specularTexture)
{
	this->shader = shader;
	this->diffuseTexture = diffuseTexture;
	this->specularTexture = specularTexture;
	vao = vbo = ebo = 0;
}


Plane::~Plane()
{

}

void Plane::InitData()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, -0.5, -50.0,  0,  0,
		 50.0, -0.5, -50.0, 50,  0,
		 50.0, -0.5,  50.0, 50, 50,
		-50.0, -0.5,  50.0,  0, 50,


	};

	unsigned int indices[] = {
		// vertex order for triangles
		0,  2,  1,  0,  3,  2
	};

	// Generate vao, vbo, ebo
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Bind the Vertex Array Object first, 
	// then bind and set vertex buffer(s), 
	// and then configure vertex attributes(s).
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Create vertex attribute pointer in VAO
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Plane::InitTexture()
{
	diffuseTexture->Init();
	specularTexture->Init();
}

void Plane::Init()
{
	// Initialize buffers
	InitData();
	// Initalize texture
	InitTexture();
}


void Plane::Draw()
{
	diffuseTexture->Use(GL_TEXTURE0);
	shader->setInt("material.diffuse", 0);
	specularTexture->Use(GL_TEXTURE1);
	shader->setInt("material.specular", 1);
	shader->setFloat("material.shininess", 10.0f);

	glBindVertexArray(vao);

	glm::mat4 model;
	model = glm::scale(scale);
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, rotationAxis);

	shader->setMat4("model", model);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Plane::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Plane::SetScale(float sx, float sy, float sz)
{
	scale.x = sx;
	scale.y = sy;
	scale.z = sz;
}

void Plane::SetRotation(float angle, float x, float y, float z)
{
	this->angle = angle;
	rotationAxis.x = x;
	rotationAxis.y = y;
	rotationAxis.z = z;
}
