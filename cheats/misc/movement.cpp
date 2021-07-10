#include "movement.h"
#include "..\misc\prediction_system.h"

#define CheckIfNonValidNumber(x) (fpclassify(x) == FP_INFINITE || fpclassify(x) == FP_NAN || fpclassify(x) == FP_SUBNORMAL)

void c_movement::auto_jump() {
	if (g_ctx.local()->get_move_type() == MOVETYPE_LADDER) //-V807
		return;

	if (!g_cfg.misc.bunnyhop)
		return;

	static auto last_jumped = false;
	static auto should_jump = false;

	if (!last_jumped && should_jump)
	{
		should_jump = false;
		g_ctx.get_command()->m_buttons |= IN_JUMP;
	}
	else if (g_ctx.get_command()->m_buttons & IN_JUMP)
	{
		if (g_ctx.local()->m_fFlags() & FL_ONGROUND || !g_ctx.local()->m_vecVelocity().z)
		{
			last_jumped = true;
			should_jump = true;
		}
		else
		{
			g_ctx.get_command()->m_buttons &= ~IN_JUMP;
			last_jumped = false;
		}
	}
	else
	{
		last_jumped = false;
		should_jump = false;
	}
}

void c_movement::auto_strafe(CUserCmd* m_pcmd) //-V2008
{
	if (g_ctx.local()->get_move_type() == MOVETYPE_LADDER) //-V807
		return;

	if (g_ctx.local()->m_fFlags() & FL_ONGROUND || engineprediction::get().backup_data.flags & FL_ONGROUND)
		return;

	if (!g_cfg.misc.airstrafe)
		return;

	static auto cl_sidespeed = m_cvar()->FindVar(crypt_str("cl_sidespeed"));
	auto side_speed = cl_sidespeed->GetFloat();

	if (g_cfg.misc.airstrafe == 1)
	{
		Vector engine_angles;
		m_engine()->GetViewAngles(engine_angles);

		auto velocity = g_ctx.local()->m_vecVelocity();

		m_pcmd->m_forwardmove = min(5850.0f / velocity.Length2D(), side_speed);
		m_pcmd->m_sidemove = m_pcmd->m_command_number % 2 ? side_speed : -side_speed;

		auto yaw_velocity = math::calculate_angle(Vector(0.0f, 0.0f, 0.0f), velocity).y;
		auto ideal_rotation = math::clamp(RAD2DEG(atan2(15.0f, velocity.Length2D())), 0.0f, 45.0f);

		auto yaw_rotation = fabs(yaw_velocity - engine_angles.y) + (m_pcmd->m_command_number % 2 ? ideal_rotation : -ideal_rotation);
		auto ideal_yaw_rotation = yaw_rotation < 5.0f ? yaw_velocity : engine_angles.y;

		util::RotateMovement(m_pcmd, ideal_yaw_rotation);
	}
	else if (g_cfg.misc.airstrafe == 2)
	{
		static auto old_yaw = 0.0f;

		auto get_velocity_degree = [](float velocity)
		{
			auto tmp = RAD2DEG(atan(30.0f / velocity));

			if (CheckIfNonValidNumber(tmp) || tmp > 90.0f)
				return 90.0f;

			else if (tmp < 0.0f)
				return 0.0f;
			else
				return tmp;
		};

		if (g_ctx.local()->get_move_type() != MOVETYPE_WALK)
			return;

		auto velocity = g_ctx.local()->m_vecVelocity();
		velocity.z = 0.0f;

		auto forwardmove = m_pcmd->m_forwardmove;
		auto sidemove = m_pcmd->m_sidemove;

		if (velocity.Length2D() < 5.0f && !forwardmove && !sidemove)
			return;

		static auto flip = false;
		flip = !flip;

		auto turn_direction_modifier = flip ? 1.0f : -1.0f;
		auto viewangles = m_pcmd->m_viewangles;

		if (forwardmove || sidemove)
		{
			m_pcmd->m_forwardmove = 0.0f;
			m_pcmd->m_sidemove = 0.0f;

			auto turn_angle = atan2(-sidemove, forwardmove);
			viewangles.y += turn_angle * M_RADPI;
		}
		else if (forwardmove) //-V550
			m_pcmd->m_forwardmove = 0.0f;

		auto strafe_angle = RAD2DEG(atan(15.0f / velocity.Length2D()));

		if (strafe_angle > 90.0f)
			strafe_angle = 90.0f;
		else if (strafe_angle < 0.0f)
			strafe_angle = 0.0f;

		auto temp = Vector(0.0f, viewangles.y - old_yaw, 0.0f);
		temp.y = math::normalize_yaw(temp.y);

		auto yaw_delta = temp.y;
		old_yaw = viewangles.y;

		auto abs_yaw_delta = fabs(yaw_delta);

		if (abs_yaw_delta <= strafe_angle || abs_yaw_delta >= 30.0f)
		{
			Vector velocity_angles;
			math::vector_angles(velocity, velocity_angles);

			temp = Vector(0.0f, viewangles.y - velocity_angles.y, 0.0f);
			temp.y = math::normalize_yaw(temp.y);

			auto velocityangle_yawdelta = temp.y;
			auto velocity_degree = get_velocity_degree(velocity.Length2D());

			if (velocityangle_yawdelta <= velocity_degree || velocity.Length2D() <= 15.0f)
			{
				if (-velocity_degree <= velocityangle_yawdelta || velocity.Length2D() <= 15.0f)
				{
					viewangles.y += strafe_angle * turn_direction_modifier;
					m_pcmd->m_sidemove = side_speed * turn_direction_modifier;
				}
				else
				{
					viewangles.y = velocity_angles.y - velocity_degree;
					m_pcmd->m_sidemove = side_speed;
				}
			}
			else
			{
				viewangles.y = velocity_angles.y + velocity_degree;
				m_pcmd->m_sidemove = -side_speed;
			}
		}
		else if (yaw_delta > 0.0f)
			m_pcmd->m_sidemove = -side_speed;
		else if (yaw_delta < 0.0f)
			m_pcmd->m_sidemove = side_speed;

		auto move = Vector(m_pcmd->m_forwardmove, m_pcmd->m_sidemove, 0.0f);
		auto speed = move.Length();

		Vector angles_move;
		math::vector_angles(move, angles_move);

		auto normalized_x = fmod(m_pcmd->m_viewangles.x + 180.0f, 360.0f) - 180.0f;
		auto normalized_y = fmod(m_pcmd->m_viewangles.y + 180.0f, 360.0f) - 180.0f;

		auto yaw = DEG2RAD(normalized_y - viewangles.y + angles_move.y);

		if (normalized_x >= 90.0f || normalized_x <= -90.0f || m_pcmd->m_viewangles.x >= 90.0f && m_pcmd->m_viewangles.x <= 200.0f || m_pcmd->m_viewangles.x <= -90.0f && m_pcmd->m_viewangles.x <= 200.0f) //-V648
			m_pcmd->m_forwardmove = -cos(yaw) * speed;
		else
			m_pcmd->m_forwardmove = cos(yaw) * speed;

		m_pcmd->m_sidemove = sin(yaw) * speed;
	}
	else if (g_cfg.misc.airstrafe == 3)
	{
		static auto old_yaw = 0.0f;

		auto get_velocity_degree = [](float velocity)
		{
			auto tmp = RAD2DEG(atan(30.0f / velocity));

			if (CheckIfNonValidNumber(tmp) || tmp > 90.0f)
				return 90.0f;

			else if (tmp < 0.0f)
				return 0.0f;
			else
				return tmp;
		};

		if (g_ctx.local()->get_move_type() != MOVETYPE_WALK)
			return;

		auto velocity = g_ctx.local()->m_vecVelocity();
		velocity.z = 0;

		static auto flip = false;
		flip = !flip;

		auto turn_direction_modifier = flip ? 1.0f : -1.0f;
		auto viewangles = m_pcmd->m_viewangles;

		auto strafe_angle = RAD2DEG(atan(15.0f / velocity.Length2D()));

		if (strafe_angle > 90.0f)
			strafe_angle = 90.0f;
		else if (strafe_angle < 0.0f)
			strafe_angle = 0.0f;

		auto temp = Vector(0.0f, viewangles.y - old_yaw, 0.0f);
		temp.y = math::normalize_yaw(temp.y);

		auto yaw_delta = temp.y;
		old_yaw = viewangles.y;

		auto abs_yaw_delta = fabs(yaw_delta);

		if (abs_yaw_delta <= strafe_angle || abs_yaw_delta >= 30.0f)
		{
			Vector velocity_angles;
			math::vector_angles(velocity, velocity_angles);

			temp = Vector(0.0f, viewangles.y - velocity_angles.y, 0.0f);
			temp.y = math::normalize_yaw(temp.y);

			auto velocityangle_yawdelta = temp.y;
			auto velocity_degree = get_velocity_degree(velocity.Length2D());

			if (velocityangle_yawdelta <= velocity_degree || velocity.Length2D() <= 15.0f)
			{
				if (-velocity_degree <= velocityangle_yawdelta || velocity.Length2D() <= 15.0f)
				{
					viewangles.y += strafe_angle * turn_direction_modifier;
					m_pcmd->m_sidemove = side_speed * turn_direction_modifier;
				}
				else
				{
					viewangles.y = velocity_angles.y - velocity_degree;
					m_pcmd->m_sidemove = side_speed;
				}
			}
			else
			{
				viewangles.y = velocity_angles.y + velocity_degree;
				m_pcmd->m_sidemove = -side_speed;
			}
		}
		else if (yaw_delta > 0.0f)
			m_pcmd->m_sidemove = -side_speed;
		else if (yaw_delta < 0.0f)
			m_pcmd->m_sidemove = side_speed;

		auto move = Vector(m_pcmd->m_forwardmove, m_pcmd->m_sidemove, 0.0f);
		auto speed = move.Length();

		Vector angles_move;
		math::vector_angles(move, angles_move);

		auto normalized_x = fmod(m_pcmd->m_viewangles.x + 180.0f, 360.0f) - 180.0f;
		auto normalized_y = fmod(m_pcmd->m_viewangles.y + 180.0f, 360.0f) - 180.0f;

		auto yaw = DEG2RAD(normalized_y - viewangles.y + angles_move.y);

		if (normalized_x >= 90.0f || normalized_x <= -90.0f || m_pcmd->m_viewangles.x >= 90.0f && m_pcmd->m_viewangles.x <= 200.0f || m_pcmd->m_viewangles.x <= -90.0f && m_pcmd->m_viewangles.x <= 200.0f) //-V648
			m_pcmd->m_forwardmove = -cos(yaw) * speed;
		else
			m_pcmd->m_forwardmove = cos(yaw) * speed;

		m_pcmd->m_sidemove = sin(yaw) * speed;
	}
}

