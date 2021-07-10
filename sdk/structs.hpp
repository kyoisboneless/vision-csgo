#pragma once

#include "../links/includes.hpp"
#include "interfaces\IClientEntity.hpp"
#include "misc\EHandle.hpp"
#include "misc\UtlVector.hpp"
#include "math\QAngle.hpp"
#include "..\utils\netmanager.hpp"
#include "misc\CBoneAccessor.hpp"
#include "..\cheats\misc\fakelag.h"
#include "..\sdk\misc\Recv.hpp"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#define TIME_TO_TICKS(t) ((int)(0.5f + (float)(t) / m_globals()->m_intervalpertick))
#define TICKS_TO_TIME(t) (m_globals()->m_intervalpertick * (t))

#define NETVAR(type, name, table, netvar)                           \
    type& name##() const {                                          \
        static int _##name = netvars::get().get_offset(table, netvar);     \
        return *(type*)((uintptr_t)this + _##name);                 \
        }

#define PNETVAR(type, name, table, netvar)                           \
    type* name##() const {                                          \
        static int _##name = netvars::get().get_offset(table, netvar);     \
        return (type*)((uintptr_t)this + _##name);                 \
        }

#define OFFSET(type, name, offset)\
type &name##() const\
{\
        return *(type*)(uintptr_t(this) + offset);\
}

class player_t;
struct datamap_t;

class VarMapEntry_t
{
public:
    unsigned short type;
    unsigned short m_bNeedsToInterpolate;

    void* data;
    void* watcher;
};

struct VarMapping_t
{
    VarMapping_t()
    {
        m_Entries = nullptr;
        m_nInterpolatedEntries = 0;
        m_lastInterpolationTime = 0.0f;
    }

    VarMapEntry_t* m_Entries;
    int m_nInterpolatedEntries;
    float m_lastInterpolationTime;
};

struct client_hit_verify_t
{
    Vector position;
    float time;
    float expires;
};

class AnimationLayer;
class c_baseplayeranimationstate;
class entity_t;
class clientanimating_t;

