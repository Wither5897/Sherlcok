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

void UAJH_EditorToolWidget::LevelSaveButtonClicked(){
	me->SaveLevelWidget->SetVisibility(ESlateVisibility::Visible);
}
