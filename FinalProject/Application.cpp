#include "Application.h"

Application::Application()
{
	// ... (existing member variables)

	// Camera parameters

	screenWidth = 1500;
	cameraPos = glm::vec3(-0.1f, 0.2f, 0.5f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	firstMouse = true;
	lastX = 400.0;
	lastY = 300.0;
	sensitivity = 0.1f;

	ambientLight = glm::vec3(0.2f, 0.2f, 0.2f);
	directionalLight.direction = glm::vec3(-0.5f, -1.0f, -0.5f);
	directionalLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight.position = glm::vec3(0.0f, 1.0f, 0.0f);
	pointLight.constant = 1.0f;
	pointLight.linear = 0.09f;
	pointLight.quadratic = 0.032f;

	// Camera movement speed
	
	// ... (existing member functions)

	// New member functions for camera control
	
}

Application::~Application()
{
}

void Application::setupPerspective()
{
	//Cone of vision
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);

	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Application::setupCamera()
{
	//Lokasi dan angle kamera
	viewPos = glm::vec3(0, 2, -10);
	glm::mat4 view = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	shader->setMat4("view", view);
}

void Application::setupLighting()
{
	//Arah, posisi, dan warna cahaya
	glm::vec3 lightPos = glm::vec3( 10, 20, -10);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);
	//set ambient cahaya
	shader->setVec3("ambientLight", ambientLight);

	//set arah cahaya
	shader->setVec3("dirLight.direction", directionalLight.direction);
	shader->setVec3("dirLight.color", directionalLight.color);

	//set poin cahaya
	shader->setVec3("pointLight.position", pointLight.position);
	shader->setVec3("pointLight.color", pointLight.color);
	shader->setFloat("pointLight.constant", pointLight.constant);
	shader->setFloat("pointLght.linear", pointLight.linear);
	shader->setFloat("pointLight.quadratic", pointLight.quadratic);

}

void Application::Init()
{
	// Build a lighting map shader
	shader = new Shader("textured.vert", "textured.frag");
	shader->Init();

	//Inisialisasi objek CUBE 1 beserta teksturnya
	cubeDiffTex = new Texture("White_stone.jpg");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("Solid_white.png");
	cubeSpecTex->Init();
	cube = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cube->Init();
	cube->SetScale(0.01f, 0.01f, 0.01f);
	cubeb = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cubeb->Init();
	cubeb->SetScale(0.02f, 0.02f, 0.02f);
	cubec = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cubec->Init();
	cubec->SetScale(0.04f, 0.01f, 0.02f);
	cubed = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cubed->Init();
	cubed->SetScale(0.02f, 0.99f, 0.02f);
	crossDiffTex = new Texture("Cross.jpg");
	cross = new Cube(shader, crossDiffTex, cubeSpecTex);
	cross->Init();
	cross->SetScale(0.12f, 0.25f, 0.01f);

	//Inisialisasi objek CUBE 2 beserta teksturnya
    cubeDiffTex2 = new Texture("dark_red.jpg");
	cubeDiffTex2->Init();
	cubeSpecTex2 = new Texture("dark_red.jpg");
	cubeSpecTex2->Init();
	cube2 = new Cube(shader, cubeDiffTex2, cubeSpecTex2);
	cube2->Init();
	cube2->SetScale(0.1f, 0.005f, 0.5f);
	cube2b = new Cube(shader, cubeDiffTex2, cubeSpecTex2);
	cube2b->Init();
	cube2b->SetScale(0.02f, 0.1f, 0.5f);
	cube2c = new Cube(shader, cubeDiffTex2, cubeSpecTex2);
	cube2c->Init();
	cube2c->SetScale(0.02f, 0.02f, 0.02f);

	//Inisialisasi objek CUBE 3 beserta teksturnya
	cubeDiffTex3 = new Texture("stone.jpg");
	cubeDiffTex3->Init();
	cubeSpecTex3 = new Texture("stone.jpg");
	cubeSpecTex3->Init();
	cube3 = new Cube(shader, cubeDiffTex3, cubeSpecTex3);
	cube3->Init();
	cube3->SetScale(0.4f, 0.01f, 0.5f);

	//Inisialisasi objek CUBE 4 beserta teksturnya
	cube4 = new Cube(shader, cubeDiffTex3, cubeSpecTex3);
	cube4->Init();
	cube4->SetScale(0.4f, 0.5f, 0.01f);
	//Inisialisasi objek CUBE 4 beserta teksturnya
	cube5 = new Cube(shader, cubeDiffTex3, cubeSpecTex3);
	cube5->Init();
	cube5->SetScale(0.01f, 0.5f, 0.4f);
	// setup perspective 
	setupPerspective();
	// setup camera
	setupCamera();
	// setup lighting
	setupLighting();

}

