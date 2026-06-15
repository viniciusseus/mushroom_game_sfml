#include "Map.hpp";

Map::Map(SharedContext* l_context, BaseState* l_currentState)
	:m_context(l_context), m_defaultTile(l_context),
	m_maxMapSize(32, 32), m_tileCount(0), m_tileSetCount(0),
	m_mapGravity(512.f), m_loadNextMap(false),
	m_currentState(l_currentState)
{
	m_context->m_gameMap = this;
	LoadTiles("tiles.cfg");
}

Map::Map(SharedContext* l_context, BaseState* l_currentState)
	:m_context(l_context), m_defaultTile(l_context),
	m_maxMapSize(32, 32), m_tileCount(0), m_tileSetCount(0),
	m_mapGravity(512.f), m_loadNextMap(false),
	m_currentState(l_currentState)
{
	m_context->m_gameMap = this;
	LoadTiles("tiles.cfg");
}

Map::~Map() {
	PurgeMap();
	PurgeTileSet();
	m_context->m_gameMap = nullptr;
}

Tile* Map::GetTile(unsigned int l_x, unsigned int l_y) {
	auto itr = m_tileMap.find(ConvertCoords(l_x, l_y));
	return(itr != m_tileMap.end() ? itr->second : nullptr);
}

unsigned int Map::ConvertCoords(const unsigned int& l_x, const unsigned int& l_y)
{
	return (l_x * m_maxMapSize.x) + l_y; // Row-major.
}

void Map::Update(float l_dT) {
	if (m_loadNextMap) {
		PurgeMap();
		m_loadNextMap = false;
		if (m_nextMap != "") {
			LoadMap("media/maps/" + m_nextMap);
		}
		else {
			m_currentState->GetStateManager()->
				SwitchTo(StateType::GameOver);
		}
		m_nextMap = "";
	}
	sf::FloatRect viewSpace = m_context->m_wind->GetViewSpace();
	m_background.setPosition(viewSpace.left, viewSpace.top);
}

void Map::Draw() {
	sf::RenderWindow* l_wind = m_context->m_wind->GetRenderWindow();
	l_wind->draw(m_background);
	sf::FloatRect viewSpace = m_context->m_wind->GetViewSpace();
	sf::Vector2i tileBegin(
		floor(viewSpace.left / Sheet::Tile_Size),
		floor(viewSpace.top / Sheet::Tile_Size));
	sf::Vector2i tileEnd(
		ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size),
		ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size));
	unsigned int count = 0;
	for (int x = tileBegin.x; x <= tileEnd.x; ++x) {
		for (int y = tileBegin.y; y <= tileEnd.y; ++y) {
			if (x < 0 || y < 0) { continue; }
			Tile* tile = GetTile(x, y);
			if (!tile) { continue; }
			sf::Sprite& sprite = tile->m_properties->m_sprite;
			sprite.setPosition(x * Sheet::Tile_Size,
				y * Sheet::Tile_Size);
			l_wind->draw(sprite);
			++count;
		}
	}
}