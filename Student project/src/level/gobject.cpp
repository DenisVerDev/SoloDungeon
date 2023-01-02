#include"../../src/headers/level/GameObject.h"

//------Methods definition------

void GameObject::draw(sf::RenderTarget& target)
{
	target.draw(this->body);
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

sf::IntRect GameObject::getCollision()
{
	sf::IntRect collision(sf::Vector2i(this->position),sf::Vector2i(this->getSize()));

	return collision;
}
