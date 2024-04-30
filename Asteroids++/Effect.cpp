#include "Effect.h"
#include "Entity.h"

unordered_map<Groups, vector<EntityType>> Effect::groups{ 
	{ FREEZE_GROUP, { EntityType::TYPE_EVENT_WIND, EntityType::TYPE_PARTICLE} } 
};

Effect::Effect(float duration, bool active)
{
	this->duration = duration;
	this->active = active;
}

Effect::Effect() : active(false), duration(15.0f) {}

void Effect::setEffectActive(const bool& newEffectState)
{
	active = newEffectState;
}

bool Effect::isEffectActive()
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

float Effect::getEffectDuration()
{
	return duration;
}

void Effect::startEffect(const float& newDuration){
	duration = newDuration;
	active = true;
}