void Application::DeInit()
{
	delete cube, cubeb, cubec, cubed, cube2, cube2b, cube2c, cube3, cube4, cross;
}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	const float cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	// Handle camera rotation using mouse input
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Clamp pitch to prevent flipping
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// Update camera front direction
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void Application::Update(double deltaTime)
{
	glm::vec3 cameraTarget = cameraPos + cameraFront;
	glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	shader->setMat4("view", view);

	//angle += (float)((deltaTime * 1.5f) / 1000);
	angle += 0;
	cube->SetRotation(angle, 0, 1, 0);
	cubeb->SetRotation(angle, 0, 1, 0);
	cubec->SetRotation(angle, 0, 1, 0);
	cubed->SetRotation(angle, 0, 1, 0);
	cube2->SetRotation(angle, 0, 1, 0);
	cube2b->SetRotation(angle, 0, 1, 0);
	cube2c->SetRotation(angle, 0, 1, 0);
	cube3->SetRotation(angle, 0, 1, 0);
	cube4->SetRotation(angle, 0, 1, 0);
	cube5->SetRotation(angle, 0, 1, 0);
	cross->SetRotation(angle, 0, 1, 0);
}

void Application::Render()
{
	


	// Reset framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Ukuran Window
	glViewport(0, 0, this->screenWidth, this->screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Warna Background
	glClearColor(0.124f, 0.174f, 0.212f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	
	//Render Objek

	DrawFloor(0, 0, -5);
	DrawFloor(0, 70, -5);
	DrawFloor(0, 70, -4);
	DrawWall(0, 0, -60);
	DrawWall(0, 0, 140);
	DrawWall2(-70, 0, -2);
	DrawWall2(55, 0, -2);

	DrawSlab(0, 1, -20);
	DrawSlab(5, 1, -21);
	DrawSlab(4, 1, -22);
	DrawSlab(-2, 1, -18);
	DrawSlab(-8, 1, -20);
	DrawCarpet(-2, 0, -2);
	DrawEdge(-36, -1, -2);
	DrawEdge(25, -1, -2);
	
	DrawTower(-55, 0, -30);
	DrawTower(35, 0, -30);
	DrawTower(-55, 0, 30);
	DrawTower(35, 0, 30);
	DrawTower(-55, 0, 90);
	DrawTower(35, 0, 90);
	DrawBench(20, 0, 30);
	DrawBench(20, 0, 15);
	DrawBench(20, 0, 0);
	DrawBench(20, 0, -15);
	DrawBench(20, 0, -30);
	DrawBench(-20, 0, 30);
	DrawBench(-20, 0, 15);
	DrawBench(-20, 0, 0);
	DrawBench(-20, 0, -15);
	DrawBench(-20, 0, -30);
	
	DrawWindow(51, 14, 16);
	DrawWindow(51, 14, 80);
	DrawWindow(-70, 14, 16);
	DrawWindow(-70, 14, 80);
	DrawThrone(1, 5, 60);
	DrawDoorL(-3, 0, -28);
	DrawDoorR(5, 0, -28);
	DrawPicture(-1, 2, 140);
		
	glDisable(GL_DEPTH_TEST);
}
void Application::DrawPicture(int positionX, int positionY, int positionZ) {
	cross->SetPosition(positionX, positionY, positionZ);
	cross->Draw();
}

void Application::DrawWindow(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 37; j++) {
			for (int k = 1; k <= 2; k++) {
				int posX = i -2 + positionX;
				int posY = j + positionY;
				int posZ = k - 3 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 35; i++) {
		int posx = positionX;
		int posy = i + positionY;
		int posz = positionZ - 7;
		cube->SetPosition(posx, posy, posz);
		cube->Draw();
	}
	for (int i = 1; i <= 35; i++) {
		int posx = positionX;
		int posy = i + positionY;
		int posz = positionZ - 13;
		cube->SetPosition(posx, posy, posz);
		cube->Draw();
	}
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 37; j++) {
			for (int k = 1; k <= 2; k++) {
				int posX = i - 2 + positionX;
				int posY = j + positionY;
				int posZ = k - 1 + positionZ - 20;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 2; j++) {
			for (int k = 1; k <= 20; k++) {
				int posX = i - 2 + positionX;
				int posY = j + positionY;
				int posZ = k - 1 + positionZ - 20;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 20; i++) {
		int posx = positionX;
		int posy = positionY;
		int posz = positionZ - i;
		cube->SetPosition(posx, posy, posz);
		cube->Draw();
	}
	for (int i = 1; i <= 20; i++) {
		int posx = positionX;
		int posy = positionY + 20;
		int posz = positionZ - i;
		cube->SetPosition(posx, posy, posz);
		cube->Draw();
	}
	for (int i = 1; i <= 20; i++) {
		int posx = positionX;
		int posy = positionY + 36;
		int posz = positionZ - i;
		cube->SetPosition(posx, posy, posz);
		cube->Draw();
	}
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 2; j++) {
			for (int k = 1; k <= 2; k++) {
				cube->SetPosition(positionX - i + 1, 36 + positionY + j, positionZ - 3 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 37 + positionY + j, positionZ - 3 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 38 + positionY + j, positionZ - 4 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 39 + positionY + j, positionZ - 4 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 40 + positionY + j, positionZ - 5 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 41 + positionY + j, positionZ - 6 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 42 + positionY + j, positionZ - 7 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 42 + positionY + j, positionZ - 8 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 43 + positionY + j, positionZ - 9 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 43 + positionY + j, positionZ - 10 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 36 + positionY + j, positionZ - 21 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 37 + positionY + j, positionZ - 21 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 38 + positionY + j, positionZ - 20 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 39 + positionY + j, positionZ - 20 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 40 + positionY + j, positionZ - 19 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 41 + positionY + j, positionZ - 18 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 42 + positionY + j, positionZ - 17 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 42 + positionY + j, positionZ - 16 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 43 + positionY + j, positionZ - 15 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 43 + positionY + j, positionZ - 14 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 43 + positionY + j, positionZ - 13 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 43 + positionY + j, positionZ - 12 + k);
				cube->Draw();
				cube->SetPosition(positionX - i + 1, 43 + positionY + j, positionZ - 11+ k);
				cube->Draw();
			}
		}
	}
}
void Application::DrawSlab(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 1; j++) {
			int posx = i + positionX;
			int posy = 1 + positionY;
			int posz = j + positionZ;
			cubec->SetPosition(posx, posy, posz);
			cubec->Draw();
		}
	}
}

