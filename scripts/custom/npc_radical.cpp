#include "precompiled.h"
#include "sc_creature.h"
#include "sc_gossip.h"
#include <time.h>

/*########
## npc_logroneitor
## Radical custom npc 
######*/

/*bool is_birthday_date()
{
    time_t ltime;
    struct tm *timeinfo;
    
    ltime = time(NULL);

    timeinfo = localtime(&ltime);

    return (timeinfo.tm_mon == 5 && timeinfo.tm_mday == 24);
}  */  

//creo que esta si va a funcionar
/*bool is_birthday_date()
{
    time_t rawtime; 
    struct tm * timeinfo; 

    time ( &rawtime ); 
    timeinfo = localtime ( &rawtime ); 

    return (timeinfo.tm_mday == 24 && timeinfo.tm_mon==5);

}*/

bool GossipHello_logroneitor_horde(Player* pPlayer, Creature* pCreature)
{
    char const* GOSSIP_LONELY;
    char const* GOSSIP_NAXXRAMAS;
    char const* GOSSIP_DISASTER;
    char const* GOSSIP_HOLIDAY;
    char const* GOSSIP_WINTERN;
    char const* GOSSIP_KING;
    char const* GOSSIP_PINKY;
    char const* GOSSIP_HARD_EGG;
    char const* GOSSIP_PRIMAVERA;
    char const* GOSSIP_BIRTHDAY;

    switch (LocaleConstant currentlocale = pPlayer->GetSession()->GetSessionDbcLocale())
    {
         case LOCALE_koKR:
         case LOCALE_zhCN:
         case LOCALE_zhTW:
         case LOCALE_esES:
         case LOCALE_esMX:
             GOSSIP_LONELY = "Me siento sólo, we.";
             GOSSIP_NAXXRAMAS = "Me das pena, loco.";
             GOSSIP_DISASTER = "Te voy a dar un beso, guapetón.";
             GOSSIP_HOLIDAY = "Llevo mucho tiempo queriendo algo...";
             GOSSIP_WINTERN = "Navidaaad, navidaaad, quiero mi logro de navidaaad...";
             GOSSIP_KING = "Rey del Festival de Fuego";
             GOSSIP_PINKY = "El resplandor rosa del cohete";
             GOSSIP_HARD_EGG = "Dame el huevo de metal \\m/";
             GOSSIP_PRIMAVERA = "La primavera la sangre altera!";
             GOSSIP_BIRTHDAY = "5º aniversario de Radical";
             break;
         case LOCALE_ruRU:
         case LOCALE_enUS:
         case LOCALE_frFR:
         case LOCALE_deDE:
         default:
             GOSSIP_LONELY = "I'm lonely, goblin.";
             GOSSIP_NAXXRAMAS = "You are sad, crazy.";
             GOSSIP_DISASTER = "Kiss me, baby.";
             GOSSIP_HOLIDAY = "It's time to get one surprise.";
             GOSSIP_WINTERN = "We wish you a merry achievement.";
             GOSSIP_KING = "King of the Fire Festival";
             GOSSIP_PINKY = "The Rocket's Pink Glare";
             GOSSIP_HARD_EGG = "Metal EGG \\m/";
             GOSSIP_PRIMAVERA = "Spring alters blood! True blood.";
             GOSSIP_BIRTHDAY = "5th Radical anniversary";
             break;
    }

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LONELY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_NAXXRAMAS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DISASTER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HOLIDAY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WINTERN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_KING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PINKY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HARD_EGG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PRIMAVERA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    //if(is_birthday_date()) pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BIRTHDAY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);

    pPlayer->SEND_GOSSIP_MENU(50003, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_logroneitor_horde(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(1291);
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(1704);
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(1280);
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(271);
            pPlayer->CompletedAchievement(272);
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(252);
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(1145);
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(1696);
            break;
        case GOSSIP_ACTION_INFO_DEF+8:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(2416);
            break;
        case GOSSIP_ACTION_INFO_DEF+9:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(2497);
            break;   
        case GOSSIP_ACTION_INFO_DEF+10:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(4400);
            break;  
        default:
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }
    return true;
}

bool GossipHello_logroneitor_alliance(Player* pPlayer, Creature* pCreature)
{
    char const* GOSSIP_LONELY;
    char const* GOSSIP_NAXXRAMAS;
    char const* GOSSIP_HOLIDAY;
    char const* GOSSIP_WINTERN;
    char const* GOSSIP_KING;
    char const* GOSSIP_PINKY;
    char const* GOSSIP_HARD_EGG;
    char const* GOSSIP_PRIMAVERA;
    char const* GOSSIP_BIRTHDAY;


    switch (LocaleConstant currentlocale = pPlayer->GetSession()->GetSessionDbcLocale())
    {
        case LOCALE_koKR:
        case LOCALE_zhCN:
        case LOCALE_zhTW:
        case LOCALE_esES:
        case LOCALE_esMX:
            GOSSIP_LONELY = "Me siento sólo, we.";
            GOSSIP_NAXXRAMAS = "Me das pena, loco.";
            GOSSIP_HOLIDAY = "Llevo mucho tiempo queriendo algo...";
            GOSSIP_WINTERN = "Navidaaad, navidaaad, quiero mi logro de navidaaad...";
            GOSSIP_KING = "Rey del Festival de Fuego";
            GOSSIP_PINKY = "El resplandor rosa del cohete";
            GOSSIP_HARD_EGG = "Dame el huevo de metal \\m/";
            GOSSIP_PRIMAVERA = "La primavera la sangre altera!";
            GOSSIP_BIRTHDAY = "5º aniversario de Radical";
            break;
        case LOCALE_ruRU:
        case LOCALE_enUS:
        case LOCALE_frFR:
        case LOCALE_deDE:
        default:
            GOSSIP_LONELY = "I'm lonely, goblin.";
            GOSSIP_NAXXRAMAS = "You are sad, crazy.";
            GOSSIP_HOLIDAY = "It's time to get one surprise.";
            GOSSIP_WINTERN = "We wish you a merry achievement.";
            GOSSIP_KING = "King of the Fire Festival";
            GOSSIP_PINKY = "The Rocket's Pink Glare";
            GOSSIP_HARD_EGG = "Metal EGG \\m/";
            GOSSIP_PRIMAVERA = "Spring alters blood! True blood.";
            GOSSIP_BIRTHDAY = "5th Radical anniversary";
            break;
    }

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LONELY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_NAXXRAMAS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HOLIDAY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WINTERN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_KING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PINKY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HARD_EGG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PRIMAVERA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    //if(is_birthday_date()) pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BIRTHDAY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);

    pPlayer->SEND_GOSSIP_MENU(50003, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_logroneitor_alliance(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(1291);
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(1704);
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(271);
            pPlayer->CompletedAchievement(272);
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(252);
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(1145);
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(1696);
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(2416);
            break;
        case GOSSIP_ACTION_INFO_DEF+8:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(2419);
            break;   
        case GOSSIP_ACTION_INFO_DEF+9:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CompletedAchievement(4400);
            break;      
        default:
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }
    return true;
}

/*########
## npc_aucherus_teleporter
## Radical custom npc
######*/

bool GossipHello_acherus_teleporter_up(Player* pPlayer, Creature* pCreature)
{
    char const* OPTION = "Quiero ir al piso de arriba";
 
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_acherus_teleporter_up(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{

    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
        default:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(0, 2402.718994, -5632.788534, 420.667847, pPlayer->GetOrientation());
            break;
    }

    return true;
}

bool GossipHello_acherus_teleporter_down(Player* pPlayer, Creature* pCreature)
{
    char const* OPTION = "Quiero ir al piso de abajo";
 
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_acherus_teleporter_down(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->TeleportTo(0, 2402.718994, -5632.788534, 377.022003, pPlayer->GetOrientation());

    return true;
}

/*########
## boss_staff
## Radical custom BOSS
######*/

// Bergen

enum Bergensays
{
    BERGEN_SAY_AGRO        = -2000010,
    BERGEN_SAY_KILL        = -2000011,
    BERGEN_SAY_DEAD        = -2000012,
    BERGEN_SAY_WINGS       = -2000013,
    BERGEN_SAY_FLOOR       = -2000014
};

enum Bergenspells
{
    TAIL_SLASH                 = 71369,
    FIRE_WALL                  = 43113,
    HEAT_FLOOR                 = 22199,
    BONE_STORM                 = 69076,
    EVIL_SPIRITS               = 70498,
    PAIN_AND_AGONY             = 73790,
    MAGIC_WINGS                = 42867
};

struct MANGOS_DLL_DECL boss_bergen : public ScriptedAI
{
    boss_bergen(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    char phase;

    uint32 tailSlash;
    uint32 heatFloor;
    uint32 boneStorm;
    uint32 evilSpirits;
    uint32 painAgony;
    uint32 fireWall;
    uint32 magicWings;

    void Reset()
    {
        phase = 0;
 
        tailSlash     = 10000;
        heatFloor     = 20000;
        boneStorm     = 120000;
        evilSpirits   = 60000;
        painAgony     = 15000;
        fireWall      = 5000;
        magicWings    = 40000; 
    }
   
    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(BERGEN_SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(BERGEN_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(BERGEN_SAY_AGRO, m_creature);
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_creature->GetHealthPercent() < 5.0f) phase = 1;

        switch(phase)
        {
            case 1:
                // fire wall
                if(fireWall < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature, FIRE_WALL) == CAST_OK) fireWall = 5000;
                }
                else fireWall -= uiDiff;
                // no break
            case 0:
                if(tailSlash < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature, TAIL_SLASH) == CAST_OK) tailSlash = 10000;
                }
                else tailSlash -= uiDiff;

                if(heatFloor - 5000 < uiDiff) DoScriptText(BERGEN_SAY_FLOOR, m_creature);
 
                if(heatFloor < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature, HEAT_FLOOR) == CAST_OK) heatFloor = 20000;
                }
                else heatFloor -= uiDiff;

                if(boneStorm < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature, BONE_STORM) == CAST_OK) boneStorm = 120000;
                }
                else boneStorm -= uiDiff;

                if(painAgony < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature->getVictim(), PAIN_AND_AGONY) == CAST_OK) painAgony = 15000;

                    if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                    {
                        DoCastSpellIfCan(pTarget, PAIN_AND_AGONY);
                    } 
                }
                else painAgony -= uiDiff;

                if(magicWings < uiDiff)
                {
                    if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                    {
                        DoCastSpellIfCan(m_creature->getVictim(), MAGIC_WINGS);

                        DoScriptText(BERGEN_SAY_WINGS, m_creature);

                        m_creature->AddThreat(pTarget, 100.0f);

                        magicWings = 40000;
                    }
                }
                else magicWings -= uiDiff;

                break;
        }
       
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_bergen(Creature* pCreature)
{
    return new boss_bergen(pCreature);
}

