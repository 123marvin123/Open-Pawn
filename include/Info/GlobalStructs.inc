enum sv // Enum for the Servervariables
{
	MySQLHandle,
	svFlags:Flags,
};

enum svFlags (<<=1)
{
	NoConnectionShutDown = 1,
};
new ServerVars[sv];

enum
{
	#if RELEASE_STATE == DEBUG
	DIALOG_INFO,
	#endif
	
	DIALOG_REGISTER,
	DIALOG_LOGIN,
	DIALOG_LOGIN_INFO
};