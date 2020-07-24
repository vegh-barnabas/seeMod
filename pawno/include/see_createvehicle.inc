/*
	LEWIS HOOKS INCLUDE
*/
new VsKocsi[MAX_VEHICLES];
new Iterator:Jarmuvek<MAX_VEHICLES>;

_ALT_CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay)
{
	new id = CreateVehicle(modelid, x, y, z, angle, color1, color2, respawn_delay);
	VsKocsi[id] = -1;
	Iter_Add(Jarmuvek, id);
	CallLocalFunction("OnCarSpawn", "d", id);
	return id;
}
#define CreateVehicle _ALT_CreateVehicle

_ALT_DestroyVehicle(vehicleid)
{
	VsKocsi[vehicleid] = -1;
	Iter_Remove(Jarmuvek, vehicleid);
	return DestroyVehicle(vehicleid);
}
#define DestroyVehicle _ALT_DestroyVehicle