// Gorcrall

enum Gorcrallsays
{
    GORCRALL_SAY_AGRO        = -2000000,
    GORCRALL_SAY_KILL        = -2000001,
    GORCRALL_SAY_DEAD        = -2000002,
    GORCRALL_SAY_PET         = -2000003,
    GORCRALL_SAY_PET_DEAD    = -2000004,
    GORCRALL_SAY_OVER        = -2000005
};

enum Gorcrallspells
{
    EXPLOSIVE_SHOT       = 67985,
    AVENGING_WRATH       = 43430,
    DIVINE_SHIELD        = 40733,
    AIMED_SHOT           = 65883,
    DIVINE_STORM         = 58127 
};

struct MANGOS_DLL_DECL boss_gorcrall : public ScriptedAI
{
    boss_gorcrall(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    char phase;
    Creature *pet;

    uint32 explosiveShot;
    uint32 avengingWrath;
    uint32 aimedShot;
    uint32 divineStorm;
 
    void Reset()
    {
        phase = 0;
        pet = NULL;
 
        explosiveShot    = 10000;
        avengingWrath    = 35000;
        aimedShot        = 6000;
        divineStorm      = 4000;
    }
   
    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(GORCRALL_SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(GORCRALL_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(GORCRALL_SAY_AGRO, m_creature);
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        m_creature->SetPower(m_creature->getPowerType(), 50000000); 

        switch(phase)
        {
            case 0:
                if(m_creature->GetHealthPercent() < 85.0f) phase = 1;

                if(divineStorm < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature, DIVINE_STORM) == CAST_OK) divineStorm = urand(4000, 8000);
                }
                else divineStorm -= uiDiff;

                break;
            case 1:
                pet = m_creature->SummonCreature(80001, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 2000);
                pet->SetInCombatWith(m_creature->getVictim());
 
                DoScriptText(GORCRALL_SAY_PET, m_creature);

                if(DoCastSpellIfCan(m_creature, DIVINE_SHIELD) == CAST_OK) phase = 2;

                break;  
            case 2:
                if(pet && pet->isDead())
                {
                    if(m_creature->HasAura(DIVINE_SHIELD))m_creature->RemoveAurasDueToSpell(DIVINE_SHIELD);
                    phase = 3;
                    DoScriptText(GORCRALL_SAY_PET_DEAD, m_creature);
                    pet->ForcedDespawn();
                }

                break;
            case 3:
                if(avengingWrath < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature, AVENGING_WRATH) == CAST_OK) 
                    {
                        avengingWrath = 35000;
                        DoScriptText(GORCRALL_SAY_OVER, m_creature);
                    }
                }
                else avengingWrath -= uiDiff;

