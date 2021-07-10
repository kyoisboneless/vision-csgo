#include "../hooks.hpp"

void __fastcall hooks::process_packet(void* edx, void* ecx, void* packet, bool header) {
	static auto original_fn = netchannel_hook->get_func_address <ProcessPacket_t>(39);
	original_fn(edx, packet, header);

	//g_cl.UpdateIncomingSequences();

	// get this from CL_FireEvents string "Failed to execute event for classId" in engine.dll
	for (CEventInfo* it = m_clientstate()->m_pEvents; it != nullptr; it = it->next) {
		if (!it->classID)
			continue;

		// set all delays to instant.
		it->fire_delay = 0.f;
	}

	// game events are actually fired in OnRenderStart which is WAY later after they are received
	// effective delay by lerp time, now we call them right after theyre received (all receive proxies are invoked without delay).
	m_engine()->FireEvents();
}