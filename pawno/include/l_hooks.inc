/*

		LEWIS HOOKS INCLUDE
	
*/

new PlatoVector[MAX_VEHICLES];

_ALT_CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay)
{
	new id = CreateVehicle(modelid, x, y, z, angle, color1, color2, respawn_delay);
	if(modelid == 578)
		PlatoVector[id] = cvector();
		
	CallLocalFunction("OnCarSpawn", "d", id);
	return id;
}
#define CreateVehicle _ALT_CreateVehicle

_ALT_DestroyVehicle(vehicleid)
{
	if(vector_exists(PlatoVector[vehicleid]))
		dvector(PlatoVector[id]);
		
	return DestroyVehicle(vehicleid);
}
#define DestroyVehicle _ALT_DestroyVehicle