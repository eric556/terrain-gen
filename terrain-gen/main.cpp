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
#include "Cube.h"

void resetChunks(std::vector<Chunk*>& chunks, Material* mat, int chunkSize, sf::Vector2i xBounds, sf::Vector2i yBounds) {
	for (int i = 0; i < chunks.size(); i++) {
		delete chunks[i];
	}
	chunks.clear();
	for (int y = yBounds.x; y < yBounds.y; y++) {
		for (int x = xBounds.x; x < xBounds.y; x++) {
			chunks.push_back(new Chunk(sf::Vector2i(x * chunkSize, y * chunkSize), chunkSize, mat));
		}
	}
}


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
	glm::vec3 scale(1, 1, 1);
	modelMat = glm::translate(modelMat, glm::vec3(0, 0, 0));
	modelMat = glm::scale(modelMat, scale);
	
	int seed = 0;
	float amplitude = 0.f;
	int noiseType = 0;
	int drawType = 0;
	int chunkSize = 32;
	bool updateChunks = false;
	sf::Vector2i gridX(-3, 3);
	sf::Vector2i gridY(-3, 3);
	
	window.pushGLStates();
	std::vector<Chunk*> chunks;
	for (int y = gridY.x; y < gridY.y; y++) {
		for (int x = gridX.x; x < gridX.y; x++) {
			chunks.push_back(new Chunk(sf::Vector2i(x * chunkSize, y * chunkSize), chunkSize, testMat));
		}
	}
	testMat->SetUniform("view", cam.GetViewMatrix());
	testMat->SetUniform("model", modelMat);
	testMat->SetUniform("projection", projection);
	
	glm::mat4 modelMat2;
	glm::vec3 scale2(1, 1, 1);
	modelMat2 = glm::translate(modelMat2, glm::vec3(0, 0, 0));
	modelMat2 = glm::scale(modelMat2, scale2);

	window.popGLStates();
	
	float lastX = 0;
	float lastY = 0;
	float xOffset = 0;
	float yOffset = 0;
	bool mouseMove = false;
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
			else if (event.type == sf::Event::MouseButtonPressed) 
			{
				if (event.mouseButton.button == sf::Mouse::Left) 
				{
					mouseMove = true;
				}
			}
			else if (event.type = sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left) 
				{
					mouseMove = false;
				}
			}
		}
	
		if (mouseMove)
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
		if (updateChunks) 
		{
			resetChunks(chunks, testMat, chunkSize, gridX, gridY);
			updateChunks = false;
		}

		testMat->SetUniform("view", cam.GetViewMatrix());
		for (Chunk* chunk : chunks) {
			chunk->Update(seed, noiseType, amplitude);
		}

		Renderer::Clear(sf::Vector3f(0.1f,0.1f,0.1f));
		for (Chunk* chunk : chunks) {
			Renderer::Draw(chunk->getMesh(), chunk->getMat(), drawType);
		}

		window.popGLStates();

		ImGui::SFML::Update(window, dTime);
		ImGui::Begin("Terrain Options");
		if (ImGui::CollapsingHeader("Chunk Options")) {
			ImGui::PushItemWidth(100);
			if (ImGui::InputInt("X Min", &gridX.x))
				updateChunks = true;
			ImGui::SameLine();
			if (ImGui::InputInt("X Max", &gridX.y))
				updateChunks = true;
			if (ImGui::InputInt("Y Min", &gridY.x))
				updateChunks = true;
			ImGui::SameLine();
			if (ImGui::InputInt("Y Max", &gridY.y))
				updateChunks = true;

			ImGui::PopItemWidth();
		}
		
		if (ImGui::CollapsingHeader("Noise Options")) {
			ImGui::InputInt("Seed", &seed);
			ImGui::SliderFloat("Amplitude", &amplitude, 0.0f, 200.0f);
			ImGui::Combo("Noise Type", &noiseType, "Value\0Value Fractal\0Perlin\0Perlin Fractal\0Simplex\0Simplex Fractal\0Cellular\0White Noise\0Cubic\0Cubic Fractal");
		}

		if (ImGui::CollapsingHeader("GL Options")) {
			ImGui::Combo("Draw Type", &drawType, "GL_POINTS\0GL_LINES\0GL_LINE_STRIP\0GL_TRIANGLES");
		}

		if (ImGui::CollapsingHeader("Camera")) {
			ImGui::PushItemWidth(60);
			ImGui::InputFloat("X", &cam.GetPosition()->x);
			ImGui::SameLine();
			ImGui::InputFloat("Y", &cam.GetPosition()->y);
			ImGui::SameLine();
			ImGui::InputFloat("Z", &cam.GetPosition()->z);
			ImGui::PopItemWidth();
			ImGui::Text(("X: " + std::to_string((int)((cam.GetPosition()->x / chunkSize) / scale.x))).c_str());
			ImGui::SameLine();
			ImGui::Text(("Y: " + std::to_string((int)((cam.GetPosition()->y / chunkSize) / scale.y))).c_str());
			ImGui::SameLine();
			ImGui::Text(("Z: " + std::to_string((int)((cam.GetPosition()->z / chunkSize) / scale.z))).c_str());

		}

		ImGui::End();
		ImGui::SFML::Render(window);

		window.display();
		//std::cout << "Cam Pos: " << cam.GetPosition().x << ", " << cam.GetPosition().y << std::endl;
	}
	
	ImGui::SFML::Shutdown();

	return 0;
}