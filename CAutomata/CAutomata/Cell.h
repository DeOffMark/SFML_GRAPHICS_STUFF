
#include <SFML/System/Vector2.hpp>
enum class CellState { Dead = 0, Alive = 1 };
class Cell {
public:

	Cell();

	Cell(CellState state, sf::Vector2f position);

	CellState getState();
	void setState(CellState state);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

	void setFutureState(CellState future);
	void applyChanges();
private:
	CellState mState;
	CellState mFutureState; 
	sf::Vector2f mPosition;
};