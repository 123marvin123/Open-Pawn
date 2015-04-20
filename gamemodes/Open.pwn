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
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerFacingAngle(playerid, 270.0);
	return 1;
}