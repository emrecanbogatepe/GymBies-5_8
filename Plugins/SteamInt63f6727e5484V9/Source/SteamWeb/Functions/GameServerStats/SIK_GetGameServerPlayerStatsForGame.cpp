// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#include "SIK_GetGameServerPlayerStatsForGame.h"

USIK_GetGameServerPlayerStatsForGame* USIK_GetGameServerPlayerStatsForGame::GetGameServerPlayerStatsForGame(
    const FString& Key, const int64& GameId, const int32& AppId, const FString& RangeStart, const FString& RangeEnd,
    const int32& MaxResults)
{
    USIK_GetGameServerPlayerStatsForGame* Node = NewObject<USIK_GetGameServerPlayerStatsForGame>();
    Node->Var_Key = Key;
    Node->Var_GameId = GameId;
    Node->Var_AppId = AppId;
    Node->Var_RangeStart = RangeStart;
    Node->Var_RangeEnd = RangeEnd;
    Node->Var_MaxResults = MaxResults;
    return Node;
}

void USIK_GetGameServerPlayerStatsForGame::Activate()
{
    Super::Activate();
    FString URL = FString::Printf(TEXT("%s/ISteamGameServerStats/GetGameServerPlayerStatsForGame/v1/"), *APIEndpoint);
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(URL);
    Request->SetVerb("GET");
    Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("key"), Var_Key);
    JsonObject->SetNumberField(TEXT("gameid"), Var_GameId);
    JsonObject->SetNumberField(TEXT("appid"), Var_AppId);
    JsonObject->SetStringField(TEXT("rangestart"), Var_RangeStart);
    JsonObject->SetStringField(TEXT("rangeend"), Var_RangeEnd);
    if(Var_MaxResults != -1)
    {
        JsonObject->SetNumberField(TEXT("maxresults"), Var_MaxResults);
    }
    FString Content;
    TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Content);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    Request->SetContentAsString(Content);
    Request->OnProcessRequestComplete().BindUObject(this, &USIK_GetGameServerPlayerStatsForGame::OnResponseReceived);
    Request->ProcessRequest();
}
