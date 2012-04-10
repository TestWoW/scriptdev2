/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: boss_valithria
<<<<<<< HEAD
SD%Complete: 100%
SDComment: Completed by Walkum & Carlos93 (Correct timers of adds, worm summons)
=======
SD%Complete: 99%
SDComment:  by michalpolko with special thanks to:
            mangosR2 team and all who are supporting us with feedback, testing and fixes
            TrinityCore for some info about spells IDs
            everybody whom I forgot to mention here ;)

>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

static Locations SpawnLoc[]=
{
    {4203.470215f, 2484.500000f, 364.872009f},  // 0 Valithria
    {4240.688477f, 2405.794678f, 364.868591f},  // 1 Valithria Room 1
    {4239.579102f, 2566.753418f, 364.868439f},  // 2 Valithria Room 2
    {4166.216797f, 2564.197266f, 364.873047f},  // 3 Valithria Room 3
    {4165.112305f, 2405.872559f, 364.872925f},  // 4 Valithria Room 4
    {4228.589844f, 2469.110107f, 364.868988f},  // 5 Mob 1
    {4236.000000f, 2479.500000f, 364.869995f},  // 6 Mob 2
    {4235.410156f, 2489.300049f, 364.872009f},  // 7 Mob 3
    {4228.509766f, 2500.310059f, 364.876007f},  // 8 Mob 4
    {4236.767090f, 2484.514648f, 364.871216f},  // 9 LK
};

enum BossSpells
{
<<<<<<< HEAD
    SPELL_CHECK_ACHIEVEMENT         = 72706,
=======
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    SPELL_NIGHTMARE_PORTAL_PRE      = 71977,
    SPELL_NIGHTMARE_PORTAL          = 71987,
    SPELL_TWISTED_NIGHTMARES        = 71941,
    SPELL_TWISTED_NIGHTMARES_DOT    = 71940,
    SPELL_NIGHTMARE_CLOUD           = 71970, // Nightmare Clouds cast this on dreaming Valithria - she deals this dmg to Real Valithria
    SPELL_NIGHTMARE_CLOUD_VISUAL    = 71939,

    SPELL_DREAM_PORTAL_PRE          = 71301,
    SPELL_DREAM_PORTAL              = 71305,
    SPELL_EMERALD_VIGOR             = 70873,
    SPELL_DREAM_CLOUD_VISUAL        = 70876,

    SPELL_DREAM_STATE               = 70766,

    SPELL_DREAMWALKER_RAGE          = 71189,
    SPELL_IMMUNITY                  = 72724,
    SPELL_CORRUPTION                = 70904,
    SPELL_DREAM_SLIP                = 71196,
    SPELL_ICE_SPIKE                 = 70702,

    SPELL_CLEAR_DREAMS_NIGHTMARES   = 75863, // script effect removes Emerald Vigor and Nightmare auras

    // summons
    // these spells should be applied to dummy npcs in gates
    // they should apply these auras once the encounter has started
    // but how to apply this, which spell on which npc and when? ;/
    SPELL_SUMMON_TIMER_SUPPRESSER   = 70912,
    SPELL_SUMMON_TIMER_SKELETON     = 70913,
    SPELL_SUMMON_TIMER_ZOMBIE       = 70914,
    SPELL_SUMMON_TIMER_ABOMIN       = 70915,
    SPELL_SUMMON_TIMER_ARCHMAGE     = 70916,

    // Risen Archmage
    SPELL_FROSTBOLT_VOLLEY          = 70759,
    SPELL_MANA_VOID                 = 71179,
    SPELL_VOID_BUFF                 = 71085,
    SPELL_COLUMN_OF_FROST           = 70704,
    SPELL_COLUMN_OF_FROST_VISUAL    = 70715,
    SPELL_COLUMN_OF_FROST_TRIG      = 70702,

    // Blazing Skeleton
    SPELL_FIREBALL                  = 70754,
    SPELL_LAY_WASTE                 = 69325,

    // Suppresser
<<<<<<< HEAD
    SPELL_SUPPRESSION               = 70588,

    // Blistering Zombie
    SPELL_CORROSION                 = 70749,
    SPELL_ACID_BURST                = 70744, // 10 mode. 750ms cast time. seems like it is cast always before dying

    // Gluttonous Abomination
    SPELL_GUT_SPRAY                 = 70633,
    SPELL_ROT_WORM_SPAWNER          = 70675,
=======
    SPELL_SUPPRESSION               = 70588, // NOTE: must stack from many casters

    // Blistering Zombie
    SPELL_CORROSION                 = 70749,
    SPELL_ACID_BURST                = 70744, // 750ms cast time. seems like it is cast always before dying

    // Gluttonous Abomination
    SPELL_GUT_SPRAY                 = 71283,
    SPELL_ROT_WORM_SPAWNER          = 70675, // cast around 30% HP or something?
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    SPELL_ROT_WORM                  = 72962,

    NPC_RISEN_ARCHMAGE              = 37868,
    NPC_COLUMN_OF_FROST             = 37918,
    NPC_MANA_VOID                   = 38068,
    NPC_SUPPRESSER                  = 37863,
    NPC_BLAZING_SKELETON            = 36791,
    NPC_BLISTERING_ZOMBIE           = 37934,
    NPC_GLUTTONOUS_ABOMINATION      = 37886,
    NPC_ROT_WORM                    = 37907,

    SUMMON_TYPES_NUMBER             = 4,

    NPC_NIGHTMARE_PORTAL_PRE        = 38429,
    NPC_NIGHTMARE_PORTAL            = 38430,
    NPC_NIGHTMARE_CLOUD             = 38421,
    NPC_DREAM_PORTAL_PRE            = 38186,
    NPC_DREAM_PORTAL                = 37945,
    NPC_DREAM_CLOUD                 = 37985,
};

enum
{
<<<<<<< HEAD
    // Valithria
    SAY_AGGRO                   = -1631140,
    SAY_LICH_AGGRO              = -1631194,
=======
    SAY_AGGRO                   = -1631140,
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    SAY_PORTAL                  = -1631141,
    SAY_75_HEALTH               = -1631142,
    SAY_25_HEALTH               = -1631143,
    SAY_0_HEALTH                = -1631144,
<<<<<<< HEAD
    SAY_SLAY_1                  = -1631595,
    SAY_SLAY_2                  = -1631145,
=======
    SAY_PLAYER_DIES             = -1631145,
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    SAY_BERSERK                 = -1631146,
    SAY_VICTORY                 = -1631147,
};

static uint32 m_uiSummonedAddsEntries[SUMMON_TYPES_NUMBER] =
{
    NPC_GLUTTONOUS_ABOMINATION,
    NPC_RISEN_ARCHMAGE,
    NPC_BLISTERING_ZOMBIE,
    NPC_BLAZING_SKELETON
};

<<<<<<< HEAD
struct MANGOS_DLL_DECL boss_valithria_dreamwalkerAI : public base_icc_bossAI
{
    boss_valithria_dreamwalkerAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
=======
struct MANGOS_DLL_DECL boss_valithria_dreamwalkerAI : public ScriptedAI
{
    boss_valithria_dreamwalkerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);

>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
        SetCombatMovement(false);
        DoCastSpellIfCan(m_creature, SPELL_CORRUPTION, CAST_TRIGGERED);

