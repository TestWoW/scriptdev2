/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
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
SDName: boss_professor_putricide
SD%Complete: 70%
SDComment: by carlos93
SDCategory: Icecrown Citadel
EndScriptData */
/* Spells done:
   Slime puddle
   Unstable Experiment
   Visual models
   Mutated Plague
   Expunge Gas
*/
#include "precompiled.h"
#include "icecrown_citadel.h"

enum BossSpells
{
    // Professor Putricide
    SPELL_UNSTABLE_EXPERIMENT           = 70351, // Script effect not work on 10154. Spawn manually.
    SPELL_VOLATILE_EXPERIMENT           = 72842, // Hero only
    SPELL_SUMMON_GREEN_OOZE             = 71412,
    SPELL_SUMMON_RED_OOZE               = 71415,
    SPELL_CREATE_CONCOCTION             = 71621,
    SPELL_MALLEABLE_GOO                 = 70852,
    SPELL_GUZZLE_POTIONS                = 71893,
    SPELL_GUZZLE_POTIONS_1              = 73122,
    SPELL_MUTATED_STRENGTH              = 71604,
    SPELL_MUTATED_PLAGUE                = 72672,
    SPELL_MUTATED_PLAGUE_1              = 71451,
    SPELL_MUTATED_PLAGUE_HEAL           = 72745,
    SPELL_OOZE_THROW                    = 70342, // is triggered spell
    SPELL_GREEN_BOTTLE_0                = 71826,
    SPELL_ORANGE_BOTTLE_0               = 71827,
    SPELL_GREEN_BOTTLE_1                = 71702,
    SPELL_ORANGE_BOTTLE_1               = 71703,

    // Gas Cloud
    NPC_GAS_CLOUD                       = 37562,
    SPELL_GASEOUS_BLOAT                 = 70672,
    SPELL_EXPUNGED_GAS                  = 70701,

    // Volatile Ooze
    NPC_VOLATILE_OOZE                   = 37697,
    SPELL_OOZE_ADHESIVE                 = 70447,
    SPELL_OOZE_ERUPTION                 = 70492,

    // Tank Protections
    SPELL_OOZE_GAS_PROTECTION           = 70812,
    SPELL_OOZE_BEAM_PROTECTION          = 71530,
    SPELL_OOZE_TANK_PROTECTION          = 71770, // triggers the other protection

    // Mutated Abomination (Vehicle)  Need to implement
    NPC_MUTATED_ABOMINATION             = 37672,
    SPELL_MUTATED_TRANSFORMATION        = 70311,
    SPELL_EAT_OOZE                      = 72527,
    SPELL_REGURGITATED_OOZE             = 70539,
    SPELL_MUTATED_SLASH                 = 70542,
    SPELL_MUTATED_AURA                  = 70405,
    SPELL_VEHICLE_HARDCODED             = 46598,

    // Gas Bomb
    NPC_CHOKING_GAS_BOMB                = 38159,
    SPELL_SUMMON_CHOKING_GAS            = 71255,
    SPELL_SUMMON_CHOKING_GAS_1          = 71273,
    SPELL_SUMMON_CHOKING_GAS_2          = 71275,
    SPELL_SUMMON_CHOKING_GAS_3          = 71276,
    SPELL_CHOKING_GAS                   = 71259,
    SPELL_CHOKING_GAS_AURA              = 71278,
    SPELL_CHOKING_GAS_EXPLODE           = 71279,
    SPELL_CHOKING_GAS_EXPLODE_TRIGGER   = 71280,
    SPELL_ORANGE_RADIATION              = 45857,

    // Ooze puddle
    NPC_OOZE_PUDDLE                     = 37690,
    SPELL_SUMMON_SLIME_PUDDLE           = 70342,
    SPELL_SLIME_PUDDLE_BOTTLE           = 70341,
    SPELL_SLIME_PUDDLE                  = 70343,
    SPELL_SLIME_PUDDLE_AURA             = 70346,

    // Others
    SPELL_BERSERK                       = 47008,
    QUEST_24749                         = 71518,
    SHADOW_INFUSION_AURA                = 71516,

