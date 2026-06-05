#include "SpriteSheet.hpp";
#include "Direction.hpp";

SpriteSheet::SpriteSheet(TextureManager* l_textMgr)
	:m_textureManager(l_textMgr), m_animationCurrent(nullptr),
	m_spriteScale(1.f, 1.f), m_direction(Direction::Right) {
}

SpriteSheet::~SpriteSheet() { ReleaseSheet(); }

void SpriteSheet::ReleaseSheet() {
	m_textureManager->ReleaseResource(m_texture);
	m_animationCurrent = nullptr;
	while (m_animations.begin() != m_animations.end()) {
		delete m_animations.begin()->second;
		m_animations.erase(m_animations.begin());
	}
}

void SpriteSheet::SetSpriteSize(const sf::Vector2i& l_size) {
	m_spriteSize = l_size;
	m_sprite.setOrigin(m_spriteSize.x / 2, m_spriteSize.y);
}

void SpriteSheet::SetSpritePosition(const sf::Vector2f& l_pos) {
	m_sprite.setPosition(l_pos);
}

void SpriteSheet::SetDirection(const Direction& l_dir) {
	if (l_dir == m_direction) { return; }
	m_direction = l_dir;
	m_animationCurrent->CropSprite();
}

void SpriteSheet::CropSprite(const sf::IntRect& l_rect) {
	m_sprite.setTextureRect(l_rect);
}

bool SpriteSheet::SetAnimation(const std::string& l_name,
	const bool& l_play, const bool& l_loop)
{
	auto itr = m_animations.find(l_name);
	if (itr == m_animations.end()) { return false; }
	if (itr->second == m_animationCurrent) { return false; }
	if (m_animationCurrent) { m_animationCurrent->Stop(); }
	m_animationCurrent = itr->second;
	m_animationCurrent->SetLooping(l_loop);
	if (l_play) { m_animationCurrent->Play(); }
	m_animationCurrent->CropSprite();
	return true;
}

void SpriteSheet::Update(const float& l_dT) {
	m_animationCurrent->Update(l_dT);
}

void SpriteSheet::Draw(sf::RenderWindow* l_wnd) {
	l_wnd->draw(m_sprite);
}