class weapon_info_t
{
public:
    char pad_0000[4]; //0x0000
    char* ConsoleName; //0x0004
    char pad_0008[12]; //0x0008
    int iMaxClip1; //0x0014
    char pad_0018[12]; //0x0018
    int iMaxClip2; //0x0024
    char pad_0028[4]; //0x0028
    char* szWorldModel; //0x002C
    char* szViewModel; //0x0030
    char* szDropedModel; //0x0034
    char pad_0038[4]; //0x0038
    char* N00000984; //0x003C
    char pad_0040[56]; //0x0040
    char* szEmptySound; //0x0078
    char pad_007C[4]; //0x007C
    char* szBulletType; //0x0080
    char pad_0084[4]; //0x0084
    char* szHudName; //0x0088
    char* szWeaponName; //0x008C
    char pad_0090[60]; //0x0090
    int WeaponType; //0x00CC
    int iWeaponPrice; //0x00D0
    int iKillAward; //0x00D4
    char* szAnimationPrefex; //0x00D8
    float flCycleTime; //0x00DC
    float flCycleTimeAlt; //0x00E0
    float flTimeToIdle; //0x00E4
    float flIdleInterval; //0x00E8
    bool bFullAuto; //0x00EC
    char pad_00ED[3]; //0x00ED
    int iDamage; //0x00F0
    float flArmorRatio; //0x00F4
    int iBullets; //0x00F8
    float flPenetration; //0x00FC
    float flFlinchVelocityModifierLarge; //0x0100
    float flFlinchVelocityModifierSmall; //0x0104
    float flRange; //0x0108
    float flRangeModifier; //0x010C
    char pad_0110[28]; //0x0110
    int iCrosshairMinDistance; //0x012C
    float flMaxPlayerSpeed; //0x0130
    float flMaxPlayerSpeedAlt; //0x0134
    char pad_0138[4]; //0x0138
    float flSpread; //0x013C
    float flSpreadAlt; //0x0140
    float flInaccuracyCrouch; //0x0144
    float flInaccuracyCrouchAlt; //0x0148
    float flInaccuracyStand; //0x014C
    float flInaccuracyStandAlt; //0x0150
    float flInaccuracyJumpIntial; //0x0154
    float flInaccaurcyJumpApex;
    float flInaccuracyJump; //0x0158
    float flInaccuracyJumpAlt; //0x015C
    float flInaccuracyLand; //0x0160
    float flInaccuracyLandAlt; //0x0164
    float flInaccuracyLadder; //0x0168
    float flInaccuracyLadderAlt; //0x016C
    float flInaccuracyFire; //0x0170
    float flInaccuracyFireAlt; //0x0174
    float flInaccuracyMove; //0x0178
    float flInaccuracyMoveAlt; //0x017C
    float flInaccuracyReload; //0x0180
    int iRecoilSeed; //0x0184
    float flRecoilAngle; //0x0188
    float flRecoilAngleAlt; //0x018C
    float flRecoilVariance; //0x0190
    float flRecoilAngleVarianceAlt; //0x0194
    float flRecoilMagnitude; //0x0198
    float flRecoilMagnitudeAlt; //0x019C
    float flRecoilMagnatiudeVeriance; //0x01A0
    float flRecoilMagnatiudeVerianceAlt; //0x01A4
    float flRecoveryTimeCrouch; //0x01A8
    float flRecoveryTimeStand; //0x01AC
    float flRecoveryTimeCrouchFinal; //0x01B0
    float flRecoveryTimeStandFinal; //0x01B4
    int iRecoveryTransititionStartBullet; //0x01B8
    int iRecoveryTransititionEndBullet; //0x01BC
    bool bUnzoomAfterShot; //0x01C0
    char pad_01C1[31]; //0x01C1
    char* szWeaponClass; //0x01E0
    char pad_01E4[56]; //0x01E4
    float flInaccuracyPitchShift; //0x021C
    float flInaccuracySoundThreshold; //0x0220
    float flBotAudibleRange; //0x0224
    char pad_0228[12]; //0x0228
    bool bHasBurstMode; //0x0234
};

struct NoticeText_t
{
    wchar_t text[512];
    int unk0; // 0x400
    float unk1; // 0x404
    float unk2; // 0x408
    int unk3;   // 0x40C
    float time; // 0x410
    int unk4;       // 0x414
    float fade; // 0x418
    int unk5;   // 0x41C
};

struct KillFeed_t
{
    char pad[0x7C];
    CUtlVector <NoticeText_t> notices;
};

class entity_t : public IClientEntity
{
public:
    NETVAR(int, body, crypt_str("CBaseAnimating"), crypt_str("m_nBody"));
    NETVAR(int, m_nModelIndex, crypt_str("CBaseEntity"), crypt_str("m_nModelIndex"));
    NETVAR(int, m_iTeamNum, crypt_str("CBaseEntity"), crypt_str("m_iTeamNum"));
    NETVAR(Vector, m_vecOrigin, crypt_str("CBaseEntity"), crypt_str("m_vecOrigin"));
    NETVAR(CHandle <player_t>, m_hOwnerEntity, crypt_str("CBaseEntity"), crypt_str("m_hOwnerEntity"));
    NETVAR(int, m_CollisionGroup, crypt_str("CBaseEntity"), crypt_str("m_CollisionGroup"));
    NETVAR(int, m_nSequence, crypt_str("CBaseAnimating"), crypt_str("m_nSequence"));

    void set_m_bUseCustomBloomScale(byte value)
    {
        *reinterpret_cast<byte*>(uintptr_t(this) + (int)netvars::get().get_offset(crypt_str("CEnvTonemapController"), crypt_str("m_bUseCustomBloomScale"))) = value;
    }

    void set_m_flCustomBloomScale(float value)
    {
        *reinterpret_cast<float*>(uintptr_t(this) + (int)netvars::get().get_offset(crypt_str("CEnvTonemapController"), crypt_str("m_flCustomBloomScale"))) = value;
    }

