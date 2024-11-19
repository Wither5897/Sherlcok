// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EditorToolWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Jin/AJH_EditorActor.h"
#include "Kismet/GameplayStatics.h"
#include "Jin/AJH_EditorCharacter.h"
#include "SK/SaveLevelUI.h"
#include "Jin/AJH_WorldActor.h"
#include "Components/VerticalBox.h"

void UAJH_EditorToolWidget::NativeConstruct()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(0);
	query = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	pc = GetWorld()->GetFirstPlayerController();
	me = Cast<AAJH_EditorCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_EditorCharacter::StaticClass()));

	Main_Btn_Character->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Character);
	Main_Btn_Evidence->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Evidence);
	Main_Btn_Weapon->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Weapon);
	Main_Btn_Place->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Place);
	Main_Btn_Back->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Back);
	Main_Btn_PrePage->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_PrePage);
	Main_Btn_NextPage->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_NextPage);
	// Character
	Btn_Character_0->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyBtn_Character_0);
	Character_Btn_Back->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Back);

	// Evidence
	Btn_Evidence_0->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyBtn_Evidence_0);
	Evidence_Btn_Back->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Back);

	// Weapon
	Btn_Weapon_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyBtn_Weapon_1);
	Weapon_Btn_Back->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Back);

	// place
	Place_Btn_Furnitures_Up_0->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Furnitures_Up_0);
	Place_Btn_Furnitures_Up_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Furnitures_Up_1);
	Place_Btn_Furnitures_Down_0->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Furnitures_Down_0);
	Place_Btn_Furnitures_Down_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Furnitures_Down_1);
	Place_Btn_Back->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Back);

	// Footway
	Place_Btn_Footway_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Footway_1);
	Place_Btn_Footway_2->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Footway_2);
	Place_Btn_Footway_3->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Footway_3);
	// Road
	Place_Btn_Road_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Road_1);
	Place_Btn_Road_2->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Road_2);
	Place_Btn_Road_3->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Road_3);
	// Station
	Place_Btn_Station_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyPlace_Btn_Station_1);

	// Furnitures
	Furnitures_Btn_Back->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Back);
	///////////////////////////////////////////Furnitures_Vertical///////////////////////////////////////////
	Furnitures_Btn_Up->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Up);
	Furnitures_Btn_Bed->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Bed);
	Furnitures_Btn_Carpet->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Carpet);
	Furnitures_Btn_sofa->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_sofa);
	Furnitures_Btn_Ottoman->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Ottoman);
	Furnitures_Btn_Down->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Down);
	///////////////////////////////////////////Furnitures_Vertical_1//////////////////////////////////////
	Furnitures_Btn_Up_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Up_1);
	Furnitures_Btn_Chair_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Chair_1);
	Furnitures_Btn_Chair_2->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Chair_2);
	Furnitures_Btn_Chair_3->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Chair_3);
	Furnitures_Btn_Chair_4->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Chair_4);
	Furnitures_Btn_Down_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Down_1);
	///////////////////////////////////////////Furnitures_Vertical_2//////////////////////////////////////
	Furnitures_Btn_Up_2->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Up_2);
	Furnitures_Btn_Table_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Table_1);
	Furnitures_Btn_Table_2->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Table_2);
	Furnitures_Btn_Table_3->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Table_3);
	Furnitures_Btn_Table_4->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Table_4);
	Furnitures_Btn_Down_2->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Down_2);
	///////////////////////////////////////////Furnitures_Vertical_3//////////////////////////////////////
	Furnitures_Btn_Up_3->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Up_3);
	Furnitures_Btn_Tv->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Tv);
	Furnitures_Btn_Vase_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_1);
	Furnitures_Btn_Vase_2->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_2);
	Furnitures_Btn_Vase_3->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_3);
	Furnitures_Btn_Down_3->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Down_3);
	///////////////////////////////////////////Furnitures_Vertical_4//////////////////////////////////////
	Furnitures_Btn_Up_4->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Up_4);
	Furnitures_Btn_Vase_4->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_4);
	Furnitures_Btn_Vase_5->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_5);
	Furnitures_Btn_Vase_6->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_6);
	Furnitures_Btn_Down_4->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyFurnitures_Btn_Down_4);

	

	LevelSaveButton->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::LevelSaveButtonClicked);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_Character()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(1);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_Evidence()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(2);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_Weapon()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(3);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_Place()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(4);
	Place_Vertical_0->SetVisibility(ESlateVisibility::Visible);
	Place_Vertical_1->SetVisibility(ESlateVisibility::Collapsed);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_Back()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(0);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_PrePage()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(0);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_NextPage()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(5);
	Furnitures_Vertical->SetVisibility(ESlateVisibility::Visible);
	Furnitures_Vertical_1->SetVisibility(ESlateVisibility::Collapsed);
	Furnitures_Vertical_2->SetVisibility(ESlateVisibility::Collapsed);
	Furnitures_Vertical_3->SetVisibility(ESlateVisibility::Collapsed);
	Furnitures_Vertical_4->SetVisibility(ESlateVisibility::Collapsed);
}

