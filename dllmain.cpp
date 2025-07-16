// #include "../../__include__/H3API/single_header/H3API.hpp"
#include "patcher_x86_commented.hpp"

#pragma warning(disable : 4996)
#include "H3API.hpp"

#define activePlayerID *(int*)0x69CCF4
#define gameMgr h3::H3Main::Get()
#define battleMgr h3::H3CombatManager::Get() 

using namespace h3;

typedef h3::H3CombatMonster _BattleStack_;

#include "pch.h"
#include "era.h"

const int ADV_MAP = 37;
const int CTRL_LMB = 4;
const int LMB_PUSH = 12;

#define PINSTANCE_MAIN "Z_DisableAITurnDelay"

#include<sstream>

Patcher* globalPatcher;
PatcherInstance* Z_DisableAITurnDelay;

auto Player_HasCapitol = (int(__thiscall*)(void*)) 0x004B9C00; //5BF8E0

typedef h3::H3CombatMonster _BattleStack_;

// ----------------------------------------------

/* Retrieving data from decompiled source

   REGISTERS:
   eax
   ecx
   edx
   ebx
   esi
   edi

   -> can contains value or pointer

   int& myVariable = c->eax;         // value
   int& myVariable = *(int*)c->eax;  // pointer
*/

// ----------------------------------------------

/*
   MEMORY POINTERS:
   ebp
   esp (i've never used this, please use ebp)

   -> can contains pointer or pointer to pointer

   int& myVariable = *(int*)c->eax;    // pointer
   int*& myVariable = *(int**)c->eax;  // pointer to pointer
*/

// ----------------------------------------------
/*
_LHF_(AIPickResourcesNoPause1_004A45E2)
{
	bool isHumanPlayer = *(bool*)(c->ebp + 0x14);
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (!isHumanPlayer || goSolo)
	{
		c->return_address = 0x004A467A;
		return SKIP_DEFAULT;
	}

	return EXEC_DEFAULT;
}

_LHF_(AIPickResourcesNoPause2_004A479A)
{
	bool isHumanPlayer = *(bool*)(c->ebp + 0x14);
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (!isHumanPlayer || goSolo)
	{
		c->return_address = 0x004A4832;
		return SKIP_DEFAULT;
	}

	return EXEC_DEFAULT;
}

_LHF_(AIPickResourcesNoPause3_004A4978)
{
	bool isHumanPlayer = *(bool*)(c->ebp + 0x14);
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (!isHumanPlayer || goSolo)
	{
		c->return_address = 0x004A4A10;
		return SKIP_DEFAULT;
	}

	return EXEC_DEFAULT;
}

_LHF_(AIPickTreasureChestNoPause_004A62C3)
{
	bool isHumanPlayer = *(bool*)(c->ebp + 0x14);
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (!isHumanPlayer || goSolo)
	{
		c->return_address = 0x004A635B;
		return SKIP_DEFAULT;
	}

	return EXEC_DEFAULT;
}

_LHF_(AIPickCampfireNoPause_004A0E52)
{
	bool isHumanPlayer = *(bool*)(c->ebp + 0x14);
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (!isHumanPlayer || goSolo)
	{
		c->return_address = 0x004A0EEA;
		return SKIP_DEFAULT;
	}

	return EXEC_DEFAULT;
}
*/

_LHF_(DisableAIAllEventsDelay_004A818F)
{
	bool isHumanPlayer = *(bool*)(c->ebp + 0x14);
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (!isHumanPlayer || goSolo)
		*(int*)0x00698A10 = false;

	return EXEC_DEFAULT;
}

_LHF_(DisableAICombatDelay1_004ADF40)
{
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (goSolo)
	{
		*(int*)0x00698A10 = false;

		c->return_address = 0x004ADF4A;
		return SKIP_DEFAULT;
	}

	return EXEC_DEFAULT;
}

_LHF_(DisableAICombatDelay2_004AE5D1)
{
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (goSolo)
		*(int*)0x00698A10 = false;

	return EXEC_DEFAULT;
}

_LHF_(DisableAICombatDelay3_004AE5C2)
{
	*(int*)0x00698A10 = false;

	return EXEC_DEFAULT;
}

_LHF_(DisableAICombatDelay4_004AE1FE)
{
	BOOL8 goSolo = *(BOOL8*)0x00691259;
	if (!P_ActivePlayer->is_human || goSolo)
		*(int*)0x00698A10 = false;

	return EXEC_DEFAULT;
}

_LHF_(DisableAICombatDelay5_004A6996)
{
	bool isHumanPlayer = *(bool*)(c->ebp + 0x14);
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (!isHumanPlayer || goSolo)
		*(int*)0x00698A10 = false;

	return EXEC_DEFAULT;
}

_LHF_(DisableAICombatDelay6_004A75BC)
{
	bool isHumanPlayer = *(bool*)(c->ebp + 0x14);
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (!isHumanPlayer || goSolo)
		*(int*)0x00698A10 = false;

	return EXEC_DEFAULT;
}

_LHF_(DisableAICombatDelay7_004A6B88)
{
	bool isHumanPlayer = *(bool*)(c->ebp + 0x14);
	BOOL8 goSolo = *(BOOL8*)0x00691259;

	if (!isHumanPlayer || goSolo)
		*(int*)0x00698A10 = false;

	return EXEC_DEFAULT;
}



extern "C" __declspec(dllexport) BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{

			globalPatcher = GetPatcher();
			Z_DisableAITurnDelay = globalPatcher->CreateInstance(PINSTANCE_MAIN);
			Era::ConnectEra(hModule, PINSTANCE_MAIN);

			Z_DisableAITurnDelay->WriteLoHook(0x004A818F, DisableAIAllEventsDelay_004A818F);
			Z_DisableAITurnDelay->WriteLoHook(0x004ADF40, DisableAICombatDelay1_004ADF40);
			Z_DisableAITurnDelay->WriteLoHook(0x004AE5D1, DisableAICombatDelay2_004AE5D1);
			Z_DisableAITurnDelay->WriteLoHook(0x004AE5C2, DisableAICombatDelay3_004AE5C2);
			Z_DisableAITurnDelay->WriteLoHook(0x004AE1FE, DisableAICombatDelay4_004AE1FE);
			Z_DisableAITurnDelay->WriteLoHook(0x004A6996, DisableAICombatDelay5_004A6996);
			Z_DisableAITurnDelay->WriteLoHook(0x004A75BC, DisableAICombatDelay6_004A75BC);
			Z_DisableAITurnDelay->WriteLoHook(0x004A6B88, DisableAICombatDelay7_004A6B88);			
			
			/*
			Z_DisableAITurnDelay->WriteLoHook(0x004A479A, AIPickResourcesNoPause1_004A45E2);
			Z_DisableAITurnDelay->WriteLoHook(0x004A479A, AIPickResourcesNoPause2_004A479A);
			Z_DisableAITurnDelay->WriteLoHook(0x004A4978, AIPickResourcesNoPause3_004A4978);
			Z_DisableAITurnDelay->WriteLoHook(0x004A62C3, AIPickTreasureChestNoPause_004A62C3);
			Z_DisableAITurnDelay->WriteLoHook(0x004A0E52, AIPickCampfireNoPause_004A0E52);
			*/
			break;
		}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

