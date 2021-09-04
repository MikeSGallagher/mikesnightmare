//Spawn helper function
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
	
//Custom Spawn Objects
	SpawnObject("KR_ATMGreen", "3706.7 402.012 5984.86", "90 0 0"); //Green Mountain ATM 1
	SpawnObject("KR_ATMYellow", "3704.7 402.332 6003.1", "275 0 0"); //Green Mountain ATM 2
	SpawnObject("KR_ATMGreen", "8360.15 292.054 5994.15", "325 0 0"); //Kumyrna ATM 1
	SpawnObject("KR_ATMBlackWhite", "8350.7 292.011 5978.3", "235 0 0"); //Kumyrna ATM 2

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();
	
	//INIT WEATHER AFTER ECONOMY INIT------------------------
		Weather weather = g_Game.GetWeather();

		weather.MissionWeather(true);    // false = use weather controller from Weather.c

		weather.GetOvercast().SetLimits( 0.0 , 0.9 );
		weather.GetRain().SetLimits( 0.0 , 0.0 );
		weather.GetFog().SetLimits( 0.0 , 0.1 );
	
		weather.GetOvercast().Set( Math.RandomFloatInclusive(0.02, 0.9), 1, 0);
		//weather.GetRain().Set( 0, 0, 0);
		weather.GetRain().Set( Math.RandomFloatInclusive(0.0, 0.1), 1, 0);
		weather.GetFog().Set( Math.RandomFloatInclusive(0.0, 0.1), 1, 0);

		weather.GetOvercast().SetForecastTimeLimits( 1800 , 1800 );
		weather.GetRain().SetForecastTimeLimits( 600 , 600 );
		weather.GetFog().SetForecastTimeLimits( 600 , 600 );
		
		weather.SetWindMaximumSpeed( 20 );
		weather.SetWindFunctionParams( 0, 0, 1 );
		
	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 7, reset_day = 20;
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

			SetRandomHealth( itemEnt );

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
		   player.GetInventory().CreateInInventory("DryBag_Black");    // added items
		   player.GetInventory().CreateInInventory("Compass");    // added items
		   player.GetInventory().CreateInInventory("Canteen");    // added items
		   player.GetInventory().CreateInInventory("SardinesCan");    // added items
		   player.GetInventory().CreateInInventory("CombatKnife");    // added items
		   player.GetInventory().CreateInInventory("CanOpener");    // added items
		   player.GetInventory().CreateInInventory("ChernarusMap");    // added items
		   player.GetInventory().CreateInInventory("M4A1");    // added items
		   player.GetInventory().CreateInInventory("Mag_STANAGCoupled_30Rnd");    // added items
		   player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");    // added items
		   player.GetInventory().CreateInInventory("BandageDressing");    // added items
		   player.GetInventory().CreateInInventory("PurificationTablets");    // added items
		   player.GetInventory().CreateInInventory("WoodAxe");    // added items
		   player.GetInventory().CreateInInventory("BakedBeansCan");    // added items
		   player.GetInventory().CreateInInventory("SodaCan_Pipsi");    // added items
		   player.GetInventory().CreateInInventory("SodaCan_Spite");    // added items
		   player.GetInventory().CreateInInventory("TacticalBaconCan");    // added items
		   player.GetInventory().CreateInInventory("Matchbox");    // added items
		   player.GetInventory().CreateInInventory("DuctTape");    // added items
		   player.GetInventory().CreateInInventory("Whetstone");    // added items
		   player.GetInventory().CreateInInventory("Mag_STANAGCoupled_30Rnd");    // added items
		   player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");    // added items
		   player.GetInventory().CreateInInventory("Binoculars");    // added items
		   player.GetInventory().CreateInInventory("SewingKit");    // added items
		   player.GetInventory().CreateInInventory("WeaponCleaningKit");    // added items
		}
		
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
			SetRandomHealth( itemClothing );
		
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
	}
	
	//override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    //{
      // Don't leave out the super (super important super.InvokeOnConnect( player, identity);

    //GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(NotificationSystem.SimpleNoticiation, 1000, false ,  
    //    "Welcome to {Mikes Nightmare V2}, Check out our Server Information by Pressing PAUSE/BREAK or by Pressing ESC and Clicking Server Panel. Feel free to join our Discord", "Welcome Gamers!", 
    //    "Notifications/gui/data/notifications.edds", ARGB(240, 90, 140, 195), 30, 
    //    identity);
          
    //}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}