void UAJH_EditorToolWidget::OnMyBtn_Character_0()
{
	me->FactoryChange = Character_0Factory;
	me->FactoryChange = Character_0Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyBtn_Character_1()
{
	me->EditorChange = Character_1Factory;
	me->FactoryChange = Character_1Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyBtn_Character_2()
{
	me->FactoryChange = Character_2Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyBtn_Evidence_0()
{
	me->EditorChange = EditorEvidenceFactory_0;
	me->FactoryChange = EvidenceFactory_0;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyBtn_Weapon_1()
{
	me->EditorChange = EditorWeaponFactory_1;
	me->FactoryChange = weaponFactory_1;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Furnitures_Up_0()
{
	Place_Vertical_0->SetVisibility(ESlateVisibility::Visible);
	Place_Vertical_1->SetVisibility(ESlateVisibility::Collapsed);
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Furnitures_Up_1()
{
	Place_Vertical_0->SetVisibility(ESlateVisibility::Visible);
	Place_Vertical_1->SetVisibility(ESlateVisibility::Collapsed);
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Furnitures_Down_0()
{
	Place_Vertical_0->SetVisibility(ESlateVisibility::Collapsed);
	Place_Vertical_1->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Furnitures_Down_1()
{
	Place_Vertical_0->SetVisibility(ESlateVisibility::Collapsed);
	Place_Vertical_1->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Footway_1()
{
	me->EditorChange = EditFootway_1Factory;
	me->FactoryChange = Footway_1Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Footway_2()
{
	me->EditorChange = EditFootway_2Factory;
	me->FactoryChange = Footway_2Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Footway_3()
{
	me->EditorChange = EditFootway_3Factory;
	me->FactoryChange = Footway_3Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Road_1()
{
	me->EditorChange = EditRoad_1Factory;
	me->FactoryChange = Road_1Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Road_2()
{
	me->EditorChange = EditRoad_2Factory;
	me->FactoryChange = Road_2Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Road_3()
{
	me->EditorChange = EditRoad_3Factory;
	me->FactoryChange = Road_3Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyPlace_Btn_Station_1()
{
	me->EditorChange = EditStation_1Factory;
	me->FactoryChange = Station_1Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Up()
{
	Furnitures_Vertical->SetVisibility(ESlateVisibility::Visible);
	Furnitures_Vertical_1->SetVisibility(ESlateVisibility::Collapsed);
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Bed()
{
	me->EditorChange = EditBedFactory;
	me->FactoryChange = BedFactory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Carpet()
{
	me->EditorChange = EditCarpetFactory;
	me->FactoryChange = CarpetFactory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_sofa()
{
	me->EditorChange = EditsofaFactory;
	me->FactoryChange = sofaFactory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Ottoman()
{
	me->EditorChange = EditOttomanFactory;
	me->FactoryChange = OttomanFactory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Down()
{
	Furnitures_Vertical->SetVisibility(ESlateVisibility::Collapsed);
	Furnitures_Vertical_1->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Up_1()
{
	Furnitures_Vertical->SetVisibility(ESlateVisibility::Visible);
	Furnitures_Vertical_1->SetVisibility(ESlateVisibility::Collapsed);
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Chair_1()
{
	me->EditorChange = EditChair_1Factory;
	me->FactoryChange = Chair_1Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Chair_2()
{
	me->EditorChange = EditChair_2Factory;
	me->FactoryChange = Chair_2Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Chair_3()
{
	me->EditorChange = EditChair_3Factory;
	me->FactoryChange = Chair_3Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Chair_4()
{
	me->EditorChange = EditChair_4Factory;
	me->FactoryChange = Chair_4Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Down_1()
{
	Furnitures_Vertical_1->SetVisibility(ESlateVisibility::Collapsed);
	Furnitures_Vertical_2->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Up_2()
{
	Furnitures_Vertical_1->SetVisibility(ESlateVisibility::Visible);
	Furnitures_Vertical_2->SetVisibility(ESlateVisibility::Collapsed);
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Table_1()
{
	me->EditorChange = EditTable_1Factory;
	me->FactoryChange = Table_1Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Table_2()
{
	me->EditorChange = EditTable_2Factory;
	me->FactoryChange = Table_2Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Table_3()
{
	me->EditorChange = EditTable_3Factory;
	me->FactoryChange = Table_3Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Table_4()
{
	me->EditorChange = EditTable_4Factory;
	me->FactoryChange = Table_4Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Down_2()
{
	Furnitures_Vertical_2->SetVisibility(ESlateVisibility::Collapsed);
	Furnitures_Vertical_3->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Up_3()
{
	Furnitures_Vertical_2->SetVisibility(ESlateVisibility::Visible);
	Furnitures_Vertical_3->SetVisibility(ESlateVisibility::Collapsed);
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Tv()
{
	me->EditorChange = EditTVFactory;
	me->FactoryChange = TVFactory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_1()
{
	me->EditorChange = EditVase_1Factory;
	me->FactoryChange = Vase_1Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_2()
{
	me->EditorChange = EditVase_2Factory;
	me->FactoryChange = Vase_2Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_3()
{
	me->EditorChange = EditVase_3Factory;
	me->FactoryChange = Vase_3Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Down_3()
{
	Furnitures_Vertical_3->SetVisibility(ESlateVisibility::Collapsed);
	Furnitures_Vertical_4->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Up_4()
{
	Furnitures_Vertical_3->SetVisibility(ESlateVisibility::Visible);
	Furnitures_Vertical_4->SetVisibility(ESlateVisibility::Collapsed);
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_4()
{
	me->EditorChange = EditVase_4Factory;
	me->FactoryChange = Vase_4Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_5()
{
	me->EditorChange = EditVase_5Factory;
	me->FactoryChange = Vase_5Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_6()
{
	me->EditorChange = EditVase_6Factory;
	me->FactoryChange = Vase_6Factory;
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true);
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
	}
}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Vase_7()
{

}

void UAJH_EditorToolWidget::OnMyFurnitures_Btn_Down_4()
{
	
}

void UAJH_EditorToolWidget::LevelSaveButtonClicked(){
	me->SaveLevelWidget->SetVisibility(ESlateVisibility::Visible);
}
