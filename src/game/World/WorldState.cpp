/*
* This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
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
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/

#include "WorldState.h"
#include "Chat/ChannelMgr.h"
#include "Globals/SharedDefines.h"
#include "World/World.h"
#include "Maps/MapManager.h"
#include "Entities/Object.h"
#include "GameEvents/GameEventMgr.h"
#include <algorithm>
#include <map>
#include <World/WorldStateDefines.h>

enum
{
    GROMGOLUC_EVENT_1   = 15312,
    GROMGOLUC_EVENT_2   = 15313,
    GROMGOLUC_EVENT_3   = 15314,
    GROMGOLUC_EVENT_4   = 15315,

    OGUC_EVENT_1        = 15318,
    OGUC_EVENT_2        = 15319,
    OGUC_EVENT_3        = 15320,
    OGUC_EVENT_4        = 15321,

    GROMGOLOG_EVENT_1   = 15322,
    GROMGOLOG_EVENT_2   = 15323,
    GROMGOLOG_EVENT_3   = 15324,
    GROMGOLOG_EVENT_4   = 15325,
};

std::map<AQResources, WorldStateID> aqWorldstateMap =
{
    {AQ_PEACEBLOOM, WORLD_STATE_AQ_PEACEBLOOM_NOW},
    {AQ_LEAN_WOLF_STEAK, WORLD_STATE_AQ_LEAN_WOLF_STEAK_NOW},
    {AQ_TIN_BAR, WORLD_STATE_AQ_TIN_BARS_NOW},
    {AQ_WOOL_BANDAGE, WORLD_STATE_AQ_WOOL_BANDAGE_NOW},
    {AQ_FIREBLOOM, WORLD_STATE_AQ_FIREBLOOM_NOW},
    {AQ_HEAVY_LEATHER, WORLD_STATE_AQ_HEAVY_LEATHER_NOW},
    {AQ_MITHRIL_BAR, WORLD_STATE_AQ_MITHRIL_BARS_NOW},
    {AQ_MAGEWEAVE_BANDAGE, WORLD_STATE_AQ_MAGEWEAVE_BANDAGE_NOW},
    {AQ_RUGGED_LEATHER, WORLD_STATE_AQ_RUGGED_LEATHER_NOW},
    {AQ_BAKED_SALMON, WORLD_STATE_AQ_BAKED_SALMON_NOW},
    {AQ_LIGHT_LEATHER, WORLD_STATE_AQ_LIGHT_LEATHER_NOW},
    {AQ_LINEN_BANDAGE, WORLD_STATE_AQ_LINEN_BANDAGE_NOW},
    {AQ_MEDIUM_LEATHER, WORLD_STATE_AQ_MEDIUM_LEATHER_NOW},
    {AQ_STRANGLEKELP, WORLD_STATE_AQ_STRANGLEKELP_NOW},
    {AQ_RAINBOW_FIN_ALBACORE, WORLD_STATE_AQ_RAINBOW_FIN_ALBACORE_NOW},
    {AQ_IRON_BAR, WORLD_STATE_AQ_IRON_BARS_NOW},
    {AQ_ROAST_RAPTOR, WORLD_STATE_AQ_ROAST_RAPTOR_NOW},
    {AQ_SILK_BANDAGE, WORLD_STATE_AQ_SILK_BANDAGE_NOW},
    {AQ_THORIUM_BAR, WORLD_STATE_AQ_THORIUM_BARS_NOW},
    {AQ_ARTHAS_TEARS, WORLD_STATE_AQ_ARTHAS_TEARS_NOW},
    {AQ_COPPER_BAR_ALLY, WORLD_STATE_AQ_COPPER_BARS_ALLY_NOW},
    {AQ_PURPLE_LOTUS_ALLY, WORLD_STATE_AQ_PURPLE_LOTUS_ALLY_NOW},
    {AQ_THICK_LEATHER_ALLY, WORLD_STATE_AQ_THICK_LEATHER_ALLY_NOW},
    {AQ_SPOTTED_YELLOWTAIL_ALLY, WORLD_STATE_AQ_SPOTTED_YELLOWTAIL_ALLY_NOW},
    {AQ_RUNECLOTH_BANDAGE_ALLY, WORLD_STATE_AQ_RUNECLOTH_BANDAGE_ALLY_NOW},
    {AQ_COPPER_BAR_HORDE, WORLD_STATE_AQ_COPPER_BARS_HORDE_NOW},
    {AQ_PURPLE_LOTUS_HORDE, WORLD_STATE_AQ_PURPLE_LOTUS_HORDE_NOW},
    {AQ_THICK_LEATHER_HORDE, WORLD_STATE_AQ_THICK_LEATHER_HORDE_NOW},
    {AQ_SPOTTED_YELLOWTAIL_HORDE, WORLD_STATE_AQ_SPOTTED_YELLOWTAIL_HORDE_NOW},
    {AQ_RUNECLOTH_BANDAGE_HORDE, WORLD_STATE_AQ_RUNECLOTH_BANDAGE_HORDE_NOW},
};

std::vector<std::pair<WorldStateID, uint32>> aqWorldStateTotalsMap =
{
    {WORLD_STATE_AQ_PEACEBLOOM_TOTAL, 96000},
    {WORLD_STATE_AQ_LEAN_WOLF_STEAK_TOTAL, 10000},
    {WORLD_STATE_AQ_TIN_BARS_TOTAL, 22000},
    {WORLD_STATE_AQ_WOOL_BANDAGE_TOTAL, 250000},
    {WORLD_STATE_AQ_FIREBLOOM_TOTAL, 19000},
    {WORLD_STATE_AQ_HEAVY_LEATHER_TOTAL, 60000},
    {WORLD_STATE_AQ_MITHRIL_BARS_TOTAL, 18000},
    {WORLD_STATE_AQ_MAGEWEAVE_BANDAGE_TOTAL, 250000},
    {WORLD_STATE_AQ_RUGGED_LEATHER_TOTAL, 60000},
    {WORLD_STATE_AQ_BAKED_SALMON_TOTAL, 10000},
    {WORLD_STATE_AQ_LIGHT_LEATHER_TOTAL, 180000},
    {WORLD_STATE_AQ_LINEN_BANDAGE_TOTAL, 800000},
    {WORLD_STATE_AQ_MEDIUM_LEATHER_TOTAL, 110000},
    {WORLD_STATE_AQ_STRANGLEKELP_TOTAL, 33000},
    {WORLD_STATE_AQ_RAINBOW_FIN_ALBACORE_TOTAL, 14000},
    {WORLD_STATE_AQ_IRON_BARS_TOTAL, 28000},
    {WORLD_STATE_AQ_ROAST_RAPTOR_TOTAL, 20000},
    {WORLD_STATE_AQ_SILK_BANDAGE_TOTAL, 600000},
    {WORLD_STATE_AQ_THORIUM_BARS_TOTAL, 24000},
    {WORLD_STATE_AQ_ARTHAS_TEARS_TOTAL, 20000},
    {WORLD_STATE_AQ_COPPER_BARS_TOTAL, 45000},
    {WORLD_STATE_AQ_PURPLE_LOTUS_TOTAL, 13000},
    {WORLD_STATE_AQ_THICK_LEATHER_TOTAL, 40000},
    {WORLD_STATE_AQ_SPOTTED_YELLOWTAIL_TOTAL, 8500},
    {WORLD_STATE_AQ_RUNECLOTH_BANDAGE_TOTAL, 200000},
};

WorldState::WorldState() : m_emeraldDragonsState(0xF), m_emeraldDragonsTimer(0), m_emeraldDragonsChosenPositions(4, 0), m_isMagtheridonHeadSpawnedHorde(false), m_isMagtheridonHeadSpawnedAlliance(false),
    m_adalSongOfBattleTimer(0), m_expansion(EXPANSION_WOTLK), m_highlordKruulSpawned(false), m_highlordKruulTimer(0), m_highlordKruulChosenPosition(0)
{
    m_transportStates[GROMGOL_UNDERCITY]    = GROMGOLUC_EVENT_1;
    m_transportStates[GROMGOL_ORGRIMMAR]    = OGUC_EVENT_1;
    m_transportStates[ORGRIMMAR_UNDERCITY]  = GROMGOLOG_EVENT_1;
    memset(m_loveIsInTheAirData.counters, 0, sizeof(LoveIsInTheAir));

    for (auto& data : aqWorldstateMap)
        m_aqWorldstateMapReverse.emplace(data.second, data.first);
}


WorldState::~WorldState()
{
}

void WorldState::Load()
{
    std::unique_ptr<QueryResult> result(CharacterDatabase.Query("SELECT Id, Data FROM world_state"));

    if (result)
    {
        // always one row
        do
        {
            Field* fields = result->Fetch();
            uint32 id = fields[0].GetUInt32();
            std::string data = fields[1].GetCppString();
            std::istringstream loadStream(data);
            switch (id)
            {
                case SAVE_ID_EMERALD_DRAGONS:
                {
                    auto curTime = World::GetCurrentClockTime();
                    uint64 respawnTime;
                    if (data.size())
                    {
                        loadStream >> m_emeraldDragonsState >> respawnTime;
                        for (uint32 i = 0; i < 4; ++i)
                            loadStream >> m_emeraldDragonsChosenPositions[i];
                        if (respawnTime)
                        {
                            TimePoint respawnTimePoint = std::chrono::time_point_cast<std::chrono::milliseconds>(Clock::from_time_t(respawnTime));
                            m_emeraldDragonsTimer = std::chrono::duration_cast<std::chrono::milliseconds>(respawnTimePoint - curTime).count();
                        }
                        else m_emeraldDragonsTimer = 0;
                    }
                    break;
                }
                case SAVE_ID_AHN_QIRAJ:
                {
                    if (data.size())
                    {
                        auto curTime = World::GetCurrentClockTime();
                        uint64 time;
                        try
                        {
                            loadStream >> m_aqData.m_phase >> time;
                            if (time)
                            {
                                TimePoint timePoint = std::chrono::time_point_cast<std::chrono::milliseconds>(Clock::from_time_t(time));
                                m_aqData.m_timer = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - curTime).count();
                            }
                            for (uint32 i = 0; i < RESOURCE_MAX; ++i)
                                loadStream >> m_aqData.m_WarEffortCounters[i];
                            loadStream >> m_aqData.m_phase2Tier;
                        }
                        catch (std::exception& e)
                        {
                            sLog.outError("%s", e.what());
                            memset(m_loveIsInTheAirData.counters, 0, sizeof(LoveIsInTheAir));
                        }
                    }
                    break;
                }
                case SAVE_ID_QUEL_DANAS:
                {
                    if (data.size())
                    {
                        try
                        {
                            loadStream >> m_sunsReachData.m_phase >> m_sunsReachData.m_subphaseMask;
                            for (uint32 i = 0; i < COUNTERS_MAX; ++i)
                                loadStream >> m_sunsReachData.m_sunsReachReclamationCounters[i];
                            loadStream >> m_sunsReachData.m_gate;
                            for (uint32 i = 0; i < COUNTERS_MAX_GATES; ++i)
                                loadStream >> m_sunsReachData.m_gateCounters[i];
                        }
                        catch (std::exception& e)
                        {
                            sLog.outError("%s", e.what());
                            m_sunsReachData.m_phase = 0;
                            m_sunsReachData.m_subphaseMask = 0;
                            m_sunsReachData.m_gate = SUNWELL_ARCHONISUS_GATE3_OPEN;
                            memset(m_sunsReachData.m_sunsReachReclamationCounters, 0, sizeof(m_sunsReachData.m_sunsReachReclamationCounters));
                            memset(m_sunsReachData.m_gateCounters, 0, sizeof(m_sunsReachData.m_gateCounters));
                        }
                    }
                    else
                    {
                        m_sunsReachData.m_phase = 0;
                        m_sunsReachData.m_subphaseMask = 0;
                        m_sunsReachData.m_gate = SUNWELL_ARCHONISUS_GATE3_OPEN;
                        memset(m_sunsReachData.m_sunsReachReclamationCounters, 0, sizeof(m_sunsReachData.m_sunsReachReclamationCounters));
                        memset(m_sunsReachData.m_gateCounters, 0, sizeof(m_sunsReachData.m_gateCounters));
                    }
                    break;
                }
                case SAVE_ID_HIGHLORD_KRUUL:
                {
                    auto curTime = World::GetCurrentClockTime();
                    uint64 respawnTime;
                    if (data.size())
                    {
                        loadStream >> m_highlordKruulTimer >> respawnTime;
                        if (respawnTime)
                        {
                            TimePoint respawnTimePoint = std::chrono::time_point_cast<std::chrono::milliseconds>(Clock::from_time_t(respawnTime));
                            m_highlordKruulTimer = std::chrono::duration_cast<std::chrono::milliseconds>(respawnTimePoint - curTime).count();
                            m_highlordKruulSpawned = true;
                        }
                        else m_highlordKruulTimer = 0;
                    }
                    else
                    {
                        m_highlordKruulSpawned = false;
                        m_highlordKruulTimer = 0;
                    }
                    break;
                }
                case SAVE_ID_EXPANSION_RELEASE:
                    if (data.size())
                    {
                        uint32 expansion; // need to read as number not as character
                        loadStream >> expansion;
                        m_expansion = expansion;
                    }
                    else
                        m_expansion = sWorld.getConfig(CONFIG_UINT32_EXPANSION);
                    break;
                case SAVE_ID_LOVE_IS_IN_THE_AIR:
                    if (data.size())
                    {
                        try
                        {
                            for (uint32 i = 0; i < LOVE_LEADER_MAX; ++i)
                                loadStream >> m_loveIsInTheAirData.counters[i];
                        }
                        catch (std::exception & e)
                        {
                            sLog.outError("%s", e.what());
                            memset(m_loveIsInTheAirData.counters, 0, sizeof(LoveIsInTheAir));
                        }
                    }
                    else
                        memset(m_loveIsInTheAirData.counters, 0, sizeof(LoveIsInTheAir));
                    break;
            }
        }
        while (result->NextRow());
    }
    StartWarEffortEvent();
    SpawnWarEffortGos();
    RespawnEmeraldDragons();
    StartSunsReachPhase(true);
    StartSunwellGatePhase();
    HandleSunsReachSubPhaseTransition(m_sunsReachData.m_subphaseMask, true);
    StartExpansionEvent();
}

void WorldState::Save(SaveIds saveId)
{
    switch (saveId)
    {
        case SAVE_ID_EMERALD_DRAGONS:
        {
            uint64 time;
            if (m_emeraldDragonsTimer)
            {
                auto curTime = World::GetCurrentClockTime();
                auto respawnTime = std::chrono::milliseconds(m_emeraldDragonsTimer) + curTime;
                time = uint64(Clock::to_time_t(respawnTime));
            }
            else time = 0;
            std::string dragonsData = std::to_string(m_emeraldDragonsState) + " " + std::to_string(time);
            for (uint32 i = 0; i < 4; ++i)
                dragonsData += " " + std::to_string(m_emeraldDragonsChosenPositions[i]);
            CharacterDatabase.PExecute("DELETE FROM world_state WHERE Id='%u'", SAVE_ID_EMERALD_DRAGONS);
            CharacterDatabase.PExecute("INSERT INTO world_state(Id,Data) VALUES('%u','%s')", SAVE_ID_EMERALD_DRAGONS, dragonsData.data());
            break;
        }
        case SAVE_ID_AHN_QIRAJ:
        {
            std::string expansionData = m_aqData.GetData();
            SaveHelper(expansionData, SAVE_ID_AHN_QIRAJ);
            break;
        }
        case SAVE_ID_QUEL_DANAS:
        {
            std::string expansionData = m_sunsReachData.GetData();
            SaveHelper(expansionData, SAVE_ID_QUEL_DANAS);
            break;
        }
        case SAVE_ID_EXPANSION_RELEASE:
        {
            std::string expansionData = std::to_string(m_expansion);
            SaveHelper(expansionData, SAVE_ID_EXPANSION_RELEASE);
            break;
        }
        case SAVE_ID_LOVE_IS_IN_THE_AIR:
        {
            std::string loveData;
            for (uint32 i = 0; i < LOVE_LEADER_MAX; ++i)
            {
                if (i != 0)
                    loveData += " ";
                loveData += std::to_string(m_loveIsInTheAirData.counters[i]);
            }
            SaveHelper(loveData, SAVE_ID_LOVE_IS_IN_THE_AIR);
            break;
        }
        default: break;
    }
}

void WorldState::SaveHelper(std::string& stringToSave, SaveIds saveId)
{
    CharacterDatabase.PExecute("DELETE FROM world_state WHERE Id='%u'", saveId);
    CharacterDatabase.PExecute("INSERT INTO world_state(Id,Data) VALUES('%u','%s')", saveId, stringToSave.data());
}

void WorldState::HandleGameObjectUse(GameObject* go, Unit* user)
{
    switch (go->GetEntry())
    {
        case OBJECT_MAGTHERIDONS_HEAD:
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            if (Player* player = dynamic_cast<Player*>(user))
            {
                if (player->GetTeam() == HORDE)
                {
                    m_isMagtheridonHeadSpawnedHorde = true;
                    m_guidMagtheridonHeadHorde = go->GetObjectGuid();
                    BuffMagtheridonTeam(HORDE);
                }
                else
                {
                    m_isMagtheridonHeadSpawnedAlliance = true;
                    m_guidMagtheridonHeadAlliance = go->GetObjectGuid();
                    BuffMagtheridonTeam(ALLIANCE);
                }
            }
            break;
        }
        case OBJECT_EVENT_TRAP_THRALL:
        {
            HandleExternalEvent(CUSTOM_EVENT_LOVE_IS_IN_THE_AIR_LEADER, LOVE_LEADER_THRALL);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, GetLoveIsInTheAirCounter(LOVE_LEADER_THRALL), WORLD_STATE_LOVE_IS_IN_THE_AIR_THRALL);
            uint32 hordeSum = GetLoveIsInTheAirCounter(LOVE_LEADER_CAIRNE) + GetLoveIsInTheAirCounter(LOVE_LEADER_THRALL) + GetLoveIsInTheAirCounter(LOVE_LEADER_SYLVANAS);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, hordeSum, WORLD_STATE_LOVE_IS_IN_THE_AIR_TOTAL_HORDE);
            break;
        }
        case OBJECT_EVENT_TRAP_CAIRNE:
        {
            HandleExternalEvent(CUSTOM_EVENT_LOVE_IS_IN_THE_AIR_LEADER, LOVE_LEADER_CAIRNE);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, GetLoveIsInTheAirCounter(LOVE_LEADER_CAIRNE), WORLD_STATE_LOVE_IS_IN_THE_AIR_CAIRNE);
            uint32 hordeSum = GetLoveIsInTheAirCounter(LOVE_LEADER_CAIRNE) + GetLoveIsInTheAirCounter(LOVE_LEADER_THRALL) + GetLoveIsInTheAirCounter(LOVE_LEADER_SYLVANAS);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, hordeSum, WORLD_STATE_LOVE_IS_IN_THE_AIR_TOTAL_HORDE);
            break;
        }
        case OBJECT_EVENT_TRAP_SYLVANAS:
        {
            HandleExternalEvent(CUSTOM_EVENT_LOVE_IS_IN_THE_AIR_LEADER, LOVE_LEADER_SYLVANAS);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, GetLoveIsInTheAirCounter(LOVE_LEADER_SYLVANAS), WORLD_STATE_LOVE_IS_IN_THE_AIR_SYLVANAS);
            uint32 hordeSum = GetLoveIsInTheAirCounter(LOVE_LEADER_CAIRNE) + GetLoveIsInTheAirCounter(LOVE_LEADER_THRALL) + GetLoveIsInTheAirCounter(LOVE_LEADER_SYLVANAS);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, hordeSum, WORLD_STATE_LOVE_IS_IN_THE_AIR_TOTAL_HORDE);
            break;
        }
        case OBJECT_EVENT_TRAP_BOLVAR:
        {
            HandleExternalEvent(CUSTOM_EVENT_LOVE_IS_IN_THE_AIR_LEADER, LOVE_LEADER_BOLVAR);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, GetLoveIsInTheAirCounter(LOVE_LEADER_BOLVAR), WORLD_STATE_LOVE_IS_IN_THE_AIR_BOLVAR);
            uint32 allianceSum = GetLoveIsInTheAirCounter(LOVE_LEADER_BOLVAR) + GetLoveIsInTheAirCounter(LOVE_LEADER_TYRANDE) + GetLoveIsInTheAirCounter(LOVE_LEADER_MAGNI);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, allianceSum, WORLD_STATE_LOVE_IS_IN_THE_AIR_TOTAL_ALLIANCE);
            break;
        }
        case OBJECT_EVENT_TRAP_MAGNI:
        {
            HandleExternalEvent(CUSTOM_EVENT_LOVE_IS_IN_THE_AIR_LEADER, LOVE_LEADER_MAGNI);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, GetLoveIsInTheAirCounter(LOVE_LEADER_MAGNI), WORLD_STATE_LOVE_IS_IN_THE_AIR_MAGNI);
            uint32 allianceSum = GetLoveIsInTheAirCounter(LOVE_LEADER_BOLVAR) + GetLoveIsInTheAirCounter(LOVE_LEADER_TYRANDE) + GetLoveIsInTheAirCounter(LOVE_LEADER_MAGNI);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, allianceSum, WORLD_STATE_LOVE_IS_IN_THE_AIR_TOTAL_ALLIANCE);
            break;
        }
        case OBJECT_EVENT_TRAP_TYRANDE:
        {
            HandleExternalEvent(CUSTOM_EVENT_LOVE_IS_IN_THE_AIR_LEADER, LOVE_LEADER_TYRANDE);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, GetLoveIsInTheAirCounter(LOVE_LEADER_TYRANDE), WORLD_STATE_LOVE_IS_IN_THE_AIR_TYRANDE);
            uint32 allianceSum = GetLoveIsInTheAirCounter(LOVE_LEADER_BOLVAR) + GetLoveIsInTheAirCounter(LOVE_LEADER_TYRANDE) + GetLoveIsInTheAirCounter(LOVE_LEADER_MAGNI);
            SendWorldstateUpdate(m_loveIsInTheAirMutex, m_loveIsInTheAirCapitalsPlayers, allianceSum, WORLD_STATE_LOVE_IS_IN_THE_AIR_TOTAL_ALLIANCE);
            break;
        }
        default:
            break;
    }
}

void WorldState::HandleGameObjectRevertState(GameObject* go)
{
    switch (go->GetEntry())
    {
        case OBJECT_MAGTHERIDONS_HEAD:
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            if (go->GetObjectGuid() == m_guidMagtheridonHeadHorde)
            {
                m_isMagtheridonHeadSpawnedHorde = false;
                m_guidMagtheridonHeadHorde = ObjectGuid();
                DispelMagtheridonTeam(HORDE);
            }
            else if (go->GetObjectGuid() == m_guidMagtheridonHeadAlliance)
            {
                m_isMagtheridonHeadSpawnedAlliance = false;
                m_guidMagtheridonHeadAlliance = ObjectGuid();
                DispelMagtheridonTeam(ALLIANCE);
            }
            break;
        }
        default:
            break;
    }
}

void WorldState::HandlePlayerEnterZone(Player* player, uint32 zoneId)
{
    switch (zoneId)
    {
        case ZONEID_STORMWIND_CITY:
        case ZONEID_DARNASSUS:
        case ZONEID_IRONFORGE:
        case ZONEID_ORGRIMMAR:
        case ZONEID_THUNDER_BLUFF:
        case ZONEID_UNDERCITY:
        {
            {
                std::lock_guard<std::mutex> guard(m_loveIsInTheAirMutex);
                m_loveIsInTheAirCapitalsPlayers.push_back(player->GetObjectGuid());
            }
            {
                std::lock_guard<std::mutex> guard(m_aqData.m_warEffortMutex);
                m_aqData.m_warEffortWorldstatesPlayers.push_back(player->GetObjectGuid());
            }
            break;
        }
        case ZONEID_HELLFIRE_PENINSULA:
        case ZONEID_HELLFIRE_RAMPARTS:
        case ZONEID_HELLFIRE_CITADEL:
        case ZONEID_BLOOD_FURNACE:
        case ZONEID_SHATTERED_HALLS:
        case ZONEID_MAGTHERIDON_LAIR:
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            if (m_isMagtheridonHeadSpawnedAlliance && player->GetTeam() == ALLIANCE)
                player->CastSpell(nullptr, SPELL_TROLLBANES_COMMAND, TRIGGERED_OLD_TRIGGERED);
            if (m_isMagtheridonHeadSpawnedHorde && player->GetTeam() == HORDE)
                player->CastSpell(nullptr, SPELL_NAZGRELS_FAVOR, TRIGGERED_OLD_TRIGGERED);
            m_magtheridonHeadPlayers.push_back(player->GetObjectGuid());
            break;
        }
        case ZONEID_SHATTRATH:
        case ZONEID_BOTANICA:
        case ZONEID_MECHANAR:
        case ZONEID_ARCATRAZ:
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            if (m_adalSongOfBattleTimer)
                player->CastSpell(nullptr, SPELL_ADAL_SONG_OF_BATTLE, TRIGGERED_OLD_TRIGGERED);
            m_adalSongOfBattlePlayers.push_back(player->GetObjectGuid());
            break;
        }
        case ZONEID_ISLE_OF_QUEL_DANAS:
        case ZONEID_MAGISTERS_TERRACE:
        case ZONEID_SUNWELL_PLATEAU:
        {
            std::lock_guard<std::mutex> guard(m_sunsReachData.m_sunsReachReclamationMutex);
            m_sunsReachData.m_sunsReachReclamationPlayers.push_back(player->GetObjectGuid());
            if (zoneId != ZONEID_SUNWELL_PLATEAU && m_sunsReachData.m_subphaseMask == SUBPHASE_ALL)
                player->CastSpell(nullptr, SPELL_KIRU_SONG_OF_VICTORY, TRIGGERED_OLD_TRIGGERED);
            break;
        }
        default:
            break;
    }
    if (IsHolidayActive(HOLIDAY_FIRE_FESTIVAL)) // On midsummer starting, players can end up without buff but with bonfire in zone - keeping like this for simplicity and optimization
    {
        if (player->GetMap()->IsContinent())
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            m_zonePlayers[zoneId].push_back(player->GetObjectGuid());
        }
        std::lock_guard<std::mutex> guard(m_midsummerMutex);
        if (uint32 entry = IsBonfireInZone(player->GetTeam(), zoneId))
            if (IsBonfireActive(entry))
                player->CastSpell(nullptr, SPELL_BONFIRES_BLESSING, TRIGGERED_OLD_TRIGGERED);
    }
}

void WorldState::HandlePlayerLeaveZone(Player* player, uint32 zoneId)
{
    switch (zoneId)
    {
        case ZONEID_STORMWIND_CITY:
        case ZONEID_DARNASSUS:
        case ZONEID_IRONFORGE:
        case ZONEID_ORGRIMMAR:
        case ZONEID_THUNDER_BLUFF:
        case ZONEID_UNDERCITY:
        {
            {
                std::lock_guard<std::mutex> guard(m_loveIsInTheAirMutex);
                auto position = std::find(m_loveIsInTheAirCapitalsPlayers.begin(), m_loveIsInTheAirCapitalsPlayers.end(), player->GetObjectGuid());
                if (position != m_loveIsInTheAirCapitalsPlayers.end())
                    m_loveIsInTheAirCapitalsPlayers.erase(position);
            }
            {
                std::lock_guard<std::mutex> guard(m_aqData.m_warEffortMutex);
                auto position = std::find(m_aqData.m_warEffortWorldstatesPlayers.begin(), m_aqData.m_warEffortWorldstatesPlayers.end(), player->GetObjectGuid());
                if (position != m_aqData.m_warEffortWorldstatesPlayers.end())
                    m_aqData.m_warEffortWorldstatesPlayers.erase(position);
            }
            break;
        }
        case ZONEID_HELLFIRE_PENINSULA:
        case ZONEID_HELLFIRE_RAMPARTS:
        case ZONEID_HELLFIRE_CITADEL:
        case ZONEID_BLOOD_FURNACE:
        case ZONEID_SHATTERED_HALLS:
        case ZONEID_MAGTHERIDON_LAIR:
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            if (player->GetTeam() == ALLIANCE)
                player->RemoveAurasDueToSpell(SPELL_TROLLBANES_COMMAND);
            if (player->GetTeam() == HORDE)
                player->RemoveAurasDueToSpell(SPELL_NAZGRELS_FAVOR);
            auto position = std::find(m_magtheridonHeadPlayers.begin(), m_magtheridonHeadPlayers.end(), player->GetObjectGuid());
            if (position != m_magtheridonHeadPlayers.end()) // == myVector.end() means the element was not found
                m_magtheridonHeadPlayers.erase(position);
            break;
        }
        case ZONEID_SHATTRATH:
        case ZONEID_BOTANICA:
        case ZONEID_MECHANAR:
        case ZONEID_ARCATRAZ:
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            player->RemoveAurasDueToSpell(SPELL_ADAL_SONG_OF_BATTLE);
            auto position = std::find(m_adalSongOfBattlePlayers.begin(), m_adalSongOfBattlePlayers.end(), player->GetObjectGuid());
            if (position != m_adalSongOfBattlePlayers.end()) // == myVector.end() means the element was not found
                m_adalSongOfBattlePlayers.erase(position);
            break;
        }
        case ZONEID_ISLE_OF_QUEL_DANAS:
        case ZONEID_MAGISTERS_TERRACE:
        case ZONEID_SUNWELL_PLATEAU:
        {
            std::lock_guard<std::mutex> guard(m_sunsReachData.m_sunsReachReclamationMutex);
            player->RemoveAurasDueToSpell(SPELL_KIRU_SONG_OF_VICTORY);
            auto position = std::find(m_sunsReachData.m_sunsReachReclamationPlayers.begin(), m_sunsReachData.m_sunsReachReclamationPlayers.end(), player->GetObjectGuid());
            if (position != m_sunsReachData.m_sunsReachReclamationPlayers.end())
                m_sunsReachData.m_sunsReachReclamationPlayers.erase(position);
            break;
        }
        default:
            break;
    }
    if (IsHolidayActive(HOLIDAY_FIRE_FESTIVAL))
    {
        if (!player->IsInWorld() || player->GetMap()->IsContinent())
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            auto position = std::find(m_zonePlayers[zoneId].begin(), m_zonePlayers[zoneId].end(), player->GetObjectGuid());
            if (position != m_zonePlayers[zoneId].end())
                m_zonePlayers[zoneId].erase(position);
        }
        player->RemoveAurasDueToSpell(SPELL_BONFIRES_BLESSING);
    }
}

void WorldState::HandlePlayerEnterArea(Player* player, uint32 areaId)
{
    switch (areaId)
    {
        case AREAID_SKYGUARD_OUTPOST:
        case AREAID_SHARTUUL_TRANSPORTER:
        case AREAID_DEATHS_DOOR:
        case AREAID_THERAMORE_ISLE:
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            m_areaPlayers[areaId].push_back(player->GetObjectGuid());
            break;
        }
        default: break;
    }
}

void WorldState::HandlePlayerLeaveArea(Player* player, uint32 areaId)
{
    switch (areaId)
    {
        case AREAID_SKYGUARD_OUTPOST:
        case AREAID_SHARTUUL_TRANSPORTER:
        case AREAID_DEATHS_DOOR:
        case AREAID_THERAMORE_ISLE:
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            auto position = std::find(m_areaPlayers[areaId].begin(), m_areaPlayers[areaId].end(), player->GetObjectGuid());
            if (position != m_areaPlayers[areaId].end()) // == myVector.end() means the element was not found
                m_areaPlayers[areaId].erase(position);
            break;
        }
        default: break;
    }
}

bool WorldState::IsConditionFulfilled(uint32 conditionId, uint32 state) const
{
    if (conditionId == WAR_EFFORT_DAYS_LEFT)
        return m_aqData.GetDaysRemaining() == state;

    auto itr = m_aqWorldstateMapReverse.find(conditionId);
    if (itr != m_aqWorldstateMapReverse.end())
    {
        uint32 id = (*itr).second;
        if (id >= aqWorldStateTotalsMap.size())
            id -= 5;
        return m_aqData.m_WarEffortCounters[id] == aqWorldStateTotalsMap[id].second;
    }

    return m_transportStates.at(conditionId) == state;
}

void WorldState::HandleConditionStateChange(uint32 conditionId, uint32 state)
{
    m_transportStates[conditionId] = state;
}

void WorldState::BuffMagtheridonTeam(Team team)
{
    for (ObjectGuid& guid : m_magtheridonHeadPlayers)
    {
        if (Player* player = sObjectMgr.GetPlayer(guid))
        {
            if (team == ALLIANCE && player->GetTeam() == ALLIANCE)
            {
                player->GetMap()->GetMessager().AddMessage([guid](Map* map) -> void
                {
                    if (Player* player = map->GetPlayer(guid))
                        player->CastSpell(player, SPELL_TROLLBANES_COMMAND, TRIGGERED_OLD_TRIGGERED);
                });
            }
            if (team == HORDE && player->GetTeam() == HORDE)
            {
                player->GetMap()->GetMessager().AddMessage([guid](Map* map) -> void
                {
                    if (Player* player = map->GetPlayer(guid))
                        player->CastSpell(player, SPELL_NAZGRELS_FAVOR, TRIGGERED_OLD_TRIGGERED);
                });
            }
        }
    }
}

void WorldState::DispelMagtheridonTeam(Team team)
{
    for (ObjectGuid& guid : m_magtheridonHeadPlayers)
    {
        if (Player* player = sObjectMgr.GetPlayer(guid))
        {
            if (team == ALLIANCE && player->GetTeam() == ALLIANCE)
            {
                player->GetMap()->GetMessager().AddMessage([guid](Map* map) -> void
                {
                    if (Player* player = map->GetPlayer(guid))
                        player->RemoveAurasDueToSpell(SPELL_TROLLBANES_COMMAND);
                });
            }
            if (team == HORDE && player->GetTeam() == HORDE)
            {
                player->GetMap()->GetMessager().AddMessage([guid](Map* map) -> void
                {
                    if (Player* player = map->GetPlayer(guid))
                        player->RemoveAurasDueToSpell(SPELL_NAZGRELS_FAVOR);
                });
            }
        }
    }
}

void WorldState::HandleExternalEvent(uint32 eventId, uint32 param)
{
    std::lock_guard<std::mutex> guard(m_mutex);

    switch (eventId)
    {
        case CUSTOM_EVENT_YSONDRE_DIED:
        case CUSTOM_EVENT_LETHON_DIED:
        case CUSTOM_EVENT_EMERISS_DIED:
        case CUSTOM_EVENT_TAERAR_DIED:
        {
            uint32 bossId;
            switch (eventId)
            {
                case CUSTOM_EVENT_YSONDRE_DIED: bossId = 0; break;
                case CUSTOM_EVENT_LETHON_DIED:  bossId = 1; break;
                case CUSTOM_EVENT_EMERISS_DIED: bossId = 2; break;
                case CUSTOM_EVENT_TAERAR_DIED:  bossId = 3; break;
            }
            m_emeraldDragonsState |= 1 << bossId;
            if (m_emeraldDragonsState == 0xF)
                m_emeraldDragonsTimer = 30 * HOUR * IN_MILLISECONDS;
            Save(SAVE_ID_EMERALD_DRAGONS); // save to DB right away
            break;
        }
        case CUSTOM_EVENT_HIGHLORD_KRUUL_DIED:
        {
            m_highlordKruulSpawned = false;
            m_highlordKruulTimer = urand(4 * HOUR * IN_MILLISECONDS, 6 * HOUR * IN_MILLISECONDS);
            Save(SAVE_ID_HIGHLORD_KRUUL); // save to DB right away
            break;
        }
        case CUSTOM_EVENT_LOVE_IS_IN_THE_AIR_LEADER:
        {
            MANGOS_ASSERT(param < LOVE_LEADER_MAX);
            ++m_loveIsInTheAirData.counters[param];
            Save(SAVE_ID_LOVE_IS_IN_THE_AIR);
            break;
        }
        case CUSTOM_EVENT_ADALS_SONG_OF_BATTLE:
            m_adalSongOfBattleTimer = 120 * MINUTE * IN_MILLISECONDS; // Two hours duration
            BuffAdalsSongOfBattle();
            break;
    }
}

void WorldState::Update(const uint32 diff)
{
    std::lock_guard<std::mutex> guard(m_mutex);

    if (m_adalSongOfBattleTimer)
    {
        if (m_adalSongOfBattleTimer <= diff)
        {
            m_adalSongOfBattleTimer = 0;
            DispelAdalsSongOfBattle();
        }
        else m_adalSongOfBattleTimer -= diff;
    }

    if (m_emeraldDragonsTimer)
    {
        if (m_emeraldDragonsTimer <= diff)
        {
            m_emeraldDragonsTimer = 0;
            RespawnEmeraldDragons();
        }
        else m_emeraldDragonsTimer -= diff;
    }

    if (m_aqData.m_timer)
    {
        if (m_aqData.m_timer <= diff)
        {
            m_aqData.m_timer = 0;
            HandleWarEffortPhaseTransition(m_aqData.m_phase + 1);
        }
        else m_aqData.m_timer -= diff;

        if (m_aqData.m_phase == PHASE_2_TRANSPORTING_RESOURCES)
        {
            uint32 remainingDays = m_aqData.m_timer % (DAY * IN_MILLISECONDS);
            if (remainingDays < m_aqData.m_phase2Tier)
                ChangeWarEffortPhase2Tier(remainingDays);
        }
    }
}

void WorldState::SendWorldstateUpdate(std::mutex& mutex, GuidVector const& guids, uint32 value, uint32 worldStateId)
{
    std::lock_guard<std::mutex> guard(mutex);
    for (ObjectGuid const& guid : guids)
        if (Player* player = sObjectMgr.GetPlayer(guid))
            player->SendUpdateWorldState(worldStateId, value);
}

void WorldState::BuffAdalsSongOfBattle()
{
    for (ObjectGuid& guid : m_adalSongOfBattlePlayers)
    {
        if (Player* player = sObjectMgr.GetPlayer(guid))
        {
            player->GetMap()->GetMessager().AddMessage([guid](Map* map) -> void
            {
                if (Player* player = map->GetPlayer(guid))
                    player->CastSpell(player, SPELL_ADAL_SONG_OF_BATTLE, TRIGGERED_OLD_TRIGGERED);
            });
        }
    }
}

void WorldState::DispelAdalsSongOfBattle()
{
    for (ObjectGuid& guid : m_adalSongOfBattlePlayers)
    {
        if (Player* player = sObjectMgr.GetPlayer(guid))
        {
            player->GetMap()->GetMessager().AddMessage([guid](Map* map) -> void
            {
                if (Player* player = map->GetPlayer(guid))
                    player->RemoveAurasDueToSpell(SPELL_ADAL_SONG_OF_BATTLE);
            });
        }
    }
}

void WorldState::ExecuteOnAreaPlayers(uint32 areaId, std::function<void(Player*)> executor)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    for (ObjectGuid guid : m_areaPlayers[areaId])
        if (Player* player = sObjectMgr.GetPlayer(guid))
            executor(player);
}

void WorldState::ExecuteOnZonePlayers(uint32 zoneId, std::function<void(Player*)> executor)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    for (ObjectGuid guid : m_zonePlayers[zoneId])
        if (Player* player = sObjectMgr.GetPlayer(guid))
            executor(player);
}

// Emerald Dragons
enum EmeraldDragons : uint32
{
    NPC_YSONDRE = 14887,
    NPC_LETHON  = 14888,
    NPC_EMERISS = 14889,
    NPC_TAERAR  = 14890,
};

static float emeraldDragonSpawns[4][4] =
{
    {-10428.8f, -392.176f, 43.7411f, 0.932375f},
    {753.619f, -4012.f, 94.043f, 3.193f},
    {-2872.66f, 1884.25f, 52.7336f, 2.6529f},
    {3301.05f, -3732.57f, 173.544f, 2.9147f}
};

static uint32 pathIds[4] =
{
    1,0,0,0
};

bool WorldState::IsDragonSpawned(uint32 entry)
{
    return ((1 << (entry - NPC_YSONDRE)) & m_emeraldDragonsState) == 0;
}

void WorldState::RespawnEmeraldDragons()
{
    if (m_emeraldDragonsState == 0xF)
    {
        std::vector<uint32> ids = { NPC_YSONDRE, NPC_LETHON, NPC_EMERISS, NPC_TAERAR };
        for (uint32 i = 3; i > 0; --i)
        {
            uint32 random = urand(0, i);
            m_emeraldDragonsChosenPositions[3 - i] = ids[random];
            ids.erase(std::remove(ids.begin(), ids.end(), ids[random]), ids.end());
        }
        m_emeraldDragonsChosenPositions[3] = ids[0];
        m_emeraldDragonsState = 0;
        Save(SAVE_ID_EMERALD_DRAGONS);
    }
    sMapMgr.DoForAllMapsWithMapId(0, [&](Map* map)
    {
        if (IsDragonSpawned(m_emeraldDragonsChosenPositions[0]))
        {
            if (Creature* duskwoodDragon = WorldObject::SummonCreature(TempSpawnSettings(nullptr, m_emeraldDragonsChosenPositions[0], emeraldDragonSpawns[0][0], emeraldDragonSpawns[0][1], emeraldDragonSpawns[0][2], emeraldDragonSpawns[0][3], TEMPSPAWN_DEAD_DESPAWN, 0, false, false, pathIds[0]), map, 1))
                duskwoodDragon->GetMotionMaster()->MoveWaypoint(pathIds[0]);
        }
        if (IsDragonSpawned(m_emeraldDragonsChosenPositions[1]))
            WorldObject::SummonCreature(TempSpawnSettings(nullptr, m_emeraldDragonsChosenPositions[1], emeraldDragonSpawns[1][0], emeraldDragonSpawns[1][1], emeraldDragonSpawns[1][2], emeraldDragonSpawns[1][3], TEMPSPAWN_DEAD_DESPAWN, 0, false, false, pathIds[1]), map, 1);
    });
    sMapMgr.DoForAllMapsWithMapId(1, [&](Map* map)
    {
        if (IsDragonSpawned(m_emeraldDragonsChosenPositions[2]))
            WorldObject::SummonCreature(TempSpawnSettings(nullptr, m_emeraldDragonsChosenPositions[2], emeraldDragonSpawns[2][0], emeraldDragonSpawns[2][1], emeraldDragonSpawns[2][2], emeraldDragonSpawns[2][3], TEMPSPAWN_DEAD_DESPAWN, 0, false, false, pathIds[2]), map, 1);
        if (IsDragonSpawned(m_emeraldDragonsChosenPositions[3]))
            WorldObject::SummonCreature(TempSpawnSettings(nullptr, m_emeraldDragonsChosenPositions[3], emeraldDragonSpawns[3][0], emeraldDragonSpawns[3][1], emeraldDragonSpawns[3][2], emeraldDragonSpawns[3][3], TEMPSPAWN_DEAD_DESPAWN, 0, false, false, pathIds[3]), map, 1);
    });
}

void WorldState::AddWarEffortProgress(AQResources resource, uint32 count)
{
    std::lock_guard<std::mutex> guard(m_aqData.m_warEffortMutex);
    if (m_aqData.m_phase != PHASE_1_GATHERING_RESOURCES)
        return;
    m_aqData.m_WarEffortCounters[resource] += count;
    Save(SAVE_ID_AHN_QIRAJ);
    for (ObjectGuid& guid : m_aqData.m_warEffortWorldstatesPlayers)
        if (Player* player = sObjectMgr.GetPlayer(guid))
            player->SendUpdateWorldState(aqWorldstateMap[resource], m_aqData.m_WarEffortCounters[resource]);
    uint32 id = uint32(resource);
    if (id >= aqWorldStateTotalsMap.size())
        id -= 5;
    ChangeWarEffortGoSpawns(resource);
    if (m_aqData.m_WarEffortCounters[resource] >= aqWorldStateTotalsMap[id].second) // fulfilled this condition - check all
    {
        bool success = true;
        for (uint32 i = 0; i < RESOURCE_MAX; ++i)
        {
            uint32 id = i > RESOURCE_UNIQUE_MAX ? i - 5 : i;
            if (m_aqData.m_WarEffortCounters[i] < aqWorldStateTotalsMap[id].second)
            {
                success = false;
                break;
            }
        }
        if (success)
            HandleWarEffortPhaseTransition(PHASE_2_TRANSPORTING_RESOURCES);
    }
}

void WorldState::HandleWarEffortPhaseTransition(uint32 newPhase)
{
    StopWarEffortEvent();
    m_aqData.m_phase = newPhase;
    switch (m_aqData.m_phase)
    {
        case PHASE_2_TRANSPORTING_RESOURCES:
            m_aqData.m_phase = PHASE_2_TRANSPORTING_RESOURCES;
            m_aqData.m_timer = 5 * DAY * IN_MILLISECONDS;
            {
                std::lock_guard<std::mutex> guard(m_aqData.m_warEffortMutex);
                for (ObjectGuid& guid : m_aqData.m_warEffortWorldstatesPlayers)
                    if (Player* player = sObjectMgr.GetPlayer(guid))
                        player->SendUpdateWorldState(WORLD_STATE_AQ_DAYS_LEFT, m_aqData.GetDaysRemaining());
            }
            break;
        case PHASE_4_10_HOUR_WAR:
            m_aqData.m_phase = PHASE_4_10_HOUR_WAR;
            m_aqData.m_timer = 10 * HOUR * IN_MILLISECONDS;
            break;
        default: break;
    }
    StartWarEffortEvent();
}

void WorldState::StartWarEffortEvent()
{
    switch (m_aqData.m_phase)
    {
        case PHASE_1_GATHERING_RESOURCES: sGameEventMgr.StartEvent(GAME_EVENT_AHN_QIRAJ_EFFORT_PHASE_1); break;
        case PHASE_2_TRANSPORTING_RESOURCES: sGameEventMgr.StartEvent(GAME_EVENT_AHN_QIRAJ_EFFORT_PHASE_2); break;
        case PHASE_3_GONG_TIME: sGameEventMgr.StartEvent(GAME_EVENT_AHN_QIRAJ_EFFORT_PHASE_3); break;
        case PHASE_4_10_HOUR_WAR: sGameEventMgr.StartEvent(GAME_EVENT_AHN_QIRAJ_EFFORT_PHASE_4); break;
        case PHASE_5_DONE: sGameEventMgr.StartEvent(GAME_EVENT_AHN_QIRAJ_EFFORT_PHASE_5); break;
        default: break;
    }
}

void WorldState::StopWarEffortEvent()
{
    switch (m_aqData.m_phase)
    {
        case PHASE_1_GATHERING_RESOURCES: sGameEventMgr.StopEvent(GAME_EVENT_AHN_QIRAJ_EFFORT_PHASE_1); break;
        case PHASE_2_TRANSPORTING_RESOURCES: sGameEventMgr.StopEvent(GAME_EVENT_AHN_QIRAJ_EFFORT_PHASE_2); break;
        case PHASE_3_GONG_TIME: sGameEventMgr.StopEvent(GAME_EVENT_AHN_QIRAJ_EFFORT_PHASE_3); break;
        case PHASE_4_10_HOUR_WAR: sGameEventMgr.StopEvent(GAME_EVENT_AHN_QIRAJ_EFFORT_PHASE_4); break;
        case PHASE_5_DONE: sGameEventMgr.StopEvent(GAME_EVENT_AHN_QIRAJ_EFFORT_PHASE_5); break;
        default: break;
    }
}

void WorldState::SpawnWarEffortGos()
{
    if (m_aqData.m_phase > PHASE_2_TRANSPORTING_RESOURCES)
        return;

    for (uint32 i = 0; i < RESOURCE_MAX; ++i)
        ChangeWarEffortGoSpawns(AQResources(i), m_aqData.m_phase == PHASE_2_TRANSPORTING_RESOURCES ? m_aqData.m_phase2Tier : -1);
}

enum AQResourceTier : uint32
{
    RESOURCE_TIER_0,
    RESOURCE_TIER_1,
    RESOURCE_TIER_2,
    RESOURCE_TIER_3,
    RESOURCE_TIER_4,
    RESOURCE_TIER_5,
};

struct WarEffortSpawn
{
    AQResourceGroup resourceGroup;
    AQResourceTier resourceTier;
    uint32 dbGuid;
    Team team;
};

enum
{
    WAR_EFFORT_DB_GUID_PREFIX = 155000,

    MAP_AZEROTH = 0,
    MAP_KALIMDOR = 1,
};

static std::map<std::pair<AQResourceGroup, Team>, std::vector<AQResources>> teamResourcesMap
{
    { {RESOURCE_GROUP_SKINNING, ALLIANCE}, {AQ_THICK_LEATHER_ALLY, AQ_LIGHT_LEATHER, AQ_MEDIUM_LEATHER} },
    { {RESOURCE_GROUP_COOKING, ALLIANCE}, {AQ_RAINBOW_FIN_ALBACORE, AQ_ROAST_RAPTOR, AQ_SPOTTED_YELLOWTAIL_ALLY} },
    { {RESOURCE_GROUP_HERBS, ALLIANCE}, {AQ_STRANGLEKELP, AQ_ARTHAS_TEARS, AQ_PURPLE_LOTUS_ALLY} },
    { {RESOURCE_GROUP_BANDAGES, ALLIANCE}, {AQ_LINEN_BANDAGE, AQ_SILK_BANDAGE, AQ_RUNECLOTH_BANDAGE_ALLY} },
    { {RESOURCE_GROUP_BARS, ALLIANCE}, {AQ_IRON_BAR, AQ_THORIUM_BAR, AQ_COPPER_BAR_ALLY} },
    { {RESOURCE_GROUP_SKINNING, HORDE}, {AQ_HEAVY_LEATHER, AQ_RUGGED_LEATHER, AQ_THICK_LEATHER_HORDE} },
    { {RESOURCE_GROUP_COOKING, HORDE}, {AQ_LEAN_WOLF_STEAK, AQ_BAKED_SALMON, AQ_SPOTTED_YELLOWTAIL_HORDE} },
    { {RESOURCE_GROUP_HERBS, HORDE}, {AQ_PEACEBLOOM, AQ_FIREBLOOM, AQ_PURPLE_LOTUS_HORDE} },
    { {RESOURCE_GROUP_BANDAGES, HORDE}, {AQ_WOOL_BANDAGE, AQ_MAGEWEAVE_BANDAGE, AQ_RUNECLOTH_BANDAGE_HORDE} },
    { {RESOURCE_GROUP_BARS, HORDE}, {AQ_TIN_BAR, AQ_MITHRIL_BAR, AQ_COPPER_BAR_HORDE} }
};

static WarEffortSpawn warEffortSpawns[] =
{
    { RESOURCE_GROUP_SKINNING, RESOURCE_TIER_1, WAR_EFFORT_DB_GUID_PREFIX + 10, ALLIANCE},
    { RESOURCE_GROUP_BANDAGES, RESOURCE_TIER_1, WAR_EFFORT_DB_GUID_PREFIX + 11, ALLIANCE},
    { RESOURCE_GROUP_BARS,     RESOURCE_TIER_1, WAR_EFFORT_DB_GUID_PREFIX + 12, ALLIANCE},
    { RESOURCE_GROUP_COOKING,  RESOURCE_TIER_1, WAR_EFFORT_DB_GUID_PREFIX + 13, ALLIANCE},
    { RESOURCE_GROUP_HERBS,    RESOURCE_TIER_1, WAR_EFFORT_DB_GUID_PREFIX + 14, ALLIANCE},
    { RESOURCE_GROUP_SKINNING, RESOURCE_TIER_2, WAR_EFFORT_DB_GUID_PREFIX + 20, ALLIANCE},
    { RESOURCE_GROUP_BANDAGES, RESOURCE_TIER_2, WAR_EFFORT_DB_GUID_PREFIX + 21, ALLIANCE},
    { RESOURCE_GROUP_BARS,     RESOURCE_TIER_2, WAR_EFFORT_DB_GUID_PREFIX + 22, ALLIANCE},
    { RESOURCE_GROUP_COOKING,  RESOURCE_TIER_2, WAR_EFFORT_DB_GUID_PREFIX + 23, ALLIANCE},
    { RESOURCE_GROUP_HERBS,    RESOURCE_TIER_2, WAR_EFFORT_DB_GUID_PREFIX + 24, ALLIANCE},
    { RESOURCE_GROUP_SKINNING, RESOURCE_TIER_3, WAR_EFFORT_DB_GUID_PREFIX + 30, ALLIANCE},
    { RESOURCE_GROUP_BANDAGES, RESOURCE_TIER_3, WAR_EFFORT_DB_GUID_PREFIX + 31, ALLIANCE},
    { RESOURCE_GROUP_BARS,     RESOURCE_TIER_3, WAR_EFFORT_DB_GUID_PREFIX + 32, ALLIANCE},
    { RESOURCE_GROUP_COOKING,  RESOURCE_TIER_3, WAR_EFFORT_DB_GUID_PREFIX + 33, ALLIANCE},
    { RESOURCE_GROUP_HERBS,    RESOURCE_TIER_3, WAR_EFFORT_DB_GUID_PREFIX + 34, ALLIANCE},
    { RESOURCE_GROUP_SKINNING, RESOURCE_TIER_4, WAR_EFFORT_DB_GUID_PREFIX + 40, ALLIANCE},
    { RESOURCE_GROUP_BANDAGES, RESOURCE_TIER_4, WAR_EFFORT_DB_GUID_PREFIX + 41, ALLIANCE},
    { RESOURCE_GROUP_BARS,     RESOURCE_TIER_4, WAR_EFFORT_DB_GUID_PREFIX + 42, ALLIANCE},
    { RESOURCE_GROUP_COOKING,  RESOURCE_TIER_4, WAR_EFFORT_DB_GUID_PREFIX + 43, ALLIANCE},
    { RESOURCE_GROUP_HERBS,    RESOURCE_TIER_4, WAR_EFFORT_DB_GUID_PREFIX + 44, ALLIANCE},
    { RESOURCE_GROUP_SKINNING, RESOURCE_TIER_5, WAR_EFFORT_DB_GUID_PREFIX + 50, ALLIANCE},
    { RESOURCE_GROUP_BANDAGES, RESOURCE_TIER_5, WAR_EFFORT_DB_GUID_PREFIX + 51, ALLIANCE},
    { RESOURCE_GROUP_BARS,     RESOURCE_TIER_5, WAR_EFFORT_DB_GUID_PREFIX + 52, ALLIANCE},
    { RESOURCE_GROUP_COOKING,  RESOURCE_TIER_5, WAR_EFFORT_DB_GUID_PREFIX + 53, ALLIANCE},
    { RESOURCE_GROUP_HERBS,    RESOURCE_TIER_5, WAR_EFFORT_DB_GUID_PREFIX + 54, ALLIANCE},
    { RESOURCE_GROUP_SKINNING, RESOURCE_TIER_1, WAR_EFFORT_DB_GUID_PREFIX + 510, HORDE},
    { RESOURCE_GROUP_BANDAGES, RESOURCE_TIER_1, WAR_EFFORT_DB_GUID_PREFIX + 511, HORDE},
    { RESOURCE_GROUP_BARS,     RESOURCE_TIER_1, WAR_EFFORT_DB_GUID_PREFIX + 512, HORDE},
    { RESOURCE_GROUP_COOKING,  RESOURCE_TIER_1, WAR_EFFORT_DB_GUID_PREFIX + 513, HORDE},
    { RESOURCE_GROUP_HERBS,    RESOURCE_TIER_1, WAR_EFFORT_DB_GUID_PREFIX + 514, HORDE},
    { RESOURCE_GROUP_SKINNING, RESOURCE_TIER_2, WAR_EFFORT_DB_GUID_PREFIX + 520, HORDE},
    { RESOURCE_GROUP_BANDAGES, RESOURCE_TIER_2, WAR_EFFORT_DB_GUID_PREFIX + 521, HORDE},
    { RESOURCE_GROUP_BARS,     RESOURCE_TIER_2, WAR_EFFORT_DB_GUID_PREFIX + 522, HORDE},
    { RESOURCE_GROUP_COOKING,  RESOURCE_TIER_2, WAR_EFFORT_DB_GUID_PREFIX + 523, HORDE},
    { RESOURCE_GROUP_HERBS,    RESOURCE_TIER_2, WAR_EFFORT_DB_GUID_PREFIX + 524, HORDE},
    { RESOURCE_GROUP_SKINNING, RESOURCE_TIER_3, WAR_EFFORT_DB_GUID_PREFIX + 530, HORDE},
    { RESOURCE_GROUP_BANDAGES, RESOURCE_TIER_3, WAR_EFFORT_DB_GUID_PREFIX + 531, HORDE},
    { RESOURCE_GROUP_BARS,     RESOURCE_TIER_3, WAR_EFFORT_DB_GUID_PREFIX + 532, HORDE},
    { RESOURCE_GROUP_COOKING,  RESOURCE_TIER_3, WAR_EFFORT_DB_GUID_PREFIX + 533, HORDE},
    { RESOURCE_GROUP_HERBS,    RESOURCE_TIER_3, WAR_EFFORT_DB_GUID_PREFIX + 534, HORDE},
    { RESOURCE_GROUP_SKINNING, RESOURCE_TIER_4, WAR_EFFORT_DB_GUID_PREFIX + 540, HORDE},
    { RESOURCE_GROUP_BANDAGES, RESOURCE_TIER_4, WAR_EFFORT_DB_GUID_PREFIX + 541, HORDE},
    { RESOURCE_GROUP_BARS,     RESOURCE_TIER_4, WAR_EFFORT_DB_GUID_PREFIX + 542, HORDE},
    { RESOURCE_GROUP_COOKING,  RESOURCE_TIER_4, WAR_EFFORT_DB_GUID_PREFIX + 543, HORDE},
    { RESOURCE_GROUP_HERBS,    RESOURCE_TIER_4, WAR_EFFORT_DB_GUID_PREFIX + 544, HORDE},
    { RESOURCE_GROUP_SKINNING, RESOURCE_TIER_5, WAR_EFFORT_DB_GUID_PREFIX + 550, HORDE},
    { RESOURCE_GROUP_BANDAGES, RESOURCE_TIER_5, WAR_EFFORT_DB_GUID_PREFIX + 551, HORDE},
    { RESOURCE_GROUP_BARS,     RESOURCE_TIER_5, WAR_EFFORT_DB_GUID_PREFIX + 552, HORDE},
    { RESOURCE_GROUP_COOKING,  RESOURCE_TIER_5, WAR_EFFORT_DB_GUID_PREFIX + 553, HORDE},
    { RESOURCE_GROUP_HERBS,    RESOURCE_TIER_5, WAR_EFFORT_DB_GUID_PREFIX + 554, HORDE},
};

AQResourceTier GetResourceTier(uint32 counter, uint32 max)
{
    if (max * 90 / 100 < counter)
        return RESOURCE_TIER_5;
    if (max * 70 / 100 < counter)
        return RESOURCE_TIER_4;
    if (max * 50 / 100 < counter)
        return RESOURCE_TIER_3;
    if (max * 30 / 100 < counter)
        return RESOURCE_TIER_2;
    if (max * 10 / 100 < counter)
        return RESOURCE_TIER_1;
    return RESOURCE_TIER_0;
}

void WorldState::ChangeWarEffortGoSpawns(AQResources resource, int32 forcedTier)
{
    auto resourceInfo = GetResourceInfo(resource);
    auto counterInfo = GetResourceCounterAndMax(resourceInfo.first, resourceInfo.second);
    auto tier = GetResourceTier(counterInfo.first, counterInfo.second);
    if (forcedTier != -1)
        tier = AQResourceTier(uint32(forcedTier));
    std::vector<uint32> spawnsForSchedule;
    for (auto& spawn : warEffortSpawns)
        if (resourceInfo.first == spawn.resourceGroup && tier >= spawn.resourceTier)
            if (m_aqData.m_spawnedDbGuids.find(spawn.dbGuid) == m_aqData.m_spawnedDbGuids.end())
                spawnsForSchedule.push_back(spawn.dbGuid);
    for (uint32 dbGuid : spawnsForSchedule)
        m_aqData.m_spawnedDbGuids.insert(dbGuid);

    sMapMgr.DoForAllMapsWithMapId(resourceInfo.second == ALLIANCE ? MAP_AZEROTH : MAP_KALIMDOR, [=](Map* map)
    {
        for (uint32 dbGuid : spawnsForSchedule)
        {
            WorldObject::SpawnGameObject(dbGuid, map);
        }
    });
}

void WorldState::ChangeWarEffortPhase2Tier(uint32 remainingDays)
{
    m_aqData.m_phase2Tier = remainingDays;
    std::set<std::pair<uint32, Team>> guidsForDespawn;
    for (uint32 dbGuid : m_aqData.m_spawnedDbGuids)
        for (auto& spawn : warEffortSpawns)
            if (spawn.dbGuid == dbGuid && spawn.resourceTier > remainingDays)
                guidsForDespawn.insert({ dbGuid, spawn.team});

    DespawnWarEffortGuids(guidsForDespawn);
    Save(SAVE_ID_AHN_QIRAJ);
}

void WorldState::DespawnWarEffortGuids(std::set<std::pair<uint32, Team>>& guids)
{
    std::vector<uint32> kalimdor;
    std::vector<uint32> ek;
    for (auto& data : guids)
    {
        if (data.second == ALLIANCE)
            ek.push_back(data.first);
        else
            kalimdor.push_back(data.first);
    }
    if (!ek.empty())
    {
        for (uint32 dbGuid : ek)
            m_aqData.m_spawnedDbGuids.erase(dbGuid);

        sMapMgr.DoForAllMapsWithMapId(MAP_AZEROTH, [=](Map* map)
        {
            for (uint32 dbGuid : ek)
            {
                if (GameObject* go = map->GetGameObject(dbGuid))
                    go->AddObjectToRemoveList();
            }
        });
    }
    if (!kalimdor.empty())
    {
        for (uint32 dbGuid : kalimdor)
            m_aqData.m_spawnedDbGuids.erase(dbGuid);

        sMapMgr.DoForAllMapsWithMapId(MAP_KALIMDOR, [=](Map* map)
        {
            for (uint32 dbGuid : kalimdor)
            {
                if (GameObject* go = map->GetGameObject(dbGuid))
                    go->AddObjectToRemoveList();
            }
        });
    }
}

std::pair<AQResourceGroup, Team> WorldState::GetResourceInfo(AQResources resource)
{
    switch (resource)
    {
        case AQ_RAINBOW_FIN_ALBACORE: return { RESOURCE_GROUP_COOKING, ALLIANCE};
        case AQ_ROAST_RAPTOR: return { RESOURCE_GROUP_COOKING, ALLIANCE };
        case AQ_SPOTTED_YELLOWTAIL_ALLY: return { RESOURCE_GROUP_COOKING, ALLIANCE };
        case AQ_SPOTTED_YELLOWTAIL_HORDE: return { RESOURCE_GROUP_COOKING, HORDE };
        case AQ_LEAN_WOLF_STEAK: return { RESOURCE_GROUP_COOKING, HORDE };
        case AQ_BAKED_SALMON: return { RESOURCE_GROUP_COOKING, HORDE };
        case AQ_PEACEBLOOM: return { RESOURCE_GROUP_HERBS, HORDE };
        case AQ_FIREBLOOM: return { RESOURCE_GROUP_HERBS, HORDE };
        case AQ_PURPLE_LOTUS_HORDE: return { RESOURCE_GROUP_HERBS, HORDE };
        case AQ_PURPLE_LOTUS_ALLY: return { RESOURCE_GROUP_HERBS, ALLIANCE };
        case AQ_STRANGLEKELP: return { RESOURCE_GROUP_HERBS, ALLIANCE };
        case AQ_ARTHAS_TEARS: return { RESOURCE_GROUP_HERBS, ALLIANCE };
        case AQ_TIN_BAR: return { RESOURCE_GROUP_BARS, HORDE };
        case AQ_MITHRIL_BAR: return { RESOURCE_GROUP_BARS, HORDE };
        case AQ_IRON_BAR: return { RESOURCE_GROUP_BARS, ALLIANCE };
        case AQ_THORIUM_BAR: return { RESOURCE_GROUP_BARS, ALLIANCE };
        case AQ_COPPER_BAR_ALLY: return { RESOURCE_GROUP_BARS, ALLIANCE };
        case AQ_COPPER_BAR_HORDE: return { RESOURCE_GROUP_BARS, HORDE };
        case AQ_HEAVY_LEATHER: return { RESOURCE_GROUP_SKINNING, HORDE };
        case AQ_RUGGED_LEATHER: return { RESOURCE_GROUP_SKINNING, HORDE };
        case AQ_THICK_LEATHER_HORDE: return { RESOURCE_GROUP_SKINNING, HORDE };
        case AQ_THICK_LEATHER_ALLY: return { RESOURCE_GROUP_SKINNING, ALLIANCE };
        case AQ_LIGHT_LEATHER: return { RESOURCE_GROUP_SKINNING, ALLIANCE };
        case AQ_MEDIUM_LEATHER: return { RESOURCE_GROUP_SKINNING, ALLIANCE };
        case AQ_LINEN_BANDAGE: return { RESOURCE_GROUP_BANDAGES, ALLIANCE };
        case AQ_SILK_BANDAGE: return { RESOURCE_GROUP_BANDAGES, ALLIANCE };
        case AQ_RUNECLOTH_BANDAGE_ALLY: return { RESOURCE_GROUP_BANDAGES, ALLIANCE };
        case AQ_RUNECLOTH_BANDAGE_HORDE: return { RESOURCE_GROUP_BANDAGES, HORDE };
        case AQ_WOOL_BANDAGE: return { RESOURCE_GROUP_BANDAGES, HORDE };
        case AQ_MAGEWEAVE_BANDAGE: return { RESOURCE_GROUP_BANDAGES, HORDE };
        default: return { RESOURCE_GROUP_HERBS, HORDE };
    }
}

std::pair<uint32, uint32> WorldState::GetResourceCounterAndMax(AQResourceGroup group, Team team)
{
    auto& data = teamResourcesMap[{group, team}];
    uint32 counter = 0;
    uint32 max = 0;
    for (auto& resource : data)
    {
        counter += m_aqData.m_WarEffortCounters[resource];
        max += aqWorldStateTotalsMap[resource > RESOURCE_UNIQUE_MAX ? resource - 5 : resource].second;
    }
    return {counter, max};
}

std::string WorldState::GetAQPrintout()
{
    std::string output = "Phase: " + std::to_string(m_aqData.m_phase) + " Timer: " + std::to_string(m_aqData.m_timer) + "\nValues:";
    for (uint32 value : m_aqData.m_WarEffortCounters)
        output += " " + std::to_string(value);
    return output;
}

std::string AhnQirajData::GetData()
{
    std::string output = std::to_string(m_phase) + " " + std::to_string(m_timer);
    for (uint32 value : m_WarEffortCounters)
        output += " " + std::to_string(value);
    output += " " + std::to_string(m_phase2Tier);
    return output;
}

uint32 AhnQirajData::GetDaysRemaining() const
{
    return uint32(m_timer / (DAY * IN_MILLISECONDS));
}

// Highlord Kruul
enum HighlordKruul : uint32
{
    NPC_HIGHLORD_KRUUL = 18338
};

static float highlordKruulSpawns[10][4] =
{
    { 1975.47f, -137.368f, 32.5316f, 1.20898f },            // Undercity
    { -9550.13f, -126.712f, 57.4972f, 1.34809f },           // Stormwind
    { -5319.087f, -482.139f, 388.332f, 5.831f },            // Ironforge
    { -14737.6f, 499.647f, 3.48665f, 5.45968f },            // Booty Bay / Stranglethorn Vale
    { -234.531f, -2585.4f, 119.897f, 4.77144f },            // Hinterlands
    { 2197.334961f, -4684.198242f, 76.044106f, 0.937313f },  // Eastern Plaguelands
    { -6668.74f, -1533.09f, 243.164f, 2.00132f },           // Searing Gorge
    { 912.479f, -4502.01f, 7.34687f, 0.256955f },           // Orgrimmar
    { 2785.4f, -3823.48f, 84.2639f, 4.5062f },               // Azshara
    { 6443.186f, -3904.882f, 668.369f, 0.937313f },         // Winterpsring
};

void WorldState::RespawnHighlordKruul()
{
    if (!m_highlordKruulSpawned)
    {
        m_highlordKruulChosenPosition = urand(0, 9);
        m_highlordKruulSpawned = true;
        Save(SAVE_ID_HIGHLORD_KRUUL);
    }

    uint8 mapId = m_highlordKruulChosenPosition <= 6 ? 0 : 1;
    sMapMgr.DoForAllMapsWithMapId(mapId, [&](Map* map)
    {
        WorldObject::SummonCreature(TempSpawnSettings(nullptr, NPC_HIGHLORD_KRUUL, highlordKruulSpawns[m_highlordKruulChosenPosition][0], highlordKruulSpawns[m_highlordKruulChosenPosition][1], highlordKruulSpawns[m_highlordKruulChosenPosition][2], highlordKruulSpawns[m_highlordKruulChosenPosition][3], TEMPSPAWN_DEAD_DESPAWN, 0, true, false, m_highlordKruulChosenPosition), map, 1);
    });
}

bool WorldState::SetExpansion(uint8 expansion)
{
    if (expansion > EXPANSION_WOTLK)
        return false;

    m_expansion = expansion;
    if (expansion == EXPANSION_NONE)
        sGameEventMgr.StartEvent(GAME_EVENT_BEFORE_THE_STORM);
    else
        sGameEventMgr.StopEvent(GAME_EVENT_BEFORE_THE_STORM);
    if (m_expansion == EXPANSION_TBC)
        sGameEventMgr.StartEvent(GAME_EVENT_ECHOES_OF_DOOM);
    else
        sGameEventMgr.StopEvent(GAME_EVENT_ECHOES_OF_DOOM);
    sWorld.ExecuteForAllSessions([expansion](WorldSession& worldSession)
    {
        if (worldSession.GetSecurity() < SEC_GAMEMASTER)
            worldSession.SetExpansion(expansion);
    });
    Save(SAVE_ID_EXPANSION_RELEASE); // save to DB right away
    return true;
}

enum
{
    QUEST_ERRATIC_BEHAVIOR                  = 11524,
    QUEST_SANCTUM_WARDS                     = 11496,
    QUEST_BATTLE_FOR_THE_SUNS_REACH_ARMORY  = 11538,
    QUEST_DISTRACTION_AT_THE_DEAD_SCAR      = 11532,
    QUEST_INTERCEPTING_THE_MANA_CELLS       = 11513,
    QUEST_INTERCEPT_THE_REINFORCEMENTS      = 11542,
    QUEST_TAKING_THE_HARBOR                 = 11539,
    QUEST_MAKING_READY                      = 11535,
    QUEST_DISCOVERING_YOUR_ROOTS            = 11520,
    QUEST_A_CHARITABLE_DONATION             = 11545,
    QUEST_A_MAGNANIMOUS_BENEFACTOR          = 11549,

    // optional Sunwell Plateau PTR progressive release gates
    QUEST_AGAMATH_THE_FIRST_GATE            = 11551,
    QUEST_ROHENDOR_THE_SECOND_GATE          = 11552,
    QUEST_ARCHONISUS_THE_FINAL_GATE         = 11553,

    COUNTER_MAX_VAL_REQ_SWP_GATES           = 80,
};

void WorldState::AddSunsReachProgress(uint32 questId)
{
    uint32 counter = 0;
    int32 otherCounter = -1;
    int32 worldState = 0;
    uint32 subPhaseMask = 0;
    uint32 addedValue = 1;
    switch (questId)
    {
        case QUEST_ERRATIC_BEHAVIOR: counter = COUNTER_ERRATIC_BEHAVIOR; otherCounter = COUNTER_SANCTUM_WARDS; worldState = WORLD_STATE_QUEL_DANAS_SANCTUM; break;
        case QUEST_SANCTUM_WARDS: counter = COUNTER_SANCTUM_WARDS; otherCounter = COUNTER_SANCTUM_WARDS; worldState = WORLD_STATE_QUEL_DANAS_SANCTUM; break;
        case QUEST_BATTLE_FOR_THE_SUNS_REACH_ARMORY: counter = COUNTER_BATTLE_FOR_THE_SUNS_REACH_ARMORY; otherCounter = COUNTER_DISTRACTION_AT_THE_DEAD_SCAR; worldState = WORLD_STATE_QUEL_DANAS_ARMORY; break;
        case QUEST_DISTRACTION_AT_THE_DEAD_SCAR: counter = COUNTER_DISTRACTION_AT_THE_DEAD_SCAR; otherCounter = COUNTER_BATTLE_FOR_THE_SUNS_REACH_ARMORY; worldState = WORLD_STATE_QUEL_DANAS_ARMORY; break;
        case QUEST_INTERCEPTING_THE_MANA_CELLS: counter = COUNTER_INTERCEPTING_THE_MANA_CELLS; subPhaseMask = SUBPHASE_PORTAL; worldState = WORLD_STATE_QUEL_DANAS_PORTAL; break;
        case QUEST_INTERCEPT_THE_REINFORCEMENTS: counter = COUNTER_INTERCEPT_THE_REINFORCEMENTS; otherCounter = COUNTER_TAKING_THE_HARBOR; worldState = WORLD_STATE_QUEL_DANAS_HARBOR; break;
        case QUEST_TAKING_THE_HARBOR: counter = COUNTER_TAKING_THE_HARBOR; otherCounter = COUNTER_INTERCEPT_THE_REINFORCEMENTS; worldState = WORLD_STATE_QUEL_DANAS_HARBOR; break;
        case QUEST_MAKING_READY: counter = COUNTER_MAKING_READY; subPhaseMask = SUBPHASE_ANVIL; worldState = WORLD_STATE_QUEL_DANAS_ANVIL; break;
        case QUEST_DISCOVERING_YOUR_ROOTS: counter = COUNTER_DISCOVERING_YOUR_ROOTS; subPhaseMask = SUBPHASE_ALCHEMY_LAB; worldState = WORLD_STATE_QUEL_DANAS_ALCHEMY_LAB; break;
        case QUEST_A_CHARITABLE_DONATION: counter = COUNTER_A_CHARITABLE_DONATION; subPhaseMask = SUBPHASE_MONUMENT; worldState = WORLD_STATE_QUEL_DANAS_MONUMENT; break;
        case QUEST_A_MAGNANIMOUS_BENEFACTOR: counter = COUNTER_A_CHARITABLE_DONATION; subPhaseMask = SUBPHASE_MONUMENT; worldState = WORLD_STATE_QUEL_DANAS_MONUMENT; addedValue = 150; break;
        default: return;
    }

    uint32 previousValue = 0;
    uint32 newValue = 0;

    if (!subPhaseMask)
        previousValue = m_sunsReachData.GetPhasePercentage(m_sunsReachData.m_phase);
    else
        previousValue = m_sunsReachData.GetSubPhasePercentage(subPhaseMask);
    m_sunsReachData.m_sunsReachReclamationCounters[counter] += addedValue;
    if (!subPhaseMask)
        newValue = m_sunsReachData.GetPhasePercentage(m_sunsReachData.m_phase);
    else
        newValue = m_sunsReachData.GetSubPhasePercentage(subPhaseMask);
    if (previousValue != newValue)
        SendWorldstateUpdate(m_sunsReachData.m_sunsReachReclamationMutex, m_sunsReachData.m_sunsReachReclamationPlayers, newValue, worldState);

    bool save = true;
    uint32 counterValue = m_sunsReachData.m_sunsReachReclamationCounters[counter];
    uint32 modifier = 1;
    if (otherCounter != -1)
    {
        modifier = 2;
        counterValue += m_sunsReachData.m_sunsReachReclamationCounters[otherCounter];
    }
    if (counterValue >= sWorld.getConfig(CONFIG_UINT32_SUNSREACH_COUNTER) * modifier)
    {
        save = false;
        switch (questId)
        {
            case QUEST_ERRATIC_BEHAVIOR:
            case QUEST_SANCTUM_WARDS:
            {
                if (m_sunsReachData.m_phase == SUNS_REACH_PHASE_1_STAGING_AREA)
                    HandleSunsReachPhaseTransition(SUNS_REACH_PHASE_2_SANCTUM);
                break;
            }
            case QUEST_BATTLE_FOR_THE_SUNS_REACH_ARMORY:
            case QUEST_DISTRACTION_AT_THE_DEAD_SCAR:
            {
                if (m_sunsReachData.m_phase == SUNS_REACH_PHASE_2_SANCTUM)
                    HandleSunsReachPhaseTransition(SUNS_REACH_PHASE_3_ARMORY);
                break;
            }
            case QUEST_INTERCEPTING_THE_MANA_CELLS:
            {
                if ((m_sunsReachData.m_subphaseMask & SUBPHASE_PORTAL) == 0)
                    HandleSunsReachSubPhaseTransition(SUBPHASE_PORTAL);
                break;
            }
            case QUEST_INTERCEPT_THE_REINFORCEMENTS:
            case QUEST_TAKING_THE_HARBOR:
            {
                if (m_sunsReachData.m_phase == SUNS_REACH_PHASE_3_ARMORY)
                    HandleSunsReachPhaseTransition(SUNS_REACH_PHASE_4_HARBOR);
                break;
            }
            case QUEST_MAKING_READY:
            {
                if ((m_sunsReachData.m_subphaseMask & SUBPHASE_ANVIL) == 0)
                    HandleSunsReachSubPhaseTransition(SUBPHASE_ANVIL);
                break;
            }
            case QUEST_DISCOVERING_YOUR_ROOTS:
            {
                if ((m_sunsReachData.m_subphaseMask & SUBPHASE_ALCHEMY_LAB) == 0)
                    HandleSunsReachSubPhaseTransition(SUBPHASE_ALCHEMY_LAB);
                break;
            }
            case QUEST_A_CHARITABLE_DONATION:
            case QUEST_A_MAGNANIMOUS_BENEFACTOR:
            {
                if ((m_sunsReachData.m_subphaseMask & SUBPHASE_MONUMENT) == 0)
                    HandleSunsReachSubPhaseTransition(SUBPHASE_MONUMENT);
                break;
            }
        }
    }
    if (save)
        Save(SAVE_ID_QUEL_DANAS);
}

void WorldState::AddSunwellGateProgress(uint32 questId)
{
    uint32 counter = 0;
    int32 worldState = 0;
    uint32 addedValue = 1;
    switch (questId)
    {
        case QUEST_AGAMATH_THE_FIRST_GATE:
        case QUEST_ROHENDOR_THE_SECOND_GATE:
        case QUEST_ARCHONISUS_THE_FINAL_GATE:
            break;
        default: return;
    }
    switch (m_sunsReachData.m_gate)
    {
        case SUNWELL_ALL_GATES_CLOSED: counter = COUNTER_AGAMATH_THE_FIRST_GATE; worldState = WORLD_STATE_AGAMATH_THE_FIRST_GATE_HEALTH; break;
        case SUNWELL_AGAMATH_GATE1_OPEN: counter = COUNTER_ROHENDOR_THE_SECOND_GATE; worldState = WORLD_STATE_ROHENDOR_THE_SECOND_GATE_HEALTH; break;
        case SUNWELL_ROHENDOR_GATE2_OPEN: counter = COUNTER_ARCHONISUS_THE_FINAL_GATE; worldState = WORLD_STATE_ARCHONISUS_THE_FINAL_GATE_HEALTH; break;
        default: return;
    }

    uint32 previousValue = m_sunsReachData.GetSunwellGatePercentage(m_sunsReachData.m_gate);
    uint32 newValue = 0;
    m_sunsReachData.m_gateCounters[counter] += addedValue;
    newValue = m_sunsReachData.GetSunwellGatePercentage(m_sunsReachData.m_gate);
    if (previousValue != newValue)
        SendWorldstateUpdate(m_sunsReachData.m_sunsReachReclamationMutex, m_sunsReachData.m_sunsReachReclamationPlayers, newValue, worldState);

    bool save = true;
    if (m_sunsReachData.m_gateCounters[counter] >= COUNTER_MAX_VAL_REQ_SWP_GATES)
    {
        save = false;
        switch (questId)
        {
            case QUEST_AGAMATH_THE_FIRST_GATE:
            {
                if (m_sunsReachData.m_gate == SUNWELL_ALL_GATES_CLOSED)
                    HandleSunwellGateTransition(SUNWELL_AGAMATH_GATE1_OPEN);
                break;
            }
            case QUEST_ROHENDOR_THE_SECOND_GATE:
            {
                if (m_sunsReachData.m_gate == SUNWELL_AGAMATH_GATE1_OPEN)
                    HandleSunwellGateTransition(SUNWELL_ROHENDOR_GATE2_OPEN);
                break;
            }
            case QUEST_ARCHONISUS_THE_FINAL_GATE:
            {
                if (m_sunsReachData.m_gate == SUNWELL_ROHENDOR_GATE2_OPEN)
                    HandleSunwellGateTransition(SUNWELL_ARCHONISUS_GATE3_OPEN);
                break;
            }
        }
    }
    if (save)
        Save(SAVE_ID_QUEL_DANAS);
}

void WorldState::HandleSunsReachPhaseTransition(uint32 newPhase)
{
    if (newPhase < m_sunsReachData.m_phase)
    {
        while (newPhase != m_sunsReachData.m_phase)
        {
            StopSunsReachPhase(newPhase > m_sunsReachData.m_phase);
            --m_sunsReachData.m_phase;
        }
        StartSunsReachPhase();
    }
    else
    {
        StopSunsReachPhase(newPhase > m_sunsReachData.m_phase);
        bool moreThanOne = newPhase > m_sunsReachData.m_phase + 1; // custom command case
        m_sunsReachData.m_phase = newPhase;
        StartSunsReachPhase(moreThanOne);
    }
    switch (m_sunsReachData.m_phase)
    {
        case SUNS_REACH_PHASE_2_SANCTUM: if ((m_sunsReachData.m_subphaseMask & SUBPHASE_PORTAL) == 0) sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_2_NO_PORTAL); break;
        case SUNS_REACH_PHASE_3_ARMORY: if ((m_sunsReachData.m_subphaseMask & SUBPHASE_ANVIL) == 0) sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_3_NO_ANVIL); break;
        case SUNS_REACH_PHASE_4_HARBOR:
            if ((m_sunsReachData.m_subphaseMask & SUBPHASE_ALCHEMY_LAB) == 0) sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_4_NO_MONUMENT);
            if ((m_sunsReachData.m_subphaseMask & SUBPHASE_MONUMENT) == 0) sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_4_NO_ALCHEMY_LAB);
            break;
        default: break;
    }
    SendWorldstateUpdate(m_sunsReachData.m_sunsReachReclamationMutex, m_sunsReachData.m_sunsReachReclamationPlayers, m_sunsReachData.m_phase, WORLD_STATE_QUEL_DANAS_MUSIC);
	Save(SAVE_ID_QUEL_DANAS);
}

void WorldState::HandleSunsReachSubPhaseTransition(int32 subPhaseMask, bool initial)
{
    bool start = true;
    if (subPhaseMask < 0)
    {
        start = false;
        subPhaseMask = -subPhaseMask;
    }
    bool all = false;
    if (start)
    {
        m_sunsReachData.m_subphaseMask |= subPhaseMask;
        if ((m_sunsReachData.m_subphaseMask & SUBPHASE_ALL) == SUBPHASE_ALL)
            all = true;
    }
    else
    {
        if ((m_sunsReachData.m_subphaseMask & SUBPHASE_ALL) == SUBPHASE_ALL)
            all = true;
        m_sunsReachData.m_subphaseMask &= ~subPhaseMask;
    }
    if (initial)
    {
        if (m_sunsReachData.m_phase >= SUNS_REACH_PHASE_2_SANCTUM)
            if ((subPhaseMask & SUBPHASE_PORTAL) == 0)
                sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_2_NO_PORTAL);
        if (m_sunsReachData.m_phase >= SUNS_REACH_PHASE_3_ARMORY)
            if ((subPhaseMask & SUBPHASE_ANVIL) == 0)
                sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_3_NO_ANVIL);
        if (m_sunsReachData.m_phase >= SUNS_REACH_PHASE_4_HARBOR)
        {
            if ((subPhaseMask & SUBPHASE_ALCHEMY_LAB) == 0)
                sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_4_NO_ALCHEMY_LAB);
            if ((subPhaseMask & SUBPHASE_MONUMENT) == 0)
                sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_4_NO_MONUMENT);
        }
    }
    if ((subPhaseMask & SUBPHASE_PORTAL))
    {
        uint32 first = GAME_EVENT_QUEL_DANAS_PHASE_2_NO_PORTAL;
        uint32 second = GAME_EVENT_QUEL_DANAS_PHASE_2_PORTAL;
        if (start)
        {
            sGameEventMgr.StopEvent(first);
            sGameEventMgr.StartEvent(second);
        }
        else
        {
            sGameEventMgr.StopEvent(second);
            sGameEventMgr.StartEvent(first);
        }
    }
    if ((subPhaseMask & SUBPHASE_ANVIL))
    {
        uint32 first = GAME_EVENT_QUEL_DANAS_PHASE_3_NO_ANVIL;
        uint32 second = GAME_EVENT_QUEL_DANAS_PHASE_3_ANVIL;
        if (start)
        {
            sGameEventMgr.StopEvent(first);
            sGameEventMgr.StartEvent(second);
        }
        else
        {
            sGameEventMgr.StopEvent(second);
            sGameEventMgr.StartEvent(first);
        }
    }
    if ((subPhaseMask & SUBPHASE_ALCHEMY_LAB))
    {
        uint32 first = GAME_EVENT_QUEL_DANAS_PHASE_4_NO_ALCHEMY_LAB;
        uint32 second = GAME_EVENT_QUEL_DANAS_PHASE_4_ALCHEMY_LAB;
        if (start)
        {
            sGameEventMgr.StopEvent(first);
            sGameEventMgr.StartEvent(second);
        }
        else
        {
            sGameEventMgr.StopEvent(second);
            sGameEventMgr.StartEvent(first);
        }
    }
    if ((subPhaseMask & SUBPHASE_MONUMENT))
    {
        uint32 first = GAME_EVENT_QUEL_DANAS_PHASE_4_NO_MONUMENT;
        uint32 second = GAME_EVENT_QUEL_DANAS_PHASE_4_MONUMENT;
        if (start)
        {
            sGameEventMgr.StopEvent(first);
            sGameEventMgr.StartEvent(second);
        }
        else
        {
            sGameEventMgr.StopEvent(second);
            sGameEventMgr.StartEvent(first);
        }
    }
    if (all)
    {
        if (start)
            sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_4_KIRU);
        else
            sGameEventMgr.StopEvent(GAME_EVENT_QUEL_DANAS_PHASE_4_KIRU);

        if (!initial)
        {
            std::lock_guard<std::mutex> guard(m_sunsReachData.m_sunsReachReclamationMutex);
            for (ObjectGuid& guid : m_sunsReachData.m_sunsReachReclamationPlayers)
            {
                if (Player* player = sObjectMgr.GetPlayer(guid))
                {
                    if (player->GetZoneId() == ZONEID_SUNWELL_PLATEAU)
                        continue;

                    if (start)
                    {
                        player->GetMap()->GetMessager().AddMessage([guid](Map* map) -> void
                        {
                            if (Player* player = map->GetPlayer(guid))
                                player->CastSpell(nullptr, SPELL_KIRU_SONG_OF_VICTORY, TRIGGERED_OLD_TRIGGERED);
                        });
                    }
                    else
                    {
                        player->GetMap()->GetMessager().AddMessage([guid](Map* map) -> void
                        {
                            if (Player* player = map->GetPlayer(guid))
                                player->RemoveAurasDueToSpell(SPELL_KIRU_SONG_OF_VICTORY);
                        });
                    }
                }
            }
        }
    }
    if (!initial)
        Save(SAVE_ID_QUEL_DANAS);
}

void WorldState::HandleSunwellGateTransition(uint32 newGate)
{
    if (newGate < m_sunsReachData.m_gate)
    {
        while (newGate != m_sunsReachData.m_gate)
        {
            StopSunwellGatePhase();
            --m_sunsReachData.m_gate;
        }
        StartSunwellGatePhase();
    }
    else
    {
        StopSunwellGatePhase();
        m_sunsReachData.m_gate = newGate;
        StartSunwellGatePhase();
    }
    int32 worldState = 0;
    switch (newGate)
    {
        case SUNWELL_AGAMATH_GATE1_OPEN: worldState = WORLD_STATE_AGAMATH_THE_FIRST_GATE_HEALTH; break;
        case SUNWELL_ROHENDOR_GATE2_OPEN: worldState = WORLD_STATE_ROHENDOR_THE_SECOND_GATE_HEALTH; break;
        case SUNWELL_ARCHONISUS_GATE3_OPEN: worldState = WORLD_STATE_ARCHONISUS_THE_FINAL_GATE_HEALTH; break;
    }
    if (worldState)
        SendWorldstateUpdate(m_sunsReachData.m_sunsReachReclamationMutex, m_sunsReachData.m_sunsReachReclamationPlayers, m_sunsReachData.m_gate, worldState);
	Save(SAVE_ID_QUEL_DANAS);
}

void WorldState::SetSunsReachCounter(SunsReachCounters index, uint32 value)
{
    m_sunsReachData.m_sunsReachReclamationCounters[index] = value;
}

void WorldState::SetSunwellGateCounter(SunwellGateCounters index, uint32 value)
{
    m_sunsReachData.m_gateCounters[index] = value;
}

void WorldState::StopSunsReachPhase(bool forward)
{
    switch (m_sunsReachData.m_phase)
    {
        case SUNS_REACH_PHASE_1_STAGING_AREA: sGameEventMgr.StopEvent(GAME_EVENT_QUEL_DANAS_PHASE_1); break;
        case SUNS_REACH_PHASE_2_SANCTUM: sGameEventMgr.StopEvent(GAME_EVENT_QUEL_DANAS_PHASE_2_ONLY); if (!forward) sGameEventMgr.StopEvent(GAME_EVENT_QUEL_DANAS_PHASE_2_PERMANENT); break;
        case SUNS_REACH_PHASE_3_ARMORY: sGameEventMgr.StopEvent(GAME_EVENT_QUEL_DANAS_PHASE_3_ONLY); if (!forward) sGameEventMgr.StopEvent(GAME_EVENT_QUEL_DANAS_PHASE_3_PERMANENT); break;
        case SUNS_REACH_PHASE_4_HARBOR: sGameEventMgr.StopEvent(GAME_EVENT_QUEL_DANAS_PHASE_4); break;
        default: break;
    }
}

void WorldState::StopSunwellGatePhase()
{
    switch (m_sunsReachData.m_gate)
    {
        case SUNWELL_ALL_GATES_CLOSED: sGameEventMgr.StopEvent(GAME_EVENT_SWP_GATES_PHASE_0); break;
        case SUNWELL_AGAMATH_GATE1_OPEN: sGameEventMgr.StopEvent(GAME_EVENT_SWP_GATES_PHASE_1); break;
        case SUNWELL_ROHENDOR_GATE2_OPEN: sGameEventMgr.StopEvent(GAME_EVENT_SWP_GATES_PHASE_2); break;
        case SUNWELL_ARCHONISUS_GATE3_OPEN: sGameEventMgr.StopEvent(GAME_EVENT_SWP_GATES_PHASE_3); break;
        default: break;
    }
}

void WorldState::StartSunsReachPhase(bool initial)
{
    switch (m_sunsReachData.m_phase)
    {
        case SUNS_REACH_PHASE_1_STAGING_AREA: sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_1); break;
        case SUNS_REACH_PHASE_2_SANCTUM: sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_2_ONLY); sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_2_PERMANENT); break;
        case SUNS_REACH_PHASE_3_ARMORY:
            if (initial)
                sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_2_PERMANENT);
            sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_3_ONLY); sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_3_PERMANENT);
            break;
        case SUNS_REACH_PHASE_4_HARBOR:
            if (initial)
            {
                sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_2_PERMANENT);
                sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_3_PERMANENT);
            }
            sGameEventMgr.StartEvent(GAME_EVENT_QUEL_DANAS_PHASE_4);
            break;
        default: break;
    }
}

void WorldState::StartSunwellGatePhase()
{
    switch (m_sunsReachData.m_gate)
    {
        case SUNWELL_ALL_GATES_CLOSED: sGameEventMgr.StartEvent(GAME_EVENT_SWP_GATES_PHASE_0); break;
        case SUNWELL_AGAMATH_GATE1_OPEN: sGameEventMgr.StartEvent(GAME_EVENT_SWP_GATES_PHASE_1); break;
        case SUNWELL_ROHENDOR_GATE2_OPEN: sGameEventMgr.StartEvent(GAME_EVENT_SWP_GATES_PHASE_2); break;
        case SUNWELL_ARCHONISUS_GATE3_OPEN: sGameEventMgr.StartEvent(GAME_EVENT_SWP_GATES_PHASE_3); break;
        default: break;
    }
}

uint32 WorldState::IsBonfireInZone(Team team, uint32 zoneId)
{
    auto zoneItr = m_midsummerZoneIds[team == ALLIANCE].find(zoneId);
    if (zoneItr != m_midsummerZoneIds[team == ALLIANCE].end())
        return (*zoneItr).second;
    return 0;
}

bool WorldState::IsBonfireActive(uint32 entry)
{
    auto itr = m_midsummerBonfireStates.find(entry);
    if (itr != m_midsummerBonfireStates.end())
        return (*itr).second;
    return false;
}

void WorldState::SetBonfireActive(uint32 entry, bool team, bool apply)
{
    uint32 zoneId = 0;
    {
        std::lock_guard<std::mutex> guard(m_midsummerMutex);
        m_midsummerBonfireStates[entry] = apply;
        zoneId = m_midsummerGoToZone[entry];
    }
    ExecuteOnZonePlayers(zoneId, [team, apply](Player* player)
    {
        Team playerTeam = team ? ALLIANCE : HORDE;
        if (player->GetTeam() == playerTeam)
        {
            if (apply)
                player->CastSpell(nullptr, SPELL_BONFIRES_BLESSING, TRIGGERED_OLD_TRIGGERED);
            else
                player->RemoveAurasDueToSpell(SPELL_BONFIRES_BLESSING);
        }
    });
}

void WorldState::SetBonfireZone(uint32 entry, uint32 zoneId, bool team)
{
    std::lock_guard<std::mutex> guard(m_midsummerMutex);
    m_midsummerZoneIds[team][zoneId] = entry;
    m_midsummerGoToZone[entry] = zoneId;
}

std::string WorldState::GetSunsReachPrintout()
{
    std::string output = "Phase: " + std::to_string(m_sunsReachData.m_phase) + " Subphase mask: " + std::to_string(m_sunsReachData.m_subphaseMask) + "\nValues:";
    for (uint32 value : m_sunsReachData.m_sunsReachReclamationCounters)
        output += " " + std::to_string(value);
    output += "\nSunwell Plateau PTR Gate Phase: " + std::to_string(m_sunsReachData.m_gate) + "\nValues:";
    for (uint32 value : m_sunsReachData.m_gateCounters)
        output += " " + std::to_string(value);
    return output;
}

std::string SunsReachReclamationData::GetData()
{
    std::string output = std::to_string(m_phase) + " " + std::to_string(m_subphaseMask);
    for (uint32 value : m_sunsReachReclamationCounters)
        output += " " + std::to_string(value);
    output += " " + std::to_string(m_gate);
    for (uint32 value : m_gateCounters)
        output += " " + std::to_string(value);
    return output;
}

uint32 SunsReachReclamationData::GetPhasePercentage(uint32 phase)
{
    switch (phase)
    {
        case SUNS_REACH_PHASE_1_STAGING_AREA: return uint32((m_sunsReachReclamationCounters[COUNTER_ERRATIC_BEHAVIOR] + m_sunsReachReclamationCounters[COUNTER_SANCTUM_WARDS]) * 100 / (2 * sWorld.getConfig(CONFIG_UINT32_SUNSREACH_COUNTER)));
        case SUNS_REACH_PHASE_2_SANCTUM: return uint32((m_sunsReachReclamationCounters[COUNTER_BATTLE_FOR_THE_SUNS_REACH_ARMORY] + m_sunsReachReclamationCounters[COUNTER_DISTRACTION_AT_THE_DEAD_SCAR]) * 100 / (2 * sWorld.getConfig(CONFIG_UINT32_SUNSREACH_COUNTER)));
        case SUNS_REACH_PHASE_3_ARMORY: return uint32((m_sunsReachReclamationCounters[COUNTER_INTERCEPT_THE_REINFORCEMENTS] + m_sunsReachReclamationCounters[COUNTER_TAKING_THE_HARBOR]) * 100 / (2 * sWorld.getConfig(CONFIG_UINT32_SUNSREACH_COUNTER)));
        default: return 0;
    }
}

uint32 SunsReachReclamationData::GetSubPhasePercentage(uint32 subPhase)
{
    switch (subPhase)
    {
        case SUBPHASE_PORTAL: return uint32(m_sunsReachReclamationCounters[COUNTER_INTERCEPTING_THE_MANA_CELLS] * 100 / sWorld.getConfig(CONFIG_UINT32_SUNSREACH_COUNTER));
        case SUBPHASE_ANVIL: return uint32(m_sunsReachReclamationCounters[COUNTER_MAKING_READY] * 100 / sWorld.getConfig(CONFIG_UINT32_SUNSREACH_COUNTER));
        case SUBPHASE_ALCHEMY_LAB: return uint32(m_sunsReachReclamationCounters[COUNTER_DISCOVERING_YOUR_ROOTS] * 100 / sWorld.getConfig(CONFIG_UINT32_SUNSREACH_COUNTER));
        case SUBPHASE_MONUMENT: return uint32(m_sunsReachReclamationCounters[COUNTER_A_CHARITABLE_DONATION] * 100 / sWorld.getConfig(CONFIG_UINT32_SUNSREACH_COUNTER));
        default: return 0;
    }
}

uint32 SunsReachReclamationData::GetSunwellGatePercentage(uint32 gate)
{
    switch (gate)
    {
        case SUNWELL_ALL_GATES_CLOSED: return 100 - uint32(m_gateCounters[COUNTER_AGAMATH_THE_FIRST_GATE] * 100 / COUNTER_MAX_VAL_REQ_SWP_GATES);
        case SUNWELL_AGAMATH_GATE1_OPEN: return 100 - uint32(m_gateCounters[COUNTER_ROHENDOR_THE_SECOND_GATE] * 100 / COUNTER_MAX_VAL_REQ_SWP_GATES);
        case SUNWELL_ROHENDOR_GATE2_OPEN: return 100 - uint32(m_gateCounters[COUNTER_ARCHONISUS_THE_FINAL_GATE] * 100 / COUNTER_MAX_VAL_REQ_SWP_GATES);
        default: return 0;
    }
}

void WorldState::StartExpansionEvent()
{
    if (m_expansion == EXPANSION_NONE)
    {
        sGameEventMgr.StartEvent(GAME_EVENT_BEFORE_THE_STORM);
        RespawnHighlordKruul();
    }
    if (m_expansion == EXPANSION_TBC)
        sGameEventMgr.StartEvent(GAME_EVENT_ECHOES_OF_DOOM);
}

void WorldState::FillInitialWorldStates(ByteBuffer& data, uint32& count, uint32 zoneId, uint32 areaId)
{
    switch (zoneId)
    {
        case ZONEID_STORMWIND_CITY:
        case ZONEID_DARNASSUS:
        case ZONEID_IRONFORGE:
        case ZONEID_ORGRIMMAR:
        case ZONEID_THUNDER_BLUFF:
        case ZONEID_UNDERCITY:
        {
            if (sGameEventMgr.IsActiveHoliday(HOLIDAY_LOVE_IS_IN_THE_AIR))
            {
                uint32 allianceSum = GetLoveIsInTheAirCounter(LOVE_LEADER_BOLVAR) + GetLoveIsInTheAirCounter(LOVE_LEADER_TYRANDE) + GetLoveIsInTheAirCounter(LOVE_LEADER_MAGNI);
                uint32 hordeSum = GetLoveIsInTheAirCounter(LOVE_LEADER_CAIRNE) + GetLoveIsInTheAirCounter(LOVE_LEADER_THRALL) + GetLoveIsInTheAirCounter(LOVE_LEADER_SYLVANAS);
                FillInitialWorldStateData(data, count, WORLD_STATE_LOVE_IS_IN_THE_AIR_BOLVAR, GetLoveIsInTheAirCounter(LOVE_LEADER_BOLVAR));
                FillInitialWorldStateData(data, count, WORLD_STATE_LOVE_IS_IN_THE_AIR_TYRANDE, GetLoveIsInTheAirCounter(LOVE_LEADER_TYRANDE));
                FillInitialWorldStateData(data, count, WORLD_STATE_LOVE_IS_IN_THE_AIR_MAGNI, GetLoveIsInTheAirCounter(LOVE_LEADER_MAGNI));
                FillInitialWorldStateData(data, count, WORLD_STATE_LOVE_IS_IN_THE_AIR_TOTAL_ALLIANCE, allianceSum);
                FillInitialWorldStateData(data, count, WORLD_STATE_LOVE_IS_IN_THE_AIR_CAIRNE, GetLoveIsInTheAirCounter(LOVE_LEADER_CAIRNE));
                FillInitialWorldStateData(data, count, WORLD_STATE_LOVE_IS_IN_THE_AIR_THRALL, GetLoveIsInTheAirCounter(LOVE_LEADER_THRALL));
                FillInitialWorldStateData(data, count, WORLD_STATE_LOVE_IS_IN_THE_AIR_SYLVANAS, GetLoveIsInTheAirCounter(LOVE_LEADER_SYLVANAS));
                FillInitialWorldStateData(data, count, WORLD_STATE_LOVE_IS_IN_THE_AIR_TOTAL_HORDE, hordeSum);
            }

            if (m_aqData.m_phase == PHASE_1_GATHERING_RESOURCES)
            {
                // totals first
                for (auto itr = aqWorldStateTotalsMap.begin(); itr != aqWorldStateTotalsMap.end(); ++itr)
                    FillInitialWorldStateData(data, count, (*itr).first, (*itr).second);
                for (auto itr = aqWorldstateMap.begin(); itr != aqWorldstateMap.end(); ++itr)
                    FillInitialWorldStateData(data, count, (*itr).second, m_aqData.m_WarEffortCounters[(*itr).first]);
            }
            else if (m_aqData.m_phase == PHASE_2_TRANSPORTING_RESOURCES)
                FillInitialWorldStateData(data, count, WORLD_STATE_AQ_DAYS_LEFT, m_aqData.GetDaysRemaining());
            break;
        }
        case ZONEID_ISLE_OF_QUEL_DANAS:
        case ZONEID_MAGISTERS_TERRACE:
        case ZONEID_SUNWELL_PLATEAU:
        case ZONEID_SHATTRATH:
        {
            switch (m_sunsReachData.m_phase)
            {
                case SUNS_REACH_PHASE_1_STAGING_AREA:
                    FillInitialWorldStateData(data, count, WORLD_STATE_QUEL_DANAS_SANCTUM, m_sunsReachData.GetPhasePercentage(m_sunsReachData.m_phase));
                    break;
                case SUNS_REACH_PHASE_2_SANCTUM:
                    FillInitialWorldStateData(data, count, WORLD_STATE_QUEL_DANAS_ARMORY, m_sunsReachData.GetPhasePercentage(m_sunsReachData.m_phase));
                    break;
                case SUNS_REACH_PHASE_3_ARMORY:
                    FillInitialWorldStateData(data, count, WORLD_STATE_QUEL_DANAS_HARBOR, m_sunsReachData.GetPhasePercentage(m_sunsReachData.m_phase));
                    break;
                case SUNS_REACH_PHASE_4_HARBOR:
                    if ((m_sunsReachData.m_subphaseMask & SUBPHASE_ALCHEMY_LAB) == 0)
                        FillInitialWorldStateData(data, count, WORLD_STATE_QUEL_DANAS_ALCHEMY_LAB, m_sunsReachData.GetSubPhasePercentage(SUBPHASE_ALCHEMY_LAB));
                    if ((m_sunsReachData.m_subphaseMask & SUBPHASE_MONUMENT) == 0)
                        FillInitialWorldStateData(data, count, WORLD_STATE_QUEL_DANAS_MONUMENT, m_sunsReachData.GetSubPhasePercentage(SUBPHASE_MONUMENT));
                    break;
            }
            switch (m_sunsReachData.m_gate)
            {
                case SUNWELL_ALL_GATES_CLOSED:
                    FillInitialWorldStateData(data, count, WORLD_STATE_AGAMATH_THE_FIRST_GATE_HEALTH, m_sunsReachData.GetSunwellGatePercentage(m_sunsReachData.m_gate));
                    break;
                case SUNWELL_AGAMATH_GATE1_OPEN:
                    FillInitialWorldStateData(data, count, WORLD_STATE_ROHENDOR_THE_SECOND_GATE_HEALTH, m_sunsReachData.GetSunwellGatePercentage(m_sunsReachData.m_gate));
                    break;
                case SUNWELL_ROHENDOR_GATE2_OPEN:
                    FillInitialWorldStateData(data, count, WORLD_STATE_ARCHONISUS_THE_FINAL_GATE_HEALTH, m_sunsReachData.GetSunwellGatePercentage(m_sunsReachData.m_gate));
                    break;
            }
            if (m_sunsReachData.m_phase >= SUNS_REACH_PHASE_3_ARMORY && (m_sunsReachData.m_subphaseMask & SUBPHASE_ANVIL) == 0)
                FillInitialWorldStateData(data, count, WORLD_STATE_QUEL_DANAS_ANVIL, m_sunsReachData.GetSubPhasePercentage(SUBPHASE_ANVIL));

            FillInitialWorldStateData(data, count, WORLD_STATE_QUEL_DANAS_MUSIC, m_sunsReachData.m_phase);

            if (m_sunsReachData.m_phase >= SUNS_REACH_PHASE_2_SANCTUM && (m_sunsReachData.m_subphaseMask & SUBPHASE_PORTAL) == 0)
                FillInitialWorldStateData(data, count, WORLD_STATE_QUEL_DANAS_PORTAL, m_sunsReachData.GetSubPhasePercentage(SUBPHASE_PORTAL));
            break;
        }
    }
}