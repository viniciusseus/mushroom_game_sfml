#pragma once
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include <iostream>
#include "StateManager.hpp"
#include "EventManager.hpp"
#include "EntityManager.hpp"

class Game {
	public:
		Game();
		~Game();
		void HandleInput();
		void Update();
		void Render();

		sf::Time GetElapsed();
		void RestartClock();

		sf::RenderWindow GetRendererWindow();
		Window* GetWindow();

		void LateUpdate();

	private:
		void MoveMushroom();
		void MoveSprite(EventDetails* l_details);
		Window m_window;

		sf::Texture m_mushroomTexture;
		sf::Sprite m_mushroom;
		sf::Sprite m_sprite;
		sf::Vector2i m_increment;

		sf::Clock m_clock;
		sf::Time m_elapsed;
		StateManager m_stateManager;
		SharedContext m_context;
		EntityManager m_entityManager;
};