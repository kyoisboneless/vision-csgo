#pragma once
#include "../../links/includes.hpp"
#include "..\..\sdk\structs.hpp"

class c_chams : public singleton <c_chams> {
public:
	bool OnDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* bone_to_world);

};