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
SDName: boss_blood_queen_lanathel
SD%Complete: 95%
SDComment: by carlos93 && michalpolko
SDCategory: Icecrown Citadel
EndScriptData */
// Need to implement MC
#include "precompiled.h"
#include "icecrown_citadel.h"

enum BossSpells
{
    SPELL_BERSERK                           = 47008,
    SPELL_INCITE_TERROR                     = 73070,
    SPELL_SHROUD_OF_SORROW                  = 72981,
    SPELL_DELIRIOUS_SLASH_1                 = 71623,
    SPELL_DELIRIOUS_SLASH_2                 = 72264,
    SPELL_BLOOD_MIRROR_TANK                 = 70821,
    SPELL_BLOOD_MIRROR_OFF                  = 70838,
    SPELL_VAMPIRIC_BITE                     = 71726,
    SPELL_ESSENCE_OF_BLOOD_QUEEN            = 70867,
    SPELL_ESSENCE_OF_BLOOD_QUEEN_2          = 70871,
    SPELL_FRENZIED_BLOODTHIRST              = 70877,
    SPELL_UNCONTROLLABLE_FRENZY             = 70923,
    SPELL_PACT_OF_DARKFALLEN                = 71336,
    SPELL_SWARMING_SHADOWS                  = 71264,
    SPELL_TWILIGHT_BLOODBOLT                = 71446,
    SPELL_BLOODBOLT_WHIRL                   = 71772,
    SPELL_PRESENCE_OF_DARKFALLEN            = 71952,

    NPC_SWARMING_SHADOWS                    = 38163,
    SPELL_SWARMING_SHADOWS_VISUAL           = 71267,
    THIRST_QUENCHED_AURA                    = 72154,
};

// talks
enum
{
    SAY_AGGRO                   = -1631121,
    SAY_BITE_1                  = -1631122,
    SAY_BITE_2                  = -1631123,
    SAY_SHADOWS                 = -1631124,
    SAY_PACT                    = -1631125,
    SAY_MC                      = -1631126,
    SAY_AIR_PHASE               = -1631127,
    SAY_BERSERK                 = -1631128,
    SAY_DEATH                   = -1631129,
};

enum
{
    PHASE_GROUND                = 0,
    PHASE_MOVING_CENTER         = 1,
    PHASE_FLYING                = 2,
    PHASE_AIR                   = 3,

    POINT_CENTER_GROUND         = 0,
    POINT_CENTER_AIR            = 1,
};

enum Equipment
{
    EQUIP_MAIN           = 29996, // TODO: Need true id weapon.
    EQUIP_OFFHAND        = EQUIP_NO_CHANGE,
    EQUIP_RANGED         = EQUIP_NO_CHANGE,
    EQUIP_DONE           = EQUIP_NO_CHANGE,
};

static Locations QueenLocs[]=
{
    {4595.640137f, 2769.195557f, 400.137054f},  // 0 Phased
    {4595.904785f, 2769.315918f, 421.838623f},  // 1 Fly
};


struct MANGOS_DLL_DECL boss_blood_queen_lanathelAI : public base_icc_bossAI
{
    boss_blood_queen_lanathelAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiPhase;
    uint32 m_uiPhaseTimer;
    uint32 m_uiBiteTimer;
    uint32 m_uiDeliriousSlashTimer;
    uint32 m_uiPactTimer;
    uint32 m_uiShadowsTimer;
    uint32 m_uiTwilightTimer;
    uint32 m_uiBloodboltWhirlTimer;
    uint32 m_uiEnrageTimer;
    uint32 m_uiBloodMirrorCheckTimer;

    bool m_bBite;

