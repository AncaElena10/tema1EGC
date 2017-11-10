#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSpaceShip(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color)
{
	glm::vec3 spaceShipPosition = leftBottomCorner;

	std::vector<VertexFormat> spaceShipVertices =
	{
		VertexFormat(spaceShipPosition + glm::vec3(-0.5, -0.5, 0), color),
		VertexFormat(spaceShipPosition + glm::vec3(0, 0, 0), color),
		VertexFormat(spaceShipPosition + glm::vec3(0.5, -0.5, 0), color),
		VertexFormat(spaceShipPosition + glm::vec3(0.5, 0.5, 0), color),
		VertexFormat(spaceShipPosition + glm::vec3(-0.5, 0.5, 0), color)
	};

	Mesh* spaceShip = new Mesh(name);
	std::vector<unsigned short> spaceShipIndices =
	{
		0, 1, 4,
		1, 2, 3 
	};

	spaceShip->InitFromData(spaceShipVertices, spaceShipIndices);
	return spaceShip;
}

Mesh* Object2D::CreateScore(std::string name, glm::vec3 upRight, glm::vec3 color)
{
	glm::vec3 scorePosition = upRight;

	std::vector<VertexFormat> scoreVertices =
	{
		VertexFormat(scorePosition + glm::vec3(0, 0, 0), color),
		VertexFormat(scorePosition + glm::vec3(0.25, 0, 0), color),
		VertexFormat(scorePosition + glm::vec3(0.25, 1, 0), color),
		VertexFormat(scorePosition + glm::vec3(0, 1, 0), color),
	};

	Mesh* score = new Mesh(name);
	std::vector<unsigned short> scoreIndices =
	{
		0, 1, 2, 
		0, 2, 3
	};

	score->InitFromData(scoreVertices, scoreIndices);
	return score;
}

Mesh* Object2D::CreatePewPew(std::string name, glm::vec3 center, glm::vec3 color)
{
	glm::vec3 pewPosition = center;

	std::vector<VertexFormat> pewVertices =
	{
		VertexFormat(pewPosition + glm::vec3(-0.05, -0.25, 0), color),
		VertexFormat(pewPosition + glm::vec3(0.05, -0.25, 0), color),
		VertexFormat(pewPosition + glm::vec3(-0.05, 0.25, 0), color),
		VertexFormat(pewPosition + glm::vec3(0.05, 0.25, 0), color),
	};

	Mesh* pewpew = new Mesh(name);
	std::vector<unsigned short> pewIndices =
	{
		0, 1, 2,
		2, 1, 3
	};

	pewpew->InitFromData(pewVertices, pewIndices);
	return pewpew;
}
