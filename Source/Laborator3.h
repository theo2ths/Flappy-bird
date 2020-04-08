#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
class Laborator3 : public SimpleScene
{
	public:
		Laborator3();
		~Laborator3();

		void Init() override;

	private:
		void MyRenderMesh(Mesh*, glm::mat3 &modelMatrix, Texture2D *tex);
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		std::unordered_map<std::string, Texture2D*> mapTextures;
		
	protected:
		float time1 = 0;
		glm::mat3 modelMatrix, modelMatrixCap, modelMatrixC, ModelMatrixA1, ModelMatrixA2,
			modelMatrixCif1 = glm::mat3(1), modelMatrixCif2 = glm::mat3(1);
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
		glm:: mat3 r;
		bool up = false;
		bool down = true;
		float birdx = 0, birdy = 0;
		float dead = 0;
		int pressed = 0;
		int playbg = 0;
		float unghi = 0;
		bool score = false;
		int scorenumb = 0;
		
};