void c_movement::automatic_peek(CUserCmd* cmd, float wish_yaw)
{
	if (!g_ctx.globals.weapon->is_non_aim() && key_binds::get().get_key_bind_state(18))
	{
		if (g_ctx.globals.start_position.IsZero())
		{
			g_ctx.globals.start_position = g_ctx.local()->GetAbsOrigin();

			if (!(engineprediction::get().backup_data.flags & FL_ONGROUND))
			{
				Ray_t ray;
				CTraceFilterWorldAndPropsOnly filter;
				CGameTrace trace;

				ray.Init(g_ctx.globals.start_position, g_ctx.globals.start_position - Vector(0.0f, 0.0f, 1000.0f));
				m_trace()->TraceRay(ray, MASK_SOLID, &filter, &trace);

				if (trace.fraction < 1.0f)
					g_ctx.globals.start_position = trace.endpos + Vector(0.0f, 0.0f, 2.0f);
			}
		}
		else
		{
			auto revolver_shoot = g_ctx.globals.weapon->m_iItemDefinitionIndex() == WEAPON_REVOLVER && !g_ctx.globals.revolver_working && (cmd->m_buttons & IN_ATTACK || cmd->m_buttons & IN_ATTACK2);

			if (cmd->m_buttons & IN_ATTACK && g_ctx.globals.weapon->m_iItemDefinitionIndex() != WEAPON_REVOLVER || revolver_shoot)
				g_ctx.globals.fired_shot = true;

			if (g_ctx.globals.fired_shot)
			{
				auto current_position = g_ctx.local()->GetAbsOrigin();
				auto difference = current_position - g_ctx.globals.start_position;

				if (difference.Length2D() > 5.0f)
				{
					auto velocity = Vector(difference.x * cos(wish_yaw / 180.0f * M_PI) + difference.y * sin(wish_yaw / 180.0f * M_PI), difference.y * cos(wish_yaw / 180.0f * M_PI) - difference.x * sin(wish_yaw / 180.0f * M_PI), difference.z);

					cmd->m_forwardmove = -velocity.x * 20.0f;
					cmd->m_sidemove = velocity.y * 20.0f;
				}
				else
				{
					g_ctx.globals.fired_shot = false;
					g_ctx.globals.start_position.Zero();
				}
			}
		}
	}
	else
	{
		g_ctx.globals.fired_shot = false;
		g_ctx.globals.start_position.Zero();
	}
}

