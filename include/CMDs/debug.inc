Cmd->v(playerid, params[])
{
	new ModelID;
	if(sscanf(params, "d", ModelID)) return SendClientMessage(playerid, Color(White), "Verwendung: /v [ModelID (400 - 611)]");
	if(ModelID >= 400 && ModelID <= 611)
	{
		new Float:Pos[3];
		GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
		CreateVehicle(ModelID, Pos[0], Pos[1] + 1.5, Pos[2] + 1.5, 0.0, random(255),random(255), -1, 0);
		return true;
	}
	return SendClientMessage(playerid, Color(White), "Verwendung: /v [ModelID (400 - 611)]"); 
	
}

Cmd->d(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		DestroyVehicle(GetPlayerVehicleID(playerid));
	}
	return true;
}