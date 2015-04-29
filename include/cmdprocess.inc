#define Cmd->%1(%2) forward CMD_%1(%2); public CMD_%1(%2)

public OnPlayerCommandText(playerid,cmdtext[])
{
	new cmd[38], k = 1;
	for(; ;)
	{
		switch(cmdtext[k])
		{
			case '\0', '\1', ' ': break; 
			case 'A' .. 'Z': cmd[k - 1] = cmdtext[k] + 32;
			default: cmd[k - 1] = cmdtext[k];
		}
		++k;
	}
	strins(cmd, "CMD_", 0, 4); // much better than format.
	new idx = funcidx(cmd), pointer;
	if(idx == -1)
	{
		#if defined CMD_OnPlayerCommandText
			return CMD_OnPlayerCommandText(playerid, cmdtext);
		#else
			return false;
		#endif
	}
	
	strdel(cmdtext,0,k+1);
	// Get the pointer to the public function list.
	#emit LCTRL       1
    #emit NEG
    #emit ADD.C       32
    #emit STOR.S.pri  pointer
    #emit LREF.S.alt  pointer
	// Get the pointer to the function at the given index.
    #emit LCTRL       1
    #emit NEG
    #emit ADD
    #emit LOAD.S.alt  idx
    #emit SHL.C.alt   3
    #emit ADD
    #emit STOR.S.pri  pointer
    #emit LREF.S.pri  pointer
    #emit STOR.S.pri  pointer
	// Call the function
    #emit PUSH.S cmdtext
    #emit PUSH.S playerid
    #emit PUSH.C      8
    #emit LCTRL       6
    #emit ADD.C       28      
    #emit PUSH.pri          
    #emit LOAD.S.pri  pointer
    #emit SCTRL       6     
    #emit STACK       16
	
	#if defined CMD_OnPlayerCommandText
		return CMD_OnPlayerCommandText(playerid, cmdtext);
	#else
		return true;
	#endif
}

#if defined CMD_OnPlayerCommandText
	forward CMD_OnPlayerCommandText(playerid, cmdtext);
#endif

#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText CMD_OnPlayerCommandText