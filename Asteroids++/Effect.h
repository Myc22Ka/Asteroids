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
	static float duration;
	static bool active;
public:
	Effect(float duration, bool active);

	static void setEffectActive(const bool& newEffectState);
	static bool isEffectActive();
	static void setEffectDuration(const float& newduration);
	static void updateEffectDuration(const float& deltaduration);
	static float getEffectDuration();
	static void startEffect(const float& newduration);

	static unordered_map<Groups, vector<EntityType>> groups;
};

#endif
