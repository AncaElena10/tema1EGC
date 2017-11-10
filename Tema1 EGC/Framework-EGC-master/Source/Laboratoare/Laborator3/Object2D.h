#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{
	Mesh* CreateSpaceShip(std::string name, glm::vec3 center, glm::vec3 color);
	Mesh* CreateScore(std::string name, glm::vec3 upRight, glm::vec3 color);
	Mesh* CreatePewPew(std::string name, glm::vec3 center, glm::vec3 color);
}