    void set_m_bUseCustomAutoExposureMin(byte value)
    {
        *reinterpret_cast<byte*>(uintptr_t(this) + (int)netvars::get().get_offset(crypt_str("CEnvTonemapController"), crypt_str("m_bUseCustomAutoExposureMin"))) = value;
    }

    void set_m_flCustomAutoExposureMin(float value)
    {
        *reinterpret_cast<float*>(uintptr_t(this) + (int)netvars::get().get_offset(crypt_str("CEnvTonemapController"), crypt_str("m_flCustomAutoExposureMin"))) = value;
    }

    void set_m_bUseCustomAutoExposureMax(byte value)
    {
        *reinterpret_cast<byte*>(uintptr_t(this) + (int)netvars::get().get_offset(crypt_str("CEnvTonemapController"), crypt_str("m_bUseCustomAutoExposureMax"))) = value;
    }

    void set_m_flCustomAutoExposureMax(float value)
    {
        *reinterpret_cast<float*>(uintptr_t(this) + (int)netvars::get().get_offset(crypt_str("CEnvTonemapController"), crypt_str("m_flCustomAutoExposureMax"))) = value;
    }

    const matrix3x4_t& m_rgflCoordinateFrame()
    {
        static auto _m_rgflCoordinateFrame = netvars::get().get_offset(crypt_str("CBaseEntity"), crypt_str("m_CollisionGroup")) - 0x30;
        return *(matrix3x4_t*)((uintptr_t)this + _m_rgflCoordinateFrame);
    }
    int GetPropInt(std::string& table, std::string& var)
    {
        static auto offset = netvars::get().get_offset(table.c_str(), var.c_str());
        int val = *(int*)(uintptr_t(this) + (int)offset);
        return val;
    }
    float GetPropFloat(std::string& table, std::string& var)
    {
        static auto offset = netvars::get().get_offset(table.c_str(), var.c_str());
        float val = *(float*)(uintptr_t(this) + (int)offset);
        return val;
    }
    bool GetPropBool(std::string& table, std::string& var)
    {
        static auto offset = netvars::get().get_offset(table.c_str(), var.c_str());
        bool val = *(bool*)(uintptr_t(this) + (int)offset);
        return val;
    }
    std::string GetPropString(std::string& table, std::string& var)
    {
        static auto offset = netvars::get().get_offset(table.c_str(), var.c_str());
        char* val = (char*)(uintptr_t(this) + (int)offset);
        return std::string(val);
    }

    void SetPropInt(std::string& table, std::string& var, int val)
    {
        *reinterpret_cast<int*>(uintptr_t(this) + (int)netvars::get().get_offset(table.c_str(), var.c_str())) = val;
    }
    void SetPropFloat(std::string& table, std::string& var, float val)
    {
        *reinterpret_cast<float*>(uintptr_t(this) + (int)netvars::get().get_offset(table.c_str(), var.c_str())) = val;
    }
    void SetPropBool(std::string& table, std::string& var, bool val)
    {
        *reinterpret_cast<float*>(uintptr_t(this) + (int)netvars::get().get_offset(table.c_str(), var.c_str())) = val;
    }
    datamap_t* GetPredDescMap();
    std::array <float, 24>& m_flPoseParameter();
    bool is_player();
    void set_model_index(int index);
    void set_abs_angles(const Vector& angle);
    void set_abs_origin(const Vector& origin);
    bool compute_hitbox_surrounding_box(Vector* mins, Vector* maxs);
};

class attributableitem_t : public entity_t
{
public:

    NETVAR(int, m_iItemDefinitionIndex, crypt_str("CBaseAttributableItem"), crypt_str("m_iItemDefinitionIndex"));
    NETVAR(int, m_nFallbackStatTrak, crypt_str("CBaseAttributableItem"), crypt_str("m_nFallbackStatTrak"));
    NETVAR(int, m_nFallbackPaintKit, crypt_str("CBaseAttributableItem"), crypt_str("m_nFallbackPaintKit"));
    NETVAR(int, m_nFallbackSeed, crypt_str("CBaseAttributableItem"), crypt_str("m_nFallbackSeed"));
    NETVAR(float, m_flFallbackWear, crypt_str("CBaseAttributableItem"), crypt_str("m_flFallbackWear"));
    NETVAR(int, m_iAccountID, crypt_str("CBaseAttributableItem"), crypt_str("m_iAccountID"));
    NETVAR(int, m_iItemIDHigh, crypt_str("CBaseAttributableItem"), crypt_str("m_iItemIDHigh"));
    PNETVAR(char, m_szCustomName, crypt_str("CBaseAttributableItem"), crypt_str("m_szCustomName"));
    NETVAR(int, m_OriginalOwnerXuidLow, crypt_str("CBaseAttributableItem"), crypt_str("m_OriginalOwnerXuidLow"));
    NETVAR(int, m_OriginalOwnerXuidHigh, crypt_str("CBaseAttributableItem"), crypt_str("m_OriginalOwnerXuidHigh"));
    NETVAR(int, m_iEntityQuality, crypt_str("CBaseAttributableItem"), crypt_str("m_iEntityQuality"));
};

class weapon_t : public attributableitem_t
{
public:
    NETVAR(float, m_flNextPrimaryAttack, crypt_str("CBaseCombatWeapon"), crypt_str("m_flNextPrimaryAttack"));
    NETVAR(float, m_flNextSecondaryAttack, crypt_str("CBaseCombatWeapon"), crypt_str("m_flNextSecondaryAttack"));
    NETVAR(bool, initialized, crypt_str("CBaseAttributableItem"), crypt_str("m_bInitialized"));
    NETVAR(int, weapon, crypt_str("CBaseViewModel"), crypt_str("m_hWeapon"));
    NETVAR(short, m_iItemDefinitionIndex, crypt_str("CBaseCombatWeapon"), crypt_str("m_iItemDefinitionIndex"));
    NETVAR(int, m_iClip1, crypt_str("CBaseCombatWeapon"), crypt_str("m_iClip1"));
    NETVAR(int, m_iViewModelIndex, crypt_str("CBaseCombatWeapon"), crypt_str("m_iViewModelIndex"));
    NETVAR(int, m_iWorldModelIndex, crypt_str("CBaseCombatWeapon"), crypt_str("m_iWorldModelIndex"));
    NETVAR(float, m_fAccuracyPenalty, crypt_str("CWeaponCSBase"), crypt_str("m_fAccuracyPenalty"));
    NETVAR(int, m_zoomLevel, crypt_str("CWeaponCSBaseGun"), crypt_str("m_zoomLevel"));
    NETVAR(bool, m_bPinPulled, crypt_str("CBaseCSGrenade"), crypt_str("m_bPinPulled"));
    NETVAR(float, m_fThrowTime, crypt_str("CBaseCSGrenade"), crypt_str("m_fThrowTime"));
    NETVAR(float, m_flPostponeFireReadyTime, crypt_str("CWeaponCSBase"), crypt_str("m_flPostponeFireReadyTime"));
    NETVAR(float, m_fLastShotTime, crypt_str("CWeaponCSBase"), crypt_str("m_fLastShotTime"));
    NETVAR(float, m_flRecoilSeed, crypt_str("CWeaponCSBase"), crypt_str("m_flRecoilIndex"));
    NETVAR(int, m_weaponMode, crypt_str("CWeaponCSBase"), crypt_str("m_weaponMode"));
    NETVAR(CHandle <weapon_t>, m_hWeaponWorldModel, crypt_str("CBaseCombatWeapon"), crypt_str("m_hWeaponWorldModel"));

    weapon_info_t* get_csweapon_info();
    bool is_empty();
    bool can_fire(bool check_revolver);
    int get_weapon_group(bool rage);
    bool is_rifle();
    bool is_smg();
    bool is_shotgun();
    bool is_pistol();
    bool is_sniper();
    bool is_grenade();
    bool is_knife();
    bool is_non_aim();
    bool can_double_tap();
    int get_max_tickbase_shift();
    float get_inaccuracy();
    float get_spread();
    void update_accuracy_penality();
    char* get_icon();
    std::string get_name();
};

