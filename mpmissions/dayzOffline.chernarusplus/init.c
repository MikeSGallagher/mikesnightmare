#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\CustomObjects\\SpawnObject.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\CustomObjects\\CustomBridgePrison.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\CustomObjects\\CustomAreas.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\CustomObjects\\Traders.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\CustomObjects\\Admins.c"

void main()
{

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
	Place_BridgePrison();
	Place_CustomAreas();
    Place_Traders();
    Place_Admins();
	
   //GetCEApi().ExportProxyData( "7500 0 7500", 10000 );  //Center of map, radius of how far to go out and find buildings.
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
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}