// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "..\hooks.hpp"

void __fastcall hooks::hooked_clip_ray_collideable(void* ecx, void* edx, const Ray_t& ray, uint32_t fMask, ICollideable* pCollide, CGameTrace* pTrace)
{
	static auto original_fn = trace_hook->get_func_address <ClipRayCollideable_t> (4);

	auto backup_maxs = pCollide->OBBMaxs().z;
	pCollide->OBBMaxs().z += 5.0f;

	original_fn(ecx, ray, fMask, pCollide, pTrace);
	pCollide->OBBMaxs().z = backup_maxs;
}

void __fastcall hooks::hooked_trace_ray(void* ecx, void* edx, const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace)
{
	static auto original_fn = trace_hook->get_func_address <TraceRay_t> (5);

	if (!g_ctx.globals.autowalling)
		return original_fn(ecx, ray, fMask, pTraceFilter, pTrace);

	original_fn(ecx, ray, fMask, pTraceFilter, pTrace);
	pTrace->surface.flags |= SURF_SKY;
}