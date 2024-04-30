#pragma once
#ifndef EFFECT_H
#define EFFECT_H

#include <unordered_map>
#include "Entity.h"
#include <vector>

using namespace std;

enum Groups
{
	FREEZE_GROUP
};

class Effect{
	float duration;
	bool active;
public:
	Effect(float duration, bool active);
	Effect();

	void setEffectActive(const bool& newEffectState);
	bool isEffectActive();
	void setEffectDuration(const float& newduration);
	void updateEffectDuration(const float& deltaduration);
	float getEffectDuration();
	void startEffect(const float& newduration);

	static unordered_map<Groups, vector<EntityType>> groups;
};

#endif