class viewmodel_t;

class player_t : public entity_t
{
public:
    NETVAR(bool, m_bClientSideAnimation, crypt_str("CBaseAnimating"), crypt_str("m_bClientSideAnimation"));
    NETVAR(bool, m_bHasDefuser, crypt_str("CCSPlayer"), crypt_str("m_bHasDefuser"));
    NETVAR(bool, m_bGunGameImmunity, crypt_str("CCSPlayer"), crypt_str("m_bGunGameImmunity"));
    NETVAR(int, m_iShotsFired, crypt_str("CCSPlayer"), crypt_str("m_iShotsFired"));
    NETVAR(Vector, m_angEyeAngles, crypt_str("CCSPlayer"), crypt_str("m_angEyeAngles[0]"));
    NETVAR(Vector, m_angRotation, crypt_str("CBaseEntity"), crypt_str("m_angRotation"));
    NETVAR(int, m_ArmorValue, crypt_str("CCSPlayer"), crypt_str("m_ArmorValue"));
    NETVAR(int, m_iAccount, crypt_str("CCSPlayer"), crypt_str("m_iAccount"));
    NETVAR(bool, m_bHasHelmet, crypt_str("CCSPlayer"), crypt_str("m_bHasHelmet"));
    NETVAR(bool, m_bHasHeavyArmor, crypt_str("CCSPlayer"), crypt_str("m_bHasHeavyArmor"));
    NETVAR(bool, m_bIsScoped, crypt_str("CCSPlayer"), crypt_str("m_bIsScoped"));
    NETVAR(float, m_flLowerBodyYawTarget, crypt_str("CCSPlayer"), crypt_str("m_flLowerBodyYawTarget"));
    NETVAR(float, m_flFlashDuration, crypt_str("CCSPlayer"), crypt_str("m_flFlashDuration"));
    NETVAR(CBaseHandle, m_hVehicle, crypt_str("CBasePlayer"), crypt_str("m_hVehicle"));
    NETVAR(int, m_iHealth, crypt_str("CBasePlayer"), crypt_str("m_iHealth"));
    NETVAR(int, m_lifeState, crypt_str("CBasePlayer"), crypt_str("m_lifeState"));
    NETVAR(int, m_fFlags, crypt_str("CBasePlayer"), crypt_str("m_fFlags"));
    NETVAR(int, m_nHitboxSet, crypt_str("CBasePlayer"), crypt_str("m_nHitboxSet"));
    NETVAR(int, m_nTickBase, crypt_str("CBasePlayer"), crypt_str("m_nTickBase"));
    NETVAR(Vector, m_vecViewOffset, crypt_str("CBasePlayer"), crypt_str("m_vecViewOffset[0]"));
    NETVAR(Vector, m_viewPunchAngle, crypt_str("CBasePlayer"), crypt_str("m_viewPunchAngle"));
    NETVAR(Vector, m_aimPunchAngle, crypt_str("CBasePlayer"), crypt_str("m_aimPunchAngle"));
    NETVAR(Vector, m_aimPunchAngleVel, crypt_str("CBasePlayer"), crypt_str("m_aimPunchAngleVel"));
    NETVAR(CHandle <viewmodel_t>, m_hViewModel, crypt_str("CBasePlayer"), crypt_str("m_hViewModel[0]"));
    NETVAR(Vector, m_vecVelocity, crypt_str("CBasePlayer"), crypt_str("m_vecVelocity[0]"));
    NETVAR(Vector, m_vecMins, crypt_str("CBaseEntity"), crypt_str("m_vecMins"));
    NETVAR(Vector, m_vecMaxs, crypt_str("CBaseEntity"), crypt_str("m_vecMaxs"));
    NETVAR(float, m_flVelocityModifier, crypt_str("CCSPlayer"), crypt_str("m_flVelocityModifier"));
    NETVAR(float, m_flSimulationTime, crypt_str("CBaseEntity"), crypt_str("m_flSimulationTime"));
    OFFSET(float, m_flOldSimulationTime, netvars::get().get_offset(crypt_str("CBaseEntity"), crypt_str("m_flSimulationTime")) + 0x4);
    NETVAR(float, m_flDuckSpeed, crypt_str("CCSPlayer"), crypt_str("m_flDuckSpeed"));
    NETVAR(float, m_flDuckAmount, crypt_str("CCSPlayer"), crypt_str("m_flDuckAmount"));
    NETVAR(bool, m_bDucked, crypt_str("CCSPlayer"), crypt_str("m_bDucked"));
    NETVAR(bool, m_bDucking, crypt_str("CCSPlayer"), crypt_str("m_bDucking"));
    NETVAR(float, m_flHealthShotBoostExpirationTime, crypt_str("CCSPlayer"), crypt_str("m_flHealthShotBoostExpirationTime"));
    NETVAR(int, m_bInBombZone, crypt_str("CCSPlayer"), crypt_str("m_bInBombZone"));
    NETVAR(float, m_flFallVelocity, crypt_str("CBasePlayer"), crypt_str("m_flFallVelocity"));
    NETVAR(float, m_flStepSize, crypt_str("CBaseEntity"), crypt_str("m_flStepSize"));
    NETVAR(float, m_flNextAttack, crypt_str("CBaseCombatCharacter"), crypt_str("m_flNextAttack"));
    PNETVAR(CBaseHandle, m_hMyWearables, crypt_str("CBaseCombatCharacter"), crypt_str("m_hMyWearables"));
    NETVAR(int, m_iObserverMode, crypt_str("CBasePlayer"), crypt_str("m_iObserverMode"));
    NETVAR(CHandle <player_t>, m_hObserverTarget, crypt_str("CBasePlayer"), crypt_str("m_hObserverTarget"));
    NETVAR(CHandle <weapon_t>, m_hActiveWeapon, crypt_str("CBaseCombatCharacter"), crypt_str("m_hActiveWeapon"));
    NETVAR(CHandle <attributableitem_t>, m_hWeaponWorldModel, crypt_str("CBaseCombatWeapon"), crypt_str("m_hWeaponWorldModel"));
    NETVAR(CHandle <entity_t>, m_hGroundEntity, crypt_str("CBasePlayer"), crypt_str("m_hGroundEntity"));
    NETVAR(bool, m_bSpotted, crypt_str("CBaseEntity"), crypt_str("m_bSpotted"));
    NETVAR(int, m_vphysicsCollisionState, crypt_str("CBasePlayer"), crypt_str("m_vphysicsCollisionState"));
    NETVAR(bool, m_bIsWalking, crypt_str("CCSPlayer"), crypt_str("m_bIsWalking"));
    NETVAR(bool, m_bIsDefusing, crypt_str("CCSPlayer"), crypt_str("m_bIsDefusing"));
    VIRTUAL(think(void), 138, void(__thiscall*)(void*));
    VIRTUAL(pre_think(void), 317, void(__thiscall*)(void*));
    VIRTUAL(post_think(void), 318, void(__thiscall*)(void*));
    VIRTUAL(set_local_view_angles(Vector& angle), 372, void(__thiscall*)(void*, Vector&), angle);