void Application::DrawBench(int positionX, int positionY, int positionZ) {

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			for (int k = 1; k <= 5; k++) {
				int posX = i * 10 - 30 + positionX;
				int posY = j + positionY;
				int posZ = k + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 1; j++) {
			for (int k = 1; k <= 1; k++) {
				int posX = i - 20 + positionX;
				int posY = j + 1 + positionY;
				int posZ = k + 3 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 21; i++) {
		for (int j = 1; j <= 1; j++) {
			for (int k = 1; k <= 5; k++) {
				int posX = i - 21 + positionX;
				int posY = j + 3 + positionY;
				int posZ = k + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 21; i++) {
		for (int j = 1; j <= 6; j++) {
			for (int k = 1; k <= 1; k++) {
				int posX = i - 21 + positionX;
				int posY = j + 3 + positionY;
				int posZ = k + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 3; j++) {
			for (int k = 1; k <= 5; k++) {
				int posX = i * 20 - 40 + positionX;
				int posY = j + 3 + positionY;
				int posZ = k + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
}

void Application::DrawCarpet(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 4; j++) {
			int posx = i + positionX;
			int posy = 1 + positionY;
			int posz = j + positionZ;
			cube2->SetPosition(posx, posy, posz);
			cube2->Draw();
		}
	}
}

void Application::DrawEdge(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 4; j++) {
			int posx = i + positionX;
			int posy = 1 + positionY;
			int posz = j + positionZ;
			cube2b->SetPosition(posx, posy, posz);
			cube2b->Draw();
		}
	}
}

void Application::DrawCorner(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 2; j++) {
			int posx = i + positionX;
			int posy = j + positionY;
			int posz =  positionZ;
			cubed->SetPosition(posx, posy, posz);
			cubed->Draw();
		}
	}
}

void Application::DrawThrone(int positionX, int positionY, int positionZ) {
	//Center
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <=10; j++) {
			int posx = i - 17 + positionX;
			int posy = 1 + positionY;
			int posz = j + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 2; j++) {
			for (int k = 1; k <= 3; k++) {
				int posx = i - 10 + positionX;
				int posy = j + 1 + positionY;
				int posz = k + 5 + positionZ;
				cube2c->SetPosition(posx, posy, posz);
				cube2c->Draw();
			}
		}
	}
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 5; j++) {
			int posx = i - 17 + positionX;
			int posy = j - 5 + positionY;
			int posz = 1 + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	for (int i = 1; i <= 18; i++) {
		int posx = i - 16 + positionX;
		int posy = positionY;
		int posz = positionZ;
		cubeb->SetPosition(posx, posy, posz);
		cubeb->Draw();
	}
	for (int i = 1; i <= 18; i++) {
		int posx = i - 16 + positionX;
		int posy = -1 + positionY;
		int posz = -1 + positionZ;
		cubeb->SetPosition(posx, posy, posz);
		cubeb->Draw();
	}
	for (int i = 1; i <= 18; i++) {
		int posx = i - 16 + positionX;
		int posy = -2 + positionY;
		int posz = -2 + positionZ;
		cubeb->SetPosition(posx, posy, posz);
		cubeb->Draw();
	}
	for (int i = 1; i <= 18; i++) {
		int posx = i - 16 + positionX;
		int posy = -3 + positionY;
		int posz = -3 + positionZ;
		cubeb->SetPosition(posx, posy, posz);
		cubeb->Draw();
	}
	for (int i = 1; i <= 18; i++) {
		int posx = i - 16 + positionX;
		int posy = -4 + positionY;
		int posz = -4 + positionZ;
		cubeb->SetPosition(posx, posy, posz);
		cubeb->Draw();
	}
	for (int i = 1; i <= 18; i++) {
		int posx = i - 16 + positionX;
		int posy = -5 + positionY;
		int posz = -5 + positionZ;
		cubeb->SetPosition(posx, posy, posz);
		cubeb->Draw();
	}
	for (int i = 1; i <= 6; i++) {
		for (int j= 1; j <= 6; j++) {
			int posx = - 16 + positionX;
			int posy = i -5 + positionY;
			int posz = j - 6 + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 6; j++) {
			int posx = 3 + positionX;
			int posy = i - 5 + positionY;
			int posz = j - 6 + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	//Left
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 10; j++) {
			int posx = i - 20 + positionX;
			int posy = positionY;
			int posz = j + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int posx = i - 20 + positionX;
			int posy = j - 5 + positionY;
			int posz = 1 + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 10; j++) {
			int posx = i - 40 + positionX;
			int posy = positionY - 1;
			int posz = j + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 3; j++) {
			int posx = i - 40 + positionX;
			int posy = j - 5 + positionY;
			int posz = 1 + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	//Right
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 10; j++) {
			int posx = i  + 3 + positionX;
			int posy = positionY;
			int posz = j + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int posx = i + 3 + positionX;
			int posy = j - 5 + positionY;
			int posz = 1 + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 10; j++) {
			int posx = i + 7 + positionX;
			int posy = positionY - 1;
			int posz = j + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 3; j++) {
			int posx = i + 7 + positionX;
			int posy = j - 5 + positionY;
			int posz = 1 + positionZ;
			cubeb->SetPosition(posx, posy, posz);
			cubeb->Draw();
		}
	}
}

