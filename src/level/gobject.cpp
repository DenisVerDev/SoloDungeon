#include"../../src/headers/level/GameObject.h"

//------Constructor definition------

GameObject::GameObject(bool hasCollision)
{
	this->hasCollision = hasCollision;
}

//------Methods definition------

void GameObject::draw(sf::RenderTarget& target)
{
	target.draw(this->body);
}

void GameObject::saveObject(std::ofstream& stream)
{
	stream.write((const char*)&this->texture_rect,sizeof(this->texture_rect));
	stream.write((const char*)&this->position, sizeof(this->position));
	stream.write((const char*)&this->hasCollision, sizeof(this->hasCollision));
}

void GameObject::loadObject(std::ifstream& stream)
{
	stream.read((char*)&this->texture_rect, sizeof(this->texture_rect));
	stream.read((char*)&this->position, sizeof(this->position));
	stream.read((char*)&this->hasCollision, sizeof(this->hasCollision));
}

//------Setters definition------

void GameObject::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->body.setPosition(this->position);
}

void GameObject::setTexture(sf::Texture& texture)
{
	this->body.setTexture(texture);
	this->body.setTextureRect(this->texture_rect);
}

void GameObject::setTexture(sf::Texture& texture, const sf::IntRect rect)
{
	this->body.setTexture(texture);

	this->texture_rect = rect;
	this->body.setTextureRect(this->texture_rect);
}

//------Getters definition------

sf::Vector2f GameObject::getPosition()
{
	return this->position;
}

sf::Vector2f GameObject::getSize()
{
	return sf::Vector2f(this->texture_rect.width,this->texture_rect.height);
}
