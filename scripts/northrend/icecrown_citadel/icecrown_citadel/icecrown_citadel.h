/* Copyright (C) 2010 -2011 by /dev/rsa for ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_icecrown_citadel_H
#define DEF_icecrown_citadel_H
#include "BSW_ai.h"
#include "BSW_instance.h"

enum
{
    TYPE_TELEPORT                       = 0,
    TYPE_MARROWGAR                      = 1,
    TYPE_DEATHWHISPER                   = 2,
    TYPE_FLIGHT_WAR                     = 3,
    TYPE_SAURFANG                       = 4,
    TYPE_FESTERGUT                      = 5,
    TYPE_ROTFACE                        = 6,
    TYPE_PUTRICIDE                      = 7,
    TYPE_BLOOD_COUNCIL                  = 8,
    TYPE_LANATHEL                       = 9,
    TYPE_VALITHRIA                      = 10,
    TYPE_SINDRAGOSA                     = 11,
    TYPE_LICH_KING                      = 12,
    MAX_ENCOUNTERS,

    TYPE_FROSTMOURNE_ROOM,
    TYPE_KINGS_OF_ICC,
    TYPE_ICECROWN_QUESTS,
    TYPE_STINKY,
    TYPE_PRECIOUS,
    TYPE_SVALNA,

    NPC_LORD_MARROWGAR                  = 36612,
    NPC_LADY_DEATHWHISPER               = 36855,
    NPC_DEATHBRINGER_SAURFANG           = 37813,
    NPC_FESTERGUT                       = 36626,
    NPC_ROTFACE                         = 36627,
    NPC_PROFESSOR_PUTRICIDE             = 36678,
    NPC_TALDARAM                        = 37973,
    NPC_VALANAR                         = 37970,
    NPC_KELESETH                        = 37972,
    NPC_LANATHEL                        = 37955,

    NPC_HORDE_1                         = 37032,
    NPC_HORDE_2                         = 37028,
    NPC_HORDE_3                         = 37029,
    NPC_HORDE_4                         = 37030,
    NPC_HORDE_5                         = 37146,

    NPC_ALLY_1                          = 37003,
    NPC_ALLY_2                          = 37017,
    NPC_ALLY_3                          = 37021,
    NPC_ALLY_4                          = 37026,
    NPC_ALLY_5                          = 37027,

    NPC_CROK                            = 37129,
    NPC_ARNATH                          = 37122,
    NPC_ARNATH_UNDEATH                  = 37491,
    NPC_BRANDON                         = 37123,
    NPC_BRANDON_UNDEATH                 = 37493,
    NPC_GRONDEL                         = 37124,
    NPC_GRONDEL_UNDEATH                 = 37494,
    NPC_RUPERT                          = 37125,
    NPC_RUPERT_UNDEATH                  = 37495,
    NPC_SVALNA                          = 37126,

    NPC_VALITHRIA                       = 36789,
    NPC_VALITHRIA_QUEST                 = 38589,
    NPC_LICH_TRIGGER                    = 37181,
    NPC_SINDRAGOSA                      = 36853,
    NPC_LICH_KING                       = 36597,

    NPC_LANATHEL_INTRO                  = 38004,
    NPC_BLOOD_ORB_CONTROL               = 38008,

    NPC_MURADIN                         = 36948,

    NPC_TIRION                          = 38995,
    NPC_MENETHIL                        = 38579,
    NPC_SPIRIT_WARDEN                   = 36824,
    NPC_TERENAS_FROSTMOURNE             = 36823,

    NPC_FROSTMOURNE_TRIGGER             = 38584,
    NPC_FROSTMOURNE_HOLDER              = 27880,

    NPC_STINKY                          = 37025,
    NPC_PRECIOUS                        = 37217,

    NPC_RIMEFANG                        = 37533,
    NPC_SPINESTALKER                    = 37534,

    NPC_COMBAT_TRIGGER                  = 38752,
    NPC_CULT_ADHERENT                   = 37949,
    NPC_REANIMATED_ADHERENT             = 38010,
    NPC_CULT_FANATIC                    = 37890,
    NPC_REANIMATED_FANATIC              = 38009,
    NPC_DEFORMED_FANATIC                = 38135,
    NPC_PUDDLE_STALKER                  = 37013,
    NPC_LITTLE_OOZE                     = 36897,
    NPC_BIG_OOZE                        = 36899,
    NPC_OOZE_SPRAY_STALKER              = 37986,
    NPC_ORANGE_GAS_STALKER              = 36659,
    NPC_MALLEABLE_GOO                   = 38556,
    NPC_GREEN_ORANGE_OOZE_STALKER       = 37824,
    NPC_GROWING_OOZE_PUDDLE             = 37690,
    NPC_GROWING_OOZE_PUDDLE_TRIG        = 38234,
    NPC_CHOKING_GAS_BOMB                = 38159,
    NPC_VOLATILE_OOZE                   = 37697,
    NPC_MUTATED_ABOMINATION             = 37672,

    GO_TELEPORT_GOSSIP_MESSAGE          = 99323,
    TELEPORT_GOSSIP_MESSAGE             = 99322,

    GO_ICEWALL_1                        = 201911,
    GO_ICEWALL_2                        = 201910,

    GO_MARROWGAR_DOOR                   = 201857,

    GO_ORATORY_DOOR                     = 201563,
    GO_DEATHWHISPER_ELEVATOR            = 202220, //5653

    GO_SAURFANG_DOOR                    = 201825,

    GO_GAS_RELEASE_VALVE                = 201616, //72479

    GO_ORANGE_PLAGUE                    = 201371, //72536
    GO_GREEN_PLAGUE                     = 201370, //72537

    GO_SCIENTIST_DOOR_GREEN             = 201614, //72530
    GO_SCIENTIST_DOOR_ORANGE            = 201613, //72531
    GO_SCIENTIST_DOOR_COLLISION         = 201612,
    GO_SCIENTIST_DOOR                   = 201372, //72541

    GO_BLOODWING_DOOR                   = 201920, //72532
    GO_CRIMSON_HALL_DOOR                = 201376, //72532
    GO_COUNCIL_DOOR_1                   = 201377, //72533
    GO_COUNCIL_DOOR_2                   = 201378, //72534

    GO_BLOODPRINCE_DOOR                 = 201746,
    GO_ICECROWN_GRATE                   = 201755,

    GO_FROSTWING_DOOR                   = 201919,
    GO_GREEN_DRAGON_DOOR_1              = 201375, //1202
    GO_GREEN_DRAGON_DOOR_2              = 201374, //1200
    GO_VALITHRIA_DOOR_1                 = 201381, //1618
    GO_VALITHRIA_DOOR_2                 = 201382, //1482
    GO_VALITHRIA_DOOR_3                 = 201383, //1335
    GO_VALITHRIA_DOOR_4                 = 201380, //1558

    GO_SINDRAGOSA_DOOR_1                = 201369, //1619
    GO_SINDRAGOSA_DOOR_2                = 201379,

    GO_SINDRAGOSA_ENTRANCE              = 201373,

    GO_SINDRAGOSA_ICEWALL               = 201385,

    GO_FROZENTRONE_TR                   = 202223, //72061

    GO_SAURFANG_CACHE_10                = 202239,
    GO_SAURFANG_CACHE_25                = 202240,
    GO_SAURFANG_CACHE_10_H              = 202238,
    GO_SAURFANG_CACHE_25_H              = 202241,

    GO_GUNSHIP_ARMORY_A_10              = 201872, //
    GO_GUNSHIP_ARMORY_A_25              = 201873, //
    GO_GUNSHIP_ARMORY_A_10H             = 201874, //
    GO_GUNSHIP_ARMORY_A_25H             = 201875, //

    GO_GUNSHIP_ARMORY_H_10              = 202177, //
    GO_GUNSHIP_ARMORY_H_25              = 202178, //
    GO_GUNSHIP_ARMORY_H_10H             = 202179, //
    GO_GUNSHIP_ARMORY_H_25H             = 202180, //

    GO_DREAMWALKER_CACHE_10             = 201959, //
    GO_DREAMWALKER_CACHE_25             = 202339, //
    GO_DREAMWALKER_CACHE_10_H           = 202338, //
    GO_DREAMWALKER_CACHE_25_H           = 202340, //

    GO_PLAGUE_SIGIL                     = 202182,
    GO_FROSTWING_SIGIL                  = 202181,
    GO_BLOODWING_SIGIL                  = 202183,

    GO_ICESHARD_1                       = 202142, //8304
    GO_ICESHARD_2                       = 202141, //8364
    GO_ICESHARD_3                       = 202143, //8310
    GO_ICESHARD_4                       = 202144, //9007

    GO_FROSTY_WIND                      = 202188, //
    GO_FROSTY_EDGE                      = 202189, //
    GO_SNOW_EDGE                        = 202190, //
    GO_ARTHAS_PLATFORM                  = 202161, //
    GO_ARTHAS_PRECIPICE                 = 202078, //

    //TYPE_EVENT_TIMER                    = 99,
    //TYPE_EVENT                          = 100,
    //TYPE_EVENT_NPC                      = 101,
    MAP_NUM                             = 631,
    //DATA_DIRECTION                      = 1001,
    //DATA_BLOOD_INVOCATION               = 1002,
    DESPAWN_TIME                        = 300000,
    SPELL_SHADOWS_EDGE                  = 71168,

    TYPE_BONED                          = 0,
    TYPE_FULL_HOUSE                     = 1,
    TYPE_ON_THE_BOAT                    = 2,
    TYPE_IVE_MADE_AND_MESS              = 3,
    TYPE_DANCES_WITH_OOZES              = 4,
    TYPE_FLU_SHORT_SHORTAGE             = 5,
    TYPE_NAUSEA_HEATBURN_INDIGESTION    = 6,
    TYPE_ORB_WHISPERER                  = 7,
    TYPE_ONCE_BITTEN_TWICE_SHY_N        = 8,
    TYPE_ONCE_BITTEN_TWICE_SHY_V        = 9,
    TYPE_PORTAL_JOCKEY                  = 10,
    TYPE_ALL_YOU_CAN_EAT                = 11,
    TYPE_BEEN_WAITING_A_LONG_TIME       = 12,
    TYPE_NECK_DEEP_IN_VILE              = 13,

    MAX_SPECIAL_ACHIEV_CRITS            = 14,

    // Lord Marrowgar
    CRITERIA_BONED_10N                  = 12775,
    CRITERIA_BONED_25N                  = 12962,
    CRITERIA_BONED_10H                  = 13393,
    CRITERIA_BONED_25H                  = 13394,

    // Lady Deathwhisper
    CRITERIA_FULL_HOUSE_10N             = 12776,
    CRITERIA_FULL_HOUSE_25N             = 12997,
    CRITERIA_FULL_HOUSE_10H             = 12995,
    CRITERIA_FULL_HOUSE_25H             = 12998,

    // Deathbringer Saurfang
    CRITERIA_IVE_MADE_AND_MESS_10N      = 12778,
    CRITERIA_IVE_MADE_AND_MESS_25N      = 13036,
    CRITERIA_IVE_MADE_AND_MESS_10H      = 13035,
    CRITERIA_IVE_MADE_AND_MESS_25H      = 13037,

    // Rotface
    CRITERIA_DANCES_WITH_OOZES_10N      = 12984,
    CRITERIA_DANCES_WITH_OOZES_25N      = 12966,
    CRITERIA_DANCES_WITH_OOZES_10H      = 12985,
    CRITERIA_DANCES_WITH_OOZES_25H      = 12983,

    // Festergut
    CRITERIA_FLU_SHORT_SHORTAGE_10N     = 12977,
    CRITERIA_FLU_SHORT_SHORTAGE_25N     = 12967,
    CRITERIA_FLU_SHORT_SHORTAGE_10H     = 12986,
    CRITERIA_FLU_SHORT_SHORTAGE_25H     = 12982,

    // Professor Putricide
    CRITERIA_NAUSEA_10N                 = 12987,
    CRITERIA_NAUSEA_25N                 = 12968,
    CRITERIA_NAUSEA_10H                 = 12988,
    CRITERIA_NAUSEA_25H                 = 12981,

    // Blood Prince Council
    CRITERIA_ORB_WHISPERER_10N          = 13033,
    CRITERIA_ORB_WHISPERER_25N          = 12969,
    CRITERIA_ORB_WHISPERER_10H          = 13034,
    CRITERIA_ORB_WHISPERER_25H          = 13032,

    // Blood-Queen Lana'thel
    CRITERIA_KILL_LANA_THEL_10M         = 13340,
    CRITERIA_KILL_LANA_THEL_25M         = 13360,
    CRITERIA_ONCE_BITTEN_TWICE_SHY_10N  = 12780,
    CRITERIA_ONCE_BITTEN_TWICE_SHY_25N  = 13012,
    CRITERIA_ONCE_BITTEN_TWICE_SHY_10V  = 13011,
    CRITERIA_ONCE_BITTEN_TWICE_SHY_25V  = 13013,

    // Valthiria Dreamwalker
    CRITERIA_PORTAL_JOCKEY_10N          = 12978,
    CRITERIA_PORTAL_JOCKEY_25N          = 12971,
    CRITERIA_PORTAL_JOCKEY_10H          = 12979,
    CRITERIA_PORTAL_JOCKEY_25H          = 12980,

    // Sindragosa
    CRITERIA_ALL_YOU_CAN_EAT_10N        = 12822,
    CRITERIA_ALL_YOU_CAN_EAT_25N        = 12972,
    CRITERIA_ALL_YOU_CAN_EAT_10H        = 12996,
    CRITERIA_ALL_YOU_CAN_EAT_25H        = 12989,

    // The lich king
    CRITERIA_BEEN_WAITING_10N           = 13246,
    CRITERIA_BEEN_WAITING_10H           = 13247,
    CRITERIA_BEEN_WAITING_25N           = 13244,
    CRITERIA_BEEN_WAITING_25H           = 13245,

    CRITERIA_NECK_DEEP_IN_VILE_10N      = 12823,
    CRITERIA_NECK_DEEP_IN_VILE_10H      = 13163,
    CRITERIA_NECK_DEEP_IN_VILE_25N      = 13243,
    CRITERIA_NECK_DEEP_IN_VILE_25H      = 13164,
};

class MANGOS_DLL_DECL instance_icecrown_citadel : public ScriptedInstance
{
public:
    instance_icecrown_citadel(Map* pMap);
    ~instance_icecrown_citadel() {}

    void Initialize();

    void OnObjectCreate(GameObject* pGo);
    void OnCreatureCreate(Creature* pCreature);

    bool IsEncounterInProgress() const;
    bool IsRaidWiped();

    void DoOpenDoor(ObjectGuid guid);
    void DoCloseDoor(ObjectGuid guid);
    void DoOpenDoor(uint32 entry);
    void DoCloseDoor(uint32 entry);

    void SetData(uint32 uiType, uint32 uiData);
    uint32 GetData(uint32 uiType);

    const char* Save() { return strSaveData.c_str(); }
    void Load(const char* chrIn);
    void SetSpecialAchievementCriteria(uint32 uiType, bool bIsMet);
    bool CheckAchievementCriteriaMeet(uint32 criteria_id, Player const* /*source*/, Unit const* /*target*/, uint32 /*miscvalue1*/);

