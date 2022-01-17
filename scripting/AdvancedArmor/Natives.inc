#include <amxmodx>

#define RegisterNative(%1) \
    register_native(fmt(__NATIVE_NAME_TPL, %1), fmt(__NATIVE_FUNC_TPL, %1))

static const __NATIVE_NAME_TPL[] = "AdvArmor_%s";
static const __NATIVE_FUNC_TPL[] = "@_%s";

public plugin_natives() {
    RegisterNative("SetUserArmor");
    RegisterNative("AddUserArmor");
    RegisterNative("GetUserArmor");
}

// native AdvArmor_SetUserArmor(const UserId, const iAmount);
@_SetUserArmor() {
    if(!CheckPlayer())
        return;

    SetArmor(get_param(1), get_param(2));
}

// native AdvArmor_AddUserArmor(const UserId, const iAmount, const iMax = 100);
@_AddUserArmor() {
    if(!CheckPlayer())
        return;
        
    AddArmor(get_param(1), get_param(2), get_param(3));
}

// native AdvArmor_GetUserArmor(const UserId);
@_GetUserArmor() {
    if(!CheckPlayer())
        return 0;
        
    return GetArmor(get_param(1));
}

static CheckPlayer(const iParamId = 1) {
    new UserId = get_param(iParamId);
    
    if(!is_user_alive(UserId)) {
        log_error(0, "[ERROR] User #%d not alive.", UserId);
        return false;
    }
    return true;
}
