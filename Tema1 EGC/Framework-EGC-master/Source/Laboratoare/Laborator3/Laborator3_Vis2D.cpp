#include "Laborator3_Vis2D.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

float backgroundTime = 0.0f;
float backgroundColor = 0.0f;
double actualTime = Engine::GetElapsedTime();
float lastTime = 0.0f;
float intervalBetween = 2.0f;
double angularStep = 0.0f;
float rotationSpeed = 1.0f;
float step = 0.01f;
float goPew = 0.1f;
int enemyNumber = 10;
float scaleAnimation = 0.0f;
bool first = true, second = true, third = true;
// culori alese pentru obiecte
glm::vec3 blue = glm::vec3(0.2f, 0.6f, 1);
glm::vec3 purple = glm::vec3(0.6, 0, 0.6f);
glm::vec3 pink = glm::vec3(1, 0.6f, 0.8f);
glm::vec3 yellow = glm::vec3(1, 1, 0);
glm::vec3 green = glm::vec3(0, 1, 0);
glm::vec3 orange = glm::vec3(1, 0.4f, 0.4f);

Laborator3_Vis2D::Laborator3_Vis2D()
{
}

Laborator3_Vis2D::~Laborator3_Vis2D()
{
}

void Laborator3_Vis2D::Init() // MODELARE OBIECTE
{
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	cameraInput->SetActive(false);


	logicSpace.x = 0;		// logic x
	logicSpace.y = 0;		// logic y
	logicSpace.width = 18;	// logic width
	logicSpace.height = 18;	// logic height
	glm::vec3 corner = glm::vec3(0, 0, 0); // pozitie de start pentru toate obiectele, dupa urmeaza sa fie translatate corespunzator

	 // mesh spaceShip
	Mesh* spaceShip = Object2D::CreateSpaceShip("spaceShip", corner, yellow);
	AddMeshToList(spaceShip);

	// mesh score
	Mesh* score = Object2D::CreateScore("score", corner, pink);
	AddMeshToList(score);

	// mesh inamic simplu - culoare albastra
	Mesh* enemyShip = Object2D::CreateSpaceShip("enemyShip", corner, blue);
	AddMeshToList(enemyShip);

	// mesh inamic cu doua vieti - culoare mov
	Mesh* smartEnemyShip = Object2D::CreateSpaceShip("smartEnemyShip", corner, purple);
	AddMeshToList(smartEnemyShip);

	// mesh inamic scalat - culoare portocalie
	Mesh* littleEnemyShip = Object2D::CreateSpaceShip("littleEnemyShip", corner, orange);
	AddMeshToList(littleEnemyShip);

	// mesh proiectil
	Mesh* pewpew = Object2D::CreatePewPew("pewpew", corner, green);
	AddMeshToList(pewpew);
}

// 2D visualization matrix
glm::mat3 Laborator3_Vis2D::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
	float sx, sy, tx, ty;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	tx = viewSpace.x - sx * logicSpace.x;
	ty = viewSpace.y - sy * logicSpace.y;

	return glm::transpose(glm::mat3(sx, 0.0f, tx,
		0.0f, sy, ty,
		0.0f, 0.0f, 1.0f)
	);
}

// functie pentru sfarsitul jocului
void Laborator3_Vis2D::TheEnd(float deltaTimeSeconds) {
	if (first == false && second == false && third == false) {
		if (backgroundTime <= 2) {
			SetViewportArea(viewSpace, glm::vec3(backgroundColor, 0, 0), true);
			if (backgroundColor <= 1) {  // maxim 1 pentru ca rosu este (1, 0, 0)
				backgroundColor += deltaTimeSeconds * 0.45f;
			}
			backgroundTime += deltaTimeSeconds;
		}
		else
			SetViewportArea(viewSpace, glm::vec3(1, 0, 0), true); // ramane ecranul rosu

		for (int i = 0; i < moreEnemy.size(); i++) {
			moreEnemy[i].speed = 0;
		}
		spaceShip.speed = 0;
		rotationSpeed = 0;
		RenderHero();
		RenderEnemy();
		for (int i = 0; i < morePewPew.size(); i++) {
			morePewPew[i].speed = 0;
		}
		RenderPew();
	}
}

