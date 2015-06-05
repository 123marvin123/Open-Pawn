public OnGameModeInit()
{
	print("----------------------------------");
	print("Initializing MySQL Connection\n");
	
	mysql_log(LOG_ALL);
	
	ServerVars[MySQLHandle] = mysql_connect(HOST, USER, DB, PASS);
	
	new error = mysql_errno(ServerVars[MySQLHandle]);
	if(error == ER_DBACCESS_DENIED_ERROR || error == ER_ACCESS_DENIED_ERROR || error == 2005) // 2005 = Unknown MySQL server host
	{
		print("Couldn't reach the MySQL Server.\nServer shutting down.\nOpen the mysql_log.txt for more information.");
		ServerVars[Flags] |= NoConnectionShutDown;
		SetTimer("ShuttingDown", 5000, false);
		return true;
	}
	print("Connection successfull");
	
	mysql_log(LOG_ALL);
	print("\nMySQL Connection initialized");
	print("----------------------------------");
	
	#if defined mysql_OnGameModeInit
		return mysql_OnGameModeInit();
	#else
		return true;
	#endif
}

public OnGameModeExit()
{
	if(!(ServerVars[Flags] & NoConnectionShutDown))
	{
		new tc = tickcount();
		while((tickcount() - tc) < 3000) //pause server for 3 seconds
		{ }
		mysql_close(ServerVars[MySQLHandle]);
	}
	#if defined mysql_OnGameModeExit
		return mysql_OnGameModeExit();
	#else
		return true;
	#endif
}

forward ShuttingDown();
public ShuttingDown()
{
	SendRconCommand("exit");
	return true;
}

/* 
 * ---------------------------------------------------------
 * Hooking part
 * ---------------------------------------------------------
 */

#if defined mysql_OnGameModeInit
	forward mysql_OnGameModeInit();
#endif
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit mysql_OnGameModeInit

#if defined mysql_OnGameModeExit
	forward mysql_OnGameModeExit();
#endif
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit mysql_OnGameModeExit