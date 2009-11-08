/*
 * Copyright (C) 2008 - 2009 Trinity <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "precompiled.h"
#include "azshara_crater.h"

enum Yells
{
    SAY_TEMP = -1234567
};

enum Spells
{
	SPELL_TEMP = 12345
};

enum Events
{
	EVENT_TEMP
};

enum Creatures
{
    NPC_TEMP              = 16506
};

struct TRINITY_DLL_DECL boss_silethAI : public BossAI
{
    boss_silethAI(Creature *c) : BossAI(c, BOSS_SILETH)
	{
		pInstance = c->GetInstanceData();
	}
	
	ScriptedInstance* pInstance;
	
	void Reset()
	{
		if (pInstance)
			pInstance->SetData(PHASE_RASEN,NOT_STARTED);

		 events.ScheduleEvent(EVENT_TEMP, urand(12000,15000));
	}
    void EnterCombat(Unit *who)
    {
        if (pInstance)
			pInstance->SetData(PHASE_RASEN,IN_PROGRESS);
    }

    void MoveInLineOfSight(Unit *who)
    {
      BossAI::MoveInLineOfSight(who);
    }

    void KilledUnit(Unit* victim)
    {

    }

    void JustDied(Unit* Killer)
    {
        _JustDied();

    }
	
	void SpellHit(Unit* caster, const SpellEntry *spell)
    {
       
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        while(uint32 eventId = events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_TEMP:
                   
					events.ScheduleEvent(EVENT_TEMP, urand(12000,15000));
                    return;
            }
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_sileth(Creature* pCreature)
{
    return new boss_silethAI (pCreature);
}

void AddSC_boss_sileth()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_sileth";
    newscript->GetAI = &GetAI_boss_sileth;
    newscript->RegisterSelf();
}