    // Tentacles
    NPC_OOZE_TENTACLE                   = 38308,
    NPC_SLIMY_TENTACLE                  = 38309,

    // Tear Gas
    NPC_TEAR_GAS_STALKER                = 38317,
    SPELL_TEAR_GAS                      = 71617,
    SPELL_TEAR_GAS_1                    = 71615,
    SPELL_TEAR_GAS_2                    = 71618,

    //
    VIEW_1                              = 30881,
    VIEW_2                              = 30881,
    VIEW_3                              = 30993,
};

// talks
enum
{
    SAY_AGGRO                   = -1631092,
    SAY_AIRLOCK                 = -1631093,
    SAY_PHASE_CHANGE            = -1631094,
    SAY_TRANSFORM_1             = -1631095,
    SAY_TRANSFORM_2             = -1631096,
    SAY_SLAY_1                  = -1631097,
    SAY_SLAY_2                  = -1631098,
    SAY_BERSERK                 = -1631099,
    SAY_DEATH                   = -1631100,

    // during other fights
    SAY_SLIME_FLOW_1            = -1631074,
    SAY_SLIME_FLOW_2            = -1631075,
    SAY_BLIGHT                  = -1631083,
    SAY_FESTERGUT_DEATH         = -1631091,
    SAY_ROTFACE_DEATH           = -1631080,
};

static Locations SpawnLoc[]=
{
    {4356.779785f, 3263.510010f, 389.398010f, 1.586f},  // 0 Putricide start point o=1.586
    {4295.081055f, 3188.883545f, 389.330261f, 4.270f},  // 1 Puticide Festergut say, o=4.27
    {4417.302246f, 3188.219971f, 389.332520f, 5.102f},  // 2 Putricide Rotface say o=5.102
    {4325.971421f, 3219.162627f, 389.332520f, 5.939f},  // 3 Loc Orange Ooze
    {4388.100098f, 3213.290039f, 389.332520f, 3.340f},  // 4 Loc Green Ooze
};