    CBaseHandle* m_hMyWeapons()
    {
        return (CBaseHandle*)((uintptr_t)this + 0x2DF8);
    }

    float& m_flSpawnTime()
    {
        return *(float*)((uintptr_t)this + 0xA370);
    }

    uint32_t& m_iMostRecentModelBoneCounter();
    float& m_flLastBoneSetupTime();

    void select_item(const char* string, int sub_type);
    bool using_standard_weapons_in_vechile();
    bool physics_run_think(int index);

    VarMapping_t* var_mapping();
    c_baseplayeranimationstate* get_animation_state();
    CStudioHdr* m_pStudioHdr();
    bool setup_bones_rebuilt(matrix3x4_t* matrix, int mask);
    Vector get_shoot_position();
    void modify_eye_position(Vector& eye_position);
    uint32_t& m_fEffects();
    uint32_t& m_iEFlags();
    float& m_surfaceFriction();
    Vector& m_vecAbsVelocity();
    int get_hitbox_bone_id(int hitbox_id);
    Vector hitbox_position(int hitbox_id);
    Vector hitbox_position_matrix(int hitbox_id, matrix3x4_t matrix[MAXSTUDIOBONES]);
    AnimationLayer* get_animlayers();
    CUtlVector <matrix3x4_t>& m_CachedBoneData();
    CBoneAccessor& m_BoneAccessor();
    void invalidate_bone_cache();
    void set_abs_velocity(const Vector& velocity);
    Vector get_render_angles();
    void set_render_angles(const Vector& angles);
    void update_clientside_animation();
    bool is_alive();
    bool valid(bool check_team, bool check_dormant = true);
    int get_move_type();
    int animlayer_count();
    int sequence_activity(int sequence);
    float get_max_desync_delta();
    void invalidate_physics_recursive(int change_flags);
};

