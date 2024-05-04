#include "Effect.h"
#include "Entity.h"

Effect::Effect(float duration, bool active, Bar* bar) : duration(duration), active(active), bar(bar) {}

Effect::Effect(float duration, bool active) : duration(duration), active(active), bar(new Bar()) {}

Effect::Effect() : active(false), duration(15.0f), bar(new Bar()) {}

void Effect::setEffectActive(const bool& newEffectState)
{
	active = newEffectState;
}

bool Effect::isEffectActive() const
{
	return active;
}

void Effect::setEffectDuration(const float& newDuration)
{
	duration = newDuration;
}

void Effect::updateEffectDuration(const float& deltaDuration)
{
	duration -= deltaDuration;

	if (duration < 0) active = false;
}

float Effect::getEffectDuration() const
{
	return duration;
}

void Effect::startEffect(const float& newDuration){
	duration = newDuration;
	active = true;
}

Bar* Effect::getBar(){
	return bar;
}

void Effect::setBar(Bar* bar){
	this->bar = bar;
}