// functie de generare a inamicilor
void Laborator3_Vis2D::GenerateEnemy() {
	if (actualTime < Engine::GetElapsedTime() - intervalBetween) {
		if (intervalBetween >= 0.5f) {
			intervalBetween -= 0.04f;
		}
		enemy enemyObject;
		glm::vec3 colorsVec[] = { blue, purple };
		int randomize = rand() % 2;
		enemyObject.chosenColor = colorsVec[randomize];

		int singleLife = 1, doubleLife = 2;
		// daca inamicul este albastru, areo viata
		if (enemyObject.chosenColor == blue) {
			enemyObject.life = singleLife;
		}

		// daca inamicul este mov, ii asociez doua vieti
		if (enemyObject.chosenColor == purple) {
			enemyObject.life = doubleLife;
		}
		// adaugare inamici rand pe rand in vector
		moreEnemy.push_back(enemyObject);
		actualTime = Engine::GetElapsedTime();
	}
}

void Laborator3_Vis2D::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);
	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	camera->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	camera->Update();
}

// functie de randare a inamicilor
void Laborator3_Vis2D::RenderEnemy() {
	for (int i = 0; i < moreEnemy.size(); i++) {
		// daca va fi aleasa random culoarea albastra, se deseneaza inamicul cu o viata
		if (moreEnemy[i].chosenColor == blue) {
			modelMatrix = visMatrix * Transform2D::Translate(moreEnemy[i].x, moreEnemy[i].y);
			modelMatrix *= Transform2D::Rotate((float)moreEnemy[i].angle);
			modelMatrix *= Transform2D::Scale(1.2f, 1.2f);
			RenderMesh2D(meshes["enemyShip"], shaders["VertexColor"], modelMatrix);
		}

		// daca va fi aleasa random culoarea mov, se deseneaza inamicul cu doua vieti
		if (moreEnemy[i].chosenColor == purple) {
			modelMatrix = visMatrix * Transform2D::Translate(moreEnemy[i].x, moreEnemy[i].y);
			modelMatrix *= Transform2D::Rotate((float)moreEnemy[i].angle);
			modelMatrix *= Transform2D::Scale(1.2f, 1.2f);
			if (moreEnemy[i].doScale) {
				modelMatrix = visMatrix * Transform2D::Translate(moreEnemy[i].x, moreEnemy[i].y);
				modelMatrix *= Transform2D::Rotate((float)moreEnemy[i].angle);
				// scalare la jumatate
				modelMatrix *= Transform2D::Scale(0.6f, 0.6f);
				RenderMesh2D(meshes["littleEnemyShip"], shaders["VertexColor"], modelMatrix);
			}
			RenderMesh2D(meshes["smartEnemyShip"], shaders["VertexColor"], modelMatrix);
		}
	}
}

// functie de randare a proiectilelor
void Laborator3_Vis2D::RenderPew() {
	for (int i = 0; i < morePewPew.size(); i++) {
		morePewPew[i].y += goPew * sin((float)(morePewPew[i].angle)) * morePewPew[i].speed;
		morePewPew[i].x += goPew * cos((float)(morePewPew[i].angle)) * morePewPew[i].speed;

		modelMatrix = visMatrix * Transform2D::Translate(morePewPew[i].x - spaceShip.length / 2, morePewPew[i].y - spaceShip.length / 2);
		modelMatrix *= Transform2D::Rotate((float)(morePewPew[i].angle - M_PI / 2));
		RenderMesh2D(meshes["pewpew"], shaders["VertexColor"], modelMatrix);
	}
}

// functie de randare a navei spatiale
void Laborator3_Vis2D::RenderHero() {
	modelMatrix = visMatrix * Transform2D::Translate(spaceShip.x, spaceShip.y);
	modelMatrix *= Transform2D::Rotate((float)angularStep);
	RenderMesh2D(meshes["spaceShip"], shaders["VertexColor"], modelMatrix);
}

void Laborator3_Vis2D::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// Sets the screen area where to draw - the left half of the window
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0), true);

	// Compute the 2D visualization matrix
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

	DrawScene(visMatrix);

	// sfarsitul jocului
	TheEnd(deltaTimeSeconds);
}

