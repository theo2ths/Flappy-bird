#pragma comment(lib, "Winmm.lib")
#include "Laborator3.h"
#include <vector>
#include <iostream>
#include <mmsystem.h>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include <time.h> 

using namespace std;
using namespace glm;
float sign1 = -1;



class Tube
{
	public:
		float x, y;
		float width = 0.1f;
		int sign = 1; 
		float speed = 0.5f;
};

class TubePair
{
	public:
		bool awardedPoint = false;
		Tube *tube1, *tube2;
		float scaleFactor = 0.45;
		float scaleFactor1 = 0.45f;

		TubePair()
		{
			tube1 = new Tube();
			tube2 = new Tube();
		}

		void TranslateX(float distance)
		{
			tube1->x += distance;
			tube2->x += distance;
		}

		void TranslateY(float distance)
		{
			tube1->y += distance;
		}
		void TranslateY1(float distance)
		{
			tube2->y += distance;
		}

		void Teleport(float coordinate)
		{
			tube1->x = coordinate;
			tube2->x = coordinate;
		}
		
};

TubePair tubePair[3];
float speed = 1;

bool Collides(float x1, float y1, float w1, float h1,
	float x2, float y2, float w2, float h2)
{
	if (x1 + w1 / 2 < x2 - w2 / 2) return false;

	if (x1 - w1 / 2 > x2 + w2 / 2) return false;

	if (y1 - h1 / 2 > y2 + h2 / 2) return false;

	if (y1 + h1 / 2 < y2 - h2 / 2) return false;

	return true;
}

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{

	srand(time(NULL));

	tubePair[0].Teleport(1); tubePair[0].tube1->y = 0.55; tubePair[0].tube2->y = -0.85;
	tubePair[1].Teleport(1.90); 
	tubePair[1].tube1->y = 0.55; tubePair[1].tube2->y = -0.85;
	tubePair[2].Teleport(2.8);
	tubePair[2].tube1->y = 0.55; tubePair[2].tube2->y = -0.85;
	







	ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->View = mat4(1);
	camera->Projection= mat4(1);
	GetCameraInput()->SetActive(false);

	mapTextures["cap"] = new Texture2D();
	mapTextures["cap"]->Load2D("Resources/Falfaietoarea/cap.png");//, GL_REPEAT);

	mapTextures["corp"] = new Texture2D();
	mapTextures["corp"]->Load2D("Resources/Falfaietoarea/corp.png", GL_REPEAT);

	mapTextures["aripa"] = new Texture2D();
	mapTextures["aripa"]->Load2D("Resources/Falfaietoarea/aripa.png", GL_REPEAT);

	mapTextures["back"] = new Texture2D();
	mapTextures["back"]->Load2D("Resources/Falfaietoarea/background.png");

	mapTextures["start"] = new Texture2D();
	mapTextures["start"]->Load2D("Resources/Falfaietoarea/start.png");

	mapTextures["tube"] = new Texture2D();
	mapTextures["tube"]->Load2D("Resources/Falfaietoarea/tube.png");

	mapTextures["0"] = new Texture2D();
	mapTextures["0"]->Load2D("Resources/Falfaietoarea/0.png");

	mapTextures["1"] = new Texture2D();
	mapTextures["1"]->Load2D("Resources/Falfaietoarea/1.png");

	mapTextures["2"] = new Texture2D();
	mapTextures["2"]->Load2D("Resources/Falfaietoarea/2.png");

	mapTextures["3"] = new Texture2D();
	mapTextures["3"]->Load2D("Resources/Falfaietoarea/3.png");

	mapTextures["4"] = new Texture2D();
	mapTextures["4"]->Load2D("Resources/Falfaietoarea/4.png");

	mapTextures["5"] = new Texture2D();
	mapTextures["5"]->Load2D("Resources/Falfaietoarea/5.png");

	mapTextures["6"] = new Texture2D();
	mapTextures["6"]->Load2D("Resources/Falfaietoarea/6.png");

	mapTextures["7"] = new Texture2D();
	mapTextures["7"]->Load2D("Resources/Falfaietoarea/7.png");

	mapTextures["8"] = new Texture2D();
	mapTextures["8"]->Load2D("Resources/Falfaietoarea/8.png");

	mapTextures["9"] = new Texture2D();
	mapTextures["9"]->Load2D("Resources/Falfaietoarea/9.png");

	Mesh* quad = Object2D::CreateQuad("quad", vec3(1, 0, 0));
	quad->UseMaterials(false);
	AddMeshToList(quad);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.2, 0.8, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}