                if(divineStorm < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature, DIVINE_STORM) == CAST_OK) divineStorm = urand(4000, 8000);
                }
                else divineStorm -= uiDiff;

                break;
        } 

        // no phase spells
        if(aimedShot < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                DoCastSpellIfCan(pTarget, AIMED_SHOT);
                aimedShot = 6000;
            } 
        }
        else aimedShot -= uiDiff;

        if(explosiveShot < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                DoCastSpellIfCan(pTarget, EXPLOSIVE_SHOT);
                explosiveShot = 10000;
            } 
        }
        else explosiveShot -= uiDiff;

        DoMeleeAttackIfReady();   
    }
};

CreatureAI* GetAI_boss_gorcrall(Creature* pCreature)
{
    return new boss_gorcrall(pCreature);
}

// Hastur

enum Hastursays
{
    HASTUR_SAY_AGRO        = -2000020,
    HASTUR_SAY_KILL        = -2000021,
    HASTUR_SAY_DEAD        = -2000022,
    HASTUR_SAY_BALL        = -2000023
};

enum Hasturspells
{
    DETOANATE_MANA           = 27819,
    JAWS_OF_DEATH            = 56692,
    CLEAVE                   = 27794,
    FROSTBOMB                = 51103,
    SUPER_SNOWBALL           = 25686
};