class viewmodel_t : public entity_t
{
public:
    NETVAR(int, m_nModelIndex, crypt_str("CBaseViewModel"), crypt_str("m_nModelIndex"));
    NETVAR(int, m_nViewModelIndex, crypt_str("CBaseViewModel"), crypt_str("m_nViewModelIndex"));
    NETVAR(CHandle <weapon_t>, m_hWeapon, crypt_str("CBaseViewModel"), crypt_str("m_hWeapon"));
    NETVAR(CHandle <player_t>, m_hOwner, crypt_str("CBaseViewModel"), crypt_str("m_hOwner"));
    NETVAR(int, m_nAnimationParity, crypt_str("CBaseViewModel"), crypt_str("m_nAnimationParity"));

    float& m_flCycle();
    float& m_flAnimTime();
    void SendViewModelMatchingSequence(int sequence);
};

class CCSBomb : public entity_t
{
public:
    NETVAR(float, m_flDefuseCountDown, crypt_str("CPlantedC4"), crypt_str("m_flDefuseCountDown"));
    NETVAR(int, m_hBombDefuser, crypt_str("CPlantedC4"), crypt_str("m_hBombDefuser"));
    NETVAR(float, m_flC4Blow, crypt_str("CPlantedC4"), crypt_str("m_flC4Blow"));
    NETVAR(bool, m_bBombDefused, crypt_str("CPlantedC4"), crypt_str("m_bBombDefused"));
};

class ragdoll_t : public entity_t
{
public:
    NETVAR(Vector, m_vecForce, crypt_str("CCSRagdoll"), crypt_str("m_vecForce"));
    NETVAR(Vector, m_vecRagdollVelocity, crypt_str("CCSRagdoll"), crypt_str("m_vecRagdollVelocity"));
};

struct inferno_t : public entity_t
{
    OFFSET(float, get_spawn_time, 0x20);
    // OFFSET(int, m_fireCount, 0x000013A8);
    NETVAR(int, m_nFireEffectTickBegin, crypt_str("DT_Inferno"), crypt_str("m_nFireEffectTickBegin"));

    NETVAR(int, m_fireCount, crypt_str("DT_Inferno"), crypt_str("m_fireCount"));

    static float get_expiry_time()
    {
        return 7.03125f;
    }

};

struct smoke_t : public entity_t
{
    NETVAR(int, m_nSmokeEffectTickBegin, crypt_str("CSmokeGrenadeProjectile"), crypt_str("m_nSmokeEffectTickBegin"));
    NETVAR(bool, m_bDidSmokeEffect, crypt_str("CSmokeGrenadeProjectile"), crypt_str("m_bDidSmokeEffect"));

    static float get_expiry_time()
    {
        return 19.0f;
    }
};

class CHudChat
{
public:
    char pad_0x0000[0x4C];
    int m_timesOpened;
    char pad_0x0050[0x8];
    bool m_isOpen;
    char pad_0x0059[0x427];

    void chat_print(const char* fmt, ...);
};

