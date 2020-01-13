#pragma once
class Powerup
{
public:
	Powerup(const char name[30] , float health, float attack, float defence);
	~Powerup();


	char* getName();
	float getHealthMultiplier();
	float getAttackMultiplier();
	float getDefenceMultiplier();

private:
	char m_name[30];

	float m_healthMultiplier;
	float m_attackMultiplier;
	float m_defenceMultiplier;
};