void c_movement::fake_duck(CUserCmd* cmd) {
	// fakelag disabled.
	if (fakelag::get().condition) {
		g_ctx.globals.fakeducking = false;
		return;
	}

	// not on ground.
	if (!(g_ctx.local()->m_fFlags() & FL_ONGROUND && engineprediction::get().backup_data.flags & FL_ONGROUND)) {
		g_ctx.globals.fakeducking = false;
		return;
	}

	// valve server.
	if (m_gamerules()->m_bIsValveDS()) {
		g_ctx.globals.fakeducking = false;
		return;
	}

	// what is that shit??
	if (!key_binds::get().get_key_bind_state(20)) {
		g_ctx.globals.fakeducking = false;
		return;
	}

	if (!g_ctx.globals.fakeducking && m_clientstate()->iChokedCommands != 7)
		return;

	if (m_clientstate()->iChokedCommands >= 7)
		cmd->m_buttons |= IN_DUCK;
	else
		cmd->m_buttons &= ~IN_DUCK;

	g_ctx.globals.fakeducking = true;
}

void c_movement::movement_fix(Vector& wish_angle, CUserCmd* m_pcmd) {
	Vector view_fwd, view_right, view_up, cmd_fwd, cmd_right, cmd_up;
	auto viewangles = m_pcmd->m_viewangles;
	viewangles.Normalized();

	// roll nospread fix.
	if (!(g_ctx.local()->m_fFlags() & FL_ONGROUND) && viewangles.z != 0.f)
		m_pcmd->m_sidemove = 0.f;

	math::angle_vectors(wish_angle, &view_fwd, &view_right, &view_up);
	math::angle_vectors(viewangles, &cmd_fwd, &cmd_right, &cmd_up);

	float v8 = sqrtf((view_fwd.x * view_fwd.x) + (view_fwd.y * view_fwd.y));
	float v10 = sqrtf((view_right.x * view_right.x) + (view_right.y * view_right.y));
	float v12 = sqrtf(view_up.z * view_up.z);

	Vector norm_view_fwd((1.f / v8) * view_fwd.x, (1.f / v8) * view_fwd.y, 0.f);
	Vector norm_view_right((1.f / v10) * view_right.x, (1.f / v10) * view_right.y, 0.f);
	Vector norm_view_up(0.f, 0.f, (1.f / v12) * view_up.z);

	float v14 = sqrtf((cmd_fwd.x * cmd_fwd.x) + (cmd_fwd.y * cmd_fwd.y));
	float v16 = sqrtf((cmd_right.x * cmd_right.x) + (cmd_right.y * cmd_right.y));
	float v18 = sqrtf(cmd_up.z * cmd_up.z);

	Vector norm_cmd_fwd((1.f / v14) * cmd_fwd.x, (1.f / v14) * cmd_fwd.y, 0.f);
	Vector norm_cmd_right((1.f / v16) * cmd_right.x, (1.f / v16) * cmd_right.y, 0.f);
	Vector norm_cmd_up(0.f, 0.f, (1.f / v18) * cmd_up.z);

	float v22 = norm_view_fwd.x * m_pcmd->m_forwardmove;
	float v26 = norm_view_fwd.y * m_pcmd->m_forwardmove;
	float v28 = norm_view_fwd.z * m_pcmd->m_forwardmove;
	float v24 = norm_view_right.x * m_pcmd->m_sidemove;
	float v23 = norm_view_right.y * m_pcmd->m_sidemove;
	float v25 = norm_view_right.z * m_pcmd->m_sidemove;
	float v30 = norm_view_up.x * m_pcmd->m_upmove;
	float v27 = norm_view_up.z * m_pcmd->m_upmove;
	float v29 = norm_view_up.y * m_pcmd->m_upmove;

	m_pcmd->m_forwardmove = ((((norm_cmd_fwd.x * v24) + (norm_cmd_fwd.y * v23)) + (norm_cmd_fwd.z * v25))
		+ (((norm_cmd_fwd.x * v22) + (norm_cmd_fwd.y * v26)) + (norm_cmd_fwd.z * v28)))
		+ (((norm_cmd_fwd.y * v30) + (norm_cmd_fwd.x * v29)) + (norm_cmd_fwd.z * v27));
	m_pcmd->m_sidemove = ((((norm_cmd_right.x * v24) + (norm_cmd_right.y * v23)) + (norm_cmd_right.z * v25))
		+ (((norm_cmd_right.x * v22) + (norm_cmd_right.y * v26)) + (norm_cmd_right.z * v28)))
		+ (((norm_cmd_right.x * v29) + (norm_cmd_right.y * v30)) + (norm_cmd_right.z * v27));
	m_pcmd->m_upmove = ((((norm_cmd_up.x * v23) + (norm_cmd_up.y * v24)) + (norm_cmd_up.z * v25))
		+ (((norm_cmd_up.x * v26) + (norm_cmd_up.y * v22)) + (norm_cmd_up.z * v28)))
		+ (((norm_cmd_up.x * v30) + (norm_cmd_up.y * v29)) + (norm_cmd_up.z * v27));

	static auto cl_forwardspeed = m_cvar()->FindVar(crypt_str("cl_forwardspeed"));
	static auto cl_sidespeed = m_cvar()->FindVar(crypt_str("cl_sidespeed"));
	static auto cl_upspeed = m_cvar()->FindVar(crypt_str("cl_upspeed"));

	m_pcmd->m_forwardmove = math::clamp(m_pcmd->m_forwardmove, -cl_forwardspeed->GetFloat(), cl_forwardspeed->GetFloat());
	m_pcmd->m_sidemove = math::clamp(m_pcmd->m_sidemove, -cl_sidespeed->GetFloat(), cl_sidespeed->GetFloat());
	m_pcmd->m_upmove = math::clamp(m_pcmd->m_upmove, -cl_upspeed->GetFloat(), cl_upspeed->GetFloat());
}