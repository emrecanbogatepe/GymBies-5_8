// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#include "SIK_UpdateItemDefs.h"

USIK_UpdateItemDefs* USIK_UpdateItemDefs::UpdateItemDefs(const FString& Key, const int32& AppId,
    const TArray<FSIK_WebItemDef> ItemDefs)
{
    USIK_UpdateItemDefs* Node = NewObject<USIK_UpdateItemDefs>();
    Node->Var_Key = Key;
    Node->Var_AppId = AppId;
    Node->Var_ItemDefs = ItemDefs;
    return Node;
}

void USIK_UpdateItemDefs::Activate()
{
    Super::Activate();
    FString URL = FString::Printf(TEXT("%s/IGameInventory/UpdateItemDefs/v1/"), *APIEndpoint);
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(URL);
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("key"), Var_Key);
    JsonObject->SetNumberField(TEXT("appid"), Var_AppId);
    TArray<TSharedPtr<FJsonValue>> ItemDefsArray;
    for (FSIK_WebItemDef ItemDef : Var_ItemDefs)
    {
        TSharedPtr<FJsonObject> ItemDefObject = MakeShareable(new FJsonObject);
        ItemDefObject->SetNumberField(TEXT("appid"), FCString::Atoi(*ItemDef.AppId));
        ItemDefObject->SetNumberField(TEXT("itemdefid"), FCString::Atoi(*ItemDef.ItemDefId));
        ItemDefObject->SetStringField(TEXT("type"), ItemDef.Type);
        ItemDefObject->SetStringField(TEXT("display_type"), ItemDef.DisplayType);
        ItemDefObject->SetStringField(TEXT("name"), ItemDef.Name);
        ItemDefObject->SetStringField(TEXT("description"), ItemDef.Description);
        ItemDefObject->SetStringField(TEXT("background_color"), ItemDef.BackgroundColor);
        ItemDefObject->SetBoolField(TEXT("tradable"), ItemDef.Tradable);
        ItemDefObject->SetBoolField(TEXT("marketable"), ItemDef.Marketable);
        ItemDefObject->SetBoolField(TEXT("commodity"), ItemDef.Commodity);
        ItemDefObject->SetStringField(TEXT("tags"), ItemDef.Tags);
        ItemDefsArray.Add(MakeShareable(new FJsonValueObject(ItemDefObject)));
    }
    JsonObject->SetArrayField(TEXT("itemdefs"), ItemDefsArray);
    FString Content;
    TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Content);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    Request->SetContentAsString(Content);
    Request->OnProcessRequestComplete().BindUObject(this, &USIK_UpdateItemDefs::OnResponseReceived);
    Request->ProcessRequest();
}
