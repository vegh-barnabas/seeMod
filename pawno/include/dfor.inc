#if defined _dfor_included
	#endinput
#endif	
#define _dfor_included

#define DIterator:%1<%2> _D_ITER_%1__SZAMLAL,_D_ITER_%1__TOMB[%2]={-1, ...}
#define dforeach(%1,%2) for(new _D_ITER_CIKLUS=-1,%2;(++_D_ITER_CIKLUS<(_D_ITER_%1__SZAMLAL))&&((%2=_D_ITER_%1__TOMB[_D_ITER_CIKLUS])>-1);)
#define DIter_Add(%1,%2) DIter_AddEx(_D_ITER_%1__TOMB,%2,_D_ITER_%1__SZAMLAL)
#define DIter_Remove(%1,%2) DIter_RemoveEx(_D_ITER_%1__TOMB,%2,_D_ITER_%1__SZAMLAL)
#define DIter_Count(%1) (_D_ITER_%1__SZAMLAL)
#define DIter_Random(%1) ((_D_ITER_%1__SZAMLAL?(_D_ITER_%1__TOMB[random(_D_ITER_%1__SZAMLAL)]):(-1)))

/*stock DIterSub_Len(iter[], len = sizeof(iter))
{
	new i = -1,
		ret = 0;
	//printf("Igen: %d", iter[0]);
	for(;++i < len;)
	{
		if(iter[i] > -1)
			ret++;
		
		if(iter[i] == -1)
			break;
	}
	
	//printf("Asd: %d", ret);
	return ret;
}*/
//DIter_AddEx(iter[], value, &count, len = sizeof(iter))
stock
	DIter_AddEx(iter[], value, &count, length = sizeof(iter))
	//DIter_AddEx(iter[], value, &count)
{
	//new len = DIterSub_Len(iter, length);
	new len = count;
	
	if((length == len))
		return true;
	
	new i = -1;
	
	len++;
	for(;++i < len;) //0,1,2 2-találat
		if(iter[i] == value)
			return true;
	
	iter[i - 1] = value;
	count++;
	return true;
}

/*
stock
	DIter_AddEx(iter[], value, &count, length = sizeof(iter))
	//DIter_AddEx(iter[], value, &count)
{
	new len = DIterSub_Len(iter, length);
	//printf("%d | %d | %d", length, len, value); //beágyazok
	if((length == len))
		return true;
	
	new i = -1,
		ret = -1,
		a = 0,
		bool:talalt = false;
	
	len++;
	
	/
		1 - 1
		
	/
	printf("A: %d", len);
	for(;++i < len;) //0,1,2 2-találat
	{
		/if(talalt && (iter[i] == -1))
			break;
		
		if(iter[i] > -1)
			count = a++;
		
		//printf("Az: %d", a);
		if(iter[i] == value)
			talalt = true;
		
		if((iter[i] == -1) && (ret == -1))
			ret = i;/
		
		//printf("Jah: %d | %d", i, len);
		if(iter[i] == value)
			return true;
			
		//printf("Az: %d", i);
	}
	
	/if(len == 1)
		printf("A2"), iter[0] = value;
	else
		printf("A3 | %d", i), iter[i] = value;/
	printf("%d", i - 1);
	iter[i - 1] = value;
	//printf("asd");
	count++;
	return true;
}*/

stock
	DIter_RemoveEx(iter[], value, &count, len = sizeof(iter))
{
	new i = -1,
		a = 0,
		temp,
		bool:talalt = false;
	
	for(;++i < len;)
	{
		if(iter[i] > -1)
			a++;
			
		if(talalt) //3
		{
			temp = iter[i];
			iter[i - 1] = temp;
			
			if(iter[i + 1] == -1)
				{ iter[i] = -1; a--; break; }
		}
		
		if((iter[i] == value) || talalt) //2
		{
			iter[i] = -1;
			talalt = true;
		}
	}
	
	if(talalt)
		count--;
	
	return true;
}