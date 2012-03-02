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
SDName: boss_festergut
SD%Complete: 99%
SDComment: targeting spells of Malleable Goo and Vile Gas unclear, coded targeting in script
SDCategory: Icecrown Citadel
EndScriptData */
#include "precompiled.h"
#include "icecrown_citadel.h"

enum
{
    SPELL_BERSERK               = 47008,

    // Stinky
    SPELL_STINKY_DECIMATE       = 71123,
    SPELL_STINKY_MORTALWOUND    = 71127,

    // Gastric Bloat
    SPELL_GASTRIC_BLOAT         = 72214, // proc aura, ~8 sec cooldown, currently not used
    SPELL_GASTRIC_BLOAT_TRIG    = 72219,

    // Inhale Blight
    SPELL_INHALE_BLIGHT         = 69165,
    SPELL_INHALED_BLIGHT_10     = 69166,
    SPELL_INHALED_BLIGHT_25     = 71912,

    // Pungent Blight
    SPELL_PUNGENT_BLIGHT        = 69195,

    // Gaseous Blight
    // periodic auras spells
    SPELL_GASEUS_BLIGHT_DUMMY   = 69125, // gas is spread into the room on aggro
    SPELL_GASEOUS_BLIGHT_1      = 69157,
    SPELL_GASEOUS_BLIGHT_2      = 69162,
    SPELL_GASEOUS_BLIGHT_3      = 69164,
    // visual gas dummy auras
    SPELL_GASEOUS_BLIGHT_DUMMY1 = 69126,
    SPELL_GASEOUS_BLIGHT_DUMMY2 = 69152,
    SPELL_GASEOUS_BLIGHT_DUMMY3 = 69154,

    // Inoculent
    SPELL_REMOVE_INOCULENT      = 69298,

    // Gas Spore
    SPELL_GAS_SPORE             = 69278,

    // Vile Gas
    SPELL_VILE_GAS_SUMMON       = 72288,
    SPELL_VILE_GAS_SUMMON_TRIG  = 72287,
    SPELL_VILE_GAS              = 71307,
    SPELL_VILE_GAS_TRIGGERED    = 69240,

    // Malleable Goo
    SPELL_MALLEABLE_GOO_SUMMON  = 72299,
    SPELL_MALLEABLE_GOO         = 72295,
    SPELL_MALLEABLE_GOO_VISUAL  = 75845,
    SPELL_MALLEABLE_GOO_MISSILE = 70852,
};

// talks
enum
{
    SAY_STINKY_DIES             = -1631081,
    SAY_AGGRO                   = -1631082,
    SAY_BLIGHT                  = -1631083,
    SAY_SPORE                   = -1631084,
    SAY_PUNGUENT_BLIGHT         = -1631085,
    SAY_PUNGUENT_BLIGHT_EMOTE   = -1631086,
    SAY_SLAY_1                  = -1631087,
    SAY_SLAY_2                  = -1631088,
    SAY_BERSERK                 = -1631089,
    SAY_DEATH                   = -1631090,
};