private:

    uint8 Difficulty;
    bool needSave;
    std::string strSaveData;
    bool m_abAchievCriteria[MAX_SPECIAL_ACHIEV_CRITS];

    //Creatures GUID
    uint32 m_auiEncounter[MAX_ENCOUNTERS+1];

    uint32 m_uiGunshipArmoryA_ID;
    uint32 m_uiGunshipArmoryH_ID;
    uint32 m_uiValithriaCache;
    uint32 m_uiSaurfangCache;
};

struct MANGOS_DLL_DECL base_icc_bossAI : public ScriptedAI
{
    base_icc_bossAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_icecrown_citadel*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        m_creature->SetRespawnTime(7*DAY);
        m_creature->SetLevitate(false);
        Reset();
    }

    instance_icecrown_citadel* m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIsHeroic;
    bool m_bIs25Man;

    uint32 m_uiCheckWipeTimer;

    void Reset()
    {
        m_uiCheckWipeTimer = 2000;
    }
    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiCheckWipeTimer < uiDiff)
        {
            if (m_pInstance->IsRaidWiped())
                m_creature->AI()->EnterEvadeMode();
        }
        else
            m_uiCheckWipeTimer -= uiDiff;
    }

    Unit* SelectRandomRangedTarget(Unit *pSource)
    {
        Unit *pResult = NULL;
        std::list<Unit*> lTargets;
        ThreatList const& tList = m_creature->getThreatManager().getThreatList();

        for (ThreatList::const_iterator i = tList.begin();i != tList.end(); ++i)
        {
            if (!(*i)->getUnitGuid().IsPlayer())
                continue;

            if (Unit* pTmp = m_creature->GetMap()->GetUnit((*i)->getUnitGuid()))
                lTargets.push_back(pTmp);
        }

        if (!lTargets.empty())
        {
            uint8 max = m_bIs25Man ? 8 : 3;
            std::list<Unit*>::iterator iter;

            lTargets.sort(ObjectDistanceOrderReversed(pSource));
            iter = lTargets.begin();

            if (max >= lTargets.size())
                max = lTargets.size() - 1;

            std::advance(iter, urand(0, max));
            pResult = (*iter);
        }

        return pResult;
    }
};

#endif

