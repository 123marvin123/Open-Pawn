InitRegistrationDraws()
{
	ServerVars[RegisterArrow][0] = TextDrawCreate(333.0, 241.0, ">>");
	TextDrawLetterSize(ServerVars[RegisterArrow][0], 0.47, 2.9);
	TextDrawSetShadow(ServerVars[RegisterArrow][0], 0);
	TextDrawUseBox(ServerVars[RegisterArrow][0], 1);
	TextDrawBoxColor(ServerVars[RegisterArrow][0], 0);
	TextDrawTextSize(ServerVars[RegisterArrow][0], 355.0, 15.0);
	TextDrawSetSelectable(ServerVars[RegisterArrow][0], 1);

	ServerVars[RegisterArrow][1] = TextDrawCreate(267.0, 241.0, "<<");
	TextDrawLetterSize(ServerVars[RegisterArrow][1], 0.47, 2.9);
	TextDrawSetShadow(ServerVars[RegisterArrow][1], 0);
	TextDrawUseBox(ServerVars[RegisterArrow][1], 1);
	TextDrawBoxColor(ServerVars[RegisterArrow][1], 0);
	TextDrawTextSize(ServerVars[RegisterArrow][1], 289.000000, 15.000000);
	TextDrawSetSelectable(ServerVars[RegisterArrow][1], 1);
	
	ServerVars[Done][0] = TextDrawCreate(287.0, 156.0, "Los geht's");
	TextDrawLetterSize(ServerVars[Done][0], 0.29, 2.0);
	TextDrawSetShadow(ServerVars[Done][0], 0);
	TextDrawUseBox(ServerVars[Done][0], 1);
	TextDrawBoxColor(ServerVars[Done][0], 0);
	TextDrawTextSize(ServerVars[Done][0], 337.0, 15.0);
	TextDrawSetSelectable(ServerVars[Done][0], 1);

	ServerVars[Done][1] = TextDrawCreate(275.0, 172.0, ".");
	TextDrawLetterSize(ServerVars[Done][1], 6.93, 0.7);
	TextDrawSetOutline(ServerVars[Done][1], 0);
	TextDrawSetShadow(ServerVars[Done][1], 0);
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(clickedid == Text:INVALID_TEXT_DRAW && (!(cPlayer->cFlags[playerid] & Logedin)))
	{
		SelectTextDraw(playerid, Color(Aquamarine));
		return true;
	}
	else if(clickedid == ServerVars[RegisterArrow][0])
	{
		cPlayer->Skin[playerid] = ((cPlayer->Skin[playerid] + 1) > MAX_SKINS) ? (0) : (cPlayer->Skin[playerid] + 1);
		cPlayer->ActorID[playerid] = RespawnActor(cPlayer->ActorID[playerid], cPlayer->Skin[playerid]);
		return true;
	}
	else if(clickedid == ServerVars[RegisterArrow][1])
	{
		cPlayer->Skin[playerid] = ((cPlayer->Skin[playerid] - 1) < 0) ? (MAX_SKINS) : (cPlayer->Skin[playerid] - 1);
		cPlayer->ActorID[playerid] = RespawnActor(cPlayer->ActorID[playerid], cPlayer->Skin[playerid]);
		return true;
	}
	else if(clickedid == ServerVars[Done][0])
	{
		SetPlayerSkin(playerid, cPlayer->Skin[playerid]);
		SaveSkin(playerid);
		
		cPlayer->cFlags[playerid] |= Logedin;
		if(!(cPlayer->cFlags[playerid] & NoSkin))
		{
			OnPlayerRegister(playerid);
		}
		else
		{
			OnPlayerLogin(playerid);
		}
		return true;
	}
	#if defined GTH_OnPlayerClickTextDraw
		return GTH_OnPlayerClickTextDraw(playerid, clickedid);
	#else
		return true;
	#endif 
}

/* 
 * ---------------------------------------------------------
 * Hooking part
 * ---------------------------------------------------------
 */

#if defined GTH_OnPlayerClickTextDraw
forward GTH_OnPlayerClickTextDraw(playerid);
#endif
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
	#else
		#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw GTH_OnPlayerClickTextDraw