struct MANGOS_DLL_DECL boss_hastur : public ScriptedAI
{
    boss_hastur(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 detonateMana;
    uint32 jawsOfDeath;
    uint32 cleave;
    uint32 frostBomb;
    uint32 snowBall;
 
    void Reset()
    {
        detonateMana   = 20000;
        jawsOfDeath    = 10000;
        cleave         = 6000;
        frostBomb      = 15000;
        snowBall       = 30000;
    }
   
    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(HASTUR_SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(HASTUR_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(HASTUR_SAY_AGRO, m_creature);
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(detonateMana < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                DoCastSpellIfCan(pTarget, DETOANATE_MANA);
                detonateMana = 20000;
            }
        }
        else detonateMana -= uiDiff;

        if(jawsOfDeath < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                pTarget->CastSpell(pTarget, JAWS_OF_DEATH, false);
                jawsOfDeath = 10000;
            }
        }
        else jawsOfDeath -= uiDiff;

        if(frostBomb < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                DoCastSpellIfCan(pTarget, FROSTBOMB);
                frostBomb = 15000;
            }
        }
        else frostBomb -= uiDiff;
        
        if(cleave < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), CLEAVE);
            cleave = 6000;
        }
        else cleave -= uiDiff;

        if(snowBall < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                DoScriptText(HASTUR_SAY_BALL, m_creature);

                DoCastSpellIfCan(pTarget, SUPER_SNOWBALL);
                DoCastSpellIfCan(pTarget, SUPER_SNOWBALL);
                DoCastSpellIfCan(pTarget, SUPER_SNOWBALL);
                DoCastSpellIfCan(pTarget, SUPER_SNOWBALL);

                snowBall = 15000;
            }
        }
        else snowBall -= uiDiff;

        DoMeleeAttackIfReady();   
    }
};

CreatureAI* GetAI_boss_hastur(Creature* pCreature)
{
    return new boss_hastur(pCreature);
}

// shyla

enum shylasays
{
    SHYLA_SAY_AGRO        = -2000030,
    SHYLA_SAY_KILL        = -2000031,
    SHYLA_SAY_DEAD        = -2000032,
    SHYLA_SAY_ESSENCE     = -2000033
};

enum shylaspells
{
    FROST_BALL_VOLEY          = 72907,
    MANA_BARRIER              = 70842,
    DEATH_AND_DECAY           = 72110,
    ESSENCE                   = 71533,
    DELIRIUS_SLASH            = 72264
};

struct MANGOS_DLL_DECL boss_shyla : public ScriptedAI
{
    boss_shyla(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 frostBall;
    uint32 deathAndDecay;
    uint32 essence;
    uint32 deliriusSlash;
 
    void Reset()
    {
        frostBall        = 15000;
        deathAndDecay    = 10000;
        essence          = 30000;
        deliriusSlash    = 20000;  
    }
   
    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SHYLA_SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SHYLA_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SHYLA_SAY_AGRO, m_creature);
        DoCastSpellIfCan(m_creature, MANA_BARRIER);
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(frostBall < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                DoCastSpellIfCan(pTarget, FROST_BALL_VOLEY);
                frostBall = 15000;
            }
        }
        else frostBall -= uiDiff;

        if(deathAndDecay < uiDiff)
        {
            bool range = urand(1,0);
            
            if(range) 
            {
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                {
                    DoCastSpellIfCan(pTarget, DEATH_AND_DECAY);
                    deathAndDecay = 10000;
                }
            }
            else if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                DoCastSpellIfCan(pTarget, DEATH_AND_DECAY);
                deathAndDecay = 10000;
            }
        }
        else deathAndDecay -= uiDiff;

        if(essence < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                DoScriptText(SHYLA_SAY_ESSENCE, m_creature);
                DoCastSpellIfCan(pTarget, ESSENCE);
                essence = 90000;
            }
        }
        else essence -= uiDiff;
        
        if(deliriusSlash < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                if (DoCastSpellIfCan(pTarget, DELIRIUS_SLASH) == CAST_OK)
                    deliriusSlash = 20000;
            }
        }
        else deliriusSlash -= uiDiff;

        DoMeleeAttackIfReady();   
    }
};

CreatureAI* GetAI_boss_shyla(Creature* pCreature)
{
    return new boss_shyla(pCreature);
}

// Ailin

enum ailinsays
{
    AILIN_SAY_AGRO        = -2000050,
    AILIN_SAY_KILL        = -2000051,
    AILIN_SAY_PREDEAD     = -2000052,
    AILIN_SAY_DEAD        = -2000053,
    AILIN_SAY_SEDUCTION   = -2000054,
    AILIN_SAY_AGRO2       = -2000055
};

