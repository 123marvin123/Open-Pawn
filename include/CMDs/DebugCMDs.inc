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
	if(modelid < 0 && modelid > MAX_SKINS) return SendClientMessage(playerid, Color(White), "Verwendung: /ca [modelid (0 - 311)]");
	new actorid, str[40], Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	actorid = CreateActor(modelid, Pos[0] + 1.5, Pos[1] + 1.5, Pos[2], 0);
	format(str, sizeof(str), "Der Actor hat die ID %d", actorid);
	SendClientMessage(playerid, Color(White), str);
	format(str, sizeof(str), "ActorID: %d", actorid);
	Actor->Label[actorid] = Create3DTextLabel(str, Color(Green), Pos[0] + 1.5, Pos[1] + 1.5, Pos[2] + 1, 250, 0);
	return true;
}

Cmd->da(playerid, params[])
{
	new actorid;
	if(sscanf(params, "d", actorid)) return SendClientMessage(playerid, Color(White), "Verwendung: /da [actorid]");
	if(actorid > MAX_ACTORS) return true;
	if(IsValidActor(actorid))
	{
		Delete3DTextLabel(Actor->Label[actorid]);
		DestroyActor(actorid);
	}
	return true;
}
Cmd->ha(playerid, params[])
{
	new actorid, Float:HealthToSet;
	if(sscanf(params, "df", actorid, HealthToSet)) return SendClientMessage(playerid, Color(White), "Verwendung: /ha [actorid] [health]");
	if(IsValidActor(actorid))
	{
		SetActorHealth(actorid, HealthToSet);
		new str[60];
		format(str, sizeof(str), "Actor (ID: %d) health set to %f", actorid, HealthToSet);
		SendClientMessage(playerid, Color(White), str);
	}
	return true;
}
Cmd->skin(playerid,params[])
{
	new Skinid;
	if(sscanf(params,"i",Skinid)) return SendClientMessage(playerid,-1, "Verwendung: /skin [0 - 311]");
	if(Skinid < 311 && Skinid > 0) SetPlayerSkin(playerid, Skinid);
	return true;
}
Cmd->fixveh(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInAnyVehicle(playerid))
	{
		RepairVehicle(GetPlayerVehicleID(playerid));
		SendClientMessage(playerid, -1, "Fahrzeug repariert");
	}
	return true;
}

Cmd->wep(playerid, params[])
{
	new Wep, Amo;
	if(sscanf(params,"ii",Wep, Amo)) return SendClientMessage(playerid,-1, "Verwendung: /wep [weapon] [ammo]");
	ResetPlayerWeapons(playerid);
	GivePlayerWeapon(playerid, Wep, Amo);
	return true;
}

Cmd->jet(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
	{
		SetPlayerSpecialAction(playerid, ((GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK) ? SPECIAL_ACTION_NONE : SPECIAL_ACTION_USEJETPACK));
	}	
	return true;
}
Cmd->carry(playerid, params[])
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
	return true;
}
Cmd->streamskintest(playerid, params[])
{
	cPlayer->CamObj[playerid] = CreatePlayerObject(playerid, 19300, -2381.091308, 2196.152832, 15.140089, 0.0, 0.0, 0.0);
	TogglePlayerSpectating(playerid, true);
	AttachCameraToPlayerObject(playerid, cPlayer->CamObj[playerid]);
	MovePlayerObject(playerid, cPlayer->CamObj[playerid], 0, 0, 0, 150);
	new rand = random(MAX_SKINS);
	SetPlayerSkin(playerid, rand);
	return true;
}
Cmd->makeadmin(playerid, params[]) {
	new user, adminrank, string[128], name[128];
	if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, Color(White), "Du bist kein RCON Administrator!");
	if(sscanf(params, "ui", user, adminrank)) return SendClientMessage(playerid, Color(White), "Verwendung: /makeadmin [Teil des Benutzernames / Benutzerid] [Rank]");
	if(!IsPlayerConnected(user)) return SendClientMessage(playerid, Color(White), "Der Benutzer ist nicht online.");
	GetPlayerName(user, name, sizeof(name));
	format(string, sizeof(string), "Du hast dem Benutzer %s den Adminrank %d gegeben!", name, adminrank); SendClientMessage(playerid, Color(White), string);
	GetPlayerName(playerid, name, sizeof(name));
	format(string, sizeof(string), "Der Benutzer %s hat dir den Adminrank %d gegeben!", name, adminrank); SendClientMessage(playerid, Color(White), string);
	
	cPlayer->adminRank[user] = adminrank;

	return true;
}


public OnPlayerObjectMoved(playerid, objectid)
{
	if(objectid == cPlayer->CamObj[playerid] && cPlayer->cFlags[playerid] & LoginDone)
	{
		DestroyPlayerObject(playerid, cPlayer->CamObj[playerid]);
		TogglePlayerSpectating(playerid, false);
		SetCameraBehindPlayer(playerid);
		return true;
	}
	#if defined DCMDs_OnPlayerObjectMoved
		return DCMDs_OnPlayerObjectMoved(playerid, objectid);
	#else
		return true;
	#endif
}

#if defined DCMDs_OnPlayerObjectMoved
forward DCMDs_OnPlayerObjectMoved(playerid, objectid);
#endif
#if defined _ALS_OnPlayerObjectMoved
	#undef OnPlayerObjectMoved
	#else
		#define _ALS_OnPlayerObjectMoved
#endif
#define OnPlayerObjectMoved DCMDs_OnPlayerObjectMoved