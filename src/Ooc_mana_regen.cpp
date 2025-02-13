#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "Configuration/Config.h"

class ooc_mana_regen_announce : public PlayerScript
{
private:
    uint32 time_elapsed = 0;
    void UpdataMana(Player* player) {
        int maxMana = player->GetMaxPower(POWER_MANA);
        int current_mana = player->GetPower(POWER_MANA);

        int mana_to_add = maxMana / sConfigMgr->GetOption<float>("OOCManaRegen.ManaRegenMult", 10);
        int newMana = current_mana + mana_to_add;

        player->SetPower(POWER_MANA, std::min(newMana, maxMana));
    }
public:
    ooc_mana_regen_announce() : PlayerScript("ooc_mana_regen") { }

    void OnLogin(Player* player) override
    {
        if (sConfigMgr->GetOption<bool>("OOCManaRegen.Announce", true))
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00Out of Combat Mana Regen |rmodule.");
        }
    }

    void OnUpdate(Player* player, uint32 diff) {
        if (player->IsInCombat()) {
            time_elapsed = 0;
            return;
        }

        time_elapsed += diff;
        if (time_elapsed < sConfigMgr->GetOption<int>("OOCManaRegen.Timer", 5000)) return;

        UpdataMana(player);
        time_elapsed = 0;
    }
};

void Addooc_mana_regenScripts()
{
    new ooc_mana_regen_announce();
}
