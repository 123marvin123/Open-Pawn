#include <../../include/header>

main()
{
	print("\n----------------------------------");
	print(" Open Source Gamemode");
	print(" Source can be found under:");
	print(" https://github.com/Reclusior/Open-Pawn");
	print("----------------------------------\n");
}

public OnGameModeInit()
{
	SetGameModeText(MODE);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	SetPlayerPos(playerid, -2248.2258,2330.5852,4.9741);
	SetPlayerFacingAngle(playerid, 55.0);
	SetCameraBehindPlayer(playerid);
	return 1;
}