#pragma once
#include "../links/includes.hpp"

class c_movement : public singleton <c_movement> {
public:
	void auto_jump();
	void auto_strafe(CUserCmd* m_pcmd);
	void automatic_peek(CUserCmd* cmd, float wish_yaw);
	void fake_duck(CUserCmd* cmd);
	void movement_fix(Vector& wish_angle, CUserCmd* m_pcmd);

};