void Application::DrawDoorL(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 20; j++) {
			for (int k = 1; k <= 1; k++) {
				int posX = i - 10 + positionX;
				int posY = j + positionY;
				int posZ = k + positionZ;
				cubeb->SetPosition(posX, posY, posZ);
				cubeb->Draw();
			}
		}
	}
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 20; j++) {
			for (int k = 1; k <= 2; k++) {
				int posX = i - 11 + positionX;
				int posY = j + positionY;
				int posZ = k + positionZ;
				cubeb->SetPosition(posX, posY, posZ);
				cubeb->Draw();
			}
		}
	}
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 1; j++) {
			for (int k = 1; k <= 2; k++) {
				int posX = i - 10 + positionX;
				int posY = j + 20 + positionY;
				int posZ = k + positionZ;
				cubeb->SetPosition(posX, posY, posZ);
				cubeb->Draw();
			}
		}
	}
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 1; j++) {
			for (int k = 1; k <= 2; k++) {
				int posX = i - 10 + positionX;
				int posY = j + 5 + positionY;
				int posZ = k + positionZ;
				cubeb->SetPosition(posX, posY, posZ);
				cubeb->Draw();
			}
		}
	}
}
void Application::DrawDoorR(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 20; j++) {
			for (int k = 1; k <= 1; k++) {
				int posX = i - 10 + positionX;
				int posY = j + positionY;
				int posZ = k + positionZ;
				cubeb->SetPosition(posX, posY, posZ);
				cubeb->Draw();
			}
		}
	}
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 20; j++) {
			for (int k = 1; k <= 2; k++) {
				int posX = i - 3 + positionX;
				int posY = j + positionY;
				int posZ = k + positionZ;
				cubeb->SetPosition(posX, posY, posZ);
				cubeb->Draw();
			}
		}
	}
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 1; j++) {
			for (int k = 1; k <= 2; k++) {
				int posX = i - 10 + positionX;
				int posY = j + 20 + positionY;
				int posZ = k + positionZ;
				cubeb->SetPosition(posX, posY, posZ);
				cubeb->Draw();
			}
		}
	}
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 1; j++) {
			for (int k = 1; k <= 2; k++) {
				int posX = i - 10 + positionX;
				int posY = j + 5 + positionY;
				int posZ = k + positionZ;
				cubeb->SetPosition(posX, posY, posZ);
				cubeb->Draw();
			}
		}
	}
}

