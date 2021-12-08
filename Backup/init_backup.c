void SpawnObject( string type, vector position, vector orientation )
{
    auto obj = GetGame().CreateObject( type, position );
    obj.SetPosition( position );
    obj.SetOrientation( orientation );
    obj.SetOrientation( obj.GetOrientation() ); //Collision fix
    obj.Update();
    obj.SetAffectPathgraph( true, false );
    if( obj.CanAffectPathgraph() ) GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().UpdatePathgraphRegionByObject, 100, false, obj );
}

void main()
{
	SpawnObject("KR_ATM", "3706.7 402.012 5984.86", "90 0 0"); //Green Mountain ATM 1
	SpawnObject("KR_ATMGreen", "3704.7 402.332 6003.1", "275 0 0"); //Green Mountain ATM 2
	SpawnObject("KR_ATMBlue", "8360.15 292.054 5994.15", "325 0 0"); //Kumyrna ATM 1
	SpawnObject("KR_ATMBlackWhite", "8350.7 292.011 5978.3", "235 0 0"); //Kumyrna ATM 2

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
			
			itemEnt = itemClothing.GetInventory().CreateInInventory( "BandageDressing" );
			if ( Class.CastTo( itemBs, itemEnt ) )
				itemBs.SetQuantity( 2 );

			string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
			int rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( chemlightArray[rndIndex] );
			SetRandomHealth( itemEnt );

			rand = Math.RandomFloatInclusive( 0.0, 1.0 );
			if ( rand < 0.35 )
				itemEnt = player.GetInventory().CreateInInventory( "Apple" );
			else if ( rand > 0.65 )
				itemEnt = player.GetInventory().CreateInInventory( "Pear" );
			else
				itemEnt = player.GetInventory().CreateInInventory( "Plum" );

			SetRandomHealth( itemEnt );
		}
		
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
			SetRandomHealth( itemClothing );
		
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}