static Locations SpawnLoc[]=
{
    {4322.85f, 3164.17f, 389.40f, 3.76f},               // festergut side
    {4311.91f, 3157.42f, 389.00f, 3.62f},               // hacky (LoS problems?) festergut side
    {4391.38f, 3163.71f, 389.40f, 5.8f}                 // rotface side
};
// Festergut
struct MANGOS_DLL_DECL boss_festergutAI : public base_icc_bossAI
{
    boss_festergutAI(Creature *pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    bool m_bAchievFail;

    uint32 m_uiBerserkTimer;
    uint32 m_uiGastricBloatTimer;
    uint32 m_uiInhaleBlightTimer;
    uint32 m_uiGasSporeTimer;
    uint32 m_uiVileGasTimer;
    uint32 m_uiMalleableGooTimer;
    uint32 m_uiCheckTimer;

    void Reset()
    {
        m_uiBerserkTimer = 5 * MINUTE * IN_MILLISECONDS;
        m_uiGastricBloatTimer = 10000;
        m_uiInhaleBlightTimer = 30000;
        m_uiGasSporeTimer = 20000;
        m_uiVileGasTimer = 10000;
        m_uiMalleableGooTimer = urand(15000, 20000);
        m_uiCheckTimer = 1000;
    }

    void Aggro(Unit *pWho)
    {
        // not working as intended currently
        // DoCastSpellIfCan(m_creature, SPELL_GASTRIC_BLOAT, CAST_TRIGGERED);

        DoCastSpellIfCan(m_creature, SPELL_GASEOUS_BLIGHT_1, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_GASEUS_BLIGHT_DUMMY, CAST_TRIGGERED);

        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_FESTERGUT, IN_PROGRESS);

            if (Creature *pProfessor = m_pInstance->GetSingleCreatureFromStorage(NPC_PROFESSOR_PUTRICIDE))
            {
                pProfessor->NearTeleportTo(SpawnLoc[m_bIsHeroic ? 1 : 0].x, SpawnLoc[m_bIsHeroic ? 1 : 0].y, SpawnLoc[m_bIsHeroic ? 1 : 0].z, SpawnLoc[m_bIsHeroic ? 1 : 0].o);
                pProfessor->SetInCombatWithZone();
            }
        }
    }

    void KilledUnit(Unit *pVictim)
    {
        DoScriptText(SAY_SLAY_1 - urand(0, 1), m_creature);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_FESTERGUT, FAIL);

            if (Creature *pProfessor = m_pInstance->GetSingleCreatureFromStorage(NPC_PROFESSOR_PUTRICIDE))
                pProfessor->AI()->EnterEvadeMode();
        }

        DoCastSpellIfCan(m_creature, SPELL_REMOVE_INOCULENT, CAST_TRIGGERED);
        m_creature->RemoveAllAuras();
    }

    void JustDied(Unit *pKiller)
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_FESTERGUT, DONE);

            if (Creature *pProfessor = m_pInstance->GetSingleCreatureFromStorage(NPC_PROFESSOR_PUTRICIDE))
                pProfessor->AI()->EnterEvadeMode();
        }

        DoScriptText(SAY_DEATH, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_REMOVE_INOCULENT, CAST_TRIGGERED);
    }

    void CheckAchievement()
    {
        if (!m_pInstance)
            return;

        Map* pMap = m_creature->GetMap();
        Map::PlayerList const& pPlayers = pMap->GetPlayers();
        if (!pPlayers.isEmpty())
        {
            for (Map::PlayerList::const_iterator itr = pPlayers.begin(); itr != pPlayers.end(); ++itr)
            {
                Unit *pTarget = itr->getSource();
                if (pTarget)
                {
                    SpellAuraHolderPtr holder = pTarget->GetSpellAuraHolder(69291);
                    if (m_bIs25Man && !m_bIsHeroic)
                        holder = pTarget->GetSpellAuraHolder(72101);
                    if (!m_bIs25Man && m_bIsHeroic)
                        holder = pTarget->GetSpellAuraHolder(72102);
                    if (m_bIs25Man && m_bIsHeroic)
                        holder = pTarget->GetSpellAuraHolder(72103);
                    if (holder)
                    {
                        if (holder->GetStackAmount() >= 3)
                        {
                            m_pInstance->SetSpecialAchievementCriteria(TYPE_FLU_SHORT_SHORTAGE, false);
                            m_bAchievFail = true;
                        }
                    }
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Berserk
        if (m_uiBerserkTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
            {
                DoScriptText(SAY_BERSERK, m_creature);
                m_uiBerserkTimer = 5 * MINUTE * IN_MILLISECONDS;
            }
        }
        else
            m_uiBerserkTimer -= uiDiff;

        // Gastric Bloat
        if (m_uiGastricBloatTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_GASTRIC_BLOAT_TRIG) == CAST_OK)
                m_uiGastricBloatTimer = 10000;
        }
        else
            m_uiGastricBloatTimer -= uiDiff;

        // Inhale Blight, Pungent Blight
        if (m_uiInhaleBlightTimer <= uiDiff)
        {
            // check for Pungent Blight
            SpellAuraHolderPtr holder = m_creature->GetSpellAuraHolder(SPELL_INHALED_BLIGHT_10);
            if (!holder)
                holder = m_creature->GetSpellAuraHolder(SPELL_INHALED_BLIGHT_25);
            if (holder)
            {
                if (holder->GetStackAmount() >= 3)
                {
                    // can't inhale anymore...
                    if (DoCastSpellIfCan(m_creature, SPELL_PUNGENT_BLIGHT) == CAST_OK)
                    {
                        DoScriptText(SAY_PUNGUENT_BLIGHT, m_creature);
                        DoScriptText(SAY_PUNGUENT_BLIGHT_EMOTE, m_creature);
                        m_uiInhaleBlightTimer = 35000;
                    }

                    return;
                }
            }

            if (DoCastSpellIfCan(m_creature, SPELL_INHALE_BLIGHT) == CAST_OK)
            {
                if (m_pInstance)
                {
                    if (Creature *pProfessor = m_pInstance->GetSingleCreatureFromStorage(NPC_PROFESSOR_PUTRICIDE))
                        DoScriptText(SAY_BLIGHT, pProfessor);
                }
                m_uiInhaleBlightTimer = 30000;
            }
        }
        else
            m_uiInhaleBlightTimer -= uiDiff;

        // Gas Spore
        if (m_uiGasSporeTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_GAS_SPORE) == CAST_OK)
            {
                DoScriptText(SAY_SPORE, m_creature);
                m_uiGasSporeTimer = 40000;
                if (m_uiVileGasTimer <= 10000)
                    m_uiVileGasTimer = 10000;
            }
        }
        else
            m_uiGasSporeTimer -= uiDiff;

        // Vile Gas
        if (m_uiVileGasTimer <= uiDiff)
        {
            // DoCastSpellIfCan(m_creature, SPELL_VILE_GAS_SUMMON, CAST_TRIGGERED);
            // DoCastSpellIfCan(m_creature, SPELL_VILE_GAS, CAST_TRIGGERED);

            if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
            {
                pTarget->CastSpell(pTarget, SPELL_VILE_GAS_SUMMON_TRIG, true);
                DoCastSpellIfCan(m_creature, SPELL_VILE_GAS, CAST_TRIGGERED);
            }
            m_uiVileGasTimer = 30000;
        }
        else
            m_uiVileGasTimer -= uiDiff;

        // Malleable Goo
        if (m_bIsHeroic)
        {
            if (m_uiMalleableGooTimer <= uiDiff)
            {
                if (Creature *pProfessor = m_pInstance->GetSingleCreatureFromStorage(NPC_PROFESSOR_PUTRICIDE))
                {
                    if (Unit *pTarget = SelectRandomRangedTarget(m_creature))
                    {
                        // pProfessor->CastSpell(m_creature, SPELL_MALLEABLE_GOO_SUMMON, true);
                        // pProfessor->CastSpell(m_creature, SPELL_MALLEABLE_GOO, true);

                        float x, y, z;
                        pTarget->GetPosition(x, y, z);
                        if (Creature *pTmp = m_creature->SummonCreature(NPC_MALLEABLE_GOO, x, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 20000))
                        {
                            pProfessor->CastSpell(pTmp, SPELL_MALLEABLE_GOO_MISSILE, false);
                            m_uiMalleableGooTimer = urand(15000, 20000);
                        }
                    }
                }
            }
            else
                m_uiMalleableGooTimer -= uiDiff;
        }

        // Check achievement
        if (!m_bAchievFail)
        {
            if (m_uiCheckTimer < uiDiff)
            {
                CheckAchievement();
                m_uiCheckTimer = 1000;
            }
            else m_uiCheckTimer = uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_festergut(Creature* pCreature)
{
    return new boss_festergutAI(pCreature);
}

struct MANGOS_DLL_DECL mob_vile_gas_malleable_gooAI : public ScriptedAI
{
    mob_vile_gas_malleable_gooAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        SetCombatMovement(false);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }
    void DamageTaken(Unit *pDealer, uint32 &uiDamage){ uiDamage = 0; }
    void Reset(){}
    void AttackStart(Unit *pWho){}
    void UpdateAI(const uint32 uiDiff){}
};