        Reset();
    }

<<<<<<< HEAD
    bool m_bCombatStarted;
    bool m_bLichAggro;
=======
    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIsHeroic;
    bool m_bIs25Man;

    bool m_bCombatStarted;
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    bool m_bIsEnrage;
    bool m_bSaidOver25;
    bool m_bSaidOver75;
    bool m_bIsHealed;

    uint32 m_uiEnrageTimer;
    uint32 m_uiHealthCheckTimer;
    uint32 m_uiSummonPortalsTimer;
<<<<<<< HEAD
    uint32 m_uiLichAggroTimer;
    uint32 m_uiOutroTimer;

    uint32 m_uiSummonCounter;
    uint32 m_uiSummonIter;
    uint32 m_uiSummonAddTimer;
    uint32 m_uiSummonSuppresserTimer;

    std::list<ObjectGuid> mobsGUIDList;

    void Reset()
    {
        m_bCombatStarted        = false;
        m_bIsEnrage             = false;
        m_bSaidOver25           = false;
        m_bSaidOver75           = false;
        m_bIsHealed             = false;

        m_uiEnrageTimer         = 7 * MINUTE * IN_MILLISECONDS;
        m_uiHealthCheckTimer    = 30000; // no need to check in the beginning of the fight
        m_uiLichAggroTimer      = 10000;
        m_uiOutroTimer          = 4000;
        m_uiSummonPortalsTimer  = 30000;

        m_uiSummonCounter       = 0;
        m_uiSummonIter          = 9;
        m_uiSummonAddTimer      = 20000;
        m_uiSummonSuppresserTimer = 25000;

        m_creature->SetHealth(m_creature->GetMaxHealth() / 2.0f);
        DoCastSpellIfCan(m_creature, SPELL_CORRUPTION, CAST_TRIGGERED);

        DespawnMobs();
=======
    uint32 m_uiOutroTimer;

    uint32 m_uiSummonSuppresserTimer;
    uint32 m_uiSummonAbominationTimer;
    uint32 m_uiSummonZombieTimer;
    uint32 m_uiSummonSkeletonTimer;
    uint32 m_uiSummonArchmageTimer;

    uint32 m_uiSummonSuppresserCounter;
    uint32 m_uiSummonSkeletonCounter;

    void Reset()
    {
        m_bCombatStarted            = false;
        m_bIsEnrage                 = false;
        m_bSaidOver25               = false;
        m_bSaidOver75               = false;
        m_bIsHealed                 = false;

        m_uiEnrageTimer             = 7 * MINUTE * IN_MILLISECONDS;
        m_uiHealthCheckTimer        = 30000; // no need to check in the beginning of the fight
        m_uiOutroTimer              = 4000;
        m_uiSummonPortalsTimer      = 30000;

        m_uiSummonSuppresserTimer   = 60000;
        m_uiSummonAbominationTimer  = 30000;
        m_uiSummonZombieTimer       = 35000;
        m_uiSummonSkeletonTimer     = 45000;
        m_uiSummonArchmageTimer     = 40000;

        m_uiSummonSuppresserCounter = 0;
        m_uiSummonSkeletonCounter   = 0;

        m_creature->SetHealth(m_creature->GetMaxHealth() / 2.0f);
        DoCastSpellIfCan(m_creature, SPELL_CORRUPTION, CAST_TRIGGERED);
    }

    void JustReachedHome()
    {
        DoCastSpellIfCan(m_creature, SPELL_CORRUPTION, CAST_TRIGGERED);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VALITHRIA, FAIL);

        m_creature->SetHealth(m_creature->GetMaxHealth() / 2.0f);
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    }

    void JustReachedHome()
    {
<<<<<<< HEAD
        DoCastSpellIfCan(m_creature, SPELL_CORRUPTION, CAST_TRIGGERED);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VALITHRIA, FAIL);

        m_creature->SetHealth(m_creature->GetMaxHealth() / 2.0f);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (m_bCombatStarted)
            return;

        if (pWho->GetTypeId() == TYPEID_PLAYER && !((Player*)pWho)->isGameMaster() && m_creature->GetDistance(pWho) < 50.0f)
        {
            DoScriptText(SAY_AGGRO, m_creature);
            DoCastSpellIfCan(m_creature, SPELL_IMMUNITY, CAST_TRIGGERED);

            if (m_pInstance)
            {
                m_pInstance->SetData(TYPE_VALITHRIA, IN_PROGRESS);
                m_bLichAggro = true;

                m_creature->SummonCreature(NPC_LICH_TRIGGER, SpawnLoc[9].x, SpawnLoc[9].y, SpawnLoc[9].z, 0, TEMPSUMMON_TIMED_DESPAWN, 25000);

                if (Creature *pTmp = m_pInstance->GetSingleCreatureFromStorage(NPC_COMBAT_TRIGGER))
                {
                    pTmp->SetInCombatWithZone();
                    m_bCombatStarted = true;
                }
            }
=======
        if (m_bCombatStarted)
            return;

        if (pWho->GetTypeId() == TYPEID_PLAYER && !((Player*)pWho)->isGameMaster() &&
            m_creature->GetDistance(pWho) < 50.0f)
        {
            DoScriptText(SAY_AGGRO, m_creature);
            DoCastSpellIfCan(m_creature, SPELL_IMMUNITY, CAST_TRIGGERED);

            if (m_pInstance)
            {
                m_pInstance->SetData(TYPE_VALITHRIA, IN_PROGRESS);

                if (Creature *pTmp = m_pInstance->GetSingleCreatureFromStorage(NPC_COMBAT_TRIGGER))
                {
                    pTmp->SetInCombatWithZone();
                    m_bCombatStarted = true;
                }
            }
        }
    }

    void EnterEvadeMode()
    {
        m_bCombatStarted = false;
        ScriptedAI::EnterEvadeMode();
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            DoScriptText(SAY_PLAYER_DIES, m_creature, pVictim);
    }

    void JustDied(Unit *pKiller)
    {
        DoScriptText(SAY_0_HEALTH, m_creature);

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_VALITHRIA, FAIL);

            if (Creature *pTrigger = m_pInstance->GetSingleCreatureFromStorage(NPC_COMBAT_TRIGGER))
                pTrigger->AI()->EnterEvadeMode();
        }

        m_creature->SetRespawnDelay(60);
    }

    void DoSummonAdd(uint32 uiEntry)
    {
        uint32 loc = urand(1, 2 + (m_bIs25Man ? 2 : 0));
        m_creature->SummonCreature(uiEntry, SpawnLoc[loc].x, SpawnLoc[loc].y, SpawnLoc[loc].z, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);

        // some additional control of summoning adds (anti flood system)
        if (!m_bIsEnrage)
        {
            if (m_uiSummonAbominationTimer < 5000)
                m_uiSummonAbominationTimer += 5000;
            else if (m_uiSummonZombieTimer < 5000)
                m_uiSummonZombieTimer += 5000;

            if (m_uiSummonArchmageTimer < 5000)
                m_uiSummonArchmageTimer += 5000;
            else if (m_uiSummonSkeletonTimer < 5000)
                m_uiSummonSkeletonTimer += 5000;
        }
    }

    void JustSummoned(Creature *pCreature)
    {
        pCreature->SetInCombatWithZone();

        if (pCreature->GetEntry() == NPC_SUPPRESSER)
        {
            pCreature->AddThreat(m_creature, 100000);
            pCreature->GetMotionMaster()->MoveChase(m_creature);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_bCombatStarted)
            return;

        // Outro
        if (m_bIsHealed)
        {
            if (m_uiOutroTimer <= uiDiff)
            {
                if (m_pInstance)
                {
                    m_pInstance->SetData(TYPE_VALITHRIA, DONE);

                    if (Creature *pDummy = m_pInstance->GetSingleCreatureFromStorage(NPC_COMBAT_TRIGGER))
                        m_creature->DealDamage(pDummy, pDummy->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
                }

                m_uiOutroTimer = 30000;
                m_creature->ForcedDespawn(1000);
            }
            else
                m_uiOutroTimer -= uiDiff;

            return;
        }

        // Health Check
        if (m_uiHealthCheckTimer <= uiDiff)
        {
            float fHP = m_creature->GetHealthPercent();

            // when reached 75% health
            if (!m_bSaidOver75)
            {
                if (fHP > 75.0f)
                {
                    DoScriptText(SAY_75_HEALTH, m_creature);
                    m_bSaidOver75 = true;
                }
            }

            // when reached 25% health
            if (!m_bSaidOver25)
            {
                if (fHP < 25.0f)
                {
                    DoScriptText(SAY_25_HEALTH, m_creature);
                    m_bSaidOver25 = true;
                }
            }

            // check if encounter is completed
            if (fHP > 95.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_DREAMWALKER_RAGE) == CAST_OK)
                {
                    DoScriptText(SAY_VICTORY, m_creature);
                    m_creature->RemoveAllAuras();
                    m_bIsHealed = true;
                    return;
                }
            }

            m_uiHealthCheckTimer = 1000;
        }
        else
            m_uiHealthCheckTimer -= uiDiff;

        // Enrage
        // After 7 minutes summoning of Suppressers is much faster
        if (!m_bIsEnrage)
        {
            if (m_uiEnrageTimer <= uiDiff)
            {
                m_bIsEnrage = true;
            }
            else
                m_uiEnrageTimer -= uiDiff;
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
        }

        // Summon Portals
        if (m_uiSummonPortalsTimer <= uiDiff)
        {
            uint32 max = m_bIs25Man ? 12 : 6;

            // this way makes sure that spell is cast
            // this should be done via ScriptEffect spell, but we don't need it in SD2
            for (uint32 i = 0; i < max; ++i)
                m_creature->CastSpell(m_creature, m_bIsHeroic ? SPELL_NIGHTMARE_PORTAL_PRE : SPELL_DREAM_PORTAL_PRE, true);

            if (!m_bIsHeroic)
                DoScriptText(SAY_PORTAL, m_creature);

            m_uiSummonPortalsTimer = 45000;
        }
        else
            m_uiSummonPortalsTimer -= uiDiff;

        // Summon adds

        // Summon Suppresser
        if (m_uiSummonSuppresserTimer <= uiDiff)
        {
            uint32 uiReduction;

            for (uint32 i = 0; i < urand(1, m_bIs25Man ? 3 : 2) + m_uiSummonSuppresserCounter; ++i)
                DoSummonAdd(NPC_SUPPRESSER);

            // 5s faster each summoning
            uiReduction = m_uiSummonSuppresserCounter >= 10 ? 50000 : (m_uiSummonSuppresserCounter * 5000);
            m_uiSummonSuppresserTimer = 60000 - uiReduction; 
            ++m_uiSummonSuppresserCounter;
        }
        else
            m_uiSummonSuppresserTimer -= uiDiff;

        // Summon Blazing Skeleton
        if (m_uiSummonSkeletonTimer <= uiDiff)
        {
            uint32 uiReduction;

            DoSummonAdd(NPC_BLAZING_SKELETON);
            // 5s faster each summoning
            uiReduction = m_uiSummonSkeletonCounter >= 10 ? 50000 : (m_uiSummonSkeletonCounter * 5000);
            m_uiSummonSkeletonTimer = 60000 - uiReduction;
            ++m_uiSummonSkeletonCounter;
        }
        else
            m_uiSummonSkeletonTimer -= uiDiff;

        // Summon Abomination
        if (m_uiSummonAbominationTimer <= uiDiff)
        {
            DoSummonAdd(NPC_GLUTTONOUS_ABOMINATION);
            m_uiSummonAbominationTimer = urand(30000, 60000);
        }
        else
            m_uiSummonAbominationTimer -= uiDiff;

        // Summon Zombie
        if (m_uiSummonZombieTimer <= uiDiff)
        {
            DoSummonAdd(NPC_BLISTERING_ZOMBIE);
            m_uiSummonZombieTimer = urand(25000, 50000);
        }
        else
            m_uiSummonZombieTimer -= uiDiff;

        // Summon Archmage
        if (m_uiSummonArchmageTimer <= uiDiff)
        {
            DoSummonAdd(NPC_RISEN_ARCHMAGE);
            m_uiSummonArchmageTimer = urand(20000, 50000);
        }
        else
            m_uiSummonArchmageTimer -= uiDiff;
    }
};

