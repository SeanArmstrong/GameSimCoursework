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
	SOIL_load_OGL_texture("Things", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	const int WIDTH = 640;
	const int HEIGHT = 480;

	const int NUMOFSPHERES = 15;
	const float cubeSize = 50.0f;
	const float minStartingVelocity = 0.001f;
	const float maxStartingVelocity = 0.003f;
	

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Physics Sim");

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
	//SFMLRenderer o;
	//o.SetViewMatrix(Matrix4::Orthographic(-1, 1, WIDTH / 2, -WIDTH / 2, HEIGHT / 2, -HEIGHT / 2));

	sf::Clock clock;

	Matrix4 viewMatrix = Matrix4::BuildViewMatrix(Vector3(0, 0, 200), Vector3(0, 0, -10));
	r.SetProjectionMatrix(Matrix4::Perspective(1.0f, 1000.0f, 1.33f, 45.0f));
	r.SetViewMatrix(viewMatrix);

	PhysicsEngine pe;
	bool gravity = false;
	bool upwardsForce = false;
	float dragFactor = 0.5f;

	/*Plane *p1 = pe.addPlane(Vector3(1, 0, 0), cubeSize);
	Plane *p2 = pe.addPlane(Vector3(-1, 0, 0), cubeSize);
	Plane *p3 = pe.addPlane(Vector3(0, 1, 0), cubeSize);
	Plane *p4 = pe.addPlane(Vector3(0, -1, 0), cubeSize);
	Plane *p5 = pe.addPlane(Vector3(0, 0, 1), cubeSize);
	Plane *p6 = pe.addPlane(Vector3(0, 0, -1), cubeSize);*/

	pe.addPlane(Vector3(0, -1, 0), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.5f, 0.5f, -0.5f), Vector3(-0.5f, 0.5f, -0.5f), Vector3(-0.5f, 0.5f, 0.5f), cubeSize);
	pe.addPlane(Vector3(0, 0, 1), Vector3(0.5f, 0.5f, -0.5f), Vector3(-0.5f, 0.5f, -0.5f), Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.5f, -0.5f, -0.5f), cubeSize);
	pe.addPlane(Vector3(1, 0, 0), Vector3(-0.5f, 0.5f, 0.5f), Vector3(-0.5f, 0.5f, -0.5f), Vector3(-0.5f, -0.5f, -0.5f), Vector3(-0.5f, -0.5f, 0.5f), cubeSize); // Left
	pe.addPlane(Vector3(-1, 0, 0), Vector3(0.5f, -0.5f, -0.5f), Vector3(0.5f, 0.5f, -0.5f), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.5f, -0.5f, 0.5f), cubeSize); // Right
	pe.addPlane(Vector3(0, 1, 0), Vector3(0.5f, -0.5f, 0.5f), Vector3(0.5f, -0.5f, -0.5f), Vector3(-0.5f, -0.5f, -0.5f), Vector3(-0.5f, -0.5f, 0.5f), cubeSize);
	pe.addPlane(Vector3(0, 0, -1), Vector3(0.5f, 0.5f, 0.5f), Vector3(-0.5f, 0.5f, 0.5f), Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.5f, -0.5f, 0.5f), cubeSize);


	// Test Spheres
	Sphere *s1 = pe.addSphere(Vector3(0, 0, 0), 10.0f, 1, Vector3(0, 0, 0));
	//Sphere *s2 = pe.addSphere(Vector3(-10, 0, 0), 5.5f, 1, Vector3(0, 0, 0));
	//Sphere *s3 = pe.addSphere(Vector3(0, -10, 0), 5.5f, 1, Vector3(0, 0, 0));
	s1->setVelocity(Vector3(0, 1, 0), 0.01f);
	//s2->setVelocity(Vector3(1, 0, 0), 0.01f);
	//s3->setVelocity(Vector3(0, 1, 0), 0.01f);

	/*for (int i = 0; i < NUMOFSPHERES; i++){
		Sphere* s = pe.addSphere(Vector3(randomFloat(-cubeSize, cubeSize), randomFloat(-cubeSize, cubeSize), randomFloat(-cubeSize, cubeSize)),
			randomFloat(0.5f, 3.0f), 10);
		s->setVelocity(Vector3(randomFloat(0.1f, maxStartingVelocity), randomFloat(0.1f, maxStartingVelocity), randomFloat(0.1f, maxStartingVelocity)), 1.0f);
	}*/
	
	sf::Font font;
	font.loadFromFile("assets/fonts/arial.ttf");
	// Create a text
	sf::Text gravityText("Gravity - Off", font);
	gravityText.setCharacterSize(10);
	gravityText.setColor(sf::Color::White);
	gravityText.setStyle(sf::Text::Regular);
	pe.setDragSphereFactor(0.5f);
	sf::Text dragText("Drag = 0.5", font);
	dragText.setCharacterSize(10);
	dragText.setColor(sf::Color::White);
	dragText.setStyle(sf::Text::Regular);
	dragText.setPosition(sf::Vector2<float>(0.0f, 12.0f));


	// http://gafferongames.com/game-physics/fix-your-timestep/
	// Game timer needed

	while (window.isOpen()){

		if (upwardsForce == true){
			if (gravity){
				pe.applyGravity();
			}
			else{
				pe.removeAcclerationFromAllSpheres();
			}
			upwardsForce = false;
		}

		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed){
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::G){
					if (gravity){
						pe.removeAcclerationFromAllSpheres();
						gravityText.setString("Gravity - Off");
						gravity = false;
					}
					else {
						pe.applyGravity();
						gravityText.setString("Gravity - On");
						gravity = true;
					}
				}
				else if (event.key.code == sf::Keyboard::F){
					upwardsForce = true;
					pe.applyUpwardsForce();
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
				else if (event.key.code == sf::Keyboard::L){
					// Rotate cube around Z
				}
				else if (event.key.code == sf::Keyboard::K){
					// Rotate cube around X
				}
				else if (event.key.code == sf::Keyboard::Up){
					if (dragFactor < 0.99f){
						dragFactor = dragFactor + 0.01f;
						pe.setDragSphereFactor(dragFactor);
						std::stringstream string;
						string << "Drag = " << dragFactor;
						dragText.setString(string.str());
					}
				}
				else if (event.key.code == sf::Keyboard::Down){
					if (dragFactor > 0.01f){
						dragFactor = dragFactor - 0.01f;
						pe.setDragSphereFactor(dragFactor);
						std::stringstream string;
						string << "Drag = " << dragFactor;
						dragText.setString(string.str());
					}
				}
			}
		}

		r.SetViewMatrix(viewMatrix);
		sf::Int32 elapsed1 = clock.getElapsedTime().asMilliseconds();

		// only update at given fps
		// at the moment its as much as possible
		//if (elapsed1 > 1.0f / 60.0f){
			pe.update(1.0f / 60.0f);
			//clock.restart();
		//}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		pe.draw(r, 1.0f / 60.0f);
		
		// Draw Helpers
		
		/*glBindBuffer(GL_ARRAY_BUFFER, 0);
		window.pushGLStates();
		window.draw(gravityText);
		window.draw(dragText);
		window.popGLStates();*/

		window.display();
		//clock.restart();
	}

	return 0;
}

float randomFloat(float minBound, float maxBound){
	return (((maxBound - minBound)*((float)rand() / RAND_MAX)) + minBound);
}