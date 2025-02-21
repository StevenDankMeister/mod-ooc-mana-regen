#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "Configuration/Config.h"

class ooc_mana_regen_announce : public PlayerScript
{
private:
    std::unordered_map<ObjectGuid, uint32> player_timers;
    void UpdateMana(Player *player)
    {
        int max_mana = player->GetMaxPower(POWER_MANA);
        int current_mana = player->GetPower(POWER_MANA);

        int mana_to_add = max_mana * (sConfigMgr->GetOption<float>("OOCManaRegen.ManaRegenMult", 10) / 100);
        int new_mana = current_mana + mana_to_add;

        player->SetPower(POWER_MANA, std::min(new_mana, max_mana));
    }

public:
    ooc_mana_regen_announce() : PlayerScript("ooc_mana_regen") {}

    void OnLogin(Player *player) override
    {
        if (sConfigMgr->GetOption<bool>("OOCManaRegen.Announce", true))
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00Out of Combat Mana Regen |rmodule.");
        }
    }

    void OnUpdate(Player *player, uint32 diff)
    {
        if (player->IsInCombat())
        {
            player_timers[player->GetGUID()] = 0;
            return;
        }

        player_timers[player->GetGUID()] += diff;
        if (player_timers[player->GetGUID()] < sConfigMgr->GetOption<int>("OOCManaRegen.Timer", 5000))
            return;

        UpdateMana(player);
        player_timers[player->GetGUID()] = 0;
    }
};

void Addooc_mana_regenScripts()
{
    new ooc_mana_regen_announce();
}