<<<<<<< HEAD
    void EnterEvadeMode()
    {
        m_bCombatStarted = false;
        ScriptedAI::EnterEvadeMode();
    }

    void JustDied(Unit *pKiller)
    {
        DoScriptText(SAY_0_HEALTH, m_creature);

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_VALITHRIA, FAIL);

            if (Creature *pTrigger = m_pInstance->GetSingleCreatureFromStorage(NPC_COMBAT_TRIGGER))
                pTrigger->AI()->EnterEvadeMode();
        }

        m_creature->SetRespawnDelay(60);
    }

    void DoSummonAdd()
    {
        uint32 loc = urand(1, 2 + (m_bIs25Man ? 2 : 0));
        uint32 uiEntry = m_uiSummonedAddsEntries[m_uiSummonIter];
        m_uiSummonIter = (m_uiSummonIter + 1) % SUMMON_TYPES_NUMBER;

        m_creature->SummonCreature(uiEntry, SpawnLoc[loc].x, SpawnLoc[loc].y, SpawnLoc[loc].z, 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
    }

    void CheckAchiev(Unit *pCreature)
    {
        Map* pMap = m_creature->GetMap();
        Map::PlayerList const& pPlayers = pMap->GetPlayers();
        if (!pPlayers.isEmpty())
        {
            for (Map::PlayerList::const_iterator itr = pPlayers.begin(); itr != pPlayers.end(); ++itr)
            {
                Unit *pTarget = itr->getSource();
                if (pTarget)
                    pCreature->CastSpell(pTarget, SPELL_CHECK_ACHIEVEMENT, true);
            }
        }
    }

    void JustSummoned(Creature *pCreature)
    {
        if (!m_pInstance || !pCreature)
            return;

        ++m_uiSummonCounter;
        pCreature->SetInCombatWithZone();

        if (pCreature->GetEntry() == NPC_SUPPRESSER)
        {
            pCreature->AddThreat(m_creature, 100000);
            pCreature->GetMotionMaster()->MoveChase(m_creature);
        }

        mobsGUIDList.push_back(pCreature->GetObjectGuid());
=======
CreatureAI* GetAI_boss_valithria_dreamwalker(Creature* pCreature)
{
    return new boss_valithria_dreamwalkerAI(pCreature);
};

struct MANGOS_DLL_DECL mob_valithria_dream_phaseAI : public ScriptedAI
{
    mob_valithria_dream_phaseAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_creature->HandleEmoteState(EMOTE_STATE_FLYGRABCLOSED);
    }
    void Reset(){}
    void UpdateAI(const uint32 uiDiff){}
    void AttackStart(Unit *pWho){}
    void DamageTaken(Unit *pDealer, uint32 &uiDamage)
    {
        if (ScriptedInstance *pInstance = (ScriptedInstance*)m_creature->GetInstanceData())
        {
            if (Creature *pValithria = pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
            {
                if (pValithria->isAlive())
                {
                    if (boss_valithria_dreamwalkerAI *pValAI = dynamic_cast<boss_valithria_dreamwalkerAI*>(pValithria->AI()))
                    {
                        if (pValAI->m_bCombatStarted)
                            pValithria->DealDamage(pValithria, uiDamage, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
                    }
                }
            }
        }

        uiDamage = 0;
    }
};

CreatureAI* GetAI_mob_valithria_dream_phase(Creature* pCreature)
{
    return new mob_valithria_dream_phaseAI(pCreature);
};

struct MANGOS_DLL_DECL mob_valithria_combat_triggerAI : public ScriptedAI
{
    mob_valithria_combat_triggerAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 m_uiCheckTimer;

    void Reset()
    {
        m_uiCheckTimer = 2000;
    }

    void AttackStart(Unit *pWho){}

    void EnterEvadeMode()
    {
        if (m_pInstance)
        {
            if (Creature *pVal = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
                pVal->AI()->EnterEvadeMode();
        }

        ScriptedAI::EnterEvadeMode();
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (m_uiCheckTimer <= uiDiff)
        {
<<<<<<< HEAD
            if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
            {
                if (pTemp->isAlive())
                {
                    pTemp->DeleteThreatList();
                    pTemp->CombatStop(true);
                    pTemp->ForcedDespawn();
                }
            }
=======
            if (Creature *pValithria = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
            {
                if (boss_valithria_dreamwalkerAI *pValAI = dynamic_cast<boss_valithria_dreamwalkerAI*>(pValithria->AI()))
                {
                    if (pValAI->m_bCombatStarted && !m_creature->SelectHostileTarget())
                        EnterEvadeMode();
                }
            }
            else
                EnterEvadeMode();

            m_uiCheckTimer = 2000;
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
        }
        else
            m_uiCheckTimer -= uiDiff;
    }
};

<<<<<<< HEAD
    uint32 GetNextSummonTimer()
    {
        // max timer 20 - 25 sec
        // min timer 15 - 20 sec
        uint32 min = 5000;
        uint32 max = 10000;

        if (m_uiSummonCounter > 10)
        {
            min = 4000;
            max = 9000;
        }
        if (m_uiSummonCounter > 20)
        {
            min = 3000;
            max = 8000;
        }
        if (m_uiSummonCounter > 30)
        {
            min = 2000;
            max = 7000;
        }
        if (m_uiSummonCounter > 40)
        {
            min = 1000;
            max = 6000;
        }
        if (m_uiSummonCounter > 50) // almost 7 minutes - considered as enrage
        {
            min = 0;
            max = 5000;
        }

        return m_bIsEnrage ? 3000 : 15000 + urand(min, max);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_bCombatStarted)
            return;

        // Lich Aggro
        if (m_bLichAggro)
        {
            if (m_uiLichAggroTimer <= uiDiff)
            {
                if (Creature *pLich = m_pInstance->GetSingleCreatureFromStorage(NPC_LICH_TRIGGER))
                {
                    DoScriptText(SAY_LICH_AGGRO, pLich);
                    m_bLichAggro = false;
                }
            }
            else
                m_uiLichAggroTimer -= uiDiff;
        }

        // Outro
        if (m_bIsHealed)
        {
            if (m_uiOutroTimer <= uiDiff)
            {
                if (m_pInstance)
                {
                    if (Creature *pDummy = m_pInstance->GetSingleCreatureFromStorage(NPC_COMBAT_TRIGGER))
                    {
                        CheckAchiev(pDummy);
                        m_creature->DealDamage(pDummy, pDummy->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
                    }

                    m_pInstance->SetData(TYPE_VALITHRIA, DONE);
                }
                m_uiOutroTimer = 30000;
                m_creature->ForcedDespawn(10000);
            }
            else
                m_uiOutroTimer -= uiDiff;

            return;
        }

        // Health Check
        if (m_uiHealthCheckTimer <= uiDiff)
        {
            float fHP = m_creature->GetHealthPercent();

            // when reached 75% health
            if (!m_bSaidOver75)
            {
                if (fHP > 75.0f)
                {
                    DoScriptText(SAY_75_HEALTH, m_creature);
                    m_bSaidOver75 = true;
                }
            }

            // when reached 25% health
            if (!m_bSaidOver25)
            {
                if (fHP < 25.0f)
                {
                    DoScriptText(SAY_25_HEALTH, m_creature);
                    m_bSaidOver25 = true;
                }
            }

            // check if encounter is completed
            if (fHP >= 100.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_DREAMWALKER_RAGE) == CAST_OK)
                {
                    DoScriptText(SAY_VICTORY, m_creature);
                    m_creature->RemoveAllAuras();
                    m_bIsHealed = true;
                    return;
                }
            }

            m_uiHealthCheckTimer = 1000;
        }
        else
            m_uiHealthCheckTimer -= uiDiff;

        // Enrage
        // After 7 minutes summoning of Suppressers is much faster
        if (!m_bIsEnrage)
        {
            if (m_uiEnrageTimer <= uiDiff)
            {
                m_bIsEnrage = true;
            }
            else
                m_uiEnrageTimer -= uiDiff;
        }

        // Summon Portals
        if (m_uiSummonPortalsTimer <= uiDiff)
        {
            uint32 max = m_bIs25Man ? 12 : 6;

            // this way makes sure that spell is cast
            // this should be done via ScriptEffect spell, but we don't need it in SD2
            for (uint32 i = 0; i < max; ++i)
                m_creature->CastSpell(m_creature, m_bIsHeroic ? SPELL_NIGHTMARE_PORTAL_PRE : SPELL_DREAM_PORTAL_PRE, true);

            if (!m_bIsHeroic)
                DoScriptText(SAY_PORTAL, m_creature);

            m_uiSummonPortalsTimer = 45000;
        }
        else
            m_uiSummonPortalsTimer -= uiDiff;

        // Summon Adds
        if (m_uiSummonAddTimer <= uiDiff)
        {
            DoSummonAdd();
            m_uiSummonAddTimer = GetNextSummonTimer();
        }
        else
            m_uiSummonAddTimer -= uiDiff;

        // Summon Suppresser
        if (m_uiSummonSuppresserTimer <= uiDiff)
        {
            uint32 max = 1;
            if (roll_chance_i(30))
                ++max;
            if (m_bIsEnrage)
                ++max;

            for (uint32 i = 0; i < max; ++i)
            {
                uint32 loc = urand(1, 2 + (m_bIs25Man ? 2 : 0));
                m_creature->SummonCreature(NPC_SUPPRESSER, SpawnLoc[loc].x, SpawnLoc[loc].y, SpawnLoc[loc].z, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);

                if (m_bIsEnrage)
                {
                    loc = urand(1, 2 + (m_bIs25Man ? 2 : 0));
                    m_creature->SummonCreature(NPC_BLAZING_SKELETON, SpawnLoc[loc].x, SpawnLoc[loc].y, SpawnLoc[loc].z, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
                }
            }

            m_uiSummonSuppresserTimer = m_bIsEnrage ? urand(10000, 15000) : urand(25000, 30000);
        }
        else
            m_uiSummonSuppresserTimer -= uiDiff;
    }
};

CreatureAI* GetAI_boss_valithria_dreamwalker(Creature* pCreature)
{
    return new boss_valithria_dreamwalkerAI(pCreature);
};

struct MANGOS_DLL_DECL mob_valithria_dream_phaseAI : public ScriptedAI
{
    mob_valithria_dream_phaseAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_creature->HandleEmoteState(EMOTE_STATE_FLYGRABCLOSED);
    }
    void Reset(){}
    void UpdateAI(const uint32 uiDiff){}
    void AttackStart(Unit *pWho){}
    void DamageTaken(Unit *pDealer, uint32 &uiDamage)
    {
        if (ScriptedInstance *pInstance = (ScriptedInstance*)m_creature->GetInstanceData())
        {
            if (Creature *pValithria = pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
            {
                if (pValithria->isAlive())
                {
                    if (boss_valithria_dreamwalkerAI *pValAI = dynamic_cast<boss_valithria_dreamwalkerAI*>(pValithria->AI()))
                    {
                        if (pValAI->m_bCombatStarted)
                            pValithria->DealDamage(pValithria, uiDamage, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
                    }
                }
            }
        }

        uiDamage = 0;
    }
};

CreatureAI* GetAI_mob_valithria_dream_phase(Creature* pCreature)
{
    return new mob_valithria_dream_phaseAI(pCreature);
};

struct MANGOS_DLL_DECL mob_valithria_combat_triggerAI : public ScriptedAI
{
    mob_valithria_combat_triggerAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 m_uiCheckTimer;

    void Reset()
    {
        m_uiCheckTimer = 2000;
    }

    void AttackStart(Unit *pWho){}

    void EnterEvadeMode()
    {
        if (m_pInstance)
        {
            if (Creature *pVal = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
                pVal->AI()->EnterEvadeMode();
        }

        ScriptedAI::EnterEvadeMode();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (m_uiCheckTimer <= uiDiff)
        {
            if (Creature *pValithria = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
            {
                if (boss_valithria_dreamwalkerAI *pValAI = dynamic_cast<boss_valithria_dreamwalkerAI*>(pValithria->AI()))
                {
                    if (pValAI->m_bCombatStarted && !m_creature->SelectHostileTarget())
                        EnterEvadeMode();
                }
            }
            else
                EnterEvadeMode();

            m_uiCheckTimer = 2000;
        }
        else
            m_uiCheckTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_valithria_combat_trigger(Creature *pCreature)
{
    return new mob_valithria_combat_triggerAI(pCreature);
};

// Gluttonous Abomination
struct MANGOS_DLL_DECL mob_gluttonous_abominationAI : public ScriptedAI
{
    mob_gluttonous_abominationAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
    }

    uint32 m_uiGutSprayTimer;
    ScriptedInstance *m_pInstance;

    void Reset()
    {
        m_uiGutSprayTimer = urand(3000, 5000);
    }

    void KilledUnit(Unit *pVictim)
    {
        if (Creature *pValithria = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
        {
            switch(urand(0,1))
            {
            case 0: DoScriptText(SAY_SLAY_1 ,pValithria, pVictim); break;
            case 1: DoScriptText(SAY_SLAY_2 ,pValithria, pVictim); break;
            default: break;
            }
        }
    }

    void JustDied(Unit *pVictim)
    {
        m_creature->CastSpell(m_creature, SPELL_ROT_WORM_SPAWNER, false);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        // Gut Spray
        if (m_uiGutSprayTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_GUT_SPRAY) == CAST_OK)
                m_uiGutSprayTimer = urand(5000, 10000);
        }
        else
            m_uiGutSprayTimer -= uiDiff;
=======
CreatureAI* GetAI_mob_valithria_combat_trigger(Creature *pCreature)
{
    return new mob_valithria_combat_triggerAI(pCreature);
};

// Gluttonous Abomination
struct MANGOS_DLL_DECL mob_gluttonous_abominationAI : public ScriptedAI
{
    mob_gluttonous_abominationAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiGutSprayTimer;

    void Reset()
    {
        m_uiGutSprayTimer = urand(3000, 5000);
    }

    void JustDied(Unit *pKiller)
    {
        DoCastSpellIfCan(m_creature, SPELL_ROT_WORM_SPAWNER, CAST_TRIGGERED);
    }

    void JustSummoned(Creature *pCreature)
    {
        pCreature->SetInCombatWithZone();
        pCreature->CastSpell(pCreature, SPELL_ROT_WORM, true);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Gut Spray
        if (m_uiGutSprayTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_GUT_SPRAY) == CAST_OK)
                m_uiGutSprayTimer = urand(5000, 10000);
        }
        else
            m_uiGutSprayTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_gluttonous_abomination(Creature *pCreature)
{
    return new mob_gluttonous_abominationAI(pCreature);
};

// Blistering Zombie
struct MANGOS_DLL_DECL mob_blistering_zombieAI : public ScriptedAI
{
    mob_blistering_zombieAI(Creature *pCreature) : ScriptedAI(pCreature){}

    bool m_bHasDied;

    void Reset()
    {
        m_bHasDied = false;
    }

    void Aggro(Unit *pWho)
    {
        DoCastSpellIfCan(m_creature, SPELL_CORROSION, CAST_TRIGGERED);
    }

    void DamageTaken(Unit *pDealer, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            uiDamage = 0;
            SetCombatMovement(false);
            if (!m_bHasDied)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_ACID_BURST) == CAST_OK)
                {
                    m_bHasDied = true;
                    m_creature->ForcedDespawn(2000);
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bHasDied)
            return;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_blistering_zombie(Creature *pCreature)
{
    return new mob_blistering_zombieAI(pCreature);
};

// Risen Archmage
struct MANGOS_DLL_DECL mob_risen_archmageAI : public ScriptedAI
{
    mob_risen_archmageAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiFrostboltVolleyTimer;
    uint32 m_uiColumnOfFrostTimer;
    uint32 m_uiManaVoidTimer;

    void Reset()
    {
        m_uiFrostboltVolleyTimer = urand(3000, 5000);
        m_uiColumnOfFrostTimer = urand(3000, 5000);
        m_uiManaVoidTimer = urand(5000, 10000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Frostbolt Volley
        if (m_uiFrostboltVolleyTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_FROSTBOLT_VOLLEY) == CAST_OK)
                m_uiFrostboltVolleyTimer = urand(5000, 15000);
        }
        else
            m_uiFrostboltVolleyTimer -= uiDiff;

        // Column of Frost
        if (m_uiColumnOfFrostTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_COLUMN_OF_FROST) == CAST_OK)
                    m_uiColumnOfFrostTimer = urand(10000, 15000);
            }
        }
        else
            m_uiColumnOfFrostTimer -= uiDiff;

        // Mana Void
        if (m_uiManaVoidTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_MANA_VOID) == CAST_OK)
                    m_uiManaVoidTimer = urand(10000, 15000);
            }
        }
        else
            m_uiManaVoidTimer -= uiDiff;
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5

        DoMeleeAttackIfReady();
    }
};

<<<<<<< HEAD
CreatureAI* GetAI_mob_gluttonous_abomination(Creature *pCreature)
{
    return new mob_gluttonous_abominationAI(pCreature);
};

// Blistering Zombie
struct MANGOS_DLL_DECL mob_blistering_zombieAI : public ScriptedAI
{
    mob_blistering_zombieAI(Creature *pCreature) : ScriptedAI(pCreature)
=======
CreatureAI* GetAI_mob_risen_archmage(Creature *pCreature)
{
    return new mob_risen_archmageAI(pCreature);
};

// Blazing Skeleton
struct MANGOS_DLL_DECL mob_blazing_skeletonAI : public ScriptedAI
{
    mob_blazing_skeletonAI(Creature *pCreature) : ScriptedAI(pCreature)
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    {
        Reset();
    }

<<<<<<< HEAD
    ScriptedInstance *m_pInstance;

    void Reset(){}

    void Aggro(Unit *pWho)
    {
        DoCastSpellIfCan(m_creature, SPELL_CORROSION, CAST_TRIGGERED);
    }

    void KilledUnit(Unit *pVictim)
    {
        if (Creature *pValithria = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
        {
            switch(urand(0,1))
            {
            case 0: DoScriptText(SAY_SLAY_1 ,pValithria, pVictim); break;
            case 1: DoScriptText(SAY_SLAY_2 ,pValithria, pVictim); break;
            default: break;
            }
        }
    }
    void DamageTaken(Unit *pDealer, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            uiDamage = 0;
            SetCombatMovement(false);
            if (DoCastSpellIfCan(m_creature, SPELL_ACID_BURST) == CAST_OK)
                m_creature->ForcedDespawn(1000);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_blistering_zombie(Creature *pCreature)
{
    return new mob_blistering_zombieAI(pCreature);
};

// Risen Archmage
struct MANGOS_DLL_DECL mob_risen_archmageAI : public ScriptedAI
{
    mob_risen_archmageAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    uint32 m_uiFrostboltVolleyTimer;
    uint32 m_uiColumnOfFrostTimer;
    uint32 m_uiManaVoidTimer;

    ScriptedInstance *m_pInstance;

    void Reset()
    {
        m_uiFrostboltVolleyTimer = urand(3000, 5000);
        m_uiColumnOfFrostTimer = urand(3000, 5000);
        m_uiManaVoidTimer = urand(5000, 10000);
    }

    void KilledUnit(Unit *pVictim)
    {
        if (Creature *pValithria = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
        {
            switch(urand(0,1))
            {
            case 0: DoScriptText(SAY_SLAY_1 ,pValithria, pVictim); break;
            case 1: DoScriptText(SAY_SLAY_2 ,pValithria, pVictim); break;
            default: break;
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        // Frostbolt Volley
        if (m_uiFrostboltVolleyTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_FROSTBOLT_VOLLEY) == CAST_OK)
                m_uiFrostboltVolleyTimer = urand(5000, 15000);
        }
        else
            m_uiFrostboltVolleyTimer -= uiDiff;

        // Column of Frost
        if (m_uiColumnOfFrostTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_COLUMN_OF_FROST) == CAST_OK)
                    m_uiColumnOfFrostTimer = urand(10000, 15000);
            }
        }
        else
            m_uiColumnOfFrostTimer -= uiDiff;

        // Mana Void
        if (m_uiManaVoidTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_MANA_VOID) == CAST_OK)
                    m_uiManaVoidTimer = urand(10000, 15000);
            }
        }
        else
            m_uiManaVoidTimer -= uiDiff;
=======
    uint32 m_uiFireballTimer;
    uint32 m_uiLayWasteTimer;

    void Reset()
    {
        m_uiFireballTimer = urand(3000, 5000);
        m_uiLayWasteTimer = urand(15000, 30000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Fireball
        if (m_uiFireballTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_FIREBALL) == CAST_OK)
                    m_uiFireballTimer = urand(3000, 5000);
            }
        }
        else
            m_uiFireballTimer -= uiDiff;

        // Lay Waste
        if (m_uiLayWasteTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_LAY_WASTE) == CAST_OK)
                m_uiLayWasteTimer = urand(20000, 25000);
        }
        else
            m_uiLayWasteTimer -= uiDiff;
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5

        DoMeleeAttackIfReady();
    }
};

