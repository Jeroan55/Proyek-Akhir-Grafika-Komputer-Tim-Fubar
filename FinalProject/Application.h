#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "Plane.h"
#include "Shader.h"
#include "Texture.h"

class Application :
    public RenderEngine
{
public:
    Application();
    ~Application();
private:
	Shader *shader, *shadowShader;
	Texture *cubeDiffTex, *cubeDiffTex2, *cubeDiffTex3, * cubeDiffTex4, *cubeSpecTex, *cubeSpecTex2, *cubeSpecTex3, *cubeSpecTex4, *planeDiffTex, *planeSpecTex, *crossDiffTex;
	GLuint shaderProgram, depthMapFBO, depthMap;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	Cube *cube, *cubeb, *cubec, *cubed, *cube2, *cube2b, *cube2c, *cube3, *cube4, *cube5, *cross;
	float angle = 0;
	glm::vec3 viewPos;
	void setupPerspective();
	void setupCamera();
	void setupLighting();
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	void DrawWindow(int positionX, int positionY, int positionZ);
	void DrawPicture(int positionX, int positionY, int positionZ);
	void DrawSlab(int positionX, int positionY, int positionZ);
	void DrawCorner(int positionX, int positionY, int positionZ);
	void DrawEdge(int positionX, int positionY, int positionZ);
	void DrawDoorL(int positionX, int positionY, int positionZ);
	void DrawDoorR(int positionX, int positionY, int positionZ);
	void DrawBench(int positionX, int positionY, int positionZ);
	void DrawCarpet(int positionX, int positionY, int positionZ);
	void DrawTower(int positionX, int positionY, int positionZ);
	void DrawFloor(int positionX, int positionY, int positionZ);
	void DrawThrone(int positionX, int positionY, int positionZ);
	void DrawWall(int positionX, int positionY, int positionZ);
	void DrawWall2(int positionX, int positionY, int positionZ);

	// Add these member variables to the Application class
	float yaw;
	float pitch;
	bool firstMouse;
	double lastX;
	double lastY;
	float sensitivity;

};

