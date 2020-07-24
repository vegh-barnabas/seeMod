/*
 *  walkstyle.inc - Walking/running styles.
 *  Created by Emmet on November 3, 2012 @ 9:19 AM
*/
#if defined walkstyle_included
	#endinput
#endif
#define walkstyle_included

/*
	native SetWalkingKey(key);
	native AddWalkingStyle(animlib[], animname[], Float:fDelta = 4.0, loop = 1, lockx = 1, locky = 1, freeze = 1, time = 1);
	native RemoveWalkingStyle(styleid);
	native SetPlayerWalkingStyle(playerid, styleid);
	native GetPlayerWalkingStyle(playerid);
	native ResetPlayerWalkingStyle(playerid);
	native IsPlayerWalking(playerid);
*/
#include <a_samp>

#if !defined MAX_WALKING_STYLES
	#define MAX_WALKING_STYLES (128)
#endif

#define IsPlayerWalking(%0)         GetPVarInt(%0, "Walking")
#define GetPlayerWalkingStyle(%0)   GetPVarInt(%0, "WalkingStyle")

enum E_WALKING_ENUM
{
	E_STYLE_ACTIVE,
	E_STYLE_LIB[32],
	E_STYLE_ANIM[32],
	Float:E_STYLE_DELTA,
	E_STYLE_LOOP,
	E_STYLE_LOCK_X,
	E_STYLE_LOCK_Y,
	E_STYLE_FREEZE,
	E_STYLE_TIME
};
new WalkingStyles[MAX_WALKING_STYLES + 1][E_WALKING_ENUM];
new walking_key = KEY_WALK;

stock SetWalkingKey(key)
{
	if (walking_key == key) return 0;
	walking_key = key;
	return 1;
}

stock AddWalkingStyle(animlib[], animname[], Float:fDelta = 4.0, loop = 1, lockx = 1, locky = 1, freeze = 1, time = 1)
{
	new id;
	for (new i = 1; i < sizeof(WalkingStyles); i ++)
	{
		if (!WalkingStyles[i][E_STYLE_ACTIVE])
		{
		    id = i;
		    break;
		}
	}
	if (!id)
	{
		return 0;
	}
	else
	{
	 	WalkingStyles[id][E_STYLE_ACTIVE] = 1;
		format(WalkingStyles[id][E_STYLE_LIB], 32, animlib);
		format(WalkingStyles[id][E_STYLE_ANIM], 32, animname);
		WalkingStyles[id][E_STYLE_DELTA] = fDelta;
		WalkingStyles[id][E_STYLE_LOOP] = loop;
		WalkingStyles[id][E_STYLE_LOCK_X] = lockx;
		WalkingStyles[id][E_STYLE_LOCK_Y] = locky;
		WalkingStyles[id][E_STYLE_FREEZE] = freeze;
		WalkingStyles[id][E_STYLE_TIME] = time;
	}
	return id;
}

stock RemoveWalkingStyle(styleid)
{
	if (styleid < 1 || styleid > MAX_WALKING_STYLES)
	{
	    return 0;
	}
	else if (!WalkingStyles[styleid][E_STYLE_ACTIVE])
	{
	    return 0;
	}
	else
	{
	    for (new i = 0; i < MAX_PLAYERS; i ++)
	    {
	        if (IsPlayerConnected(i) && GetPlayerWalkingStyle(i) == styleid)
	        {
	            ResetPlayerWalkingStyle(i);
	        }
		}
	    WalkingStyles[styleid][E_STYLE_ACTIVE] = 0;
		strdel(WalkingStyles[styleid][E_STYLE_LIB], 0, 32);
		strdel(WalkingStyles[styleid][E_STYLE_ANIM], 0, 32);
		WalkingStyles[styleid][E_STYLE_DELTA] = 0.0;
		WalkingStyles[styleid][E_STYLE_LOOP] = 0;
		WalkingStyles[styleid][E_STYLE_LOCK_X] = 0;
		WalkingStyles[styleid][E_STYLE_LOCK_Y] = 0;
		WalkingStyles[styleid][E_STYLE_FREEZE] = 0;
		WalkingStyles[styleid][E_STYLE_TIME] = 0;
	}
	return 1;
}

stock SetPlayerWalkingStyle(playerid, styleid)
{
	if (GetPVarInt(playerid, "WalkingStyle") == styleid) return 0;
	return SetPVarInt(playerid, "WalkingStyle", styleid);
}

