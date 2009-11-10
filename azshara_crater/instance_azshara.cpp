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

#define MAX_ENCOUNTER          3

/* Azshara crater encounters:
1 - Rasen
2 - Sileth
3 - Xavius*/

enum Models
{
	MODEL_ELF_FORM_FEMALE							= 19112,
	MODEL_ELF_FORM_MALE								= 19116
}
enum Creatures
{
	CREATURE_KRASUS				                    = 50053,
    CREATURE_RASEN				                    = 50051,
	CREATURE_SILETH				                    = 50050,
	CREATURE_XAVIUS				                    = 50052
};
enum GameObjects
{
    GO_TEMP                                         = 191723,
};

struct TRINITY_DLL_DECL instance_azshara : public ScriptedInstance
{
    instance_azshara(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint64 uiKrasus;
    uint64 uiRasen;
    uint64 uiSileth;
    uint64 uiXavius;

	uint64 uiTemp;

    uint8 m_auiEncounter[MAX_ENCOUNTER];

	std::string str_data;

    void Initialize()
    {
        uiKrasus = 0;
        uiRasen = 0;
        uiSileth = 0;
        uiXavius = 0;

		uiTemp = 0;

        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
    }

    bool IsEncounterInProgress() const
    {
        for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS) return true;

        return false;
    }

	void OnPlayerEnter(Player* pPlayer)
	{
		if(pPlayer->getGender() == GENDER_FEMALE)
		{
			pPlayer->SetDisplayId(MODEL_ELF_FORM_FEMALE);
		}else pPlayer->SetDisplayId(MODEL_ELF_FORM_MALE);
	}

    void OnCreatureCreate(Creature* pCreature, bool add)
    {
        switch(pCreature->GetEntry())
        {
            case CREATURE_KRASUS:
                uiKrasus = pCreature->GetGUID();
                break;
            case CREATURE_RASEN:
                uiRasen = pCreature->GetGUID();
                break;
            case CREATURE_SILETH:
                uiSileth = pCreature->GetGUID();
                break;
            case CREATURE_XAVIUS:
                uiXavius = pCreature->GetGUID();
                break;
        }
    }

    void OnGameObjectCreate(GameObject* pGo, bool add)
    {
        switch(pGo->GetEntry())
        {
            case GO_TEMP:
                uiTemp = pGo->GetGUID();
                break;
        }
    }

    void SetData(uint32 type, uint32 data)
    {
        switch(type)
        {
            case PHASE_RASEN:
                m_auiEncounter[1] = data;
                if (data == DONE)
                    SaveToDB();
                break;
			case PHASE_SILETH:
                m_auiEncounter[2] = data;
                if (data == DONE)
                    SaveToDB();
                break;
			case PHASE_XAVIUS:
                m_auiEncounter[3] = data;
                if (data == DONE)
                    SaveToDB();
                break;
        }
    }

    uint32 GetData(uint32 type)
    {
        switch(type)
        {
            case PHASE_SILETH:                  return m_auiEncounter[1];
			case PHASE_RASEN:					return m_auiEncounter[2];
            case PHASE_XAVIUS:					return m_auiEncounter[3];
        }

        return 0;
    }

    uint64 GetData64(uint32 identifier)
    {
        switch(identifier)
        {
            case DATA_KRASUS:                   return uiKrasus;
            case DATA_RASEN:                    return uiRasen;
            case DATA_SILETH:                   return uiSileth;
            case DATA_XAVIUS:                   return uiXavius; 
        }

        return 0;
    }

    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "A C " << m_auiEncounter[0] << " " << m_auiEncounter[1] << " "
            << m_auiEncounter[2] << " " << m_auiEncounter[3];

        str_data = saveStream.str();

        OUT_SAVE_INST_DATA_COMPLETE;
        return str_data;
    }

    void Load(const char* in)
    {
        if (!in)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(in);

        char dataHead1, dataHead2;
        uint16 data0, data1, data2, data3, data4;

        std::istringstream loadStream(in);
        loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3;

        if (dataHead1 == 'A' && dataHead2 == 'C')
        {
            m_auiEncounter[0] = data0;
            m_auiEncounter[1] = data1;
            m_auiEncounter[2] = data2;
			m_auiEncounter[3] = data3;

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (m_auiEncounter[i] == IN_PROGRESS)
                    m_auiEncounter[i] = NOT_STARTED;

        } else OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
    }
};

InstanceData* GetInstanceData_instance_azshara(Map* pMap)
{
    return new instance_azshara(pMap);
}

void AddSC_instance_azshara()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_azshara_crater";
    newscript->GetInstanceData = &GetInstanceData_instance_azshara;
    newscript->RegisterSelf();
}
