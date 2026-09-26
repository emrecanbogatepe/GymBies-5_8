// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#include "SIK_UpdateSession.h"

USIK_UpdateSession* USIK_UpdateSession::UpdateSession(const FString& Key, const int64& SessionId, const int32& AppId,
    const FString& Title, const FString& Users, const int64& SteamId)
{
    USIK_UpdateSession* Node = NewObject<USIK_UpdateSession>();
    Node->Var_Key = Key;
    Node->Var_SessionId = SessionId;
    Node->Var_AppId = AppId;
    Node->Var_Title = Title;
    Node->Var_Users = Users;
    Node->Var_SteamId = SteamId;
    return Node;
}

void USIK_UpdateSession::Activate()
{
    Super::Activate();
    FString URL = FString::Printf(TEXT("%s/IGameNotificationsService/UpdateSession/v1/"), *APIEndpoint);
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(URL);
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("key"), Var_Key);
    JsonObject->SetNumberField(TEXT("sessionid"), Var_SessionId);
    JsonObject->SetNumberField(TEXT("appid"), Var_AppId);
    JsonObject->SetStringField(TEXT("title"), Var_Title);
    JsonObject->SetStringField(TEXT("users"), Var_Users);
    JsonObject->SetNumberField(TEXT("steamid"), Var_SteamId);
    FString Content;
    TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Content);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    Request->SetContentAsString(FString::Printf(TEXT("key=%s&input_json=%s"), *Var_Key, *Content));
    Request->OnProcessRequestComplete().BindUObject(this, &USIK_UpdateSession::OnResponseReceived);
    Request->ProcessRequest();
}
