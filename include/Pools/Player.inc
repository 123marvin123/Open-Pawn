enum constantvars
{
	uID,
	cName[MAX_PLAYER_NAME],
	Skin,
	constantflags:cFlags
};

enum constantflags (<<= 1)
{
	Loggedin = 1
};
new constPlayer[MAX_PLAYERS][constantvars];