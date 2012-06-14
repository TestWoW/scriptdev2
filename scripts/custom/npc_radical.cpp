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
}
