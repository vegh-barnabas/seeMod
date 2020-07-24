/*
	SA-MP FloodControl Include
	Copyright © 2012 RoacH`
*/

#if defined _FloodControl_Included
    #error Flood Control is already defined.
		#endinput
			#endif
				#define _FloodControl_Included
			#if !defined _samp_included
		#error Please include a_samp before Flood Control.
	#endif
#pragma library "FloodControl"

//BY Y_LESS
#if !defined _ALS_
    forward public _ALS_();
    _ALS_()<_ALS_:unhooked>{}
    _ALS_()<_ALS_:hooked>{}
    _ALS_()<>{}
#endif

enum {
	FLOOD_CONTROL_DEATH,
	FLOOD_CONTROL_BOOT,
	FLOOD_CONTROL_VEHICLES,
	FLOOD_CONTROL_COMMAND,
	FLOOD_CONTROL_CHAT
};
forward OnPlayerFloodControl(playerid, config);

new
	tempIP[20],
	templastIP[20],
 	tempBoot[MAX_PLAYERS],
	flood_stamp[MAX_PLAYERS],
	flood_stampcmd[MAX_PLAYERS]
;

//-=-=-=--=-=-=--=-=-=-FAKE-KILL + FLOOD DEATH-=-=-=--=-=-=--=-=-=-
//					   *Precisão do sistema 95%
public OnPlayerDeath(playerid, killerid, reason) {
	state _ALS_:hooked;
	if(killerid != INVALID_PLAYER_ID) {
		if(playerid == killerid) {
			if(funcidx(#OnPlayerFloodControl)) {
   				CallLocalFunction(#OnPlayerFloodControl, #ii, playerid, FLOOD_CONTROL_DEATH);
   			}
  		}
		if(gettime() - GetPVarInt(playerid, #lastdeath) < 2) {
			if(funcidx(#OnPlayerFloodControl)) {
   				CallLocalFunction(#OnPlayerFloodControl, #ii, playerid, FLOOD_CONTROL_DEATH);
			}
			return false;
		}
  		SetPVarInt(playerid, #lastdeath, gettime());
	}
	return flood_controlOnPlayerDeath(playerid, killerid, reason);
}
//-=-=-=--=-=-=--=-=-=-FUNÇÃO HOOKEADA!(OnPlayerDeath)-=-=-=--=-=-=--=-=-=-
forward flood_controlOnPlayerDeath(playerid, killerid, reason);
#if defined _ALS_OnPlayerDeath
    #undef OnPlayerDeath
#else
    #define _ALS_OnPlayerDeath
#endif
public flood_controlOnPlayerDeath(playerid, killerid, reason) <_ALS_:unhooked> return 1;
public flood_controlOnPlayerDeath(playerid, killerid, reason) <> return 1;
#define OnPlayerDeath(%0,%0,%0) flood_controlOnPlayerDeath(%0,%0,%0)<_ALS_:hooked>
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//-=-=-=--=-=-=--=-=-=-CAR MASS SPAWNER(FLOOD VEHICLE)-=-=-=--=-=-=--=-=-=-
//					      *Precisão do sistema 82%
public OnPlayerUpdate(playerid) {
	state _ALS_:hooked;
    new 
        iVehicle = GetPlayerVehicleID(playerid) 
    ; 
    if(GetPlayerVehicleSeat(playerid) != 0) { 
        if(GetPVarInt(playerid, #lastvehicle) != iVehicle) { 
            SetPVarInt(playerid, #lastvehicle, iVehicle); 
            if(GetVehicleModel(iVehicle)) { 
                OnPlayerStateChange(playerid, PLAYER_STATE_DRIVER, INVALID_PLAYER_ID);
            } 
        } 
    }
	return flood_controlOnPlayerUpdate(playerid);
}
//-=-=-=--=-=-=--=-=-=-FUNÇÃO HOOKEADA!(OnPlayerUpdate)-=-=-=--=-=-=--=-=-=-=
forward flood_controlOnPlayerUpdate(playerid);
#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
public flood_controlOnPlayerUpdate(playerid) <_ALS_:unhooked> return 1;
public flood_controlOnPlayerUpdate(playerid) <> return 1;
#define OnPlayerUpdate(%0) flood_controlOnPlayerUpdate(%0)<_ALS_:hooked>
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

public OnPlayerStateChange(playerid, newstate, oldstate) { 
	state _ALS_:hooked;
    if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER && GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { 
        if((gettime() - GetPVarInt(playerid, #gettick)) < 2) { 
			if(funcidx(#OnPlayerFloodControl)) {
   				CallLocalFunction(#OnPlayerFloodControl, #ii, playerid, FLOOD_CONTROL_VEHICLES);
			}
		} 
		SetPVarInt(playerid, #gettick, gettime()); 
    } 
    return flood_controlOnChangeVeh(playerid, newstate, oldstate);
}
//-=-=-=--=-=-=--=-=-=-FUNÇÃO HOOKEADA!(OnPlayerStateChange)-=-=-=--=-=-=--=-=-=-=-
forward flood_controlOnChangeVeh(playerid, newstate, oldstate);
#if defined _ALS_OnPlayerStateChange
    #undef OnPlayerStateChange
#else
    #define _ALS_OnPlayerStateChange
#endif
public flood_controlOnChangeVeh(playerid, newstate, oldstate) <_ALS_:unhooked> return 1;
public flood_controlOnChangeVeh(playerid, newstate, oldstate) <> return 1;
#define OnPlayerStateChange(%0,%0,%0) flood_controlOnChangeVeh(%0,%0,%0)<_ALS_:hooked>
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//-=-=-=--=-=-=--=-=-=-FLOOD COMMANDS/TEXTS-=-=-=--=-=-=--=-=-=-
//					 *Precisão do sistema 96%
forward OnPlayerFloodChat@Command(playerid, config, iCount, iTime);
public OnPlayerFloodChat@Command(playerid, config, iCount, iTime) 
{
	new bool:flood = false;
	if(config == FLOOD_CONTROL_CHAT) 
	{
		if((gettime() - GetPVarInt(playerid, #lasttext)) <= iTime && flood_stamp[playerid] >= iCount) 
		{
			if(funcidx(#OnPlayerFloodControl)) {
				CallLocalFunction(#OnPlayerFloodControl, #ii, playerid, config);
				flood = true;
			}
		}
		else
			flood_stamp[playerid] = 0;
		SetPVarInt(playerid, #lasttext, gettime());
		++flood_stamp[playerid];
	}
	if(config == FLOOD_CONTROL_COMMAND) {
		if((gettime() - GetPVarInt(playerid, #lastcmd)) <= iTime && flood_stampcmd[playerid] >= iCount) 
		{
			if(funcidx(#OnPlayerFloodControl)) {
				CallLocalFunction(#OnPlayerFloodControl, #ii, playerid, config);
				flood = true;
			}
		}
		else
			flood_stampcmd[playerid] = 0;
		
		SetPVarInt(playerid, #lastcmd, gettime());
		++flood_stampcmd[playerid];
	}	
	return flood;
}

//-=-=-=--=-=-=--=-=-=-FLOOD BOOT DDoS SAMP-=-=-=--=-=-=--=-=-=-
//					 *Precisão do sistema 90%
forward registerPlayer(playerid);
public registerPlayer(playerid) {
	if(GetPVarInt(playerid, #blockmessage) == 1) return false;
	flood_stamp[playerid] = 0, flood_stampcmd[playerid] = 0;
	tempBoot[playerid] = 0;
	SetPVarInt(playerid, #lastdeath, gettime());
	GetPlayerIp(playerid, tempIP, sizeof(tempIP));
	GetPlayerIp(playerid, templastIP, sizeof(templastIP));
	SetPVarInt(playerid, #lastconnect, gettime());
	return registerBoot(playerid);
}

forward registerBoot(playerid);
public registerBoot(playerid) {
	if(strcmp(tempIP, templastIP, true) == 0 && gettime() - GetPVarInt(playerid, #lastconnect) < 4) {
 		++tempBoot[playerid];
   		if(tempBoot[playerid] >= 3) {
			if(funcidx(#OnPlayerFloodControl)) {
				SetPVarInt(playerid, #blockmessage, 1);
				CallLocalFunction(#OnPlayerFloodControl, #ii, playerid, FLOOD_CONTROL_BOOT);
            }
		}
    }
	return false;
}

forward removeRegister(playerid);
public removeRegister(playerid) {
	return tempBoot[playerid] = 0;
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

public OnPlayerConnect(playerid) {
	state _ALS_:hooked;
	registerPlayer(playerid);
	return flood_controlOnPlayerConnect(playerid);
}
//-=-=-=--=-=-=--=-=-=-FUNÇÃO HOOKEADA!(OnPlayerConnect)-=-=-=--=-=-=--=-=-=-
forward flood_controlOnPlayerConnect(playerid);
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
public flood_controlOnPlayerConnect(playerid) <_ALS_:unhooked> return 1;
public flood_controlOnPlayerConnect(playerid) <> return 1;
#define OnPlayerConnect(%0) flood_controlOnPlayerConnect(%0)<_ALS_:hooked>
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

public OnPlayerDisconnect(playerid, reason) {
	if(GetPVarInt(playerid, #blockmessage) == 1) return false;
	return flood_controlOnPlayerDisconnect(playerid, reason);
}
//-=-=-=--=-=-=--=-=-=-FUNÇÃO HOOKEADA!(OnPlayerDisconnect)-=-=-=--=-=-=--=-=-=-
forward flood_controlOnPlayerDisconnect(playerid, reason);
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
public flood_controlOnPlayerDisconnect(playerid, reason) <_ALS_:unhooked> return 1;
public flood_controlOnPlayerDisconnect(playerid, reason) <> return 1;
#define OnPlayerDisconnect(%0,%0) flood_controlOnPlayerDisconnect(%0,%0)<_ALS_:hooked>
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-