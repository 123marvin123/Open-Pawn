/*
 * ----------------------------------------
 * Native Part
 * ----------------------------------------
 */

native _SetPlayerSkin(playerid, skinid) = SetPlayerSkin;


#define SetPlayerSkin						__SetPlayerSkin
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