#include "Board.hpp"
#include "Ball.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace pong 
{
  Board::Board(sf::Vector2<unsigned int> resolution, sf::Vector2f size, sf::Vector2f scale)
    : scale(scale)
  {
    mSource.loadFromFile("assets/pixel.png");
    mSprite = sf::Sprite(mSource);
    mSprite.setScale(size.x * scale.x, size.y * scale.y);
    mSprite.setPosition(resolution.x / 2.f, resolution.y - size.y * scale.y - 32 * scale.y);
    mSprite.setOrigin(0.5, 0.5);
  }
  void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    target.draw(mSprite, states);
  }
  void Board::moveLeft(float deltaTime)
  {
    mSprite.move(sf::Vector2<float>(-speed * deltaTime * scale.x, 0));
  }
  void Board::moveRight(float deltaTime)
  {
    mSprite.move(sf::Vector2<float>(speed * deltaTime * scale.y, 0));
  }
  sf::Vector2f Board::getPosition()
  {
    return mSprite.getPosition();
  }
  float Board::getWidth()
  {
    return mSprite.getScale().y;
  }
  float Board::getLength()
  {
    return mSprite.getScale().x;
  }
  bool Board::intersects(Ball ball)
  {
    //ORIGIN IS AT CENTER OF BOARD
    if(ball.getPosition().x + ball.getRadius() < getPosition().x - getLength()/2) //left
      return false;
    if(ball.getPosition().x - ball.getRadius() > getPosition().x + getLength()/2) //right
      return false;
    if(ball.getPosition().y + ball.getRadius() < getPosition().y - getWidth()/2) //bottom
      return false;
    if(ball.getPosition().y - ball.getRadius() > getPosition().y + getWidth()/2) //top
      return false;
    return true;
  }
  float Board::getSpeed()
  {
    return speed;
  }
  void Board::setSpeed(float newSpeed)
  {
    speed = newSpeed;
  }
}























