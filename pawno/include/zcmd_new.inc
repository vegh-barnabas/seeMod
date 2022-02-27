/**********************************
 *                                *
 *   @Author:      ZeeX           *
 *   @Version:     0.3.1          *
 *   @Released:    31/10/2009     *
 *                                *
 **********************************/
/* Specialis karakterek kezeleset hozzaadta xelor
tamogatas itt: http://gtaforum.hu/index.php?topic=14679.0 */
// M�dos�totta GameStar (30/09/12)

#include <YSI\y_amx>

#if defined _zcmd_included
	#endinput
#endif	
#define _zcmd_included

//native funcname(index, dest[], len = sizeof(dest));

#define MAX_FUNC_NAME (32)
#define ZCMD_PROPERTY_ID (0)

#define ZCMD_Alias(%1,%2) \
	setproperty(.id = ZCMD_PROPERTY_ID, .value = funcidx("cmd_"#%1), .name = %2)
	
#define COMMAND:%1(%2)          \
			forward cmd_%1(%2); \
			public cmd_%1(%2)		
			
#define CMD:%1(%2) \
			COMMAND:%1(%2)

#define command(%1,%2,%3) \
			COMMAND:%1(%2, %3)      
      
#define cmd(%1,%2,%3) \
			COMMAND:%1(%2, %3)

#if !defined isnull
	#define isnull(%1) \
				((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif


forward OnPlayerCommandReceived(playerid, cmdtext[]); 
forward OnPlayerCommandPerformed(playerid, cmdtext[], success); 


static
	bool:zcmd_g_HasOPCS = false,
	bool:zcmd_g_HasOPCE = false;

#if defined FILTERSCRIPT

public OnFilterScriptInit()
{
	zcmd_g_HasOPCS = funcidx("OnPlayerCommandReceived") != -1;
	zcmd_g_HasOPCE = funcidx("OnPlayerCommandPerformed") != -1;
    return CallLocalFunction("zcmd_OnFilterScriptInit", "");
}

#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit zcmd_OnFilterScriptInit
forward zcmd_OnFilterScriptInit();

#else /*not a filterscript*/

public OnGameModeInit()
{
	zcmd_g_HasOPCS = funcidx("OnPlayerCommandReceived") != -1;
	zcmd_g_HasOPCE = funcidx("OnPlayerCommandPerformed") != -1;
	if (funcidx("zcmd_OnGameModeInit") != -1)
	{
		return CallLocalFunction("zcmd_OnGameModeInit", "");
	}	
	return 1;
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit zcmd_OnGameModeInit
forward zcmd_OnGameModeInit();

#endif /*if defined FILTERSCRIPT*/

public OnPlayerCommandText(playerid, cmdtext[])
{
    if(zcmd_g_HasOPCS && !CallLocalFunction("OnPlayerCommandReceived", "is", playerid, cmdtext))
    {
        return 1;
    }
    new
        pos,
        _funcname[MAX_FUNC_NAME],
        srcidx;
    while (cmdtext[++pos] > ' ') 
	{
		_funcname[pos-1] = tolower(cmdtext[pos]);
	}
	srcidx = getproperty(.id = ZCMD_PROPERTY_ID, .name = _funcname);
	if(srcidx)
	{
	    AMX_GetName(AMX_TABLE_PUBLICS, srcidx, _funcname);
	    //funcname(srcidx, _funcname, MAX_FUNC_NAME);
	}
	else
	{
		format(_funcname, MAX_FUNC_NAME, "cmd_%s", _funcname);
	}
    while (cmdtext[pos] == ' ') pos++;
	if (!cmdtext[pos])
	{
		if (zcmd_g_HasOPCE)
		{
			return CallLocalFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, CallLocalFunction(_funcname, "is", playerid, "\1"));
		}
		return CallLocalFunction(_funcname, "is", playerid, "\1");
	}
	if (zcmd_g_HasOPCE)
	{
		return CallLocalFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, CallLocalFunction(_funcname, "is", playerid, cmdtext[pos]));
	}
	return CallLocalFunction(_funcname, "is", playerid, cmdtext[pos]);
}


#if defined _ALS_OnPlayerCommandText
    #undef OnPlayerCommandText
#else
    #define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText zcmd_OnPlayerCommandText
forward zcmd_OnPlayerCommandText(playerid, cmdtext[]);