void Laborator3_Vis2D::DrawScene(glm::mat3 visMatrix) // DESENARE OBIECTE
{
	// generare inamici de tipul structurii enemy
	GenerateEnemy();

	// prima viata
	if (first == true) {
		modelMatrix = visMatrix * Transform2D::Translate(16, 15.5f);
		modelMatrix *= Transform2D::Scale(0.5f, 0.8f);
		RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);
	}

	// a doua viata
	if (second == true) {
		modelMatrix = visMatrix * Transform2D::Translate(16.25f, 15.5f);
		modelMatrix *= Transform2D::Scale(0.5f, 0.8f);
		RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);
	}

	// a treia viata
	if (third == true) {
		modelMatrix = visMatrix * Transform2D::Translate(16.5f, 15.5f);
		modelMatrix *= Transform2D::Scale(0.5f, 0.8f);
		RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);
	}

	// nava mama
	RenderHero();

	// proiectil
	RenderPew();

	// inamici
	for (int i = 0; i < moreEnemy.size(); i++) {
		float distOX = spaceShip.x - moreEnemy[i].x;
		float distOY = spaceShip.y - moreEnemy[i].y;
		float distMeEnemy = sqrt(distOX * distOX + distOY * distOY);
		float dX = (float)(step * (distOX / distMeEnemy));
		float dY = (float)(step * (distOY / distMeEnemy));

		moreEnemy[i].x += dX * moreEnemy[i].speed; // coordonata de translatare pe ox
		moreEnemy[i].y += dY * moreEnemy[i].speed; // coordonata de translatare pe oy
		moreEnemy[i].angle = (float)(atan2(distOY, distOX) + M_PI / 2); // unghiul dintre mine si inamic

		int collisionMeEnemy = 0;

		// verificare coliziune intre mine si inamici
		if (abs(spaceShip.x - moreEnemy[i].x) < ((spaceShip.length + moreEnemy[i].length) / 2 - 0.3f) &&
			abs(spaceShip.y - moreEnemy[i].y) < ((spaceShip.length + moreEnemy[i].length) / 2 - 0.3f)) {
			collisionMeEnemy = 1;
		}

		// daca exista
		if (collisionMeEnemy == 1) {
			moreEnemy.erase(moreEnemy.begin() + i); // sterg inamicul
			if (first == true && second == false && third == false) {
				first = false;
			}
			if (first == true && second == true && third == false) {
				second = false;
			}
			third = false;
			continue; // trece la urmatorul inamic, cu acesta a terminat
		}

		// daca nu exista
		if (collisionMeEnemy == 0) {
			RenderEnemy();
		}

		// verificare coliziune intre proiectil si inamic
		for (int k = 0; k < morePewPew.size(); k++) {
			if (abs(morePewPew[k].x - moreEnemy[i].x) < ((morePewPew[k].length + moreEnemy[i].length) / 2 + 0.5f) &&
				abs(morePewPew[k].y - moreEnemy[i].y) < ((morePewPew[k].length + moreEnemy[i].length) / 2 + 0.5f)) {
				morePewPew.erase(morePewPew.begin() + k); // sterg proiectilul

				// inamicul albastru are o viata
				if (moreEnemy[i].life == 1) {
					moreEnemy[i].life--;
				}

				// inamicul mov, daca ramane cu o viata, i se dubleaza viteza si se scaleaza la jumatate
				if (moreEnemy[i].life == 2) {
					moreEnemy[i].life--;
					moreEnemy[i].speed *= 2;
					moreEnemy[i].doScale = true;
				}

				// inamicii ramasi fara viata sunt stersi
				if (moreEnemy[i].life == 0) {
					moreEnemy.erase(moreEnemy.begin() + i);
				}
				return;
			}
		}
	}

	// stergere proiectil daca depaseste ecranul
	for (int i = 0; i < morePewPew.size(); i++) {
		if (morePewPew[i].x > logicSpace.width || morePewPew[i].y > logicSpace.height || morePewPew[i].x < 0 || morePewPew[i].y < 0) {
			morePewPew.erase(morePewPew.begin() + i);
		}
	}
}

// functie care realizeaza miscarea obiectului pe ecran cu tastele W, A, S, D
void Laborator3_Vis2D::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		spaceShip.y += deltaTime * spaceShip.speed;
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		spaceShip.x -= deltaTime * spaceShip.speed;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		spaceShip.y -= deltaTime * spaceShip.speed;
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		spaceShip.x += deltaTime * spaceShip.speed;
	}
}

// functie care ajuta la rotirea navei dupa pozitia mouse-ului
void Laborator3_Vis2D::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	float delta_x = logicSpace.width / viewSpace.width * mouseX - spaceShip.x;
	float delta_y = logicSpace.height - (logicSpace.height / viewSpace.height * mouseY) - spaceShip.y;
	angularStep = (atan2(delta_y, delta_x) - M_PI / 2) * rotationSpeed;
}

// functie care creeaza un proiectil la fiecare click stanga
void Laborator3_Vis2D::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		morePews pewObject;

		// stabilire specificatii pentru fiecare proiectil in parte
		pewObject.angle = (float)(angularStep + M_PI / 2);
		pewObject.x = spaceShip.x + spaceShip.length / 2;
		pewObject.y = spaceShip.y + spaceShip.length / 2;

		// adaugare proiectil in vector
		morePewPew.push_back(pewObject);
	}
}