enum ailinspells
{
    FLAME_BRATH           = 74528,
    SEDUCTION             = 6358,
    CREEPENG_PARALIZIS    = 43095,
    SOUL_STONE            = 20763,
    LIGHTNING_WHIRL       = 61915,
    SUNBEAM               = 62623,
    RUNE_OF_DEATH         = 62269
};

struct MANGOS_DLL_DECL boss_ailin : public ScriptedAI
{
    boss_ailin(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool endcombat;
    bool revive;

    uint32 flameBreath;
    uint32 seduction;
    uint32 creepengParalizis;
    uint32 sunbeam;
    uint32 LightningWhirl;
    uint32 runeOFdeath;

    void Reset()
    {
        endcombat   = false;
        revive      = true;

        flameBreath        = 20000;
        seduction          = 12000;
        creepengParalizis  = 35000;
        sunbeam            = 80000;
        LightningWhirl     = 30000;
        runeOFdeath        = 40000;
    }
   
    void KilledUnit(Unit* pVictim)
    {
    }

    void JustDied(Unit* pKiller)
    {
        if(!endcombat)
        {
            m_creature->SetDeathState(ALIVE);
            m_creature->SetHealthPercent(30.0f);
            DoScriptText(AILIN_SAY_PREDEAD, m_creature);
            endcombat = true;
            DoMeleeAttackIfReady();
        }
        else DoScriptText(AILIN_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        if(revive)
        { 
            DoScriptText(AILIN_SAY_AGRO, m_creature);
            DoScriptText(AILIN_SAY_AGRO2, m_creature);
        }
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        m_creature->SetPower(m_creature->getPowerType(), 50000000); 

        if(revive && m_creature->GetHealthPercent() < 20.0f)
        {
            if (DoCastSpellIfCan(m_creature, SOUL_STONE) == CAST_OK) revive = false;
        }
        
        if(flameBreath < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, FLAME_BRATH) == CAST_OK)
                flameBreath = 20000;
        }
        else flameBreath -= uiDiff;

        if(seduction < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                if (DoCastSpellIfCan(pTarget, SEDUCTION) == CAST_OK)
                {
                    seduction = 12000;
                    DoScriptText(AILIN_SAY_SEDUCTION, m_creature);
                }
            }            
        }
        else seduction -= uiDiff;  

        if(sunbeam < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                if (DoCastSpellIfCan(pTarget, SUNBEAM) == CAST_OK)
                {
                    sunbeam = 8000;
                }
            }            
        }
        else sunbeam -= uiDiff;   

        if(creepengParalizis < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, CREEPENG_PARALIZIS) == CAST_OK)
                creepengParalizis = 35000;
        }
        else creepengParalizis -= uiDiff;   

        if(runeOFdeath < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, RUNE_OF_DEATH) == CAST_OK)
                runeOFdeath = 40000;
        }
        else runeOFdeath -= uiDiff;  

        if(LightningWhirl < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, LIGHTNING_WHIRL) == CAST_OK)
                LightningWhirl = 30000;
        }
        else LightningWhirl -= uiDiff; 

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_ailin(Creature* pCreature)
{
    return new boss_ailin(pCreature);
}

// Gedeon

enum gedeonsays
{
    GEDEON_SAY_AGRO        = -2000080,
    GEDEON_SAY_KILL        = -2000081,
    GEDEON_SAY_DEAD        = -2000082
};

enum gedeonspells
{
    THUNDER_STORM         = 60010,
    G_FROSTBALL_VOLLEY    = 72905,
    LAVA_GOUT             = 74394
};

struct MANGOS_DLL_DECL boss_gedeon : public ScriptedAI
{
    boss_gedeon(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 thunderStorm;
    uint32 frostball;
    uint32 LavaGout;

    void Reset()
    {
        SetCombatMovement(false);

        thunderStorm = 5000;
        frostball    = 12000;
        LavaGout     = 0;
    }
   
    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(GEDEON_SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(GEDEON_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        SetCombatMovement(false);
        DoScriptText(GEDEON_SAY_AGRO, m_creature);
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
 
        SetCombatMovement(false);

        if(thunderStorm < uiDiff)
        {
            if(DoCastSpellIfCan(m_creature, THUNDER_STORM) == CAST_OK)
            {
                thunderStorm = 5000;
            }
        }
        else thunderStorm -= uiDiff;

        if(frostball < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, G_FROSTBALL_VOLLEY) == CAST_OK) frostball = 12000;
        }
        else frostball -= uiDiff;

        if (LavaGout <= uiDiff)
        {
            if(DoCastSpellIfCan(m_creature->getVictim(), LAVA_GOUT) == CAST_OK)
                LavaGout = 3000;
        }
        else LavaGout -= uiDiff;
    
    }
};

CreatureAI* GetAI_boss_gedeon(Creature* pCreature)
{
    return new boss_gedeon(pCreature);
}

// Douce

enum doucesays
{
    DOUCE_SAY_AGRO        = -2000040,
    DOUCE_SAY_KILL        = -2000041,
    DOUCE_SAY_DEAD        = -2000042,
    DOUCE_SAY_BERSERK     = -2000043
};