<<<<<<< HEAD
CreatureAI* GetAI_mob_risen_archmage(Creature *pCreature)
{
    return new mob_risen_archmageAI(pCreature);
};

// Blazing Skeleton
struct MANGOS_DLL_DECL mob_blazing_skeletonAI : public ScriptedAI
{
    mob_blazing_skeletonAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    uint32 m_uiFireballTimer;
    uint32 m_uiLayWasteTimer;

    ScriptedInstance *m_pInstance;

    void Reset()
    {
        m_uiFireballTimer = urand(3000, 5000);
        m_uiLayWasteTimer = urand(5000, 15000);
    }

    void KilledUnit(Unit *pVictim)
    {
        if (Creature *pValithria = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
        {
            switch(urand(0,1))
            {
            case 0: DoScriptText(SAY_SLAY_1 ,pValithria, pVictim); break;
            case 1: DoScriptText(SAY_SLAY_2 ,pValithria, pVictim); break;
            default: break;
            }
=======
CreatureAI* GetAI_mob_blazing_skeleton(Creature *pCreature)
{
    return new mob_blazing_skeletonAI(pCreature);
};

// Suppresser
struct MANGOS_DLL_DECL mob_suppresserAI : public ScriptedAI
{
    mob_suppresserAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
    }

    ScriptedInstance *m_pInstance;

    void Reset(){}

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_pInstance)
        {
            if (m_pInstance->GetData(TYPE_VALITHRIA) == FAIL)
            {
                m_creature->ForcedDespawn();
                return;
            }
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->CanReachWithMeleeAttack(m_creature->getVictim()))
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SUPPRESSION);
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
        }
    }
};