void Laborator3::MyRenderMesh(Mesh* mesh, glm::mat3 &modelMatrix, Texture2D *tex)
{
	glUseProgram(shaders["blUe"]->program);
	int i = 0;
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, tex->GetTextureID());
	glUniform1i(glGetUniformLocation(shaders["blUe"]->program, "u_texture_0"), i);
	RenderMesh2D(mesh, shaders["blUe"], modelMatrix);
}
void Laborator3::Update(float deltaTimeSeconds)
{
	time1 += deltaTimeSeconds;
	modelMatrix = glm::mat3(1);

	if (pressed == 0) {
		
		if (!playbg) {

			PlaySound(TEXT("Resources/Falfaietoarea/rad.wav"), NULL, SND_ASYNC | SND_FILENAME);
			playbg = 1;
		}

		modelMatrix = Transform2D::Scale(0.5, 0.5);
		MyRenderMesh(meshes["quad"], modelMatrix, mapTextures["start"]);

		//aripa
		ModelMatrixA1 = Transform2D::Translate(-0.8, -0.8) *
			Transform2D::Translate(0, 0.03) *
			Transform2D::Scale(1, 0) *
			Transform2D::Scale(0.1, 0.07) *
			Transform2D::Translate(0, 1);
		MyRenderMesh(meshes["quad"], ModelMatrixA1, mapTextures["aripa"]);


		//corp

		modelMatrixC = Transform2D::Translate(-0.8, -0.8) *
			Transform2D::Translate(0, 0) *
			Transform2D::Scale(0.15, 0.1);
		MyRenderMesh(meshes["quad"], modelMatrixC, mapTextures["corp"]);

		//cap

		modelMatrixCap = Transform2D::Translate(-0.8, -0.8) *
			Transform2D::Translate(0.14, 0.02) *
			Transform2D::Scale(0.04, 0.05);
		MyRenderMesh(meshes["quad"], modelMatrixCap, mapTextures["cap"]);

		//aripa 2

		ModelMatrixA2 = Transform2D::Translate(-0.8, -0.8) *
			Transform2D::Translate(0, 0.03) *
			Transform2D::Scale(1, 0) *
			Transform2D::Scale(0.1, 0.07) *
			Transform2D::Translate(0, 1);
		MyRenderMesh(meshes["quad"], ModelMatrixA2, mapTextures["aripa"]);
}

	else
	 {
		float s = sin(time1 * 5.1 + 0.1);
		float slowS = abs(sin(time1 * 10)) - 1;
		if (up)
		{
			sign1 = 1;
			birdx += sign1 * deltaTimeSeconds * 1.5;
			
		}
		else
			if (down)
			{
				sign1 = -1;
				birdx += sign1 * deltaTimeSeconds * 0.7;
			}
		r = Transform2D::Translate(-0.5, birdx);
		//backgroundu
		modelMatrix = glm::mat3(1);
		MyRenderMesh(meshes["quad"], modelMatrix, mapTextures["back"]);

		if(unghi < M_PI / 8 && sign1 == 1)
			unghi +=  deltaTimeSeconds * 2 + 0.06;
		if (unghi > -M_PI / 8 && sign1 == -1) {
			unghi -= deltaTimeSeconds * 2 - 0.02;
		}

		if (birdx > 1 || birdx < -1) {
			dead = 1;
		}


		for (int i = 0; i < 3; i++)
		{
			if (Collides(-0.5, birdx, 0.35, 0.13,
				tubePair[i].tube1->x, tubePair[i].tube1->y, tubePair[i].tube1->width,
				tubePair[i].scaleFactor * 2) || Collides(-0.5, birdx, 0.35, 0.1,
					tubePair[i].tube2->x, tubePair[i].tube2->y, tubePair[i].tube2->width,
					tubePair[i].scaleFactor1 *2)						
				)
			{
				dead = 1;
			}

			if (tubePair[i].tube1->x < -0.5)
			{
				if (tubePair[i].awardedPoint == false)
				{
					tubePair[i].awardedPoint = true;
					scorenumb++;

				}
			}
		}


		if (!dead) {


				//aripa1
				ModelMatrixA1 = r * Transform2D::Rotate(unghi)*
					Transform2D::Translate(0, 0.03) *
					Transform2D::Scale(1, s) *
					Transform2D::Scale(0.1, 0.07) *
					Transform2D::Translate(0, 1);
				MyRenderMesh(meshes["quad"], ModelMatrixA1, mapTextures["aripa"]);


				//corp

				modelMatrixC = r * 
					Transform2D::Rotate(unghi )*
					Transform2D::Translate(0, 0) * 
					Transform2D::Scale(0.15, 0.1);
				MyRenderMesh(meshes["quad"], modelMatrixC, mapTextures["corp"]);

				//cap
				modelMatrixCap = r * 
					Transform2D::Rotate(unghi ) * 
					Transform2D::Translate(0.14, 0.02) *
					Transform2D::Scale(0.04, 0.05);
				MyRenderMesh(meshes["quad"], modelMatrixCap, mapTextures["cap"]);

				//aripa 2

				s = sin(time1 * 5);
				ModelMatrixA2 = r *
					Transform2D::Rotate(unghi) *
					Transform2D::Translate(0, 0.03) *
					Transform2D::Scale(1, s) *
					Transform2D::Scale(0.1, 0.07) *
					Transform2D::Translate(0, 1);
				MyRenderMesh(meshes["quad"], ModelMatrixA2, mapTextures["aripa"]);


				//randare tub

				for (int i = 0; i < 3; i++)
				{
					tubePair[i].TranslateX(-deltaTimeSeconds * 0.5f);
					if (tubePair[i].tube1->x < -1 - tubePair[i].tube1->width)
					{
						tubePair[i].awardedPoint = false;
						tubePair[i].Teleport(1.45 + tubePair[i].tube1->width);
						tubePair[i].scaleFactor = 0.05 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.55)));
						tubePair[i].tube1->y = 1 - tubePair[i].scaleFactor;
						//tubePair[i].TranslateY(-0.1);
						tubePair[i].scaleFactor1 = 1 - tubePair[i].scaleFactor - 0.3;
						tubePair[i].tube2->y = -tubePair[i].scaleFactor - 0.3;

					}
					if (tubePair[i].tube1->y > 1.0f)
						tubePair[i].tube1->sign = -1;
					if (tubePair[i].tube1->y < 1 - tubePair[i].scaleFactor)
						tubePair[i].tube1->sign = 1;

					if(tubePair[i].tube2->y < -1.0)
					tubePair[i].tube2->sign = 1;
					if(tubePair[i].tube2->y >= -tubePair[i].scaleFactor - 0.3)
						tubePair[i].tube2->sign = -1;


						tubePair[i].TranslateY(tubePair[i].tube1->sign * deltaTimeSeconds * tubePair[i].tube1->speed);
						tubePair[i].TranslateY1(tubePair[i].tube2->sign * deltaTimeSeconds * tubePair[i].tube1->speed);
					modelMatrix = glm::mat3(1) *
						Transform2D::Translate(tubePair[i].tube1->x,tubePair[i].tube1->y) *
						Transform2D::Scale(0.1f, tubePair[i].scaleFactor);

					MyRenderMesh(meshes["quad"], modelMatrix, mapTextures["tube"]);

					

					modelMatrix = glm::mat3(1) *
						Transform2D::Translate(tubePair[i].tube2->x, tubePair[i].tube2->y) *
						Transform2D::Scale(0.1f, tubePair[i].scaleFactor1) *
						Transform2D::Rotate(M_PI);

					MyRenderMesh(meshes["quad"], modelMatrix, mapTextures["tube"]);
				}
				//prima cifra
				modelMatrixCif1 = Transform2D::Translate(0, 0.5) * Transform2D::Scale(0.05, 0.05);
				
				//a 2 cifra

				modelMatrixCif2 = Transform2D::Translate(0.10, 0.5) * Transform2D::Scale(0.05, 0.05);
				
				if (score) {

					scorenumb++;
					score = false;

				}
				//if(scorenumb >10 && scorenumb )
				MyRenderMesh(meshes["quad"], modelMatrixCif1, mapTextures[std::to_string(scorenumb / 10)]);
				MyRenderMesh(meshes["quad"], modelMatrixCif2, mapTextures[std::to_string(scorenumb % 10 )]);
			
		}
	}
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_SPACE)) {
		up = true;
		down = false;
	}
	else
	{
		down = true;
		up = false;
	}

}


void Laborator3::OnKeyPress(int key, int mods)
{



	if (key == GLFW_KEY_SPACE )
	{
		pressed++;

		if (pressed >= 1)
			PlaySound(TEXT("Resources/Falfaietoarea/crow.wav"), NULL, SND_ASYNC | SND_FILENAME);

	}
	if (key == GLFW_KEY_S)
	{
		score = true;
	}
	
			
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event

}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
