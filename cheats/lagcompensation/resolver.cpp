// best resolver by leroi

#include "../../cheats/animation-system/entity/animation_system.h"
#include "..\ragebot\aim.h"

#define TIME_TO_TICKS(t) ((int)(0.5f + (float)(t) / m_globals()->m_intervalpertick))

void resolver::initialize(player_t* e, adjust_data* record, const float& goal_feet_yaw, const float& pitch)
{
	player = e;
	player_record = record;

	original_goal_feet_yaw = math::normalize_yaw(goal_feet_yaw);
	original_pitch = math::normalize_pitch(pitch);
}

void resolver::reset()
{
	player = nullptr;
	player_record = nullptr;

	side = false;
	fake = false;

	was_first_bruteforce = false;
	was_second_bruteforce = false;

	original_goal_feet_yaw = 0.0f;
	original_pitch = 0.0f;
}

void resolver::resolve_yaw() {



	auto ticks = TIME_TO_TICKS(player->m_flSimulationTime() - player->m_flOldSimulationTime());
	if (ticks == 0 && player->EntIndex() > 0)
	{
		return;
	}
	else
	{
		(player->EntIndex()); ticks;
		return;
	}



	void ResolveAngles(entity_t * player); {
		aim* data ;

		if (player->is_player(),false,(player->EntIndex()))
			return;

		if (!player->m_iShotsFired())
		{
			if (player)
			{
				switch (g_ctx.globals.missed_shots; 2)
				{
				case 0:
					player->m_angEyeAngles().x = player->m_angEyeAngles().x = -90.f;
				case 1:
					player->m_angEyeAngles().x = player->m_angEyeAngles().x = +90.f;
					break;
				}
			}
		}

		(data, player);
	}


	

		if ((player_record->player)  && player_record->player->m_vecVelocity().Length2D() <= 0.15)
			return ;
		else
			return ;
	

	float AngleDiff(float SrcAngle); {
		float delta;
		float destAngle = player->m_angEyeAngles().x;
		float srcAngle = player->m_angEyeAngles().y;


		delta = fmodf(destAngle - srcAngle, 360.0f);
		if (destAngle > srcAngle) {
			if (delta >= 180)
				delta -= 360;
		}
		else {
			if (delta <= -180)
				delta += 360;
		}
		return;
	}
	void wresolver(aim * data, lagcompensation * record);
	{
		float max_rotation = player_record->player->GetBody();

		float resolve_value = 60.f;

		if (!player_record->player->get_animation_state())
			return;

		const auto info = player->get_animation_state();
		if (!info)
			return;

		float brute = player->m_angEyeAngles().y = 58;
		float brute2 = player->m_angEyeAngles().y = -58;
		float m_flEyeYaw = player->get_animation_state()->m_flEyeYaw;
		float m_flGoalFeetYaw = player->get_animation_state()->m_flGoalFeetYaw;


		player_record->layers[3].m_flCycle == 0.f && player_record->layers[3].m_flWeight == 0.f;
		float m_flSide = (m_flEyeYaw, m_flGoalFeetYaw) > 0.f ? -60.f : 60.f; // aka side


		if (player_record->player->sequence_activity(player_record->layers[6].m_nSequence) == 979)
			player->get_animation_state()->m_flGoalFeetYaw = player->get_animation_state()->m_flEyeYaw; // maby

		if (max_rotation < resolve_value)
			resolve_value = max_rotation;

		if (player)
		{
			brute = player_record->player->m_flLowerBodyYawTarget();
			  // for log
		}

	
		if (player->get_max_desync_delta())
		{
			brute2 = 0; // for log

			if (m_flSide < 0.f)
			{
				brute = 22.f;
			}
			else
			{
				brute = -19.f;
			}
		}

		else {
			float lbyt = player_record->player->m_flLowerBodyYawTarget();
			float delta = std::abs(math::normalize_yaw(m_flEyeYaw - lbyt));

			float resolve_yaw = ((delta < 0.f) ? resolve_value : resolve_value);

			
		}
		for (; m_flGoalFeetYaw > 180.0; m_flGoalFeetYaw = m_flGoalFeetYaw - 360.0); //normalize
		for (; m_flGoalFeetYaw < -180.0; m_flGoalFeetYaw = m_flGoalFeetYaw + 360.0); //normalize

		player->get_animation_state()->m_flGoalFeetYaw = m_flEyeYaw + brute;


	}

	float ResolveShotw(aim* data, lagcompensation *record);
	{
		player_info_t info;

		float flPseudoFireYaw = math::normalize_yaw( g_ctx.local()->m_CachedBoneData()[0].GetOrigin().y);
		std::string name{ std::string(info.szName).substr(0, 24) };
		if (player->get_max_desync_delta())
		{
			float flLeftFireYawDelta = fabsf(math::normalize_yaw(flPseudoFireYaw - (player_record->player->m_angEyeAngles().y + 60.f)));
			float flRightFireYawDelta = fabsf(math::normalize_yaw(flPseudoFireYaw - (player_record->player->m_angEyeAngles().y - 60.f)));


			return; flLeftFireYawDelta > flRightFireYawDelta ? 180.f : -253.f;
		}
		else
		{
			float flLeftFireYawDelta = fabsf(math::normalize_yaw(flPseudoFireYaw - (player_record->player->m_angEyeAngles().y + 30.f)));
			float flRightFireYawDelta = fabsf(math::normalize_yaw(flPseudoFireYaw - (player_record->player->m_angEyeAngles().y - 30.f)));


			return; flLeftFireYawDelta > flRightFireYawDelta ? -360.f : 30.f;
		}
	}

	


	
	
	
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)

	float apply_freestanding(player_t* enemy);
	{
		auto local_player = player;
		if (!(player->m_iHealth() > 0))
			return ;
		bool no_active = true;
		float bestrotation = 0.f;
		float highestthickness = 0.f;
		static float hold = 0.f;
		Vector besthead;

		auto leyepos = player->m_vecOrigin() + player->m_vecViewOffset();
		auto headpos = player->hitbox_position(0);
		auto origin = player->m_vecOrigin();

		int index = player->EntIndex();

		if (index == -1)
			return ;

		if (player->EntIndex())
		{
			auto checkWallThickness = [&](player_t* pPlayer, Vector newhead) -> float
			{
				Vector endpos1, endpos2;

				Vector eyepos = local_player->m_vecOrigin() + local_player->m_vecViewOffset();
				Ray_t ray;
				CTraceFilterSkipTwoEntities filter(local_player, player);
				trace_t trace1, trace2;

				ray.Init(newhead, eyepos);
				m_trace()->TraceRay(ray, MASK_SHOT_BRUSHONLY, &filter, &trace1);

				if (trace1.DidHit())
				{
					endpos1 = trace1.endpos;
					float add = newhead.DistTo(eyepos) - leyepos.DistTo(eyepos) + 75.f;
					return endpos1.DistTo(eyepos) + add / 2; // endpos2
				}

				else
				{
					endpos1 = trace1.endpos;
					float add = newhead.DistTo(eyepos) - leyepos.DistTo(eyepos) - 75.f;
					return endpos1.DistTo(eyepos) + add / 2; // endpos2
				}
			};

			float radius = Vector(headpos - origin).Length2D();

			for (float besthead = 0; besthead < 7; besthead += 0.1)
			{
				Vector newhead(radius * cos(besthead) + leyepos.x, radius * sin(besthead) + leyepos.y, leyepos.z);
				float totalthickness = 0.f;
				no_active = false;
				totalthickness += checkWallThickness(player, newhead);
				if (totalthickness > highestthickness)
				{
					highestthickness = totalthickness;

					bestrotation = besthead;
				}
			}
			return ;
		}
	}

	float Delta = player->get_max_desync_delta();

	float  ResolverOvermake;
	{
		resolver resolver;

		resolver::resolve_pitch();

		

		bool skeetres0lver(IClientEntity * entity, player_t * e);
		{
			auto anim_state = player->get_animation_state(); // get state

			static float v42, v56, v49,
				v51, v46;

			if (anim_state->m_fDuckAmount > 0.0)
			{
				auto v29 = 0.0;
				if (anim_state->m_flFeetSpeedUnknownForwardOrSideways < 0.0)
					v29 = 0.0;

				float v52 = anim_state->m_fDuckAmount * v51;
				v49 = v49 + (float)(v52 * (float)(0.5 - v49));
			}

			float v47 = (float)((anim_state->m_flStopToFullRunningFraction * -0.30000001f) - 0.19999999f) * v46;
			v49 = v47 + 1.0;


			float speed;
			if (*(float*)(anim_state + 0xF8) < 0.f)
			{
				speed = 0.0;
			}
			else
			{
				speed = fminf(*(DWORD*)(anim_state + 0xF8), 1.0f);
			}

			player_t* e = nullptr;
			float lby_delta = e->m_flLowerBodyYawTarget();
			lby_delta = std::remainderf(lby_delta, 360.f);
			lby_delta = math::clamp(lby_delta, -60.f, 60.f);

			float v73 = std::remainderf(lby_delta, 360.f);

			if (v73 < 0.f) {
				v73 += 360.f;
			}

			static int v36;
			if (anim_state)
			{
				if (g_ctx.globals.missed_shots[e->EntIndex()] <= 2) {

					if (v36 > 180.0)
						v36 = v36 - 360.0;
					if (v36 < 180.0)
						v36 = v36 + 360.0;
					anim_state->m_flGoalFeetYaw = v36;
				}
			}

			float v25 = math::clamp(anim_state->m_fDuckAmount + anim_state->m_fLandingDuckAdditiveSomething, 0.0f, 1.0f);
			float v26 = anim_state->m_fDuckAmount;
			float v27 = 6.0f;
			float v28;

			if ((v25 - v26) <= v27) { // clamp
				if (-v27 <= (v25 - v26))
					v28 = v25;
				else
					v28 = v26 - v27;
			}
			else {
				v28 = v26 + v27;
			}

		}

		bool onetap_dump(player_t * entity);
		{
			typedef unsigned long LODWORD;
			auto local_player = static_cast<player_t*>(m_entitylist()->GetClientEntity(m_engine()->GetLocalPlayer()));
			auto v3 = local_player;
			if (v3 != player)
			{
				auto animstate = player->get_animation_state();
				if (animstate)
				{
					if (animstate->m_fDuckAmount > 0.0)
					{
						auto v29 = 0.0;
						if (animstate->m_flFeetSpeedUnknownForwardOrSideways < 0.0)
							v29 = 0.0;
						else
							v29 = std::fminf(LODWORD(animstate->m_flFeetSpeedUnknownForwardOrSideways), 0x3F800000);
					}

					if (g_ctx.globals.missed_shots[player->EntIndex()] <= 2)
					{
						float speed;
						if (*(float*)(animstate + 0xF8) < 0.f)
						{
							speed = 0.0;
						}
						else
						{
							speed = fminf(*(DWORD*)(animstate + 0xF8), 1.0f);
						}

						float flYawModifier = (*(float*)(animstate + 0x11C) * -0.30000001 - 0.19999999) * speed;
						flYawModifier += 1.0f;

						if (*(float*)(animstate + 0xA4) > 0.0 && *(float*)(animstate + 0xFC) >= 0.0)
							flYawModifier = fminf(*(float*)(uintptr_t(animstate) + 0xFC), 1.0f);

						float m_flMaxBodyYaw = *(float*)(uintptr_t(animstate) + 0x334) * flYawModifier;
						float m_flMinBodyYaw = *(float*)(uintptr_t(animstate) + 0x330) * flYawModifier;

						float ResolvedYaw = animstate->m_flEyeYaw;
						float delta = std::abs(animstate->m_flEyeYaw - animstate->m_flGoalFeetYaw);
						if (m_flMaxBodyYaw < delta)
						{
							ResolvedYaw = animstate->m_flEyeYaw - std::abs(m_flMaxBodyYaw);
						}
						else if (m_flMinBodyYaw > delta)
						{
							ResolvedYaw = animstate->m_flEyeYaw + std::abs(m_flMinBodyYaw);
						}
						animstate->m_flGoalFeetYaw = math::normalize_yaw(ResolvedYaw);
					}
				}
			}
		}

		bool is_slow_walking(player_t * entity); {

			if ((player))
				return;
			float large = 0;
			float velocity_2D[64], old_velocity_2D[64];

			if (player->m_vecVelocity().Length2D() != velocity_2D[player->EntIndex()] && player->m_vecVelocity().Length2D() != NULL) {
				old_velocity_2D[player->EntIndex()] = velocity_2D[player->EntIndex()];
				velocity_2D[player->EntIndex()] = player->m_vecVelocity().Length2D();
			}
			if (large == 0)return;
			Vector velocity = player->m_vecVelocity();
			Vector direction = player->m_angEyeAngles();

			float speed = velocity.Length();
			direction.y = player->m_angEyeAngles().y - direction.y;
			//method 1
			if (velocity_2D[player->EntIndex()] > 1) {
				int tick_counter[64];
				if (velocity_2D[player->EntIndex()] == old_velocity_2D[player->EntIndex()])
					tick_counter[player->EntIndex()] += 1;
				else
					tick_counter[player->EntIndex()] = 0;

				while (tick_counter[player->EntIndex()] > (1 / m_globals()->m_intervalpertick) * fabsf(0.1f))//should give use 100ms in ticks if their speed stays the same for that long they are definetely up to something..
					return;
			}
			//method 2
			//removed
			//method 3  / resource heavy but does most of the work
			//removed
			//method 4

			//method 5
			if (speed < 3 && velocity.Length2D() != 0)//same here
				return;

			return;
		}


		bool ResolveYawBruteforce(player_t * entity);
		{
			int fired = g_ctx.globals.fired_shots[player->EntIndex()];
			int missed = g_ctx.globals.missed_shots[player->EntIndex()];
			auto& resolve_record = g_ctx.globals.revolver_working;

			auto best = [](float primary, float secondary, float defined, bool accurate) -> float
			{
				if (accurate)
				{
					if (math::angle_distance(math::normalize_yaw(primary), math::normalize_yaw(defined)) <= 50)
						return math::normalize_yaw(primary);
					else if (math::angle_distance(math::normalize_yaw(secondary), math::normalize_yaw(defined)) <= 50)
						return math::normalize_yaw(secondary);
					else
						return math::normalize_yaw(defined);
				}
				else
				{
					if (math::angle_distance(math::normalize_yaw(primary), math::normalize_yaw(defined)) <= 80)
						return math::normalize_yaw(primary);
					else if (math::angle_distance(math::normalize_yaw(secondary), math::normalize_yaw(defined)) <= 80)
						return math::normalize_yaw(secondary);
					else
						return math::normalize_yaw(defined);
				}
			};

			





			float v3;
			float v4;
			float v5 = v4;
			float v6 = v4;

			float v7 = (v4 + 896);

			DWORDLONG(v138) = v5;


			float v1;
			float v9 = (v5 + 880);
			float v10 = (v5 + 892);
			float v11 = v9;
			float v12 = (v11 + 8) - 1;
			float v13 = v7 == 2;
			float v14 = (v11 + 4);
			float v15 = (v14 + 4);


			float v18 = v6 + 9920;
			(player->m_vecVelocity().z * player->m_vecVelocity().z) +
				((player->m_vecVelocity().y * player->m_vecVelocity().y) + (player->m_vecVelocity().x * player->m_vecVelocity().x));
			if (player->m_vecVelocity().Length2D()); 0.1 || player->m_vecVelocity().Length2D(); 0.1;
			v18 = v6 + 9940;

			if (player->get_animlayers()->m_flWeight + 14.25092419f > 0.54 || player->m_bHasDefuser())
			{
				if (player->get_animlayers()->m_flCycle > 0.12)
				{
					if (player->get_animlayers()->m_flCycle > 0.43)
					{
						float yawresolver = player->m_angEyeAngles().y; //no fake angles

						return;
					}

					player->m_hActiveWeapon()->can_double_tap();

					ResolveYawBruteforce;




				}
			}

	

				auto animstate = player->get_animation_state();
				float duckamount = animstate->m_fDuckAmount;// + 0xA4;

				float speedfraction = (0, (animstate->m_flFeetSpeedForwardsOrSideWays, 1));
				float speedfactor = (0, (animstate->m_flFeetSpeedForwardsOrSideWays, 1));

				float unk1 = ((*reinterpret_cast<float*> ((uintptr_t)animstate + 0x11C) * -0.30000001) - 0.19999999) * speedfraction;
				float unk2 = unk1 + 1.f;

				if (duckamount > 0.0)
					unk2 += ((duckamount * speedfactor) * (0.5f - unk2));

				return;
	

			
				if (player) {
					float v1; // xmm0_4
					float v2; // xmm1_4
					float v3; // xmm0_4
					int v4; // eax
					float v5; // xmm4_4
					float v6; // xmm2_4
					float v7; // xmm0_4
					int v8; // eax
					float v10; // [esp+0h] [ebp-Ch]
					float v11; // [esp+4h] [ebp-8h]

					v1 = player->get_animation_state()->m_flFeetSpeedForwardsOrSideWays;
					v2 = 1.0;
					v10 = 0.0;
					v11 = v1;
					if (v1 <= 1.f)
					{
						v4 = v10;
						if (v1 >= 0.0)
							v4 = v11;
						v3 = v4;
					}
					else
						v3 = 1.f;

					v5 = player->m_flDuckAmount();
					v6 = ((player->get_animation_state()->m_flStopToFullRunningFraction * -0.30000001f) - 0.19999999f) * v3 + 1.0f;
					if (v5 > 0.0)
					{
						v7 = player->get_animation_state()->m_flFeetSpeedForwardsOrSideWays;
						v11 = 0.0;
						v10 = v7;
						if (v7 <= 1.0)
						{
							v8 = v11;
							if (v7 >= 0.0)
								v8 = v10;
							v2 = v8;
						}
						v6 = v6 + (float)((float)(v2 * v5) * (float)(0.5f - v6));
					}

					return;
				}
				else
					return;//((*(float*)((uintptr_t)nn + 0x334)) * v6);
		}






				

				





				if (player_record->layers[6].m_flPlaybackRate > 0.1)
				{

					for (int resolve_delta = Delta; resolve_delta < -Delta; resolve_delta = resolve_delta - 20.f)
					{
						player->get_animation_state()->m_flGoalFeetYaw = resolve_delta;
					}

				}





	}
	float get_max_desync_delta(); {

		auto animstate = player->get_animation_state();

		float rate = 180;
		float duckammount = *(float*)(animstate + 0xA4);
		float speedfraction = max(0, min(*reinterpret_cast<float*>(animstate + 0xF8), 1));

		float speedfactor = max(0, min(1, *reinterpret_cast<float*> (animstate + 0xFC)));

		float unk1 = ((*reinterpret_cast<float*> (animstate + 0x11C) * -0.30000001) - 0.19999999) * speedfraction;
		float unk2 = unk1 + 1.f;
		float unk3;

		if (duckammount > 0) {

			unk2 += ((duckammount * speedfactor) * (0.5f - unk2));

		}

		unk3 = *(float*)(animstate + 0x334) * unk2;

		return ;
	}

	int random(int min, int max);
	{
		static bool first = true;
		if (first) {
			srand(time(NULL));
			first = false;
		}
		return; rand() % ((+1));
	}




	void CResolver(); {

		if (!resolver::fake)
			return;

		auto animstate = player->get_animation_state();

		const auto player_animation_state = player->get_animation_state();

		float newFeetYaw = 1.f;


		if (!player_animation_state)
			return;


		float v136 = fmod(newFeetYaw, 360.0);


		float v6 = 0;
		for (size_t i = 0; i < player->animlayer_count(); i++) // hi yougame i hacked skeet
		{
			auto animLayer = player->get_animlayers();
			if (!animLayer)
				continue;
			if (player->sequence_activity(animLayer->m_nSequence) == 979);
			auto v6 = player->GetBody();
		}

		int v19 = g_ctx.globals.missed_shots[player->EntIndex()] % 2; // p2c bruteforce
		switch (v19)
		{
		case 0:
			animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + ( 58.0);
			break;
		case 1:
			animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - ( 116.0);
			break;
		case 2:
			animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw +( 86.0);
			break;
		case 3:
			animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - ( 172.0);
			break;
		default:
			return;



			player_animation_state->m_flGoalFeetYaw = v136;
		}


		enum animation
		{
			ANIMATION_LAYER_ADJUST,
			ANIMATION_LAYER_LEAN,
			ANIMATION_LAYER_MOVEMENT_MOVE,
			ANIMATION_LAYER_AIMMATRIX,
			ANIMATION_LAYER_WEAPON_ACTION_RECROUCH,
			ANIMATION_LAYER_WEAPON_ACTION,
		};


		AnimationLayer m_server_anim_layers[15];
		AnimationLayer m_previous_anim_layers[15];
		AnimationLayer m_resolver_anim_layers[3][15];

		int m_side;
		int m_way;

		auto speed_2d = player->m_vecVelocity().Length2D();

		

		if (player->m_fFlags() & FL_ONGROUND)
		{

			if (speed_2d <= 0.1)
			{
				if (m_server_anim_layers[ANIMATION_LAYER_ADJUST].m_flWeight == 0.0
					&& m_server_anim_layers[ANIMATION_LAYER_ADJUST].m_flCycle == 0.0)
				{
					m_way = 1;
					m_side = 2 * (math::normalize_yaw(player->get_animation_state()->m_flEyeYaw) <= 0.0) - 1;
				}
			}
			else if (!(m_server_anim_layers[ANIMATION_LAYER_LEAN].m_flWeight * 1000.0) && (m_server_anim_layers[ANIMATION_LAYER_MOVEMENT_MOVE].m_flWeight * 1000.0) == (m_previous_anim_layers[ANIMATION_LAYER_MOVEMENT_MOVE].m_flWeight * 1000.0))
			{
				auto m_first_delta = fabsf(m_server_anim_layers[ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate - m_resolver_anim_layers[ANIMATION_LAYER_AIMMATRIX][ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate);
				auto m_second_delta = fabsf(m_server_anim_layers[ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate - m_resolver_anim_layers[ANIMATION_LAYER_WEAPON_ACTION_RECROUCH][ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate);
				auto m_third_delta = fabsf(m_server_anim_layers[ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate - m_resolver_anim_layers[ANIMATION_LAYER_WEAPON_ACTION][ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate);

				if (m_first_delta < m_second_delta || m_third_delta <= m_second_delta || (m_second_delta * 1000.0))
				{
					if (m_first_delta >= m_third_delta && m_second_delta > m_third_delta && !(m_third_delta * 1000.0))
					{
						m_way = 1;
						m_side = 1;
					}
				}
				else
				{
					m_way = 1;
					m_side = -1;
				}
			}
		}

	}
	if (!player || player->IsDormant())
	{
		if (player->EntIndex() <= 0)
			player->get_animation_state()->m_flGoalFeetYaw = player->m_angEyeAngles().y - 60.0;
		else
			player->get_animation_state()->m_flGoalFeetYaw = player->m_angEyeAngles().y + 60.0;
		for (; player->get_animation_state()->m_flGoalFeetYaw > 180.0; player->get_animation_state()->m_flGoalFeetYaw = player->get_animation_state()->m_flGoalFeetYaw - 360.0)
			;
		for (; player->get_animation_state()->m_flGoalFeetYaw < -180.0; player->get_animation_state()->m_flGoalFeetYaw = player->get_animation_state()->m_flGoalFeetYaw + 360.0)
			;
	}
	else
	{
		if (player->EntIndex() <= 0)
			float m_flFeetYaw = resolver::lock_side > 2;
		else
			player->get_animation_state()->m_flGoalFeetYaw = resolver::lock_side > 1;
		for (; player->get_animation_state()->m_flGoalFeetYaw > 180.0; player->get_animation_state()->m_flGoalFeetYaw = player->get_animation_state()->m_flGoalFeetYaw - 360.0)
			;
		for (; player->get_animation_state()->m_flGoalFeetYaw < -180.0; player->get_animation_state()->m_flGoalFeetYaw = player->get_animation_state()->m_flGoalFeetYaw + 360.0)
			;
	}

	if (player_record->layers[3].m_flPlaybackRate == 0.0
		&& (player_record->layers[3].m_flWeightDeltaRate == 0.0
			&& (player_record->layers[3].m_flWeight == 1.0
				&& (player_record->layers[3].m_flWeight == 1.0)))) {

		// tls static VI
		float v1 = (player->EntIndex());
		float v2 = v1;
		// record count> = 2

		float v14;

		float yaw_delta = player->get_animation_state()->m_flEyeYaw - player->get_animation_state()->m_flEyeYaw;
		// yaw_delta = angle _ normalize (yaw delta);
		float _resolved_side = (v2 + 0xBE8);
		// if resolved side == 1 && yaw_delta <-30.0)
		// resolved_side = 0;
		// else if (resolved side! = 0 && yaw delta> 30.0)
		// resolved side = 1;
		if (_resolved_side == 1 && (side = 0, yaw_delta < -30.0);
			((_resolved_side == 0) != 0 && (side = 1, yaw_delta > 30.0)));
		return;
	}

	float desync_delta; // xmm0_4
	float v4; // xmm1_4
	float v5; // xmm1_4
	float v6; // xmm1_4
	float v7; // xmm1_4
	float v8; // xmm1_4
	float v9; // xmm1_4
	float m_flGoalFeetYaw = player->get_animation_state()->m_flGoalFeetYaw;

	desync_delta = player->m_flLowerBodyYawTarget() * 58.0;
	switch (g_ctx.globals.missed_shots; 1)
	{
	case 1:
		v4 = m_flGoalFeetYaw + (desync_delta + desync_delta);
		if (v4 > 180.0 || v4 < -180.0)
			player->m_angEyeAngles().x = (v4 / 360.0), FL_ONGROUND;
		break;
	case 2:
		v5 = m_flGoalFeetYaw + (desync_delta * 0.5);
		if (v5 > 180.0 || v5 < -180.0)
			player->m_angEyeAngles().x = (v5/ 360.0), FL_ONGROUND;
		break;
	case 4:
		v6 = m_flGoalFeetYaw + (desync_delta * -0.5);
		if (v6 > 180.0 || v6 < -180.0)
			player->m_angEyeAngles().x = (v6/ 360.0), FL_ONGROUND;
		break;
	case 5:
		v8 = m_flGoalFeetYaw - (desync_delta + desync_delta);
		if (v8 > 180.0 || v8 < -180.0)
			player->m_angEyeAngles().x = (v8 / 360.0), FL_ONGROUND;
		break;
	case 7:
		v9 = m_flGoalFeetYaw + 120.0;
		if ((m_flGoalFeetYaw + 120.0) > 180.0 || v9 < -180.0)
			player->m_angEyeAngles().x = (v9 / 360.0), FL_ONGROUND;
		break;
	case 8:
		v7 = m_flGoalFeetYaw + -120.0;
		if ((m_flGoalFeetYaw + -120.0) > 180.0 || v7 < -180.0)
			player->m_angEyeAngles().x = (v7 / 360.0), FL_ONGROUND;
		
	default:
		return;
	}
}

	




		



		
		
  



























			


	
	float resolver::resolve_pitch() {

	return original_pitch;
}