enum doucespells
{
    IMTIMIDATING_ROAR = 74384
};

struct MANGOS_DLL_DECL boss_douce : public ScriptedAI
{
    boss_douce(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 enrage;
    uint32 ImtimidatingRoar;

    void Reset()
    {
        enrage = 4 * MINUTE * IN_MILLISECONDS;
        ImtimidatingRoar = 15000;
    }
   
    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(DOUCE_SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(DOUCE_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(DOUCE_SAY_AGRO, m_creature);
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (enrage < uiDiff)
        {
            if(DoCastSpellIfCan(m_creature, 47008, CAST_TRIGGERED) == CAST_OK)
            {
                DoScriptText(DOUCE_SAY_BERSERK, m_creature);
                enrage = 3 * MINUTE * IN_MILLISECONDS;
            }
        }
        else enrage -= uiDiff;

        if (ImtimidatingRoar <= uiDiff)
        {
            if(DoCastSpellIfCan(m_creature->getVictim(), IMTIMIDATING_ROAR) == CAST_OK)
            {
                ImtimidatingRoar = 15000;
            }
        }
        else ImtimidatingRoar -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_douce(Creature* pCreature)
{
    return new boss_douce(pCreature);
}

// Aerom

enum aeromsays
{
    AEROM_SAY_AGRO        = -2000070,
    AEROM_SAY_KILL        = -2000071,
    AEROM_SAY_DEAD        = -2000072
};

enum aeromspells
{
    BLADESTORM       = 65947,
    REPELLING_WAVE   = 74509,
    HEROISM          = 32182,
    PSICHICK_SCREAM  = 8122,
    BLOOD_BEAST      = 72173,
    SPELL_REFLECTION = 23920,
    RENEW            = 62441,
    CHAIN_LIGHTING   = 62131
};

struct MANGOS_DLL_DECL boss_aerom : public ScriptedAI
{
    boss_aerom(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool heroism;

    uint32 bladestorm;
    uint32 repellingwave;
    uint32 scream;
    uint32 beast;
    uint32 reflection;
    uint32 renew;
    uint32 chain;

    void Reset()
    {
        if(!m_creature->HasAura(15473)) m_creature->CastSpell(m_creature, 15473, false);
        
        heroism = true;

        bladestorm  = 20000;
        repellingwave = 56000;
        scream        = 15000;
        beast = 35000;
        reflection = 10000;
        renew = 8000;
        chain = 13000;
    }
   
    void KilledUnit(Unit* pVictim)
    {
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(AEROM_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        if(!m_creature->HasAura(15473)) m_creature->CastSpell(m_creature, 15473, false);
        DoScriptText(AEROM_SAY_AGRO, m_creature);
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        m_creature->SetPower(m_creature->getPowerType(), 50000000); 

        if(heroism && m_creature->GetHealthPercent() < 70.0f)
        {
            m_creature->CastSpell(m_creature, HEROISM, false);
            heroism = false;
        }

        if(bladestorm < uiDiff)
        {
            m_creature->CastSpell(m_creature, BLADESTORM, true);
            bladestorm  = 20000;
        }
        else bladestorm -= uiDiff;

        if(repellingwave < uiDiff)
        {
            m_creature->CastSpell(m_creature, REPELLING_WAVE, false);
            repellingwave = 56000;
        }
        else repellingwave -= uiDiff;
 
        if(scream < uiDiff)
        {
            m_creature->CastSpell(m_creature, PSICHICK_SCREAM, false);
            scream = 15000;
        }
        else scream -= uiDiff;

        if(beast < uiDiff)
        {
            m_creature->CastSpell(m_creature, BLOOD_BEAST, true);
            beast = 35000;
        }
        else beast -= uiDiff;

        if(reflection < uiDiff)
        {
            m_creature->CastSpell(m_creature, SPELL_REFLECTION, true);
            reflection = 10000;
        }
        else reflection -= uiDiff;

        if(renew < uiDiff)
        {
            m_creature->CastSpell(m_creature, RENEW, true);
            renew = 8000;
        }
        else renew -= uiDiff;

        if(chain < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                if (DoCastSpellIfCan(pTarget, CHAIN_LIGHTING) == CAST_OK)
                {
                    chain = 13000;
                }
            }  
        }
        else chain -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_aerom(Creature* pCreature)
{
    return new boss_aerom(pCreature);
}

// Raynar

enum raynarsays
{
    RAYNAR_SAY_AGRO        = -2000090,
    RAYNAR_SAY_KILL        = -2000091,
    RAYNAR_SAY_DEAD        = -2000092,
    RAYNAR_SAY_JAIL        = -2000093,
    RAYNAR_SAY_TAIL        = -2000094
};

enum raynarspells
{
    SHADOW_JAIL        = 45922,
    GRIP_OF_THE_LEGION = 31972,

};

struct MANGOS_DLL_DECL boss_raynar : public ScriptedAI
{
    boss_raynar(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    Creature *sumon;

    uint32 shadowjail;
    uint32 grip;
    uint32 cleave;
    uint32 flameBreath;
    uint32 tailSlash;
    uint32 sumon;

    void Reset()
    {
        SetEquipmentSlots(false, 54806, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE);
         
        shadowjail  = 30000;
        grip        = 10000;
        cleave      = 14000;
        flameBreath = 20000;
        tailSlash   = 20000;
        tsummon     = 60000;

        sumon = NULL;
    }  
   
    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(RAYNAR_SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(RAYNAR_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        SetEquipmentSlots(false, 54806, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE);

        DoScriptText(RAYNAR_SAY_AGRO, m_creature);
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(shadowjail < uiDiff)
        {
            if(Unit *target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {    
                target->CastSpell(target, SHADOW_JAIL, false);

                shadowjail = 2 * MINUTE * IN_MILLISECONDS;
                DoScriptText(RAYNAR_SAY_JAIL, m_creature);

            }
        }
        else shadowjail -= uiDiff;

        if(grip < uiDiff)
        {
            if(Unit *target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {    
                if (DoCastSpellIfCan(target, GRIP_OF_THE_LEGION) == CAST_OK)
                    grip = 20000;
            }
        }
        else grip -= uiDiff;

        if(cleave < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), CLEAVE);
                cleave = 12000;
        }
        else cleave -= uiDiff;

        if(flameBreath < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, FLAME_BRATH) == CAST_OK)
                flameBreath = 20000;
        }
        else flameBreath -= uiDiff;

        if(tailSlash < uiDiff)
        {
            if(DoCastSpellIfCan(m_creature, TAIL_SLASH) == CAST_OK) 
            {
                DoScriptText(RAYNAR_SAY_TAIL, m_creature);
                tailSlash = 30000;
            }
        }
        else tailSlash -= uiDiff;

        if(!sumon && tsummon < uiDiff)
        { 
            sumon = m_creature->SummonCreature(36724, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 2000); 
            if(DoCastSpellIfCan(m_creature, DIVINE_SHIELD) == CAST_OK) tsummon = 2 * MINUTE * IN_MILLISECONDS;
        }
        else tsummon -= uiDiff;

        if(sumon && sumon->isDead())
        {
            if(m_creature->HasAura(DIVINE_SHIELD))m_creature->RemoveAurasDueToSpell(DIVINE_SHIELD);  
            sumon = NULL;   
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_raynar(Creature* pCreature)
{
    return new boss_raynar(pCreature);
}

// Blend

enum blendsays
{
    BLEND_SAY_AGRO        = -2000060,
    BLEND_SAY_KILL        = -2000061,
    BLEND_SAY_DEAD        = -2000062,
    BLEND_SAY_BAN         = -2000063   
};

enum blendspells
{
    FROSTBALL_VOLLEY      = 72905,
    SLIME_SPRAY           = 69508,
    SCHORCH               = 63474,
    BLIZZARD              = 28560
};

struct MANGOS_DLL_DECL boss_blend : public ScriptedAI
{
    boss_blend(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 frostball;
    uint32 slime;
    uint32 schorch;
    uint32 blizzard;

    void Reset()
    {
        frostball  = 15000;
        slime      = 20000;
        schorch    = 32000;
        blizzard   = 17000;
    }
   
    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(BLEND_SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(BLEND_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(BLEND_SAY_AGRO, m_creature);
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(frostball < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, FROSTBALL_VOLLEY) == CAST_OK) frostball = 15000;
        }
        else frostball -= uiDiff;

        if(slime < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SLIME_SPRAY) == CAST_OK) slime = 20000;
        }
        else slime -= uiDiff;

        if(schorch < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SCHORCH) == CAST_OK) 
            {
                schorch = 32000;
                DoScriptText(BLEND_SAY_BAN, m_creature);
            }
        }
        else schorch -= uiDiff;

        if(blizzard < uiDiff)
        {
             if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                 if (DoCastSpellIfCan(pTarget, BLIZZARD) == CAST_OK) blizzard = 17000;
        }
        else blizzard -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_blend(Creature* pCreature)
{
    return new boss_blend(pCreature);
}

// Tallulah

enum tallulahsays
{
    TALLULAH_SAY_AGRO        = -2000100,
    TALLULAH_SAY_KILL        = -2000101,
    TALLULAH_SAY_DEAD        = -2000102,
};

enum tallulahspells
{
    FIREBLAST          = 45232,
    SHADOW_NOVA        = 45329,
    CONFLAGRATION      = 45342,
    CONFOUNDING_BLOW   = 45256
};

struct MANGOS_DLL_DECL boss_tallulah : public ScriptedAI
{
    boss_tallulah(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 fireblast;
    uint32 shadownova;
    uint32 confounding;

    void Reset()
    {
        fireblast   = 20000;
        shadownova  = 15000;
        confounding = 9000;
    }
   
    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(TALLULAH_SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(TALLULAH_SAY_DEAD, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(TALLULAH_SAY_AGRO, m_creature);
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(fireblast < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, FIREBLAST) == CAST_OK) 
            {
                fireblast = 20000;
            }
        }
        else fireblast -= uiDiff;

        if(shadownova < uiDiff)
        {
            if(Unit *target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {    
                bool conf = urand(0,1);

                if (DoCastSpellIfCan(target, conf ? CONFLAGRATION : SHADOW_NOVA) == CAST_OK) 
                    shadownova = 15000;
            }
        }
        else shadownova -= uiDiff;

        if(confounding < uiDiff)
        {
            if(Unit *target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {    
                if (DoCastSpellIfCan(target, CONFOUNDING_BLOW) == CAST_OK) 
                    confounding = 9000;
            }
        }
        else confounding -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_tallulah(Creature* pCreature)
{
    return new boss_tallulah(pCreature);
}

// Giresse

bool giresse_AI = false;

bool GossipHello_giresse(Player* pPlayer, Creature* pCreature)
{
    if(giresse_AI) return false;

    char const* OPTION = "Explicanos el evento";
 
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_giresse(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{

    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
        default:
            pPlayer->CLOSE_GOSSIP_MENU();
            giresse_AI = true;
            break;
    }

    return true;
}

struct MANGOS_DLL_DECL boss_giresse : public ScriptedAI
{
    boss_giresse(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool first;
    bool second;
    bool third;

    uint32 timer;

    void Reset()
    {
        SetEquipmentSlots(false, 19019, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE);

        timer   = 0;

        first   = true;
        second  = true;
        third   = true;
    }

    void KilledUnit(Unit* pVictim) {}
    void JustDied(Unit* pKiller) {}
    void Aggro(Unit* pWho) {}

    void UpdateAI(const uint32 uiDiff)
    {
        if(!giresse_AI) return;

        timer += uiDiff; 

        if(first)
        {
            m_creature->MonsterYell("Durante muchos años os he guiado por el camino del PVE. He testeado instances, he muerto por vosotros para que pudierais derrotar a los más dificiles jefes.", 0);
            first = false;
        }

        if(second && timer > 10000)
        {
            second = false;
            m_creature->MonsterYell("Hoy, me complace presentaros mi último test. <La senda de los GMs>, dónde podréis visitar a cada uno de nuestros Maestros de juego y luchar contra ellos. Pero cuidado, os aviso que no será fácil.",0)

        }

        if(third && timer > 20000)
        {            
            third = false;
            m_creature->MonsterYell("Suerte aventureros, seguro que la vais a necesitar.",0)
        }

        if(!third) 
        {
            giresse_AI = false;
            Reset();
        }
    }

};

CreatureAI* GetAI_boss_giresse(Creature* pCreature)
{
    return new boss_giresse(pCreature);
}

void AddSC_npcs_radical()
{
    Script* pNewScript;
    
    pNewScript = new Script;
    pNewScript->Name = "logroneitor_horde";
    pNewScript->pGossipHello = &GossipHello_logroneitor_horde;
    pNewScript->pGossipSelect = &GossipSelect_logroneitor_horde;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "logroneitor_alliance";
    pNewScript->pGossipHello = &GossipHello_logroneitor_alliance;
    pNewScript->pGossipSelect = &GossipSelect_logroneitor_alliance;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "teleport_acherus_up";
    pNewScript->pGossipHello = &GossipHello_acherus_teleporter_up;
    pNewScript->pGossipSelect = &GossipSelect_acherus_teleporter_up;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "teleport_acherus_down";
    pNewScript->pGossipHello = &GossipHello_acherus_teleporter_down;
    pNewScript->pGossipSelect = &GossipSelect_acherus_teleporter_down;
    pNewScript->RegisterSelf();

    /** BOSS STAFF **/
    pNewScript = new Script;
    pNewScript->Name = "boss_bergen";
    pNewScript->GetAI = &GetAI_boss_bergen;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_gorcrall";
    pNewScript->GetAI = &GetAI_boss_gorcrall;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_hastur";
    pNewScript->GetAI = &GetAI_boss_hastur;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_shyla";
    pNewScript->GetAI = &GetAI_boss_shyla;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_ailin";
    pNewScript->GetAI = &GetAI_boss_ailin;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_gedeon";
    pNewScript->GetAI = &GetAI_boss_gedeon;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_douce";
    pNewScript->GetAI = &GetAI_boss_douce;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_aerom";
    pNewScript->GetAI = &GetAI_boss_aerom;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_raynar";
    pNewScript->GetAI = &GetAI_boss_raynar;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_blend";
    pNewScript->GetAI = &GetAI_boss_blend;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_tallulah";
    pNewScript->GetAI = &GetAI_boss_tallulah;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_giresse";
    pNewScript->pGossipHello = &GossipHello_giresse;
    pNewScript->pGossipSelect = &GossipSelect_giresse;
    pNewScript->GetAI = &GetAI_boss_giresse;
    pNewScript->RegisterSelf();
}
