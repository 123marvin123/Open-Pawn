Cmd->v(playerid, params[])
{
	new ModelID;
	if(sscanf(params, "d", ModelID)) return SendClientMessage(playerid, Color(White), "Verwendung: /v [ModelID (400 - 611)]");
	if(ModelID >= 400 && ModelID <= 611)
	{
		new Float:Pos[3];
		GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
		CreateVehicle(ModelID, Pos[0] + 1.5, Pos[1] + 1.5, Pos[2], 0.0, random(255),random(255), -1, 0);
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

Cmd->ca(playerid, params[])
{
	new modelid;
	if(sscanf(params, "d", modelid)) return SendClientMessage(playerid, Color(White), "Verwendung: /ca [modelid (0 - 311)]");
	if(modelid < 0 && modelid > 311) return SendClientMessage(playerid, Color(White), "Verwendung: /ca [modelid (0 - 311)]");
	new actorid, str[40], Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	actorid = CreateActor(modelid, Pos[0] + 1.5, Pos[1] + 1.5, Pos[2], 0);
	format(str, sizeof(str), "Der Actor hat die ID %d", actorid);
	SendClientMessage(playerid, Color(White), str);
	format(str, sizeof(str), "ActorID: %d", actorid);
	Actors[actorid][Label] = Create3DTextLabel(str, Color(Green), Pos[0] + 1.5, Pos[1] + 1.5, Pos[2] + 1, 250, 0);
	return true;
}

Cmd->da(playerid, params[])
{
	new actorid;
	if(sscanf(params, "d", actorid)) return SendClientMessage(playerid, Color(White), "Verwendung: /da [actorid]");
	if(actorid > MAX_ACTORS) return true;
	if(Actors[actorid][Flags] & Valid)
	{
		Delete3DTextLabel(Actors[actorid][Label]);
		DestroyActor(actorid);
	}
	return true;
}