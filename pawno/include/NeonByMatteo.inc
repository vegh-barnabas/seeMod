#include <a_samp>

#define Max_Slots 7



new objetosV[MAX_VEHICLES][Max_Slots];


stock SetVehicleAttachedObject(vehicleid,slot,model,Float:Vcordx,Float:Vcordy,Float:Vcordz,Float:Vrotx,Float:Vroty,Float:Vrotz)
{
if(objetosV[vehicleid][slot]){DestroyObject(objetosV[vehicleid][slot]);}
objetosV[vehicleid][slot] = CreateObject(model,0,0,0,0,0,0);
AttachObjectToVehicle(objetosV[vehicleid][slot],vehicleid,Vcordx,Vcordy,Vcordz,Vrotx,Vroty,Vrotz);
return 0;
}


stock IsVehicleAttachedObjectSlotUsed(vehicleid,slot)
{
if(objetosV[vehicleid][slot])//{return 1;}
return 1;

return 0;
}

stock RemoVehicleAttachedObject(vehicleid,slot)
{
if(objetosV[vehicleid][slot])
{
DestroyObject(objetosV[vehicleid][slot]);
objetosV[vehicleid][slot] =0;
}
return 0;
}