class AnimationLayer
{
public:
    bool m_bClientBlend;		 //0x0000
    float m_flBlendIn;			 //0x0004
    void* m_pStudioHdr;			 //0x0008
    int m_nDispatchSequence;     //0x000C
    int m_nDispatchSequence_2;   //0x0010
    uint32_t m_nOrder;           //0x0014
    uint32_t m_nSequence;        //0x0018
    float_t m_flPrevCycle;       //0x001C
    float_t m_flWeight;          //0x0020
    float_t m_flWeightDeltaRate; //0x0024
    float_t m_flPlaybackRate;    //0x0028
    float_t m_flCycle;           //0x002C
    void* m_pOwner;              //0x0030
    char pad_0038[4];            //0x0034
};

class c_baseplayeranimationstate
{
public:
    char pad[3];
    char bUnknown; //0x4
    char pad2[87];
    weapon_t* m_pLastBoneSetupWeapon; //0x5C
    player_t* m_pBaseEntity; //0x60
    weapon_t* m_pActiveWeapon; //0x64
    weapon_t* m_pLastActiveWeapon; //0x68
    float m_flLastClientSideAnimationUpdateTime; //0x6C
    int m_iLastClientSideAnimationUpdateFramecount; //0x70
    float m_flUpdateTimeDelta; //0x74
    float m_flEyeYaw; //0x78
    float m_flPitch; //0x7C
    float m_flGoalFeetYaw; //0x80
    float m_flCurrentFeetYaw; //0x84
    float m_flCurrentTorsoYaw; //0x88
    float m_flUnknownVelocityLean; //0x8C //changes when moving/jumping/hitting ground
    float m_flLeanAmount; //0x90
    char pad4[4]; //NaN
    float m_flFeetCycle; //0x98 0 to 1
    float m_flFeetYawRate; //0x9C 0 to 1
    float m_fUnknown2;
    float m_fDuckAmount; //0xA4
    float m_fLandingDuckAdditiveSomething; //0xA8
    float m_fUnknown3; //0xAC
    Vector m_vOrigin; //0xB0, 0xB4, 0xB8
    Vector m_vLastOrigin; //0xBC, 0xC0, 0xC4
    float m_vVelocityX; //0xC8
    float m_vVelocityY; //0xCC
    char pad5[4];
    float m_flUnknownFloat1; //0xD4 Affected by movement and direction
    char pad6[8];
    float m_flUnknownFloat2; //0xE0 //from -1 to 1 when moving and affected by direction
    float m_flUnknownFloat3; //0xE4 //from -1 to 1 when moving and affected by direction
    float m_unknown; //0xE8
    float m_velocity; //0xEC
    float flUpVelocity; //0xF0
    float m_flSpeedNormalized; //0xF4 //from 0 to 1
    float m_flFeetSpeedForwardsOrSideWays; //0xF8 //from 0 to 2. something  is 1 when walking, 2.something when running, 0.653 when crouch walking
    float m_flFeetSpeedUnknownForwardOrSideways; //0xFC //from 0 to 3. something
    float m_flTimeSinceStartedMoving; //0x100
    float m_flTimeSinceStoppedMoving; //0x104
    bool m_bOnGround; //0x108
    bool m_bInHitGroundAnimation; //0x109
    char pad7[10];
    float m_flLastOriginZ; //0x114
    float m_flHeadHeightOrOffsetFromHittingGroundAnimation; //0x118 from 0 to 1, is 1 when standing
    float m_flStopToFullRunningFraction; //0x11C from 0 to 1, doesnt change when walking or crouching, only running
    char pad8[4]; //NaN
    float m_flMovingFraction; //0x124 affected while jumping and running, or when just jumping, 0 to 1
    char pad9[4]; //NaN
    float m_flUnknown3;
    char pad10[528];

    float& time_since_in_air()
    {
        return *(float*)((uintptr_t)this + 0x110);
    }

    float& yaw_desync_adjustment()
    {
        return *(float*)((uintptr_t)this + 0x334);
    }
};