<<<<<<< HEAD
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        // Fireball
        if (m_uiFireballTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_FIREBALL) == CAST_OK)
                    m_uiFireballTimer = urand(3000, 5000);
            }
        }
        else
            m_uiFireballTimer -= uiDiff;

        // Lay Waste
        if (m_uiLayWasteTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_LAY_WASTE) == CAST_OK)
                m_uiLayWasteTimer = urand(10000, 15000);
        }
        else
            m_uiLayWasteTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_blazing_skeleton(Creature *pCreature)
{
    return new mob_blazing_skeletonAI(pCreature);
};

// Suppresser
struct MANGOS_DLL_DECL mob_suppresserAI : public ScriptedAI
{
    mob_suppresserAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
        m_bIsCasting = false;
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
    }

    bool m_bIsCasting;

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;

    void Reset()
    {
    }

    void JustDied(Unit *pKiller)
    {
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (!m_bIsCasting)
        {
            if (m_creature->CanReachWithMeleeAttack(m_creature->getVictim()))
            {
                if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_SUPPRESSION) == CAST_OK)
                    m_bIsCasting = true;
            }
        }
    }
};

CreatureAI* GetAI_mob_suppresser(Creature *pCreature)
{
    return new mob_suppresserAI(pCreature);
};

struct MANGOS_DLL_DECL mob_dream_portal_preAI : public ScriptedAI
{
    mob_dream_portal_preAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_uiSummonTimer = 10000;
    }

    uint32 m_uiSummonTimer;

    void Reset(){}
    void AttackStart(Unit *pWho){}
    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiSummonTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_DREAM_PORTAL, CAST_TRIGGERED) == CAST_OK)
            {
                m_uiSummonTimer = 1000;
                m_creature->ForcedDespawn(500);
            }
        }
        else
            m_uiSummonTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_dream_portal_pre(Creature *pCreature)
{
    return new mob_dream_portal_preAI(pCreature);
};

