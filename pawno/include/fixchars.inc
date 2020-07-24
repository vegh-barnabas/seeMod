// ----------------------------------
// Magyar karakterek megjelenítésének automatikus javítása
// Használathoz csak be kell ágyazni: #include <fixchars>
// Készítette GameStar 2010 (frissítve 2012 április)
// Weboldal: www.gtaforum.hu
// ----------------------------------

#if defined fixchars_included
	#endinput
#endif
#define fixchars_included

stock fixchar(chr)
{
	switch(chr)
	{
	    case 'ö': return '¨';
	    case 'Ö': return '‘';
	    case 'ü': return '¬';
	    case 'Ü': return '•';
	    case 'ó': return '¦';
	    case 'Ó': return '';
	    case 'õ': return '§';
	    case 'Õ': return '';
	    case 'ú': return 'ª';
	    case 'Ú': return '“';
	    case 'é': return '';
	    case 'É': return '‡';
	    case 'á': return '˜';
	    case 'Á': return '';
	    case 'û': return '«';
	    case 'Û': return '·';
	    case 'í': return '¢';
	    case 'Í': return '‹';
	}
	return chr;
}

stock fixchars(string[])
{
	new chr;
	while(string[chr])
	{
	    string[chr] = fixchar(string[chr]);
	    chr++;
	}
	return 1;
}

stock unfixchar(chr)
{
	switch(chr)
	{
	    case '¨': return 'ö';
	    case '‘': return 'Ö';
	    case '¬': return 'ü';
	    case '•': return 'Ü';
	    case '¦': return 'ó';
	    case '': return 'Ó';
	    case '§': return 'õ';
	    case '': return 'Õ';
	    case 'ª': return 'ú';
	    case '“': return 'Ú';
	    case '': return 'é';
	    case '‡': return 'É';
	    case '˜': return 'á';
	    case '': return 'Á';
	    case '«': return 'û';
	    case '·': return 'Û';
	    case '¢': return 'í';
	    case '‹': return 'Í';
	}
	return chr;
}

stock unfixchars(string[])
{
	new chr;
	while(string[chr])
	{
	    string[chr] = unfixchar(string[chr]);
	    chr++;
	}
	return 1;
}

stock fixchars_GameTextForPlayer(playerid,text[],time,style)
{
    fixchars(text);
	return GameTextForPlayer(playerid,text,time,style);
}
#define GameTextForPlayer fixchars_GameTextForPlayer

stock fixchars_GameTextForAll(text[],time,style)
{
    fixchars(text);
	return GameTextForAll(text,time,style);
}
#define GameTextForAll fixchars_GameTextForAll

stock Text:fixchars_TextDrawCreate(Float:x, Float:y, text[])
{
    fixchars(text);
	return TextDrawCreate(x,y,text);
}
#define TextDrawCreate fixchars_TextDrawCreate

stock Menu:fixchars_CreateMenu(title[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0)
{
    fixchars(title);
	return CreateMenu(title,columns,x,y,col1width,col2width);
}
#define CreateMenu fixchars_CreateMenu

stock fixchars_SetMenuColumnHeader(Menu:menuid, column, columnheader[])
{
    fixchars(columnheader);
	return SetMenuColumnHeader(menuid, column, columnheader);
}
#define SetMenuColumnHeader fixchars_SetMenuColumnHeader

stock fixchars_AddMenuItem(Menu:menuid, column, menutext[])
{
    fixchars(menutext);
 	return AddMenuItem(menuid, column, menutext);
}
#define AddMenuItem fixchars_AddMenuItem

stock fixchars_TextDrawSetString(Text:text, string[])
{
    fixchars(string);
	return TextDrawSetString(text,string);
}
#define TextDrawSetString fixchars_TextDrawSetString

stock PlayerText:fixchars_CreatePlayerTextDraw(playerid, Float:x, Float:y, text[])
{
	fixchars(text);
	return CreatePlayerTextDraw(playerid, x, y, text);
}
#define CreatePlayerTextDraw fixchars_CreatePlayerTextDraw

stock fixchars_PlayerTextDrawSetS(playerid, PlayerText:text, string[])
{
	fixchars(string);
	return PlayerTextDrawSetString(playerid,text,string);
}
#define PlayerTextDrawSetString fixchars_PlayerTextDrawSetS
