#pragma once
#include <GL\glew.h>
#include <SFML\Graphics.hpp>
#include <SOIL.h>
#include "PhysicsEngine.h"
#include "Sphere.h"

#include "SFMLRenderer.h"

int main()
{
	SOIL_load_OGL_texture("Things", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	int width = 640;
	int height = 480;

	sf::RenderWindow window(sf::VideoMode(width, height), "Physics Sim");

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
	r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));


	PhysicsEngine pe;
	Sphere s(Vector3(0, 0, 0), 5);
	pe.addSphere(s);

	while (window.isOpen()){

		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed)
				window.close();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sf::Int32 elapsed1 = clock.getElapsedTime().asMilliseconds();

		pe.update(elapsed1);
		pe.draw(r, elapsed1);

		window.display();
	}

	return 0;
}