struct MANGOS_DLL_DECL boss_professor_putricideAI : public ScriptedAI
{
    boss_professor_putricideAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);

        Reset();
    }

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;

    uint32 m_uiUnstableExperimentTimer;
    uint32 m_uiMalleableGooTimer;
    uint32 m_uiSlimePuddleTimer;
    uint32 m_uiChokingGasTimer;
    uint32 m_uiStep;
    uint32 m_uiEventTimer;
    uint32 m_uiNextPoint;
    uint32 m_uiMutatedPlagueTimer;

    bool m_bMovementStarted;
    bool m_bIsPhaseOne;
    bool m_bIsPhaseTwo;
    bool m_bIsPhaseThree;
    bool m_bIsEventStarted;
    bool m_bIsAssistingOnly;
    bool m_bIsGreen;
    bool m_bIsHeroic;
    bool m_bIs25Man;
    bool m_bIsTextSaid;

    void Reset()
    {
        if (!m_pInstance)
            return;

        if (m_creature->isAlive())
            m_pInstance->SetData(TYPE_PUTRICIDE, NOT_STARTED);

        SetCombatMovement(true);
        m_bIsPhaseOne = false;
        m_bIsPhaseTwo = false;
        m_bIsPhaseThree = false;
        m_bIsGreen = true;
        m_bIsAssistingOnly = false;
        m_uiMutatedPlagueTimer = 10000;
        m_uiUnstableExperimentTimer = urand(20000,30000);
        m_uiChokingGasTimer = urand(15000, 20000);
        m_uiMalleableGooTimer = urand(15000, 20000);
        m_uiSlimePuddleTimer = 17000;
        m_uiStep = 0;
        m_uiEventTimer = 0;
        if (Unit *pTentacle1 = GetClosestCreatureWithEntry(m_creature, NPC_OOZE_TENTACLE, 100.0f))
            pTentacle1->SetDisplayId(22769);
        if (Unit *pTentacle2 = GetClosestCreatureWithEntry(m_creature, NPC_SLIMY_TENTACLE, 100.0f))
            pTentacle2->SetDisplayId(22769);
    }

    void DamageTaken(Unit *pDealer, uint32 &uiDamage)
    {
        if (m_bIsAssistingOnly)
            uiDamage = 0;
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_SLAY_1 - urand(0, 1),m_creature,pVictim);
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!m_bIsTextSaid && !m_bIsAssistingOnly)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                m_bIsTextSaid = true;
                DoScriptText(SAY_AIRLOCK, m_creature, pWho);
                return;
            }
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }


    void Aggro(Unit* pWho)
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_FESTERGUT) == IN_PROGRESS || m_pInstance->GetData(TYPE_ROTFACE) == IN_PROGRESS)
        {
            SetCombatMovement(false);
            m_bIsAssistingOnly = true;
            return;
        }

        m_pInstance->SetData(TYPE_PUTRICIDE, IN_PROGRESS);
        DoScriptText(SAY_AGGRO, m_creature, pWho);

        /*if (Unit* pTarget = doSelectRandomPlayer(SPELL_SHADOWS_EDGE, true, 100.0f)) //hack! need remove later
            doAura(SHADOW_INFUSION_AURA,pTarget);*/
    }

    void JustDied(Unit *killer)
    {
        if (!m_pInstance)
            return;
        m_pInstance->SetData(TYPE_PUTRICIDE, DONE);
        DoScriptText(SAY_DEATH,m_creature, killer);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if(!m_pInstance || !pSummoned)
            return;
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
            uint8 max = m_bIs25Man ? 1 : 1;
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

    void UnstableExperiment(Unit *pTarget)
    {
        if (m_bIsGreen)
        {
            if(Creature *pGreen = m_creature->SummonCreature(NPC_VOLATILE_OOZE, SpawnLoc[4].x, SpawnLoc[4].y, SpawnLoc[4].z, SpawnLoc[4].o, TEMPSUMMON_MANUAL_DESPAWN, 0))
            {
                DoCastSpellIfCan(m_creature, SPELL_UNSTABLE_EXPERIMENT);
                m_bIsGreen = false;
                pGreen->SetInCombatWith(pTarget);
                m_uiUnstableExperimentTimer = urand(20000,30000);
            }
        }
        else if (!m_bIsGreen)
        {
            if (Creature *pRed = m_creature->SummonCreature(NPC_GAS_CLOUD, SpawnLoc[3].x, SpawnLoc[3].y, SpawnLoc[3].z, SpawnLoc[3].o, TEMPSUMMON_MANUAL_DESPAWN, 0))
            {
                DoCastSpellIfCan(m_creature, SPELL_UNSTABLE_EXPERIMENT);
                m_bIsGreen = true;
                pRed->SetInCombatWith(pTarget);
                m_uiUnstableExperimentTimer = urand(20000,30000);
            }
        }
    }

    void VolatileExperiment(Unit *pTarget1, Unit *pTarget2)
    {
        if (m_bIsHeroic)
        {
            if(Creature *pGreen = m_creature->SummonCreature(NPC_VOLATILE_OOZE, SpawnLoc[4].x, SpawnLoc[4].y, SpawnLoc[4].z, SpawnLoc[4].o, TEMPSUMMON_MANUAL_DESPAWN, 0))
            {
                if (Creature *pRed = m_creature->SummonCreature(NPC_GAS_CLOUD, SpawnLoc[3].x, SpawnLoc[3].y, SpawnLoc[3].z, SpawnLoc[3].o, TEMPSUMMON_MANUAL_DESPAWN, 0))
                {
                    DoCastSpellIfCan(m_creature, SPELL_VOLATILE_EXPERIMENT);
                    pRed->SetInCombatWith(pTarget1);
                    pGreen->SetInCombatWith(pTarget2);
                }
            }
        }
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type != POINT_MOTION_TYPE || !m_bMovementStarted)
            return;
        if (id == 0)
        {
            m_bMovementStarted = false;
            m_creature->GetMotionMaster()->MovementExpired();
        }
    }

    void StartMovement(uint32 id)
    {
        m_uiNextPoint = id;
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MovePoint(id, SpawnLoc[id].x, SpawnLoc[id].y, SpawnLoc[id].z);
        m_bMovementStarted = true;
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiStep;
        m_uiEventTimer = uiTime;
    }

    void CastOnAllPlayers(uint32 spell)
    {
        Map* pMap = m_creature->GetMap();
        Map::PlayerList const& pPlayers = pMap->GetPlayers();
        if (!pPlayers.isEmpty())
        {
            for (Map::PlayerList::const_iterator itr = pPlayers.begin(); itr != pPlayers.end(); ++itr)
            {
                Unit *pTarget = itr->getSource();
                if (pTarget && pTarget->isAlive())
                    m_creature->CastSpell(pTarget, spell, false);
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bIsAssistingOnly)
            return;

        if (m_uiEventTimer <= uiDiff)
        {
            switch (m_uiStep)
            {
            case 0:
                {
                    if (m_uiUnstableExperimentTimer < uiDiff)
                    {
                        if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                            UnstableExperiment(pTarget);
                    }
                    else m_uiUnstableExperimentTimer -= uiDiff;

                    if (m_uiSlimePuddleTimer < uiDiff)
                    {
                        if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                        {
                            DoCastSpellIfCan(pTarget, SPELL_SLIME_PUDDLE_BOTTLE, CAST_TRIGGERED);
                            m_uiSlimePuddleTimer = 30000;
                        }
                    }
                    else m_uiSlimePuddleTimer -= uiDiff;
                    DoMeleeAttackIfReady();

                    if (m_creature->GetHealthPercent() <= 80)
                        NextStep();
                    break;
                }
            case 1:
                {
                    SetCombatMovement(false);
                    m_creature->AttackStop();
                    if (!m_bIsHeroic)
                    {
                        CastOnAllPlayers(SPELL_TEAR_GAS_1);
                        DoScriptText(SAY_BLIGHT,m_creature);
                    }
                    if (m_bIsHeroic)
                    {
                        if (Unit *pTarget1 = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                        {
                            if (Unit *pTarget2 = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                            {
                                VolatileExperiment(pTarget1, pTarget2);
                                DoScriptText(SAY_PHASE_CHANGE, m_creature);
                            }
                        }
                    }
                    StartMovement(0);
                    NextStep(0);
                    break;
                }
            case 2:
                {
                    if (m_bMovementStarted)
                        return;
                    m_creature->CastSpell(m_creature, SPELL_CREATE_CONCOCTION, false);
                    NextStep(4000);
                    break;
                }
            case 3:
                {
                    if (m_creature->IsNonMeleeSpellCasted(true))
                        return;
                    if (Unit *pTentacle1 = GetClosestCreatureWithEntry(m_creature, NPC_OOZE_TENTACLE, 100.0f))
                        pTentacle1->CastSpell(pTentacle1, SPELL_ORANGE_BOTTLE_0, false);
                    if (Unit *pTentacle2 = GetClosestCreatureWithEntry(m_creature, NPC_SLIMY_TENTACLE, 100.0f))
                        pTentacle2->CastSpell(pTentacle2, SPELL_GREEN_BOTTLE_0, false);
                    NextStep(12000);
                    break;
                }
            case 4:
                {
                    DoScriptText(SAY_TRANSFORM_1,m_creature);
                    m_creature->GetMotionMaster()->Clear();
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    NextStep(0);
                    break;
                }
            case 5:
                {
                    SetCombatMovement(true);
                    if (m_uiUnstableExperimentTimer < uiDiff)
                    {
                        if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                            UnstableExperiment(pTarget);
                    }
                    else m_uiUnstableExperimentTimer -= uiDiff;

                    if (m_uiSlimePuddleTimer < uiDiff)
                    {
                        if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                        {
                            DoCastSpellIfCan(pTarget, SPELL_SLIME_PUDDLE_BOTTLE, CAST_TRIGGERED);
                            m_uiSlimePuddleTimer = 30000;
                        }
                    }
                    else m_uiSlimePuddleTimer -= uiDiff;

                    if (m_uiChokingGasTimer < uiDiff)
                    {
                        if(DoCastSpellIfCan(m_creature->getVictim(), SPELL_SUMMON_CHOKING_GAS) == CAST_OK)
                            m_uiChokingGasTimer = urand(15000, 25000);
                    }
                    else m_uiChokingGasTimer -= uiDiff;

                    if (m_uiMalleableGooTimer < uiDiff)
                    {
                        if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                        {
                            DoCastSpellIfCan(pTarget, SPELL_MALLEABLE_GOO);
                            m_uiMalleableGooTimer = urand(15000,20000);
                        }
                    }
                    else m_uiMalleableGooTimer -= uiDiff;
                    DoMeleeAttackIfReady();

                    if (m_creature->GetHealthPercent() <= 35)
                        NextStep();
                    break;
                }
            case 6:
                {
                    SetCombatMovement(false);
                    m_creature->AttackStop();
                    if (!m_bIsHeroic)
                    {
                        CastOnAllPlayers(SPELL_TEAR_GAS_1);
                        DoScriptText(SAY_BLIGHT,m_creature);
                    }
                    if (m_bIsHeroic)
                    {
                        if (Unit *pTarget1 = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                        {
                            if (Unit *pTarget2 = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                            {
                                VolatileExperiment(pTarget1, pTarget2);
                                DoScriptText(SAY_PHASE_CHANGE, m_creature);
                            }
                        }
                    }
                    StartMovement(0);
                    NextStep(0);
                    break;
                }
            case 7:
                {
                    if (m_bMovementStarted)
                        return;
                    m_creature->CastSpell(m_creature, SPELL_GUZZLE_POTIONS, false);
                    NextStep(4000);
                    break;
                }
            case 8:
                {
                    if (m_creature->IsNonMeleeSpellCasted(true))
                        return;
                    m_creature->RemoveAurasDueToSpell(SPELL_GUZZLE_POTIONS_1);
                    DoCastSpellIfCan(m_creature, SPELL_MUTATED_STRENGTH, CAST_TRIGGERED);
                    if (Unit *pTentacle1 = GetClosestCreatureWithEntry(m_creature, NPC_OOZE_TENTACLE, 100.0f))
                        pTentacle1->CastSpell(pTentacle1, SPELL_ORANGE_BOTTLE_1, false);
                    //if (Unit *pTentacle2 = GetClosestCreatureWithEntry(m_creature, NPC_SLIMY_TENTACLE, 100.0f))
                    //    pTentacle2->CastSpell(pTentacle2, SPELL_GREEN_BOTTLE_1, false);
                    NextStep(12000);
                    break;
                }
            case 9:
                {
                    DoScriptText(SAY_TRANSFORM_2,m_creature);
                    m_creature->GetMotionMaster()->Clear();
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    NextStep(0);
                    break;
                }
            case 10:
                {
                    SetCombatMovement(true);
                    m_creature->getVictim()->RemoveAurasDueToSpell(SPELL_MUTATED_PLAGUE);
                    if (m_uiMutatedPlagueTimer < uiDiff)
                    {
                        m_creature->getVictim()->_AddAura(SPELL_MUTATED_PLAGUE);
                        m_uiMutatedPlagueTimer = 10000;
                    }
                    else m_uiMutatedPlagueTimer -= uiDiff;

                    if (m_uiSlimePuddleTimer < uiDiff)
                    {
                        if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                        {
                            DoCastSpellIfCan(pTarget, SPELL_SLIME_PUDDLE_BOTTLE, CAST_TRIGGERED);
                            m_uiSlimePuddleTimer = 30000;
                        }
                    }
                    else m_uiSlimePuddleTimer -= uiDiff;

                    if (m_uiChokingGasTimer < uiDiff)
                    {
                        if(DoCastSpellIfCan(m_creature->getVictim(), SPELL_SUMMON_CHOKING_GAS) == CAST_OK)
                            m_uiChokingGasTimer = urand(15000, 25000);
                    }
                    else m_uiChokingGasTimer -= uiDiff;

                    if (m_uiMalleableGooTimer < uiDiff)
                    {
                        if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                        {
                            DoCastSpellIfCan(pTarget, SPELL_MALLEABLE_GOO);
                            m_uiMalleableGooTimer = urand(15000,20000);
                        }
                    }
                    else m_uiMalleableGooTimer -= uiDiff;
                    DoMeleeAttackIfReady();
                    break;
                }
            default:
                break;
            }
        }
        else
            m_uiEventTimer -= uiDiff;
    }
};

CreatureAI* GetAI_boss_professor_putricide(Creature* pCreature)
{
    return new boss_professor_putricideAI(pCreature);
}

struct MANGOS_DLL_DECL mob_icc_gas_cloudAI : public ScriptedAI
{
    mob_icc_gas_cloudAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    Unit* pTarget;
    bool exploded;

    void Reset()
    {
        if (!m_pInstance)
            return;

        m_creature->SetRespawnDelay(7*DAY);
        m_creature->SetWalk(true);
        m_creature->SetSpeedRate(MOVE_WALK, 0.5f);
        m_creature->SetSpeedRate(MOVE_RUN, 0.75f);
        pTarget = NULL;
        exploded = false;
    }

    void Aggro(Unit *pWho)
    {
        if (!m_pInstance || !pWho || pWho->GetTypeId() != TYPEID_PLAYER)
            return;

        if (!pTarget || pTarget!= pWho)
            pTarget = pWho;
        else return;

        m_creature->AddThreat(pTarget, 10000.0f);
        SetStacks(pTarget, SPELL_GASEOUS_BLOAT, 10);
    }

    void JustReachedHome()
    {
        if (!m_pInstance)
            return;
        pTarget = NULL;

        if(pTarget)
            pTarget->RemoveAurasDueToSpell(SPELL_GASEOUS_BLOAT);

        m_creature->ForcedDespawn();
    }

    void JustDied(Unit *pKiller)
    {
        if (!m_pInstance)
            return;
        pTarget = NULL;

        if (pTarget && pTarget->isAlive())
            pTarget->RemoveAurasDueToSpell(SPELL_GASEOUS_BLOAT);
    }

    void SetStacks(Unit *pTarget, uint32 spell, uint32 stacks)
    {
        if (pTarget)
        {
            m_creature->CastSpell(pTarget, spell, true);
            if (SpellAuraHolderPtr holder = pTarget->GetSpellAuraHolder(spell))
            {
                holder->SetStackAmount(stacks);
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (pTarget && pTarget->isAlive() && pTarget->IsWithinDistInMap(m_creature, 3.0f) && !exploded)
        {
            m_creature->CastSpell(pTarget, SPELL_EXPUNGED_GAS, true);
            pTarget->RemoveAurasDueToSpell(SPELL_GASEOUS_BLOAT);
            exploded = true;
        }
        if (exploded)
            m_creature->ForcedDespawn(500);
    }
};

CreatureAI* GetAI_mob_icc_gas_cloud(Creature* pCreature)
{
    return new mob_icc_gas_cloudAI(pCreature);
}

struct MANGOS_DLL_DECL mob_icc_volatile_oozeAI : public ScriptedAI
{
    mob_icc_volatile_oozeAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    Unit *pTarget;
    bool exploded;

    void Reset()
    {
        if (!m_pInstance)
            return;

        m_creature->SetRespawnDelay(7*DAY);
        m_creature->SetWalk(true);
        m_creature->SetSpeedRate(MOVE_WALK, 0.5f);
        m_creature->SetSpeedRate(MOVE_RUN, 0.75f);
        pTarget = NULL;
        exploded = false;
    }

    void Aggro(Unit *pWho)
    {
        if (!m_pInstance || !pWho || pWho->GetTypeId() != TYPEID_PLAYER)
            return;

        if (!pTarget || pTarget!= pWho)
            pTarget = pWho;
        else return;

        m_creature->AddThreat(pTarget, 10000.0f);
        m_creature->CastSpell(pTarget, SPELL_OOZE_ADHESIVE, true);
    }

    void JustDied(Unit *pKiller)
    {
        if (!m_pInstance)
            return;

        if (pTarget && pTarget->isAlive())
            pTarget->RemoveAurasDueToSpell(SPELL_OOZE_ADHESIVE);
    }

    void JustReachedHome()
    {
        if (!m_pInstance)
            return;

        if (pTarget)
            pTarget->RemoveAurasDueToSpell(SPELL_OOZE_ADHESIVE);

        m_creature->ForcedDespawn();
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            Aggro(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0));

        if (pTarget && pTarget->isAlive() && pTarget->IsWithinDistInMap(m_creature, 3.0f) && !exploded)
        {
            m_creature->CastSpell(pTarget, SPELL_OOZE_ERUPTION, false);
            pTarget->RemoveAurasDueToSpell(SPELL_OOZE_ADHESIVE);
            exploded = true;
        }
        if (exploded)
            m_creature->ForcedDespawn(500);
    }
};

CreatureAI* GetAI_mob_icc_volatile_ooze(Creature* pCreature)
{
    return new mob_icc_volatile_oozeAI(pCreature);
}

struct MANGOS_DLL_DECL mob_choking_gas_bombAI : public ScriptedAI
{
    mob_choking_gas_bombAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
        SetCombatMovement(false);
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiExplodeTimer;
    bool exploded;

    void Reset()
    {
        if (!m_pInstance)
            return;
        m_uiExplodeTimer = 20000;
        m_creature->SetRespawnDelay(7*DAY);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->CastSpell(m_creature, SPELL_ORANGE_RADIATION, true);
        m_creature->CastSpell(m_creature, SPELL_CHOKING_GAS, true);
        //m_creature->CastSpell(m_creature, SPELL_CHOKING_GAS_EXPLODE, true);
        exploded = false;
    }

    void DamageTaken(Unit* pDealer, uint32& uiDamage)
    {
        uiDamage = 0;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiExplodeTimer < uiDiff && !exploded)
        {
            m_creature->CastSpell(m_creature, SPELL_CHOKING_GAS_EXPLODE, true);
            exploded = true;
        }
        else m_uiExplodeTimer -= uiDiff;

        if (exploded)
            m_creature->ForcedDespawn(1500);
    }

};

CreatureAI* GetAI_mob_choking_gas_bomb(Creature* pCreature)
{
    return new mob_choking_gas_bombAI(pCreature);
};

struct MANGOS_DLL_DECL mob_ooze_puddleAI : public ScriptedAI
{
    mob_ooze_puddleAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
        SetCombatMovement(false);
    }

    ScriptedInstance* m_pInstance;
    uint32 m_uiDespawnTimer;

    void Reset()
    {
        if (!m_pInstance)
            return;
        m_uiDespawnTimer = 15000;
        m_creature->SetRespawnDelay(7*DAY);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->CastSpell(m_creature, SPELL_SLIME_PUDDLE, false);
        m_creature->SetObjectScale(0.5);
    }

    void DamageTaken(Unit* pDealer, uint32& uiDamage)
    {
        uiDamage = 0;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiDespawnTimer < uiDiff)
            m_creature->ForcedDespawn();
        else m_uiDespawnTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_ooze_puddle(Creature* pCreature)
{
    return new mob_ooze_puddleAI(pCreature);
}

/*struct MANGOS_DLL_DECL mob_mutated_abominationAI : public ScriptedAI
{
    mob_mutated_abominationAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        //m_victimGuid.Clear();
        //m_bEmerged = false;
        //SetCombatMovement(false);
    }

    ScriptedInstance *m_pInstance;

    void Reset()
    {

    }
};

CreatureAI* GetAI_mob_mutated_abomination(Creature* pCreature)
{
    return new mob_mutated_abominationAI(pCreature);
}*/

void AddSC_boss_professor_putricide()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_professor_putricide";
    newscript->GetAI = &GetAI_boss_professor_putricide;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_icc_volatile_ooze";
    newscript->GetAI = &GetAI_mob_icc_volatile_ooze;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_icc_gas_cloud";
    newscript->GetAI = &GetAI_mob_icc_gas_cloud;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_choking_gas_bomb";
    newscript->GetAI = &GetAI_mob_choking_gas_bomb;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_ooze_puddle";
    newscript->GetAI = &GetAI_mob_ooze_puddle;
    newscript->RegisterSelf();

    /*newscript = new Script;
    newscript->Name = "mob_mutated_abomination";
    newscript->GetAI = &GetAI_mob_mutated_abomination;
    newscript->RegisterSelf();*/
}



