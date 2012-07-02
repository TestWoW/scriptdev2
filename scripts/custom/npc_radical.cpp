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
                    if(DoCastSpellIfCan(m_creature, HEAT_FLOOR) == CAST_OK) heatFloor = 6000;
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
    AIMED_SHOT           = 67979,
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
                DoCastSpellIfCan(pTarget, JAWS_OF_DEATH);
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
};

enum ailinspells
{
};

struct MANGOS_DLL_DECL boss_ailin : public ScriptedAI
{
    boss_ailin(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset()
    {
    }
   
    void KilledUnit(Unit* pVictim)
    {
    }

    void JustDied(Unit* pKiller)
    {
    }

    void Aggro(Unit* pWho)
    {
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

    }
};

CreatureAI* GetAI_boss_ailin(Creature* pCreature)
{
    return new boss_ailin(pCreature);
}

// Gedeon

enum gedeonsays
{
};

enum gedeonspells
{
    THUNDER_STORM = 60010
};

struct MANGOS_DLL_DECL boss_gedeon : public ScriptedAI
{
    boss_gedeon(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 thunderStorm;

    void Reset()
    {
        m_creature->GetMotionMaster()->Clear();

        thunderStorm = 5000;
    }
   
    void KilledUnit(Unit* pVictim)
    {
    }

    void JustDied(Unit* pKiller)
    {
    }

    void Aggro(Unit* pWho)
    {
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
};

struct MANGOS_DLL_DECL boss_douce : public ScriptedAI
{
    boss_douce(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 enrage;

    void Reset()
    {
        enrage = 3 * MINUTE * IN_MILLISECONDS;
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

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_douce(Creature* pCreature)
{
    return new boss_douce(pCreature);
}

// Raynar

enum raynarsays
{
};

enum raynarspells
{
};

struct MANGOS_DLL_DECL boss_raynar : public ScriptedAI
{
    boss_raynar(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset()
    {
    }
   
    void KilledUnit(Unit* pVictim)
    {
    }

    void JustDied(Unit* pKiller)
    {
    }

    void Aggro(Unit* pWho)
    {
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
    }
};

CreatureAI* GetAI_boss_raynar(Creature* pCreature)
{
    return new boss_raynar(pCreature);
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
    pNewScript->Name = "boss_raynar";
    pNewScript->GetAI = &GetAI_boss_raynar;
    pNewScript->RegisterSelf();
}
