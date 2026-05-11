#pragma once
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Game.hpp"
#include <iostream>

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
		SharedContext m_context;
		StateManager m_stateManager;
};