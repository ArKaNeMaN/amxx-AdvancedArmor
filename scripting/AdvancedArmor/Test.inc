#include <amxmodx>
#include <VipModular>
#include <json>

static VipM_IC_T_Item:gItemId = VipM_IC_Invalid_Item;

public VipM_IC_OnLoaded() {
    new JSON:jItem = json_parse("/addons/amxmodx/data/ItemsController/AdvancedArmor/TestItem.json", true);
    gItemId = VipM_IC_JsonGetItem(jItem);
    if(gItemId == VipM_IC_Invalid_Item) {
        log_amx("[WARNING] TEST: Can't read test item from file.");
        return;
    }

    register_clcmd("aa_get", "@Test_Cmd_GetArmor");
    set_task(1.0, "@Test_Task_GiveArmor", .flags = "b");
}

@Test_Cmd_GetArmor(const UserId) {
    client_print(UserId, print_console, "Armor: %d.", GetArmor(UserId));
}

@Test_Task_GiveArmor() {
    for(new UserId = 1; UserId <= MAX_PLAYERS; UserId++) {
        if(is_user_alive(UserId) && !is_user_bot(UserId)) {
            VipM_IC_GiveItem(UserId, gItemId);
            client_print(UserId, print_console, "+armor");
        }
    }
}
