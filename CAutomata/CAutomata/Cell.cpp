
#include "Cell.h"

Cell::Cell() {
	mState = CellState::Dead;
	mPosition = { 0.f, 0.f};
	mFutureState = mState;
}

Cell::Cell(CellState state, sf::Vector2f position) {
	mState = state;
	mPosition = position;
	mFutureState = mState;
}

sf::Vector2f Cell::getPosition() {
	return mPosition;
}
void Cell::setPosition(sf::Vector2f position) {
	mPosition = position;
}

CellState Cell::getState() {
	return mState;
}
void Cell::setState(CellState state) {
	mState = state;
}

void Cell::setFutureState(CellState future) {
	mFutureState = future;
}

void Cell::applyChanges() {
	mState = mFutureState;
}