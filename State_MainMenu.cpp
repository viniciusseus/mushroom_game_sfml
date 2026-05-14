#include <SFML/Graphics.hpp>
#include "State_MainMenu.hpp"
#include "StateManager.hpp"

void State_MainMenu::OnCreate() {
	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("MAIN MENU:"));
	m_text.setCharacterSize(18);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(400, 100);
	m_buttonSize = sf::Vector2f(300.0f, 32.0f);
	m_buttonPos = sf::Vector2f(400, 200);
	m_buttonPadding = 4; // 4px.
	std::string str[3];
	str[0] = "PLAY";
	str[1] = "CREDITS";
	str[2] = "EXIT";
	for (int i = 0; i < 3; ++i) {
		sf::Vector2f buttonPosition(m_buttonPos.x, m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::Red);
		m_rects[i].setOrigin(m_buttonSize.x / 2.0f,
			m_buttonSize.y / 2.0f);
		m_rects[i].setPosition(buttonPosition);
		m_labels[i].setFont(m_font);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(12);
		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);
		m_labels[i].setPosition(buttonPosition);
	}

	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::MainMenu, "Mouse_Left",
		&State_MainMenu::MouseClick, this);
}