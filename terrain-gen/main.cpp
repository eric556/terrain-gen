#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <queue>
#include "Renderer.h"
#include "MaterialLibrary.h"
#include "Camera.h"
#include "FastNoise.h"
#include "Chunk.h"

const unsigned int X_SEGMENTS = 64;
const unsigned int Y_SEGMENTS = 64;
const float PI = 3.14159265359;


int main()
{

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	ImGui::SFML::Init(window);

	GLenum err = glewInit();
	
	if (GLEW_OK != err) {
		std::cout << "Problem with loading openGL" << std::endl;
	}
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	
	Material* testMat = MaterialLibrary::CreateMaterial("testMat", "res/basic.shader");
	Camera cam;
	
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)window.getSize().x / (float)window.getSize().y, 0.1f, 100.0f);
	glm::mat4 modelMat;
	modelMat = glm::translate(modelMat, glm::vec3(-5, -5, -30));
	modelMat = glm::scale(modelMat, glm::vec3(0.1, 0.1, 0.1));
	
	int seed = 0;
	float amplitude = 0.f;
	int noiseType = 0;
	int drawType = 0;
	int chunkSize = 32;
	
	window.pushGLStates();
	std::vector<Chunk*> chunks;
	//Chunk* chunk = new Chunk(sf::Vector2f(0, 0) ,chunkSize, testMat);
	//Chunk* chunk1 = new Chunk(sf::Vector2f(0, 128), chunkSize, testMat);
	for (int y = -3; y < 3; y++) {
		for (int x = -3; x < 3; x++) {
			chunks.push_back(new Chunk(sf::Vector2f(x * chunkSize, y * chunkSize), chunkSize, testMat));
		}
	}
	testMat->SetUniform("view", cam.GetViewMatrix());
	testMat->SetUniform("model", modelMat);
	testMat->SetUniform("projection", projection);
	window.popGLStates();
	
	float lastX = 0;
	float lastY = 0;
	float xOffset = 0;
	float yOffset = 0;
	sf::Clock clock;
	bool running = true;
	float totalTime = 0;

	while (running)
	{

		sf::Time dTime = clock.restart();
		float dt = dTime.asSeconds();
		totalTime += dt;

		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) 
			{
				running = false;
			}
			else if (event.type == sf::Event::KeyPressed) 
			{
				if (event.key.code == sf::Keyboard::W) 
				{
					cam.MoveForward(5 * dt);

				}
				else if (event.key.code == sf::Keyboard::S) 
				{
					cam.MoveForward(-5 * dt);

				}
				else if (event.key.code == sf::Keyboard::D)
				{
					cam.StrafeRight(5 * dt);

				}
				else if (event.key.code == sf::Keyboard::A) 
				{
					cam.StrafeRight(-5 * dt);

				}
			}
		}
	
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			cam.RotateY((sf::Mouse::getPosition(window).x - lastX) * dt * 10);
			cam.RotateX(((lastY - sf::Mouse::getPosition(window).y)) * dt * 10);

			lastX = sf::Mouse::getPosition(window).x;
			lastY = sf::Mouse::getPosition(window).y;
		}
		else
		{
			lastX = sf::Mouse::getPosition(window).x;
			lastY = sf::Mouse::getPosition(window).y;
		}	
	
		window.pushGLStates();
		testMat->SetUniform("view", cam.GetViewMatrix());
		//chunk->Update(seed, noiseType, chunkSize, amplitude);
		//chunk1->Update(seed, noiseType, chunkSize, amplitude);

		for (Chunk* chunk : chunks) {
			chunk->Update(seed, noiseType, chunkSize, amplitude);
		}

		Renderer::Clear(sf::Vector3f(0.1f,0.1f,0.1f));
		//Renderer::Draw(chunk->getMesh(), chunk->getMat(), drawType);
		//Renderer::Draw(chunk1->getMesh(), chunk1->getMat(), drawType);
		for (Chunk* chunk : chunks) {
			Renderer::Draw(chunk->getMesh(), chunk->getMat(), drawType);
		}
		window.popGLStates();

		ImGui::SFML::Update(window, dTime);
		ImGui::Begin("Terrain Options");
		ImGui::InputInt("Seed", &seed);
		ImGui::InputInt("Chunk Size", &chunkSize);
		ImGui::SliderFloat("Amplitude", &amplitude, 0.0f, 200.0f);
		ImGui::Combo("Noise Type", &noiseType, "Value\0Value Fractal\0Perlin\0Perlin Fractal\0Simplex\0Simplex Fractal\0Cellular\0White Noise\0Cubic\0Cubic Fractal");
		ImGui::Combo("Draw Type", &drawType, "GL_POINTS\0GL_LINES\0GL_LINE_STRIP\0GL_TRIANGLES");
		ImGui::End();
		ImGui::SFML::Render(window);

		window.display();
	}
	
	ImGui::SFML::Shutdown();

	return 0;
}