public OnPlayerConnect(playerid)
{
	SetPVarInt(playerid, "WalkingStyle", 0);
    return CallLocalFunction("walk_OnPlayerConnect", "d", playerid);
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect walk_OnPlayerConnect
forward walk_OnPlayerConnect(playerid);

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    new animlib[32], animname[32], Float:x, Float:y, Float:z;
	GetPlayerVelocity(playerid, x, y, z);
    GetAnimationName(GetPlayerAnimationIndex(playerid), animlib, sizeof(animlib), animname, sizeof(animname));

	if (newkeys & walking_key && GetPlayerWalkingStyle(playerid) && strfind(animname, "JUMP", false) == -1 && floatsqroot(floatpower(x, 2) + floatpower(y, 2) + floatpower(z, 2)) <= 0.05)
	{
	    if (GetPlayerAnimationIndex(playerid) >= 1538 && GetPlayerAnimationIndex(playerid) <= 1544 && GetPlayerAnimationIndex(playerid) != 1542)
	    {
	        return 0;
	    }
	    if (!GetPVarInt(playerid, "Frozen"))
	    {
	        new styleid = GetPlayerWalkingStyle(playerid);
	        switch (GetPVarInt(playerid, "Walking"))
	        {
		        case 0:
		        {
					if (WalkingStyles[styleid][E_STYLE_ACTIVE] && strlen(WalkingStyles[styleid][E_STYLE_LIB]) && strlen(WalkingStyles[styleid][E_STYLE_ANIM]))
					{
			 	 		ApplyAnimation(playerid, WalkingStyles[styleid][E_STYLE_LIB], WalkingStyles[styleid][E_STYLE_ANIM], WalkingStyles[styleid][E_STYLE_DELTA], WalkingStyles[styleid][E_STYLE_LOOP], WalkingStyles[styleid][E_STYLE_LOCK_X], WalkingStyles[styleid][E_STYLE_LOCK_Y], WalkingStyles[styleid][E_STYLE_FREEZE], WalkingStyles[styleid][E_STYLE_TIME], 1);
			  			SetPVarInt(playerid, "Walking", 1);
					}
				}
				case 1:
				{
					if (WalkingStyles[styleid][E_STYLE_ACTIVE] && strlen(WalkingStyles[styleid][E_STYLE_LIB]) && strlen(WalkingStyles[styleid][E_STYLE_ANIM]))
					{
			 	 		ApplyAnimation(playerid, WalkingStyles[styleid][E_STYLE_LIB], WalkingStyles[styleid][E_STYLE_ANIM], WalkingStyles[styleid][E_STYLE_DELTA], 0, WalkingStyles[styleid][E_STYLE_LOCK_X], WalkingStyles[styleid][E_STYLE_LOCK_Y], 0, WalkingStyles[styleid][E_STYLE_TIME], 1);
					}
				    DeletePVar(playerid, "Walking");
				}
			}
		}
	}
    return CallLocalFunction("walk_OnPlayerKeyStateChange", "ddd", playerid, newkeys, oldkeys);
}

stock ResetPlayerWalkingStyle(playerid)
{
	DeletePVar(playerid, "WalkingStyle");
	if (GetPVarInt(playerid, "Walking") == 1)
	{
	    new styleid = GetPlayerWalkingStyle(playerid);
		if (WalkingStyles[styleid][E_STYLE_ACTIVE] && strlen(WalkingStyles[styleid][E_STYLE_LIB]) && strlen(WalkingStyles[styleid][E_STYLE_ANIM]))
		{
			ApplyAnimation(playerid, WalkingStyles[styleid][E_STYLE_LIB], WalkingStyles[styleid][E_STYLE_ANIM], WalkingStyles[styleid][E_STYLE_DELTA], 0, WalkingStyles[styleid][E_STYLE_LOCK_X], WalkingStyles[styleid][E_STYLE_LOCK_Y], 0, WalkingStyles[styleid][E_STYLE_TIME], 1);
		}
  		DeletePVar(playerid, "Walking");
	}
	return 1;
}

stock walk_TogglePlayerControllable(playerid, toggle)
{
	SetPVarInt(playerid, "Frozen", !toggle);
	return TogglePlayerControllable(playerid, toggle);
}

#define TogglePlayerControllable walk_TogglePlayerControllable

#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange walk_OnPlayerKeyStateChange
forward walk_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);