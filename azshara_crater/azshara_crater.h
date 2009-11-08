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

#ifndef DEF_AZSHARA_CRATER_H
#define DEF_AZSHARA_CRATER_H

enum Encounter
{
    BOSS_RASEN,
	BOSS_SILETH,
	BOSS_XAVIUS
};

enum Data
{
	PHASE_NOSTART,
	PHASE_FLIGHT1,      //Flight to krasus
	PHASE_KRASUS,
	PHASE_DESTROY_ARMY, //Dragons destroy burnign legion's army and flight to 1st encounter
	PHASE_PRE_RASEN,
	PHASE_RASEN,
	PHASE_PRE_SILETH,
	PHASE_SILETH, // No idea what next :)
	PHASE_PRE_XAVIUS,
	PHASE_XAVIUS,
	PHASE_OUTRO
};

enum Data64
{
	DATA_KRASUS,
	DATA_RASEN,
	DATA_SILETH,
	DATA_XAVIUS
};

#endif