    void Reset()
    {
        m_bBite                     = false;
        m_uiPhase                   = PHASE_GROUND;
        m_uiPhaseTimer              = 2*MINUTE * IN_MILLISECONDS;
        m_uiBiteTimer               = 15000;
        m_uiPactTimer               = 15000;
        m_uiShadowsTimer            = 30000;
        m_uiTwilightTimer           = urand(12000, 17000);
        m_uiDeliriousSlashTimer     = urand(15000, 20000);
        m_uiBloodMirrorCheckTimer   = 1000;
        m_uiEnrageTimer             = 5.5 * MINUTE * IN_MILLISECONDS; //5:30 min

        m_creature->SetWalk(false);
        m_creature->SetLevitate(false);
        m_creature->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_UNK_2);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_LANATHEL, FAIL);

        DoRemoveAuraFromAll(SPELL_BLOOD_MIRROR_OFF);
        DoRemoveAuraFromAll(SPELL_BLOOD_MIRROR_TANK);
        DoRemoveAuraFromAll(SPELL_ESSENCE_OF_BLOOD_QUEEN);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
        {
            //DoScriptText(SAY_KILL, m_creature);  // Need to be implemented in BD
            m_creature->MonsterYell("Is that all you got?", 0);
        }

        if (pVictim && pVictim->HasAura(SPELL_BLOOD_MIRROR_OFF))
           pVictim->RemoveAurasDueToSpell(SPELL_BLOOD_MIRROR_OFF);

        if (pVictim && pVictim->HasAura(SPELL_BLOOD_MIRROR_TANK))
           pVictim->RemoveAurasDueToSpell(SPELL_BLOOD_MIRROR_TANK);
    }

    void MovementInform(uint32 uiMovementType, uint32 uiData)
    {
        if (uiMovementType != POINT_MOTION_TYPE)
            return;

        if (uiData == POINT_CENTER_GROUND)
        {
            if (m_uiPhase == PHASE_MOVING_CENTER)
            {
                m_creature->GetMotionMaster()->Clear();
                m_uiPhase = PHASE_AIR; // start counting timer for Bloodbolt Whirl immediately

                if (DoCastSpellIfCan(m_creature, SPELL_INCITE_TERROR) == CAST_OK)
                {
                    // fly up
                    m_creature->SetWalk(true);
                    m_creature->SetLevitate(true);
                    m_creature->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_UNK_2);

                    m_creature->GetMotionMaster()->MovePoint(POINT_CENTER_AIR, QueenLocs[1].x, QueenLocs[1].y, QueenLocs[1].z);
                    m_creature->HandleEmote(EMOTE_ONESHOT_LIFTOFF);
                }
            }
            else
            {
                m_uiPhase = PHASE_GROUND;

                // stop flying
                m_creature->SetWalk(false);
                m_creature->SetLevitate(false);
                m_creature->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_UNK_2);

                SetCombatMovement(true);
                if (m_creature->getVictim())
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
            }
        }
        else if (uiData == POINT_CENTER_AIR)
        {
            // Bloodbolt Whirl
            if (DoCastSpellIfCan(m_creature, SPELL_BLOODBOLT_WHIRL) == CAST_OK)
            {
                m_uiPhase = PHASE_AIR;
                m_uiPhaseTimer = 7000;
            }
        }
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_LANATHEL, IN_PROGRESS);

        DoCastSpellIfCan(m_creature, SPELL_SHROUD_OF_SORROW, CAST_TRIGGERED);
        SetEquipmentSlots(false, EQUIP_MAIN, EQUIP_OFFHAND, EQUIP_RANGED);

        DoScriptText(SAY_AGGRO,m_creature,pWho);
    }

    Unit* SelectClosestFriendlyTarget(Unit *pVictim)
    {
        Unit *pResult = NULL;

        if (m_pInstance)
        {
            float lastDist = 500.0f;
            const Map::PlayerList &players = m_pInstance->instance->GetPlayers();
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
            {
                if (!(*itr).getSource()->IsInWorld() ||                          // don't target not in world players
                !(*itr).getSource()->isAlive() ||                                // don't target dead players
                (*itr).getSource()->isGameMaster() ||                            // don't target GMs
                (*itr).getSource()->GetObjectGuid() == pVictim->GetObjectGuid()) // don't target current victim
                    continue;

                float dist = pVictim->GetDistance((*itr).getSource());
                if (dist < lastDist)
                {
                    pResult = (*itr).getSource();
                    lastDist = dist;
                }
            }
        }

        return pResult;
    }

    Unit* SelectVampiricBiteTarget()
    {
        const ThreatList &threatList = m_creature->getThreatManager().getThreatList();
        ThreatList::const_iterator itr = threatList.begin();
        std::advance(itr, 1); // don't target the main tank
        for (;itr != threatList.end(); ++itr)
        {
            if (Unit *pVictim = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid()))
            {
                if (!pVictim->HasAuraOfDifficulty(70867) && // Essence of the Blood Queen
                !pVictim->HasAuraOfDifficulty(70877) &&     // Frenzied Bloodthirst
                !pVictim->HasAuraOfDifficulty(SPELL_BLOOD_MIRROR_OFF) &&     // Blood Mirror
                !pVictim->HasAuraOfDifficulty(70923))       // Uncontrollable Frenzy
                {
                    return pVictim;
                }
            }
        }

        return NULL;
    }

    void JustDied(Unit *killer)
    {
        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_LANATHEL, DONE);
        DoScriptText(SAY_DEATH,m_creature,killer);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
        m_creature->GetMotionMaster()->MovePoint(3, m_creature->GetPositionX(), m_creature->GetPositionY(), QueenLocs[0].z);
        DoRemoveAuraFromAll(SPELL_BLOOD_MIRROR_OFF);
        DoRemoveAuraFromAll(SPELL_BLOOD_MIRROR_TANK);
        DoRemoveAuraFromAll(SPELL_ESSENCE_OF_BLOOD_QUEEN);
     }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiBloodMirrorCheckTimer < uiDiff)
        {
            if (Unit *pTank = /*m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0)*/m_creature->getVictim())
            {
                if (Unit *pOff = SelectClosestFriendlyTarget(m_creature->getVictim()))
                {
                    if(pTank->HasAura(SPELL_BLOOD_MIRROR_OFF))
                        pTank->RemoveAurasDueToSpell(SPELL_BLOOD_MIRROR_OFF);

                    if(pOff->HasAura(SPELL_BLOOD_MIRROR_TANK))
                        pOff->RemoveAurasDueToSpell(SPELL_BLOOD_MIRROR_TANK);

                    if (!pTank->HasAura(SPELL_BLOOD_MIRROR_TANK))
                    {
                        pOff->CastSpell(pTank, SPELL_BLOOD_MIRROR_TANK, true);
                    }
                    if (!pOff->HasAura(SPELL_BLOOD_MIRROR_OFF))
                    {
                        pTank->CastSpell(pOff, SPELL_BLOOD_MIRROR_OFF, true);
                    }
                }
            }
            m_uiBloodMirrorCheckTimer = 500;
        }
        else m_uiBloodMirrorCheckTimer -= uiDiff;

        if (m_uiEnrageTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK, CAST_TRIGGERED) == CAST_OK)
            {
                DoScriptText(SAY_BERSERK,m_creature);
                m_uiEnrageTimer = 5.5 * MINUTE * IN_MILLISECONDS;
            }
        }
        else m_uiEnrageTimer -= uiDiff;

        switch (m_uiPhase)
        {
        case PHASE_GROUND:
            if (m_uiTwilightTimer < uiDiff)
            {
                if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_TWILIGHT_BLOODBOLT) == CAST_OK)
                        m_uiTwilightTimer = urand(12000, 17000);
                }
            }
            else m_uiTwilightTimer -= uiDiff;

            // Delirious Slash
            if (m_uiDeliriousSlashTimer <= uiDiff)
            {
                /**
                 * Spell that handles targeting - we can do this here.
                 * if (DoCastSpellIfCan(m_creature, SPELL_DELIRIOUS_SLASH) == CAST_OK)
                 */
                if (Unit *pTarget = SelectClosestFriendlyTarget(m_creature->getVictim()))
                {
                    uint32 spell = SPELL_DELIRIOUS_SLASH_1;

                    // if target is not in 5yd range then cast spell with charge effect
                    if (!m_creature->IsWithinDist(pTarget, 5.0f))
                        spell = SPELL_DELIRIOUS_SLASH_2;

                    if (DoCastSpellIfCan(pTarget, spell) == CAST_OK)
                        m_uiDeliriousSlashTimer = 15000;
                }
            }
            else
                m_uiDeliriousSlashTimer -= uiDiff;

            /*if (m_uiDeliriousSlashTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,2))
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_DELIRIOUS_SLASH) == CAST_OK)
                        m_uiDeliriousSlashTimer = urand(15000, 20000);
                }
            }
            else m_uiDeliriousSlashTimer -= uiDiff;*/

            if (m_uiPactTimer < uiDiff)
            {
                //if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                //{
                    if (DoCastSpellIfCan(m_creature, SPELL_PACT_OF_DARKFALLEN) == CAST_OK)
                    {
                        DoScriptText(SAY_PACT, m_creature);
                        m_uiPactTimer = 30000;
                    }
                //}
            }
            else m_uiPactTimer -= uiDiff;

            if (m_uiShadowsTimer < uiDiff)
            {
                if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_SWARMING_SHADOWS) == CAST_OK)
                    {
                        DoScriptText(SAY_SHADOWS,m_creature);
                        m_uiShadowsTimer = 30000;
                    }
                }
            }
            else m_uiShadowsTimer -= uiDiff;

            if (m_uiBiteTimer < uiDiff && !m_bBite)
            {
                if (Unit* pTarget = SelectVampiricBiteTarget())
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_VAMPIRIC_BITE) == CAST_OK)
                    {
                        m_bBite = true;
                        DoScriptText(SAY_BITE_1, m_creature);
                    }
                }
            }
            else m_uiBiteTimer -= uiDiff;

            if (m_uiPhaseTimer < uiDiff && m_creature->GetHealthPercent() >= 5)
            {
                m_uiPhase = PHASE_MOVING_CENTER;
                m_creature->GetMotionMaster()->MovePoint(POINT_CENTER_GROUND, QueenLocs[0].x, QueenLocs[0].y, QueenLocs[0].z);
                SetCombatMovement(false);
                m_uiPhaseTimer = 13000;
            }
            else m_uiPhaseTimer -= uiDiff;

            DoMeleeAttackIfReady();
            break;
        case PHASE_MOVING_CENTER:
            break;
        case PHASE_FLYING:
            m_creature->HandleEmote(EMOTE_ONESHOT_LAND);
            break;
        case PHASE_AIR:
            // phase change timer
            if (m_uiPhaseTimer <= uiDiff)
            {
                m_uiPhase = PHASE_FLYING;
                m_uiPhaseTimer = 2 * MINUTE * IN_MILLISECONDS - 13000; // substract the air phase duration
                m_creature->GetMotionMaster()->Clear();
                m_creature->GetMotionMaster()->MovePoint(POINT_CENTER_GROUND, QueenLocs[0].x, QueenLocs[0].y, QueenLocs[0].z);
            }
            else
                m_uiPhaseTimer -= uiDiff;

            break;
        }
    }
};

