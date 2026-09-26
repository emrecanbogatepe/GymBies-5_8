// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#include "SIK_StartAssetTransaction.h"

USIK_StartAssetTransaction* USIK_StartAssetTransaction::StartAssetTransaction(const FString& Key, const int32& AppId,
    const int64& SteamId, const FString& AssetId0, const int32& AssetQuantity0, const FString& Currency,
    const FString& Language, const FString& IpAddress, const FString& Referrer, const bool& ClientAuth)
{
    USIK_StartAssetTransaction* Node = NewObject<USIK_StartAssetTransaction>();
    Node->Var_Key = Key;
    Node->Var_AppId = AppId;
    Node->Var_SteamId = SteamId;
    Node->Var_AssetId0 = AssetId0;
    Node->Var_AssetQuantity0 = AssetQuantity0;
    Node->Var_Currency = Currency;
    Node->Var_Language = Language;
    Node->Var_IpAddress = IpAddress;
    Node->Var_Referrer = Referrer;
    Node->Var_ClientAuth = ClientAuth;
    return Node;
}

void USIK_StartAssetTransaction::Activate()
{
    Super::Activate();
    FString URL = FString::Printf(TEXT("%s/ISteamEconomy/StartAssetTransaction/v1/"), *APIEndpoint);
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(URL);
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("key"), Var_Key);
    JsonObject->SetNumberField(TEXT("appid"), Var_AppId);
    JsonObject->SetNumberField(TEXT("steamid"), Var_SteamId);
    JsonObject->SetStringField(TEXT("assetid0"), Var_AssetId0);
    JsonObject->SetNumberField(TEXT("assetquantity0"), Var_AssetQuantity0);
    JsonObject->SetStringField(TEXT("currency"), Var_Currency);
    JsonObject->SetStringField(TEXT("language"), Var_Language);
    JsonObject->SetStringField(TEXT("ipaddress"), Var_IpAddress);
    if(!Var_Referrer.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("referrer"), Var_Referrer);
    }
    JsonObject->SetBoolField(TEXT("clientauth"), Var_ClientAuth);
    FString Content;
    TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Content);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    Request->SetContentAsString(Content);
    Request->OnProcessRequestComplete().BindUObject(this, &USIK_StartAssetTransaction::OnResponseReceived);
    Request->ProcessRequest();
}
