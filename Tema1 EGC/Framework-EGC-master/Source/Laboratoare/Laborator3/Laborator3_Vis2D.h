#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Laborator3_Vis2D : public SimpleScene
{
	public:
		struct ViewportSpace
		{
			ViewportSpace() : x(0), y(0), width(1), height(1) {}
			ViewportSpace(int x, int y, int width, int height)
				: x(x), y(y), width(width), height(height) {}
			int x;
			int y;
			int width;
			int height;
		};

		struct LogicSpace
		{
			LogicSpace() : x(0), y(0), width(1), height(1) {}
			LogicSpace(float x, float y, float width, float height)
				: x(x), y(y), width(width), height(height) {}
			float x;
			float y;
			float width;
			float height;
		};

		struct mySpaceShip
		{
			mySpaceShip() : x(9.0f), y(9.0f), length(1.0f), speed(7.0f) {}
			mySpaceShip(float x, float y, float length, float speed)
				: x(x), y(x), length(length), speed(speed) {}
			float x;
			float y;
			float length;
			float speed;
		};

		struct morePews {
			morePews() : x(0), y(0), speed(3.0f), angle(0), length(0.1f) {}
			morePews(float x, float y, float pewSpeed, int id, float pewAngle, float length)
				: x(x), y(y), speed(speed),  angle(angle), length(length) {}
			float x;
			float y;
			float speed;
			float angle;
			float length;
		};

		struct enemy {
			enemy() : ray((float)((rand() % 9) + 8)), directionAngle(((float)(rand() % 360) + 0)),
			x(9.0f + ray * cos(directionAngle)), y(9.0f + ray * sin(directionAngle)), speed((float) ((rand() % 2) + 4)),
			length(1.2f), angle(0), chosenColor(0), life(0), doScale(false) {}
			enemy(float ray, float directionAngle, float x, float speed, float length, float angle, glm::vec3 chosenColor, int life, bool doScale)
				: ray(ray), directionAngle(directionAngle), x(x), y(y), speed(speed), length(length), angle(angle), chosenColor(chosenColor), 
				  life(life), doScale(doScale) {}
			float ray;
			float directionAngle;
			float x;
			float y;
			float speed;
			float length;
			float angle;
			glm::vec3 chosenColor;
			int life;
			bool doScale;
		};

	public:
		Laborator3_Vis2D();
		~Laborator3_Vis2D();

		void Init() override;

	private:
		void RenderEnemy();
		void RenderPew();
		void RenderHero();
		void Update(float deltaTimeSeconds) override;
		void DrawScene(glm::mat3 visMatrix);
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

		glm::mat3 VisualizationTransf2D(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

		void TheEnd(float deltaTimeSeconds);

		void TheEnd();

		void GenerateEnemy();

		void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

	protected:
		ViewportSpace viewSpace;
		LogicSpace logicSpace;
		glm::mat3 modelMatrix, visMatrix;
		std::vector<morePews> morePewPew;
		std::vector<enemy> moreEnemy;
		mySpaceShip spaceShip;
};