CreatureAI* GetAI_boss_blood_queen_lanathel(Creature* pCreature)
{
    return new boss_blood_queen_lanathelAI(pCreature);
}

struct MANGOS_DLL_DECL mob_swarming_shadowsAI : public ScriptedAI
{
    mob_swarming_shadowsAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_creature->SetVisibility(VISIBILITY_ON);
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
        SetCombatMovement(false);
        m_creature->SetInCombatWithZone();
        DoCastSpellIfCan(m_creature, SPELL_SWARMING_SHADOWS_VISUAL, CAST_TRIGGERED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->HasAura(SPELL_SWARMING_SHADOWS_VISUAL))
            DoCastSpellIfCan(m_creature, SPELL_SWARMING_SHADOWS_VISUAL, CAST_TRIGGERED);

        m_creature->ForcedDespawn(30000);
    }
};

CreatureAI* GetAI_mob_swarming_shadows(Creature* pCreature)
{
     return new mob_swarming_shadowsAI (pCreature);
}

void AddSC_boss_blood_queen_lanathel()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_blood_queen_lanathel";
    pNewScript->GetAI = &GetAI_boss_blood_queen_lanathel;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_swarming_shadows";
    pNewScript->GetAI = &GetAI_mob_swarming_shadows;
    pNewScript->RegisterSelf();
}
