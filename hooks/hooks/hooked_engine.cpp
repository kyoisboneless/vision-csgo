#include "../hooks.hpp"

bool __fastcall hooks::hooked_ishltv(void* ecx, void* edx) {
	static auto original_fn = engine_hook->get_func_address <IsHLTV_t>(93);

	static auto setup_velocity_call = util::FindSignature(crypt_str("client.dll"), crypt_str("84 C0 75 38 8B 0D ? ? ? ? 8B 01 8B 80 ? ? ? ? FF D0"));

	// AccumulateLayers
	if (g_ctx.globals.setuping_bones)
		return true;

	// fix for animstate velocity.
	if (uintptr_t(_ReturnAddress()) == setup_velocity_call)
		return true;

	return original_fn(ecx);
}

bool __fastcall hooks::hooked_isconnected(void* ecx, void* edx) {
	static auto original_fn = engine_hook->get_func_address <IsConnected_t>(27);

	if (!g_cfg.misc.inventory_access || !m_engine()->IsInGame())
		return original_fn(ecx);

	static auto inventory_access = util::FindSignature(crypt_str("client.dll"), crypt_str("84 C0 75 04 B0 01 5F"));

	if ((DWORD)_ReturnAddress() != inventory_access)
		return original_fn(ecx);

	return false;
}

float __fastcall hooks::hooked_getscreenaspectratio(void* ecx, void* edx, int width, int height) {
	static auto original_fn = engine_hook->get_func_address <GetScreenAspectRatio_t>(101);

	if (!g_cfg.misc.aspect_ratio)
		return original_fn(ecx, width, height);

	return g_cfg.misc.aspect_ratio_amount;
}