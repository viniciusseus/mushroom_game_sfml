

Player::Player(EntityManager* l_entityMgr)
	: Character(l_entityMgr)
{
	Load("Player.char");
	m_type = EntityType::Player;
	EventManager* events = m_entityManager->
		GetContext()->m_eventManager;
	events->AddCallback<Player>(StateType::Game,
		"Player_MoveLeft", &Player::React, this);
	events->AddCallback<Player>(StateType::Game,
		"Player_MoveRight", &Player::React, this);
	events->AddCallback<Player>(StateType::Game,
		"Player_Jump", &Player::React, this);
	events->AddCallback<Player>(StateType::Game,
		"Player_Attack", &Player::React, this);
}

Player::~Player() {
	EventManager* events =
		m_entityManager->GetContext()->m_eventManager;
	events->RemoveCallback(GAME, "Player_MoveLeft");
	events->RemoveCallback(GAME, "Player_MoveRight");
	events->RemoveCallback(GAME, "Player_Jump");
	events->RemoveCallback(GAME, "Player_Attack");
}

void Player::OnEntityCollision(EntityBase* l_collider,
	bool l_attack)
{
	if (m_state == EntityState::Dying) { return; }
	if (l_attack) {
		if (m_state != EntityState::Attacking) { return; }
		if (!m_spriteSheet.GetCurrentAnim()->IsInAction()) { return; }
		if (l_collider->GetType() != EntityType::Enemy &&
			l_collider->GetType() != EntityType::Player)
		{
			return;
		}
		Character* opponent = (Character*)l_collider;
		opponent->GetHurt(1);
		if (m_position.x > opponent->GetPosition().x) {
			opponent->AddVelocity(-32, 0);
		}
		else {
			opponent->AddVelocity(32, 0);
		}
	}
	else {
		// Other behavior.
	}
}

