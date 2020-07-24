#if defined _INC_rag
	#endinput
#endif
#define _INC_rag

/*
-ból-ből 1
-ról-ről 2
-nak-nek 3
-tól-től 4
-ra-re 5
-ban-ben 6
-ba-be 7
-val-vel-ral-rel-tal-tel-kal-kel 8*
-t 9
-hoz-hez-höz 10 *

*/

/* native rag(str[],tipus); */


new mely[][] ={"a", "á", "o", "ó", "u", "ú"};
new magas[][] ={"e", "é", "i", "í", "ö", "ő", "ü", "ű"};
new all[][] = {"a", "á", "o", "ó", "u", "ú","e", "é", "i", "í", "ö", "ő", "ü", "ű"};
new other[][] = {"m", "n", "j", "l", "r", "b", "d", "g", "v","p", "t","c"};


new melytype[][] ={"ból", "ról", "nak", "tól", "ra", "ban", "ba","val","t"};
new magastype[][] ={"ből", "ről", "nek", "től", "re", "ben", "be","vel","t"};



stock CheckMaganhangzo(betu[])
{
    for(new i; i<sizeof(all); i++)
    {
        if(strcmp(betu, all[i], true) == 0) return 1;
	}
 	return 0;
}
stock CheckType(betu[])
{
	for(new i; i<sizeof(mely); i++){ if(strcmp(betu, mely[i], true) == 0) return 1;}
    for(new i; i<sizeof(magas); i++){ if(strcmp(betu, magas[i], true) == 0) return 2;}
    return 3;
}

/*public OnGameModeInit() //Tesztelni
{
	for(new i = 1; i<13; i++) printf("%s",rag("románc",i));
	return 1;
}*/


