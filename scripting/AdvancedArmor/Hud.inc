#include <amxmodx>

static const HUD_MSG_TEMPLATE[] = "Улучшенная броня: %d";
static Float:gInterval;

Hud_Init(const Float:fInterval = 1.0) {
    gInterval = fInterval;
    set_task(gInterval, "@Hud_Task_Show", .flags = "b");
}

@Hud_Task_Show() {
    for(new UserId = 1; UserId <= MAX_PLAYERS; UserId++) {
        new iArmor = GetArmor(UserId);
        if(is_user_alive(UserId) && !is_user_bot(UserId) && iArmor) {
            set_hudmessage(255, 0, 0, -1.0, 0.35, 0, 0.0, gInterval + 0.2, 0.0, 0.0);
            show_hudmessage(UserId, HUD_MSG_TEMPLATE, iArmor);
        }
    }
}
