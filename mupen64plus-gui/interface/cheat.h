/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - cheat.h                                                 *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2009 Richard Goedeken                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CHEAT_H
#define CHEAT_H

#include "m64p_types.h"

#ifdef M64P_BIG_ENDIAN
  #define sl(mot) mot
#else
  #define sl(mot) (((mot & 0xFF) << 24) | ((mot & 0xFF00) <<  8) | ((mot & 0xFF0000) >>  8) | ((mot & 0xFF000000) >> 24))
#endif

typedef enum {
  CHEAT_DISABLE,
  CHEAT_LIST,
  CHEAT_ALL,
  CHEAT_SHOW_LIST
  } eCheatMode;

typedef struct {
   int    address;
   int   *variables;
   char **variable_names;
   int    var_to_use;
   int    var_count;
} cheat_code;

typedef struct _sCheatInfo {
  int                 Number;
  int                 Count;
  int                 VariableLine;
  const char         *Name;
  const char         *Description;
  cheat_code         *Codes;
  struct _sCheatInfo *Next;
  bool                active;
  } sCheatInfo;

void ReadCheats(char *RomSection);
void CheatFreeAll(void);
sCheatInfo *CheatFindCode(int Number);
void CheatActivate(sCheatInfo *pCheat);

extern int                l_CheatCodesFound;
extern int                l_RomFound;
extern char              *l_CheatGameName;
extern sCheatInfo        *l_CheatList;

#endif // #define CHEAT_H