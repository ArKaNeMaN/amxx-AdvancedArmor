/**
 * Поддержка контроллера предметов для VipModular
 *
 * https://github.com/ArKaNeMaN/amxx-VipModular-pub/blob/master/amxmodx/scripting/VipM-ItemsController.sma
 *
 * Примечание: Контроллер не зависит от ядра вип-системы и может использоваться отдельно
*/

#include <amxmodx>
#include <json>
#include <VipModular>

enum _:IC_GiveType {
    IC_GT_Undefined = -1,

    IC_GT_Set = 0,
    IC_GT_Add,
}

static const IC_TYPE_NAME[] = "AdvancedArmor";
static const IC_PARAM_AMOUNT[] = "Amount";
static const IC_PARAM_TYPE[] = "GiveType";
static const IC_PARAM_MAX[] = "Max";

public VipM_IC_OnInitTypes() {
    VipM_IC_RegisterType(IC_TYPE_NAME);
    VipM_IC_RegisterTypeEvent(IC_TYPE_NAME, ItemType_OnRead, "@IC_OnRead");
    VipM_IC_RegisterTypeEvent(IC_TYPE_NAME, ItemType_OnGive, "@IC_OnGive");
}

@IC_OnRead(const JSON:jCfg, Trie:Params) {
    new iAmount = json_object_get_number(jCfg, IC_PARAM_AMOUNT);
    if(iAmount <= 0) {
        log_amx("[WARNING] Item '%s': %s must be greater then 0.", IC_TYPE_NAME, IC_PARAM_AMOUNT);
        return VIPM_STOP;
    }
    TrieSetCell(Params, IC_PARAM_AMOUNT, iAmount);
    
    new sType[8];
    json_object_get_string(jCfg, IC_PARAM_TYPE, sType, charsmax(sType));
    new iType = ReadGiveType(sType);
    if(iType == IC_GT_Undefined) {
        log_amx("[WARNING] Item '%s': Undefined give type '%s'.", IC_TYPE_NAME, sType);
        return VIPM_STOP;
    }
    TrieSetCell(Params, IC_PARAM_TYPE, iType);
    
    if(iType == IC_GT_Add) {
        if(!json_object_has_value(jCfg, IC_PARAM_MAX, JSONNumber)) {
            log_amx("[WARNING] Item '%s': '%s' required for '%s: Add'.", IC_TYPE_NAME, IC_PARAM_MAX, IC_PARAM_TYPE);
            return VIPM_STOP;
        }

        new iMax = json_object_get_number(jCfg, IC_PARAM_MAX);
        if(iMax <= 0) {
            log_amx("[WARNING] Item '%s': %s amount must be greater then 0.", IC_TYPE_NAME, IC_PARAM_MAX);
            return VIPM_STOP;
        }
        TrieSetCell(Params, IC_PARAM_MAX, iMax);
    }

    return VIPM_CONTINUE;
}

@IC_OnGive(const UserId, const Trie:Params) {
    new iAmount, iType;
    TrieGetCell(Params, IC_PARAM_AMOUNT, iAmount);
    TrieGetCell(Params, IC_PARAM_TYPE, iType);

    switch(iType) {
        case IC_GT_Set: {
            SetArmor(UserId, iAmount);
        }

        case IC_GT_Add: {
            new iMax;
            TrieGetCell(Params, IC_PARAM_MAX, iMax);

            AddArmor(UserId, iAmount, iMax);
        }
    }

    return VIPM_CONTINUE;
}

static ReadGiveType(const Str[]) {
    switch(Str[0]) {
        case 'S':
            return IC_GT_Set;
        case 'A':
            return IC_GT_Add;
    }
    return IC_GT_Undefined;
}
