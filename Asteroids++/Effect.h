#pragma once
#ifndef EFFECT_H
#define EFFECT_H

#include <unordered_map>
#include "Entity.h"
#include "Bar.h"
#include <vector>

using namespace std;

enum Groups
{
	FREEZE_GROUP
};

class Effect{
	float duration;
	bool active;
	Bar* bar;

public:
	Effect(float duration, bool active, Bar* bar);
	Effect(float duration, bool active);
	Effect();

	void setEffectActive(const bool& newEffectState);
	bool isEffectActive() const;
	void setEffectDuration(const float& newduration);
	void updateEffectDuration(const float& deltaduration);
	float getEffectDuration() const;
	void startEffect(const float& newduration);

	Bar* getBar();
	void setBar(Bar* bar);

	static unordered_map<Groups, vector<EntityType>> groups;
};

#endif