bool GossipHello_mob_dream_portal(Player* pPlayer, Creature* pCreature)
{
    pPlayer->CastSpell(pPlayer, SPELL_DREAM_STATE, true);
    pCreature->ForcedDespawn();
    return true;
}

struct MANGOS_DLL_DECL mob_dream_cloudAI : public ScriptedAI
{
    mob_dream_cloudAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
=======
CreatureAI* GetAI_mob_suppresser(Creature *pCreature)
{
    return new mob_suppresserAI(pCreature);
};

struct MANGOS_DLL_DECL mob_dream_portal_preAI : public ScriptedAI
{
    mob_dream_portal_preAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_uiSummonTimer = 10000;
    }

    uint32 m_uiSummonTimer;

    void Reset(){}
    void AttackStart(Unit *pWho){}
    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiSummonTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_DREAM_PORTAL, CAST_TRIGGERED) == CAST_OK)
            {
                m_uiSummonTimer = 1000;
                m_creature->ForcedDespawn(500);
            }
        }
        else
            m_uiSummonTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_dream_portal_pre(Creature *pCreature)
{
    return new mob_dream_portal_preAI(pCreature);
};

bool GossipHello_mob_dream_portal(Player* pPlayer, Creature* pCreature)
{
    pPlayer->CastSpell(pPlayer, SPELL_DREAM_STATE, true);
    pCreature->ForcedDespawn();
    return true;
}