void Application::DrawFloor(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int posx = i - 3 + positionX;
			int posy = positionY;
			int posz = j + 3 + positionZ;
			cube3->SetPosition(posx, posy, posz);
			cube3->Draw();
		}
	}
}

void Application::DrawWall2(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 2; j++) {
			for (int k = 1; k <= 5; k++) {
				int posx = i - 3 + positionX;
				int posy = j - 1 + positionY;
				int posz = k + positionZ;
				cube5->SetPosition(posx, posy, posz);
				cube5->Draw();
			}
			
		}
	}
}
void Application::DrawWall(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 2; j++) {
			for (int k = 1; k <= 4; k++) {
				int posx = i - 3 + positionX;
				int posy = j - 1 + positionY;
				int posz = k + positionZ;
				cube4->SetPosition(posx, posy, posz);
				cube4->Draw();
			}
		}
	}
}

void Application::DrawTower(int positionX, int positionY, int positionZ) {
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 1; j++) {
			int posX = i - 6 + positionX;
			int posY = 1 + positionY;
			int posZ = j + positionZ;
			cube->SetPosition(posX, posY, posZ);
			cube->Draw();
		}
	}
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 10; j++) {
			int posX = i - 6+ positionX;
			int posY = 1 + positionY;
			int posZ = j + positionZ;
			cube->SetPosition(posX, posY, posZ);
			cube->Draw();
		}
	}
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 1; j++) {
			int posX = i - 6 + positionX;
			int posY = 1 + positionY;
			int posZ = j + 9 + positionZ;
			cube->SetPosition(posX, posY, posZ);
			cube->Draw();
		}
	}
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 10; j++) {
			int posX = i + 3 + positionX;
			int posY = 1 + positionY;
			int posZ = j + positionZ;
			cube->SetPosition(posX, posY, posZ);
			cube->Draw();
		}
	}
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 12; j++) {
			for (int k = 1; k <= 8; k++) {
				int posX = i - 5 + positionX;
				int posY = j + positionY;
				int posZ = k + 1 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 12; j++) {
			for (int k = 1; k <= 8; k++) {
				int posX = i + 2 + positionX;
				int posY = j + positionY;
				int posZ = k + 1 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 12; j++) {
			for (int k = 1; k <= 1; k++) {
				int posX = i - 4 + positionX;
				int posY = j + positionY;
				int posZ = k + 1 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 12; j++) {
			for (int k = 1; k <= 1; k++) {
				int posX = i - 4 + positionX;
				int posY = j + positionY;
				int posZ = k + 8 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	//Layer 2
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			int posX = i - 6 + positionX;
			int posY = 13 + positionY;
			int posZ = j + positionZ;
			cube->SetPosition(posX, posY, posZ);
			cube->Draw();
		}
	}
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			int posX = i * 3 - 8 + positionX;
			int posY = 13 + j + positionY;
			int posZ = 2 + positionZ;
			cube->SetPosition(posX, posY, posZ);
			cube->Draw();
		}
	}
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 8; j++) {
			int posX = i * 9 - 14 + positionX;
			int posY = 13 + j + positionY;
			int posZ = 5 + positionZ;
			cube->SetPosition(posX, posY, posZ);
			cube->Draw();
		}
	}
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 8; j++) {
			int posX = i * 9 - 14 + positionX;
			int posY = 13 + j + positionY;
			int posZ = 8 + positionZ;
			cube->SetPosition(posX, posY, posZ);
			cube->Draw();
		}
	}
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			int posX = i * 3 - 8 + positionX;
			int posY = 13 + j + positionY;
			int posZ = 10 + positionZ;
			cube->SetPosition(posX, posY, posZ);
			cube->Draw();
		}
	}
	//Layer 3
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			int posX = i - 6 + positionX;
			int posZ = j + positionZ;
			cube->SetPosition(posX, 22, posZ);
			cube->Draw();
		}
	}
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 3; k++) {
				int posX = i - 5 + positionX;
				int posY = j + 22 + positionY;
				int posZ = k + 1 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 3; k++) {
				int posX = i + positionX;
				int posY = j + 22 + positionY;
				int posZ = k + 1 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 3; k++) {
				int posX = i - 5 + positionX;
				int posY = j + 22 + positionY;
				int posZ = k + 6 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 3; k++) {
				int posX = i + positionX;
				int posY = j + 22 + positionY;
				int posZ = k + 6 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	//Layer 4
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			int posX = i - 6 + positionX;
			int posY = 27 + positionY;
			int posZ = j + positionZ;
			cube->SetPosition(posX, posY, posZ);
			cube->Draw();
		}
	}
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 9; j++) {
			for (int k = 1; k <= 8; k++) {
				int posX = i - 5 + positionX;
				int posY = j + 27 + positionY;
				int posZ = k + 1 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 9; j++) {
			for (int k = 1; k <= 8; k++) {
				int posX = i + 2 + positionX;
				int posY = j + 27 + positionY;
				int posZ = k + 1 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 9; j++) {
			for (int k = 1; k <= 1; k++) {
				int posX = i - 4 + positionX;
				int posY = j + 27 + positionY;
				int posZ = k + 1 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 9; j++) {
			for (int k = 1; k <= 1; k++) {
				int posX = i - 4 + positionX;
				int posY = j + 27 + positionY;
				int posZ = k + 8 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 6; k++) {
				int posX = i - 4 + positionX;
				int posY = j + 36 + positionY;
				int posZ = k + 2 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 1; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 6; k++) {
				int posX = i + 1 + positionX;
				int posY = j + 36 + positionY;
				int posZ = k + 2 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 1; k++) {
				int posX = i - 3 + positionX;
				int posY = j + 36 + positionY;
				int posZ = k + 2 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 1; k++) {
				int posX = i - 3 + positionX;
				int posY = j + 36 + positionY;
				int posZ = k + 7 + positionZ;
				cube->SetPosition(posX, posY, posZ);
				cube->Draw();
			}
		}
	}
}


int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Cube Example", 
		800, 600, 
		false, 
		false);
}