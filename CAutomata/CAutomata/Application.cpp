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
	drawradius = 10.f;
	isRun = true;
}

void Application::handleEvents() {
	sf::Event event;
	while (mApp.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			mApp.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::P) {
				isRun = !isRun;
			}
			if (event.key.code == sf::Keyboard::C) {
				if (!isRun)
					for (auto& c: mCells){
						c.setFutureState(CellState::Dead);
					}
			}
			if (event.key.code == sf::Keyboard::Escape)
				mApp.close();
		}
		else if (event.type ==sf::Event::MouseWheelScrolled ){
			
				drawradius = std::min(100.f, std::max(10.f, drawradius +( event.mouseWheelScroll.delta * 5.f) ));
				
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
		if (isRun) {
			for (int x = 1; x < mWidth - 1; ++x) {
				for (int y = 1; y < mHeight - 1; ++y) {
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
						if (livingCells <= 1 || livingCells >= 4)
							mCells[i].setFutureState(CellState::Dead);
						
						break;
					case CellState::Dead:
						if (livingCells == 2)
							mCells[i].setFutureState(CellState::Alive);
						break;
					}
				}
			}
		}
		else {
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				for (int cx = -(int)(drawradius/2.f); cx <= (int)(drawradius / 2.f); ++cx)
					for (int cy = -(int)(drawradius / 2.f); cy <= (int)(drawradius / 2.f); ++cy) {
						int index = getIndex(sf::Mouse::getPosition(mApp).x + cx, sf::Mouse::getPosition(mApp).y + cy);
						mCells[index].setFutureState(CellState::Alive);
					}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
				for (int cx = -(int)(drawradius / 2.f); cx <= (int)(drawradius / 2.f); ++cx)
					for (int cy = -(int)(drawradius / 2.f); cy <= (int)(drawradius / 2.f); ++cy) {
						int index = getIndex(sf::Mouse::getPosition(mApp).x + cx, sf::Mouse::getPosition(mApp).y + cy);
						mCells[index].setFutureState(CellState::Dead);
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
		sf::RectangleShape rect;
		rect.setSize({ (float)mWidth - 20.f, (float)mHeight - 20.f});
		rect.setPosition(10.f, 10.f);
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineThickness(10.f);
		
		mApp.draw(mPixels.data(), mPixels.size(), sf::Points);
		if (isRun) {
			rect.setOutlineColor(sf::Color::Green);
			mApp.setTitle("Game of Life: Running State");
		}
		else {
			rect.setOutlineColor(sf::Color::Red);
			mApp.setTitle("Game of Life: Draw State");
			sf::RectangleShape drawOutline;
			drawOutline.setPosition((float)sf::Mouse::getPosition(mApp).x, (float)sf::Mouse::getPosition(mApp).y);
			drawOutline.setSize({ drawradius, drawradius });
			drawOutline.setOrigin(drawradius / 2.f, drawradius / 2.f);
			drawOutline.setFillColor(sf::Color::Transparent);
			drawOutline.setOutlineColor(sf::Color::White);
			drawOutline.setOutlineThickness(5.f);
			mApp.draw(drawOutline);
		}
		mApp.draw(rect);
		mApp.display();
		
	}
}