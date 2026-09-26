// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#include "SIK_RankedByPublicationOrder.h"

USIK_RankedByPublicationOrder* USIK_RankedByPublicationOrder::RankedByPublicationOrder(const FString& Key,
    const int64& SteamId, const int32& AppId, const int32& StartIdx, const int32& Count, const int32& TagCount,
    const int32& UserTagCount, const bool& HasAppAdminAccess, const int32& FileType, const FString& Tag0,
    const FString& UserTag0)
{
    USIK_RankedByPublicationOrder* Node = NewObject<USIK_RankedByPublicationOrder>();
    Node->Var_Key = Key;
    Node->Var_SteamId = SteamId;
    Node->Var_AppId = AppId;
    Node->Var_StartIdx = StartIdx;
    Node->Var_Count = Count;
    Node->Var_TagCount = TagCount;
    Node->Var_UserTagCount = UserTagCount;
    Node->Var_HasAppAdminAccess = HasAppAdminAccess;
    Node->Var_FileType = FileType;
    Node->Var_Tag0 = Tag0;
    Node->Var_UserTag0 = UserTag0;
    return Node;
}

void USIK_RankedByPublicationOrder::Activate()
{
    Super::Activate();
    FString URL = FString::Printf(TEXT("%s/ISteamPublishedItemSearch/RankedByPublicationOrder/v1/"), *APIEndpoint);
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(URL);
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("key"), Var_Key);
    JsonObject->SetNumberField(TEXT("steamid"), Var_SteamId);
    JsonObject->SetNumberField(TEXT("appid"), Var_AppId);
    JsonObject->SetNumberField(TEXT("startidx"), Var_StartIdx);
    JsonObject->SetNumberField(TEXT("count"), Var_Count);
    JsonObject->SetNumberField(TEXT("tagcount"), Var_TagCount);
    JsonObject->SetNumberField(TEXT("usertagcount"), Var_UserTagCount);
    JsonObject->SetBoolField(TEXT("hasappadminaccess"), Var_HasAppAdminAccess);
    if(Var_FileType != -1)
    {
        JsonObject->SetNumberField(TEXT("fileType"), Var_FileType);
    }
    if(!Var_Tag0.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("tag[0]"), Var_Tag0);
    }
    if(!Var_UserTag0.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("usertag[0]"), Var_UserTag0);
    }
    FString Content;
    TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Content);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    Request->SetContentAsString(Content);
    Request->OnProcessRequestComplete().BindUObject(this, &USIK_RankedByPublicationOrder::OnResponseReceived);
    Request->ProcessRequest();
}
