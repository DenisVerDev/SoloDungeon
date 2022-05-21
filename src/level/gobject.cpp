#include"../../src/headers/level/GameObject.h"

//------Methods definition------

void GameObject::draw(sf::RenderTarget& target)
{
	target.draw(this->body);
}

void GameObject::saveObject(std::ofstream& stream)
{
	stream.write((const char*)&this->position, sizeof(this->position));
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

//------Getters definition------

sf::Vector2f GameObject::getPosition()
{
	return this->position;
}

sf::Vector2f GameObject::getSize()
{
	return sf::Vector2f(this->texture_rect.width,this->texture_rect.height);
}

bool GameObject::getCollision()
{
	return this->hasCollision;
}