struct MANGOS_DLL_DECL mob_dream_cloudAI : public ScriptedAI
{
    mob_dream_cloudAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
        m_creature->SetRespawnDelay(15);
        Reset();
    }

    bool m_bHasCast;
    uint32 m_uiTimeToReset;

    void Reset()
    {
        m_bHasCast = false;
        DoCastSpellIfCan(m_creature, SPELL_DREAM_CLOUD_VISUAL, CAST_TRIGGERED);
    }

    void AttackStart(Unit *pWho){}

    void MoveInLineOfSight(Unit *pWho)
<<<<<<< HEAD
    {
        if (m_bHasCast)
            return;

        if (pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if (m_creature->GetDistance(pWho) < 5.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_EMERALD_VIGOR) == CAST_OK)
                {
                    m_bHasCast = true;
                    m_uiTimeToReset = 30000; // simulating respawn
                    m_creature->RemoveAllAuras();
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bHasCast)
        {
            if (m_uiTimeToReset <= uiDiff)
            {
                Reset();
            }
            else
                m_uiTimeToReset -= uiDiff;
=======
    {
        if (m_bHasCast)
            return;

        if (pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if (m_creature->GetDistance(pWho) < 5.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_EMERALD_VIGOR) == CAST_OK)
                {
                    m_bHasCast = true;
                    m_uiTimeToReset = 30000; // simulating respawn
                    m_creature->RemoveAllAuras();
                }
            }
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
        }
    }
};

CreatureAI* GetAI_mob_dream_cloud(Creature *pCreature)
{
    return new mob_dream_cloudAI(pCreature);
};

<<<<<<< HEAD
struct MANGOS_DLL_DECL mob_nightmare_portal_preAI : public ScriptedAI
{
    mob_nightmare_portal_preAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_uiSummonTimer = 15000;
=======
    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bHasCast)
        {
            if (m_uiTimeToReset <= uiDiff)
            {
                Reset();
            }
            else
                m_uiTimeToReset -= uiDiff;
        }
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    }
};

CreatureAI* GetAI_mob_dream_cloud(Creature *pCreature)
{
    return new mob_dream_cloudAI(pCreature);
};

<<<<<<< HEAD
=======
struct MANGOS_DLL_DECL mob_nightmare_portal_preAI : public ScriptedAI
{
    mob_nightmare_portal_preAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_uiSummonTimer = 15000;
    }

>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    uint32 m_uiSummonTimer;

    void Reset(){}
    void AttackStart(Unit *pWho){}
    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiSummonTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_NIGHTMARE_PORTAL, CAST_TRIGGERED) == CAST_OK)
            {
                m_uiSummonTimer = 1000;
                m_creature->ForcedDespawn(500);
            }
        }
        else
            m_uiSummonTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_nightmare_portal_pre(Creature *pCreature)
{
    return new mob_nightmare_portal_preAI(pCreature);
};

bool GossipHello_mob_nightmare_portal(Player* pPlayer, Creature* pCreature)
{
    pPlayer->CastSpell(pPlayer, SPELL_DREAM_STATE, true);
    pCreature->ForcedDespawn();
    return true;
}

struct MANGOS_DLL_DECL mob_nightmare_cloudAI : public ScriptedAI
{
    mob_nightmare_cloudAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }
<<<<<<< HEAD

    bool m_bHasCast;
    uint32 m_uiTimeToReset;

    void Reset()
    {
        m_bHasCast = false;
        DoCastSpellIfCan(m_creature, SPELL_NIGHTMARE_CLOUD_VISUAL, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_NIGHTMARE_CLOUD, CAST_TRIGGERED);
    }

    void AttackStart(Unit *pWho){}

    void MoveInLineOfSight(Unit *pWho)
    {
        if (m_bHasCast)
            return;

        if (pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if (m_creature->GetDistance(pWho) < 5.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_TWISTED_NIGHTMARES) == CAST_OK)
                {
                    m_bHasCast = true;
                    m_uiTimeToReset = 30000; // simulating respawn
                    m_creature->RemoveAllAuras();
                }
            }
        }
    }

=======

    bool m_bHasCast;
    uint32 m_uiTimeToReset;

    void Reset()
    {
        m_bHasCast = false;
        DoCastSpellIfCan(m_creature, SPELL_NIGHTMARE_CLOUD_VISUAL, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_NIGHTMARE_CLOUD, CAST_TRIGGERED);
    }

    void AttackStart(Unit *pWho){}

    void MoveInLineOfSight(Unit *pWho)
    {
        if (m_bHasCast)
            return;

        if (pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if (m_creature->GetDistance(pWho) < 5.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_TWISTED_NIGHTMARES) == CAST_OK)
                {
                    m_bHasCast = true;
                    m_uiTimeToReset = 30000; // simulating respawn
                    m_creature->RemoveAllAuras();
                }
            }
        }
    }

>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bHasCast)
        {
            if (m_uiTimeToReset <= uiDiff)
            {
                Reset();
            }
            else
                m_uiTimeToReset -= uiDiff;
        }
    }
};

CreatureAI* GetAI_mob_nightmare_cloud(Creature *pCreature)
{
    return new mob_nightmare_cloudAI(pCreature);
};

struct MANGOS_DLL_DECL mob_mana_voidAI : public ScriptedAI
{
    mob_mana_voidAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        DoCastSpellIfCan(m_creature, SPELL_VOID_BUFF, CAST_TRIGGERED);
        m_creature->ForcedDespawn(30000);
    }
    void Reset(){}
    void AttackStart(Unit *pWho){}
    void UpdateAI(const uint32 uiDiff){}
};

CreatureAI* GetAI_mob_mana_void(Creature *pCreature)
{
    return new mob_mana_voidAI(pCreature);
};

struct MANGOS_DLL_DECL mob_column_of_frostAI : public ScriptedAI
{
    mob_column_of_frostAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_uiColumnOfFrostTimer = 3000;
        DoCastSpellIfCan(m_creature, SPELL_COLUMN_OF_FROST_VISUAL, CAST_TRIGGERED);
    }

    uint32 m_uiColumnOfFrostTimer;

    void Reset(){}
    void AttackStart(Unit *pWho){}
    void UpdateAI(const uint32 uiDiff)
    {
        // Column of Frost
        if (m_uiColumnOfFrostTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_COLUMN_OF_FROST_TRIG) == CAST_OK)
            {
                m_uiColumnOfFrostTimer = 2000;
                m_creature->ForcedDespawn(1000);
            }
        }
        else
            m_uiColumnOfFrostTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_column_of_frost(Creature *pCreature)
{
    return new mob_column_of_frostAI(pCreature);
};

void AddSC_boss_valithria_dreamwalker()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_valithria_dreamwalker";
    pNewScript->GetAI = &GetAI_boss_valithria_dreamwalker;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_valithria_dream_phase";
    pNewScript->GetAI = &GetAI_mob_valithria_dream_phase;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_valithria_combat_trigger";
    pNewScript->GetAI = &GetAI_mob_valithria_combat_trigger;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_gluttonous_abomination";
    pNewScript->GetAI = &GetAI_mob_gluttonous_abomination;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_blistering_zombie";
    pNewScript->GetAI = &GetAI_mob_blistering_zombie;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_risen_archmage";
    pNewScript->GetAI = &GetAI_mob_risen_archmage;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_blazing_skeleton";
    pNewScript->GetAI = &GetAI_mob_blazing_skeleton;
    pNewScript->RegisterSelf();

<<<<<<< HEAD
    pNewScript = new Script;
    pNewScript->Name = "mob_suppresser";
    pNewScript->GetAI = &GetAI_mob_suppresser;
    pNewScript->RegisterSelf();
=======
    newscript = new Script;
    newscript->Name = "mob_valithria_dream_phase";
    newscript->GetAI = &GetAI_mob_valithria_dream_phase;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_valithria_combat_trigger";
    newscript->GetAI = &GetAI_mob_valithria_combat_trigger;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_gluttonous_abomination";
    newscript->GetAI = &GetAI_mob_gluttonous_abomination;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_blistering_zombie";
    newscript->GetAI = &GetAI_mob_blistering_zombie;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_risen_archmage";
    newscript->GetAI = &GetAI_mob_risen_archmage;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_blazing_skeleton";
    newscript->GetAI = &GetAI_mob_blazing_skeleton;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_suppresser";
    newscript->GetAI = &GetAI_mob_suppresser;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_nightmare_portal_pre";
    newscript->GetAI = &GetAI_mob_nightmare_portal_pre;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_nightmare_portal";
    newscript->pGossipHello = &GossipHello_mob_nightmare_portal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_nightmare_cloud";
    newscript->GetAI = &GetAI_mob_nightmare_cloud;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_dream_portal_pre";
    newscript->GetAI = &GetAI_mob_dream_portal_pre;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_dream_portal";
    newscript->pGossipHello = &GossipHello_mob_dream_portal;

    newscript->RegisterSelf();
    newscript = new Script;
    newscript->Name = "mob_dream_cloud";
    newscript->GetAI = &GetAI_mob_dream_cloud;
    newscript->RegisterSelf();
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5

    pNewScript = new Script;
    pNewScript->Name = "mob_nightmare_portal_pre";
    pNewScript->GetAI = &GetAI_mob_nightmare_portal_pre;
    pNewScript->RegisterSelf();

<<<<<<< HEAD
    pNewScript = new Script;
    pNewScript->Name = "mob_nightmare_portal";
    pNewScript->pGossipHello = &GossipHello_mob_nightmare_portal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_nightmare_cloud";
    pNewScript->GetAI = &GetAI_mob_nightmare_cloud;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_dream_portal_pre";
    pNewScript->GetAI = &GetAI_mob_dream_portal_pre;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_dream_portal";
    pNewScript->pGossipHello = &GossipHello_mob_dream_portal;

    pNewScript->RegisterSelf();
    pNewScript = new Script;
    pNewScript->Name = "mob_dream_cloud";
    pNewScript->GetAI = &GetAI_mob_dream_cloud;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_mana_void";
    pNewScript->GetAI = &GetAI_mob_mana_void;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_column_of_frost";
    pNewScript->GetAI = &GetAI_mob_column_of_frost;
    pNewScript->RegisterSelf();
=======
    newscript = new Script;
    newscript->Name = "mob_column_of_frost";
    newscript->GetAI = &GetAI_mob_column_of_frost;
    newscript->RegisterSelf();
>>>>>>> e3b95eb1e7415dbb8299d1f81b998dcf2748a4e5
}

