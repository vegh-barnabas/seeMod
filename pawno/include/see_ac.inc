#if defined see_ac_loaded
	#error A See Anticheat konyvtar mar be van toltve!
#endif
#define see_ac_loaded

forward OnAntiCheatDetect(playerid, cheat);
enum
{
	CHEAT_FAKEKILL,
	CHEAT_FLOOD
}
new
	//Fakekill:
	ac_countDeaths[MAX_PLAYERS],
	ac_startDeathTick[MAX_PLAYERS],
	//Antiflood:
	ac_cmdTick[MAX_PLAYERS],
	ac_cmdText[MAX_PLAYERS][32]
;

Hook:AC_OnPlayerConnect(playerid)
{
	ac_countDeaths[playerid] = 0, ac_startDeathTick[playerid] = 0;
	ac_cmdTick[playerid] = 0, ac_cmdText[playerid][0] = EOS;
	printf("[AC]playerid %d csatlakozott.", playerid);
}
Hook:AC_OnPlayerCommandReceived(playerid, cmdtext[])
{
	SendFormatMessage(playerid, -1, cmdtext);
	return 1;
}
Hook:AC_OnPlayerDeath(playerid, killerid, reason)
{
	if(gettime() - ac_startDeathTick[playerid] < 5)
    {
		ac_countDeaths[playerid] ++;
        if(ac_countDeaths[playerid] == 10) 
        {
			if(funcidx("OnAntiCheatDetect") != -1)
				CallLocalFunction("OnAntiCheatDetect", "ii", playerid, CHEAT_FAKEKILL);
				
            return ac_countDeaths[playerid] = 0;  
        }
    }
	else ac_countDeaths[playerid] = 1;
	
	ac_startDeathTick[playerid] = gettime();
	
	return 1;
}