CreatureAI* GetAI_mob_vile_gas_malleable_goo(Creature* pCreature)
{
    return new mob_vile_gas_malleable_gooAI(pCreature);
}


// Stinky
struct MANGOS_DLL_DECL mob_stinkyAI : public ScriptedAI
{
    mob_stinkyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint32 m_uiDecimateTimer;
    uint32 m_uiMortalwoundTimer;

    void Reset()
    {
        m_uiDecimateTimer = urand(10000, 12000);
        m_uiMortalwoundTimer = urand(2000, 5000);

        m_creature->SetSpeedRate(MOVE_RUN, 1.0f);
        m_creature->SetSpeedRate(MOVE_WALK, 1.0f);
    }

    void JustDied(Unit *killer)
    {
        if (Creature* pTemp = m_pInstance->GetSingleCreatureFromStorage(NPC_FESTERGUT))
            DoScriptText(SAY_STINKY_DIES,pTemp,killer);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Decimate
        if (m_uiDecimateTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_STINKY_DECIMATE) == CAST_OK)
                m_uiDecimateTimer = 32000;
        }
        else
            m_uiDecimateTimer -= uiDiff;

        // Mortal wound
        if (m_uiMortalwoundTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_STINKY_MORTALWOUND) == CAST_OK)
                m_uiMortalwoundTimer = 10000;
        }
        else
            m_uiMortalwoundTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_stinky(Creature *pCreature)
{
    return new mob_stinkyAI(pCreature);
}

void AddSC_boss_festergut()
{
    Script *pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_festergut";
    pNewScript->GetAI = &GetAI_boss_festergut;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_vile_gas_malleable_goo";
    pNewScript->GetAI = &GetAI_mob_vile_gas_malleable_goo;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_stinky";
    pNewScript->GetAI = &GetAI_mob_stinky;
    pNewScript->RegisterSelf();
}