stock rag(str[],tipus)
{
	new betu[8];
	new szo[128];
	format(szo,sizeof(szo),str); //másképp nem kezeli rendesen..
    strmid(betu, szo, strlen(szo)-1, strlen(szo)); 
    if(CheckMaganhangzo(betu) == 0)
 	{
		new lastbetu[8];
	    if(tipus == 8)
		{
		    for(new i; i<sizeof(other); i++)
		    {
		        if(strcmp(betu, other[i], true) == 0)
		    	{
		    	    for(new c; c<strlen(szo); c++)
				    {
				        strmid(betu, szo, c,c+1);
				        if(CheckType(betu) != 3) format(lastbetu,sizeof(lastbetu),betu);
					}
					if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%s%sal",szo,other[i]);
					if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%s%sel",szo,other[i]);
			        return szo;
				}
			}
			if(strcmp(betu, "z", true) == 0)
		    {
		        for(new i; i<strlen(szo); i++)
			    {
			        strmid(betu, szo, i,i+1);
			        if(CheckType(betu) != 3) format(lastbetu,sizeof(lastbetu),betu);
				}
				strmid(betu, szo, strlen(szo)-2, strlen(szo)-1);
				if(strcmp(betu, "s", true) == 0)
		    	{
		    	    strdel(szo,strlen(szo)-2,strlen(szo));
		    	    if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%ssszal",szo);
					if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%ssszel",szo);
				}
				else
				{
					if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%sal",szo);
					if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%sel",szo);
				}
		        return szo;
			}
			if(strcmp(betu, "y", true) == 0)
		    {
		        for(new i; i<strlen(szo); i++)
			    {
			        strmid(betu, szo, i,i+1);
			        if(CheckType(betu) != 3) format(lastbetu,sizeof(lastbetu),betu);
				}
				strmid(betu, szo, strlen(szo)-2, strlen(szo)-1);
				if(strcmp(betu, "g", true) == 0)
		    	{
		    	    strdel(szo,strlen(szo)-2,strlen(szo));
		    	    if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%sggyal",szo);
					if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%sggyel",szo);
				}
		        return szo;
			}
			if(strcmp(betu, "s", true) == 0)
		    {
		        for(new i; i<strlen(szo); i++)
			    {
			        strmid(betu, szo, i,i+1);
			        if(CheckType(betu) != 3) format(lastbetu,sizeof(lastbetu),betu);
				}
				strmid(betu, szo, strlen(szo)-2, strlen(szo)-1);
				if(strcmp(betu, "c", true) == 0)
		    	{
		    	    strdel(szo,strlen(szo)-2,strlen(szo));
		    	    if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%sccsal",szo);
					if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%sccsel",szo);
				}
				else if(strcmp(betu, "z", true) == 0)
		    	{
		    	    strdel(szo,strlen(szo)-2,strlen(szo));
		    	    if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%szzsal",szo);
					if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%szzsel",szo);
				}
    			else
				{
					if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%ssal",szo);
					if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%ssel",szo);
				}
		        return szo;
			}
			if(strcmp(betu, "k", true) == 0)
		    {
		        for(new i; i<strlen(szo); i++)
			    {
			        strmid(betu, szo, i,i+1);
			        if(CheckType(betu) != 3) format(lastbetu,sizeof(lastbetu),betu);
				}
				strmid(betu, szo, strlen(szo)-2, strlen(szo)-1);
				if(strcmp(betu, "k", true) == 0)
		    	{
		    	    if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%sal",szo);
					if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%sel",szo);
				}
				else
				{
					if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%skal",szo);
					if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%skel",szo);
				}
		        return szo;
			}

		}
		if(tipus == 9)
		{
		    if(strcmp(betu, "t", true) == 0 || strcmp(betu, "k", true) == 0 || strcmp(betu, "c", true) == 0)
		    {
		        for(new i; i<strlen(szo); i++)
			    {
			        strmid(betu, szo, i,i+1);
			        if(CheckType(betu) != 3) format(lastbetu,sizeof(lastbetu),betu);
				}
				if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%sot",szo);
				if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%set",szo);
		        return szo;
			}
		}
	    for(new i; i<strlen(szo); i++)
	    {
	        strmid(betu, szo, i,i+1);
	        if(CheckType(betu) != 3) format(lastbetu,sizeof(lastbetu),betu);
		}
		if(tipus == 10)
		{
		    if(strcmp(betu, "ö", true) == 0)
		    {
		        strdel(szo,strlen(szo)-1, strlen(szo));
		        format(szo,sizeof(szo),"%sőhöz",szo);
		        return szo;
			}
			if(strcmp(betu, "ő", true) == 0)
		    {
		        strdel(szo,strlen(szo)-1, strlen(szo));
		        format(szo,sizeof(szo),"%shöz",szo);
		        return szo;
			}

		}
		if(CheckType(lastbetu) == 1) format(szo,sizeof(szo),"%s%s",szo,melytype[tipus-1]);
		if(CheckType(lastbetu) == 2) format(szo,sizeof(szo),"%s%s",szo,magastype[tipus-1]);
	}
    if(CheckMaganhangzo(betu) == 1)
    {
	    if(strcmp(betu, "a", true) == 0)
	    {
	        strdel(szo,strlen(szo)-1, strlen(szo));
	        format(szo,sizeof(szo),"%sá%s",szo,melytype[tipus-1]);
	        return szo;
		}
		if(strcmp(betu, "e", true) == 0)
	    {
	        strdel(szo,strlen(szo)-1, strlen(szo));
	        format(szo,sizeof(szo),"%sé%s",szo,magastype[tipus-1]);
	        return szo;
		}
		if(tipus == 10)
		{
		    if(strcmp(betu, "ö", true) == 0)
		    {
		        strdel(szo,strlen(szo)-1, strlen(szo));
		        format(szo,sizeof(szo),"%sőhöz",szo);
		        return szo;
			}
			if(strcmp(betu, "ő", true) == 0)
		    {
		        strdel(szo,strlen(szo)-1, strlen(szo));
		        format(szo,sizeof(szo),"%shöz",szo);
		        return szo;
			}
		}
		if(CheckType(betu) == 1) format(szo,sizeof(szo),"%s%s",szo,melytype[tipus-1]);
		if(CheckType(betu) == 2) format(szo,sizeof(szo),"%s%s",szo,magastype[tipus-1]);
		return szo;
	}
	return szo;
}
