#include "Application.h"


int Application::getIndex(int x, int y) {
	return y * mWidth + x;
}

Application::Application(std::string name, const unsigned int width, const unsigned int height, int scaleX, int scaleY) :
mApp(sf::VideoMode(width, height), name, sf::Style::Default), 
mCells(width * height), mPixels(width * height) {
	mWidth = width;
	mHeight = height;
	mApp.setFramerateLimit(60);
	mApp.setSize(sf::Vector2u(mApp.getSize().x * scaleX, mApp.getSize().y * scaleY));
	mApp.setPosition(sf::Vector2i(mApp.getPosition().x / scaleX, 0));
}

void Application::handleEvents() {
	sf::Event event;
	while (mApp.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			mApp.close();
		}
	}
}

const sf::RenderWindow& Application::getWindow() const {
	return mApp;
}

void Application::run() {
	//setup
	for (int x = 0; x < mWidth; ++x) {
		for (int y = 0; y < mHeight; ++y) {
			int index = getIndex(x, y);
			mPixels[index].position = { float(x), float(y) };
			if (x % 2 == 0 )
				mCells[index].setState(CellState::Dead);
			else 
				mCells[index].setState(CellState::Alive);
			mCells[index].setPosition({ float(x), float(y) });
			switch (mCells[index].getState()) {
			case CellState::Alive:
				mPixels[index].color = sf::Color::White;
				break;
			case CellState::Dead:
				mPixels[index].color = sf::Color::Black;
				break;
			}
		}
	}

	while (mApp.isOpen()) {
		handleEvents();
		//update
		//sets future state
		for (int x = 1; x < mWidth - 1; ++x) {
			for (int y = 1; y < mHeight - 1 ; ++y) {
				int i = getIndex(x, y);
				int livingCells = 0;
				for (int cx = -1; cx <= 1; ++cx)
					for (int cy = -1; cy <= 1; ++cy) {
						int index = getIndex(x + cx, y + cy);
						livingCells += int(mCells[index].getState());
					}
			
				livingCells--;
				switch (mCells[i].getState()) {
				case CellState::Alive:
					if (livingCells < 2 || livingCells > 3) 
						mCells[i].setFutureState(CellState::Dead);
					 else 
						mCells[i].setFutureState(CellState::Alive);
					break;
				case CellState::Dead:
					if (livingCells == 2 )
						mCells[i].setFutureState(CellState::Alive);
					break;
				}
			}
		}
		mApp.clear();
		//apply changes for next iteration
		for (int i = 0; i < mCells.size(); ++i) {
			mCells[i].applyChanges();
			switch (mCells[i].getState()) {
			case CellState::Alive:
				mPixels[i].color = sf::Color::White;
				break;
			case CellState::Dead:
				mPixels[i].color = sf::Color::Black;
				break;
			}
		}
	
		//render
		mApp.draw(mPixels.data(), mPixels.size(), sf::Points);
		mApp.display();
		
	}
}