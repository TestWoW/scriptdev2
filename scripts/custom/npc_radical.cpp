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
## boss_staff
## Radical custom BOSS
######*/

// Bergen

enum Bergensays
{
    BERGEN_SAY_AGRO        = -2000010,
    BERGEN_SAY_KILL        = -2000011,
    BERGEN_SAY_DEAD        = -2000012,
    BERGEN_SAY_WINGS       = -2000013
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
    //Player *display;

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
        //display = sObjectMgr.GetPlayer(3);
 
        tailSlash     = 10000;
        heatFloor     = 20000;
        boneStorm     = 120000;
        evilSpirits   = 60000;
        painAgony     = 15000;
        fireWall      = 5000;
        magicWings    = 40000; 

        /*if(display)
            m_creature->CastSpell(m_creature, 45204, true, NULL, NULL, display->GetObjectGuid()); 
        if(display)
            m_creature->CastSpell(m_creature, 69837, true, NULL, NULL, display->GetObjectGuid());*/
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

                if(heatFloor < uiDiff)
                {
                    if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                    {
                        DoCastSpellIfCan(pTarget, HEAT_FLOOR);
                    }

                    if(DoCastSpellIfCan(m_creature, HEAT_FLOOR) == CAST_OK) heatFloor = 3000;
                }
                else heatFloor -= uiDiff;

                if(boneStorm < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature, BONE_STORM) == CAST_OK) boneStorm = 120000;
                }
                else boneStorm -= uiDiff;

                /*if(evilSpirits < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature, EVIL_SPIRITS ) == CAST_OK) evilSpirits = 60000;
                }
                else evilSpirits -= uiDiff;*/

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
                    if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    {
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
        if(pet) pet->ForcedDespawn();
        phase = 0;
 
        explosiveShot = 10000;
        avengingWrath = 35000;
        aimedShot = 6000;
        divineStorm = 4000;
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

        switch(phase)
        {
            case 0:
                if(m_creature->GetHealthPercent() < 85.0f) phase = 1;

                if(divineStorm < uiDiff)
                {
                    if(DoCastSpellIfCan(m_creature, DIVINE_STORM) == CAST_OK) divineStorm = urand(4000, 8000);
                    m_creature->SetPower(m_creature->getPowerType(), 50000000);
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
                DoCastSpellIfCan(pTarget, AIMED_SHOT);
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
    HASTUR_SAY_BALL       = -2000023,
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
        detonateMana = 20000;
        jawsOfDeath = 10000;
        cleave = 6000;
        frostBomb = 15000;
        snowBall = 30000;
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
}
