#pragma once
#include <GL\glew.h>
#include <SFML\Graphics.hpp>

#include <SOIL.h>
#include "PhysicsEngine.h"
#include "Sphere.h"
#include <iostream>
#include <sstream>

#include "SFMLRenderer.h"


float randomFloat(float minBound, float maxBound);

int main()
{
	int WIDTH = 1024;
	int HEIGHT = 768;

	const int NUMOFSPHERES = 15;
	const float cubeSize = 50.0f;
	const float veloLimit = 0.1f;
	
	bool gravity = false;
	bool upwardsForce = false;
	bool drag = false;
	bool helpers = true;

	bool fullscreen = true;


	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Physics Sim");
	//sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Physics Sim", sf::Style::Fullscreen);

	// Taken from OGLRenderer
	if (glewInit() != GLEW_OK) {	//Try to initialise GLEW
		std::cout << "OGLRenderer::OGLRenderer(): Cannot initialise GLEW!" << std::endl;
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SFMLRenderer r;

	sf::Clock clock;

	Matrix4 viewMatrix = Matrix4::BuildViewMatrix(Vector3(0, 0, 250), Vector3(0, 0, -10));
	r.SetProjectionMatrix(Matrix4::Perspective(1.0f, 1000.0f, 1.33f, 45.0f));
	r.SetViewMatrix(viewMatrix);

	PhysicsEngine pe;

	pe.addPlane(Vector3(0, -1, 0), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.5f, 0.5f, -0.5f), Vector3(-0.5f, 0.5f, -0.5f), Vector3(-0.5f, 0.5f, 0.5f), cubeSize);
	pe.addPlane(Vector3(0, 0, 1), Vector3(0.5f, 0.5f, -0.5f), Vector3(-0.5f, 0.5f, -0.5f), Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.5f, -0.5f, -0.5f), cubeSize);
	pe.addPlane(Vector3(1, 0, 0), Vector3(-0.5f, 0.5f, 0.5f), Vector3(-0.5f, 0.5f, -0.5f), Vector3(-0.5f, -0.5f, -0.5f), Vector3(-0.5f, -0.5f, 0.5f), cubeSize); // Left
	pe.addPlane(Vector3(-1, 0, 0), Vector3(0.5f, -0.5f, -0.5f), Vector3(0.5f, 0.5f, -0.5f), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.5f, -0.5f, 0.5f), cubeSize); // Right
	pe.addPlane(Vector3(0, 1, 0), Vector3(0.5f, -0.5f, 0.5f), Vector3(0.5f, -0.5f, -0.5f), Vector3(-0.5f, -0.5f, -0.5f), Vector3(-0.5f, -0.5f, 0.5f), cubeSize);
	pe.addPlane(Vector3(0, 0, -1), Vector3(0.5f, 0.5f, 0.5f), Vector3(-0.5f, 0.5f, 0.5f), Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.5f, -0.5f, 0.5f), cubeSize);


	// Test Spheres
	/*Sphere *s1 = pe.addSphere(Vector3(10, 0, 0), 10.0f, 1, Vector3(0, 0, 0));
	Sphere *s2 = pe.addSphere(Vector3(-10, 0, 0), 5.5f, 1, Vector3(0, 0, 0));
	Sphere *s3 = pe.addSphere(Vector3(0, -10, 0), 5.5f, 1, Vector3(0, 0, 0));
	s1->setVelocity(Vector3(-1, 0, 0), 0.01f);
	s2->setVelocity(Vector3(1, 0, 0), 0.01f);
	s3->setVelocity(Vector3(0, 1, 0), 0.01f);*/

	for (int i = 0; i < NUMOFSPHERES; i++){
		Sphere* s = pe.addSphere(Vector3(randomFloat(-cubeSize, cubeSize), randomFloat(-cubeSize, cubeSize), randomFloat(-cubeSize, cubeSize)),
			randomFloat(0.5f, 5.0f), randomFloat(1.0f, 10.0f));
		s->setVelocity(Vector3(randomFloat(-veloLimit, veloLimit), randomFloat(-veloLimit, veloLimit), randomFloat(-veloLimit, veloLimit)), 1.0f);
	}
	
	/* Text Info */
	sf::Font font;
	font.loadFromFile("assets/fonts/arial.ttf");
	sf::Text gravityText("Gravity - Off", font);
	gravityText.setCharacterSize(15);
	gravityText.setColor(sf::Color::White);
	gravityText.setStyle(sf::Text::Regular);
	sf::Text dragText("Drag - Off", font);
	dragText.setCharacterSize(15);
	dragText.setColor(sf::Color::White);
	dragText.setStyle(sf::Text::Regular);
	dragText.setPosition(sf::Vector2<float>(0.0f, 18.0f));
	/* end of Text */

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::G){
					if (gravity){
						pe.removeGravity();
						gravityText.setString("Gravity - Off");
						gravity = false;
					}
					else {
						pe.applyGravity();
						gravityText.setString("Gravity - On");
						gravity = true;
					}
				}
				if (event.key.code == sf::Keyboard::P){
					if (drag){
						pe.setDragSphereFactor(1.0f);
						dragText.setString("Drag - Off");
						drag = false;
					}
					else {
						pe.setDragSphereFactor(0.998f);
						dragText.setString("Drag - On");
						drag = true;
					}
				}
				else if (event.key.code == sf::Keyboard::F){
					upwardsForce = true;
				}
				else if (event.key.code == sf::Keyboard::A){
					viewMatrix = viewMatrix * Matrix4::Rotation(1.0f, Vector3(0, 1, 0));
				}
				else if (event.key.code == sf::Keyboard::D){
					viewMatrix = viewMatrix * Matrix4::Rotation(-1.0f, Vector3(0, 1, 0));
				}
				else if (event.key.code == sf::Keyboard::W){
					viewMatrix = viewMatrix * Matrix4::Translation(Vector3(0, 0, 1));
				}
				else if (event.key.code == sf::Keyboard::S){
					viewMatrix = viewMatrix * Matrix4::Translation(Vector3(0, 0, -1));
				}
			}
		}

		r.SetViewMatrix(viewMatrix);
		sf::Int32 elapsed1 = clock.getElapsedTime().asMilliseconds();

		// only update at given fps
		if (elapsed1 > 1.0f / 120.0f){
			if (upwardsForce == true){
				pe.applyUpwardsForce();
			}
			pe.update(1.0f / 120.0f);
			clock.restart();
		
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			pe.draw(r, 1.0f / 120.0f);

			// Draw Helpers
			if (helpers){
				window.pushGLStates();
				window.draw(gravityText);
				window.draw(dragText);
				window.popGLStates();
			}

			window.display();
			
			if (upwardsForce == true){
				pe.removeAcclerationFromAllSpheres();
				upwardsForce = false;
			}
		}
	}

	return 0;
}

float randomFloat(float minBound, float maxBound){
	return (((maxBound - minBound)*((float)rand() / RAND_MAX)) + minBound);
}