#include "EventHandler.h"

EventHandler::EventHandler(VertexArray particles) : particles(particles)
{
}

void EventHandler::render(RenderWindow& window) const
{
	window.draw(particles);
}