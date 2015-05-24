/*
 * ----------------------------------------
 * Native Part
 * ----------------------------------------
 */

native _SetPlayerSkin(playerid, skinid) 			= SetPlayerSkin;
native _TogglePlayerSpectating(playerid, toggle) 	= TogglePlayerSpectating;

#define SetPlayerSkin								__SetPlayerSkin
#define TogglePlayerSpectating						__TogglePlayerSpectating
/*
 * ----------------------------------------
 * Useing the Hook
 * ----------------------------------------
 */
 
__SetPlayerSkin(playerid, skinid)
{
	cPlayer->Skin[playerid] = skinid;
	return _SetPlayerSkin(playerid, skinid);
}

__TogglePlayerSpectating(playerid, toggle)
{
	if(toggle) Player->vFlags[playerid] |= Spectating;
	else Player->vFlags[playerid] &= ~Spectating;
	return _TogglePlayerSpectating(playerid, toggle);
}