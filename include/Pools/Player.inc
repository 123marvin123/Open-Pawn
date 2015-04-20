enum constantvars
{
	cName[MAX_PLAYER_NAME],
	constantflags:cFlags
};

enum constantflags (<<= 1)
{
	Loggedin = 1
};
new cPlayer[MAX_PLAYERS][constantvars];