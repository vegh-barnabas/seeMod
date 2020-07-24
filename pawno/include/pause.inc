/*
AFK Detektálás
*/
new gPaused[MAX_PLAYERS], gPausedTime[MAX_PLAYERS];
forward OnPlayerPause(playerid, paused);

stock onPause_Update(playerid)
{
	if(gPaused[playerid])
	{
		CallLocalFunction("OnPlayerPause", "dd", playerid, 0);
		gPaused[playerid] = 0;
	}

	gPausedTime[playerid] = 0;
}

stock onPause_Init()
{
	SetTimer("onPause_Timer", 990, 1);
}

forward onPause_Timer();
public onPause_Timer()
{
	foreach(Player, p)
	{
		if(Belepve(p))
		{
			gPausedTime[p]++;
			if(gPausedTime[p] == 2)
			{
				CallLocalFunction("OnPlayerPause", "dd", p, 1);
				gPaused[p] = 1;
			}
		}
	}
}