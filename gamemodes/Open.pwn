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
	UsePlayerPedAnims();
	return true;
}

public OnPlayerSpawn(playerid)
{
	SetPlayerPos(playerid, -2248.2258,2330.5852,4.9741);
	SetPlayerFacingAngle(playerid, 55.0);
	SetCameraBehindPlayer(playerid);
	return true;
}

public OnPlayerUpdate(playerid)
{
	if((cPlayer->cFlags[playerid] & Logedin) && (cPlayer->cFlags[playerid] & LoginDone))
	{
		GetPlayerPos(playerid, cPlayer->Cord[0][playerid], cPlayer->Cord[1][playerid], cPlayer->Cord[2][playerid]);
	}
	return true;
}

public OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart)
{
	if(IsValidActor(damaged_actorid))
	{
		new Float:Health;
		GetActorHealth(damaged_actorid, Health);
		if(Health < 1) RespawnActor(damaged_actorid);
	}
}