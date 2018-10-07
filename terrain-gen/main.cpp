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
	
	std::vector<Vertex> terrainVerts;
	std::vector<unsigned int> terrainIndicies;
	FastNoise noise;
	noise.SetNoiseType(static_cast<FastNoise::NoiseType>(3)); // Set the desired noise type
	
	
	unsigned int iteration = 0;
	for (int y = 0; y < 128; y++) {
		for (int x = 0; x < 128; x++){
			terrainVerts.push_back({
				glm::vec3(x, 0, y),
				glm::vec3(x, 0, y)
			});

			terrainIndicies.push_back(iteration);
			iteration++;
		}
	}
	
	window.pushGLStates();
	Mesh* mesh = new Mesh(terrainVerts, terrainIndicies);
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

	int seed = 0;
	float amplitude = 0.f;
	int noiseType = 0;


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
	
		noise.SetNoiseType(static_cast<FastNoise::NoiseType>(noiseType));
		noise.SetSeed(seed);
		terrainVerts.clear();
		terrainIndicies.clear();
		unsigned int iteration = 0;
		for (int y = 0; y < 128; y++) {
			for (int x = 0; x < 128; x++) {
				double z = noise.GetNoise(x, y);
				terrainVerts.push_back({
					glm::vec3(x, z * amplitude, y),
					glm::vec3(x, z, y)
				});
			}
		}
	
		window.pushGLStates();
		testMat->SetUniform("view", cam.GetViewMatrix());
		mesh->VBO->SetData(terrainVerts.data(), terrainVerts.size() * sizeof(Vertex));
		Renderer::Clear(sf::Vector3f(0.1f,0.1f,0.1f));
		Renderer::Draw(mesh, testMat, GL_POINTS);
		window.popGLStates();
	

		ImGui::SFML::Update(window, dTime);
		ImGui::Begin("Terrain Options");
		ImGui::InputInt("Seed", &seed);
		ImGui::SliderFloat("Amplitude", &amplitude, 0.0f, 200.0f);
		ImGui::Combo("Noise Type", &noiseType, "Value\0Value Fractal\0Perlin\0Perlin Fractal\0Simplex\0Simplex Fractal\0Cellular\0White Noise\0Cubic\0Cubic Fractal");
		ImGui::End();
		ImGui::SFML::Render(window);

		window.display();
	}
	
	ImGui::SFML::Shutdown();

	return 0;
}