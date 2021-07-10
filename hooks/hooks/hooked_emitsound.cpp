#include "..\hooks.hpp"

void __fastcall hooks::hooked_emitsound(void* thisptr, void* edx, IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, int nSeed, float flAttenuation, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, int unk) {
	static auto original_fn = engine_sound_hook->get_func_address <EmitSound_t>(5);

	// find match accept sound.
	if (!strcmp(pSoundEntry, "UIPanorama.popup_accept_match_beep") && g_cfg.misc.auto_accept) {
		static auto match_accept = reinterpret_cast<bool(__stdcall*)(const char*)>(util::FindSignature(crypt_str("client.dll"), crypt_str("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));

		// run auto accept.
		if (match_accept) {
			match_accept("");
		}
	}

	// call og.
	original_fn(thisptr, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, nSeed, flAttenuation, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, unk);
}