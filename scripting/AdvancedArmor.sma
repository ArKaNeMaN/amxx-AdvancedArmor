#include amxmodx
#include reapi

#pragma compress 1
#pragma semicolon 1

public stock const PluginName[] = "Advanved Armor";
public stock const PluginVersion[] = "1.0.0";
public stock const PluginAuthor[] = "ArKaNeMaN";
public stock const PluginUrl[] = "t.me/arkaneman";

new gPlayerArmor[MAX_PLAYERS + 1] = {0, ...};

public plugin_init() {
    register_plugin(PluginName, PluginVersion, PluginAuthor);
    
    RegisterHookChain(RG_CBasePlayer_TakeDamage, "@OnTakeDamage", false);
    RegisterHookChain(RG_CBasePlayer_Killed, "@OnKilled", true);
    RegisterHookChain(RG_CSGameRules_RestartRound, "@OnRoundRestart", false);

    Hud_Init();
}

GetArmor(const UserId) {
    return gPlayerArmor[UserId];
}

SetArmor(const UserId, const iAmount) {
    gPlayerArmor[UserId] = max(iAmount, 0);
}

AddArmor(const UserId, const iAmount, const iMax = 100) {
    new iNewArmor = GetArmor(UserId) + iAmount;
    if(iAmount > 0)
        iNewArmor = min(iMax, iNewArmor);

    // log_amx("[DEBUG] AddArmor(%n, %d, %d): old %d | new %d", UserId, iAmount, iMax, GetArmor(UserId), iNewArmor);

    SetArmor(UserId, iNewArmor);
}

public client_putinserver(UserId) {
    SetArmor(UserId, 0);
}

@OnTakeDamage(const UserId, InflictorId, AttackerId, Float:fDamage, iDamageType) {
    if(!GetArmor(UserId)) {
        return HC_CONTINUE;
    }

    new iDamage = floatround(fDamage, floatround_floor);
    
    new iArmor = GetArmor(UserId);
    AddArmor(UserId, -iDamage);

    // log_amx("[DEBUG] %n: d: %d -> %d | a: %d -> %d", UserId, iDamage, floatround(floatmax(fDamage - float(iArmor), 0.0)), iArmor, GetArmor(UserId), floatround(get_entvar(UserId, var_health)));

    if(iArmor >= iDamage) {
        SetHookChainReturn(ATYPE_INTEGER, 0);
        return HC_BREAK;
    }

    SetHookChainArg(4, ATYPE_FLOAT, floatmax(fDamage - float(iArmor), 0.0));
    return HC_CONTINUE;
}

@OnKilled(const UserId, InflictorId, AttackerId, Float:fDamage, iDamageType) {
    SetArmor(UserId, 0);
}

@OnRoundRestart() {
    if(!get_member_game(m_bCompleteReset)) {
        return;
    }

    for(new UserId = 1; UserId <= MAX_PLAYERS; UserId++) {
        SetArmor(UserId, 0);
    }
}

#include "AdvancedArmor/Hud"
#include "AdvancedArmor/Natives"
#include "AdvancedArmor/IC-Support"

// #include "AdvancedArmor/Test"
