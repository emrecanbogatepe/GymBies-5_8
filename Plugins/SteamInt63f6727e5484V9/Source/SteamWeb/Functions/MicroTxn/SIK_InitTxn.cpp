// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#include "SIK_InitTxn.h"

USIK_InitTxn* USIK_InitTxn::InitTxn(const FString& Key, const int64& OrderId, const int64& SteamId, const int32& AppId,
    const int32& ItemCount, const FString& Language, const FString& Currency, const FString& UserSession,
    const FString& IpAddress, const int32& ItemId, const int32& Qty, const int64& Amount, const FString& Description,
    const FString& Category, const int32& AssociatedBundle, const FString& BillingType, const FString& Period,
    const int32& Frequency, const int64& RecurringAmt, const int32& BundleCount, const int32& BundleId,
    const int32& BundleQty, const FString& BundleDesc, const FString& BundleCategory, bool bUseSandBox)
{
    USIK_InitTxn* Node = NewObject<USIK_InitTxn>();
    Node->Var_Key = Key;
    Node->Var_OrderId = OrderId;
    Node->Var_SteamId = SteamId;
    Node->Var_AppId = AppId;
    Node->Var_ItemCount = ItemCount;
    Node->Var_Language = Language;
    Node->Var_Currency = Currency;
    Node->Var_UserSession = UserSession;
    Node->Var_IpAddress = IpAddress;
    Node->Var_ItemId = ItemId;
    Node->Var_Qty = Qty;
    Node->Var_Amount = Amount;
    Node->Var_Description = Description;
    Node->Var_Category = Category;
    Node->Var_AssociatedBundle = AssociatedBundle;
    Node->Var_BillingType = BillingType;
    Node->Var_Period = Period;
    Node->Var_Frequency = Frequency;
    Node->Var_RecurringAmt = RecurringAmt;
    Node->Var_BundleCount = BundleCount;
    Node->Var_BundleId = BundleId;
    Node->Var_BundleQty = BundleQty;
    Node->Var_BundleDesc = BundleDesc;
    Node->Var_BundleCategory = BundleCategory;
    Node->Var_bUseSandBox = bUseSandBox;
    return Node;
}

void USIK_InitTxn::Activate()
{
    Super::Activate();
    FString URL = FString::Printf(TEXT("%s/%s/InitTxn/v3/"), *APIEndpoint, Var_bUseSandBox ? TEXT("ISteamMicroTxnSandbox") : TEXT("ISteamMicroTxn"));
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(URL);
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("key"), Var_Key);
    JsonObject->SetNumberField(TEXT("orderid"), Var_OrderId);
    JsonObject->SetNumberField(TEXT("steamid"), Var_SteamId);
    JsonObject->SetNumberField(TEXT("appid"), Var_AppId);
    JsonObject->SetNumberField(TEXT("itemcount"), Var_ItemCount);
    JsonObject->SetStringField(TEXT("language"), Var_Language);
    JsonObject->SetStringField(TEXT("currency"), Var_Currency);
    JsonObject->SetStringField(TEXT("usersession"), Var_UserSession);
    if(!Var_IpAddress.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("ipaddress"), Var_IpAddress);
    }
    JsonObject->SetNumberField(TEXT("itemid[0]"), Var_ItemId);
    JsonObject->SetNumberField(TEXT("qty[0]"), Var_Qty);
    JsonObject->SetNumberField(TEXT("amount[0]"), Var_Amount);
    JsonObject->SetStringField(TEXT("description[0]"), Var_Description);
    if(!Var_Category.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("category[0]"), Var_Category);
    }
    if(Var_AssociatedBundle != -1)
    {
        JsonObject->SetNumberField(TEXT("associated_bundle[0]"), Var_AssociatedBundle);
    }
    if(!Var_BillingType.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("billingtype[0]"), Var_BillingType);
    }
    if(!Var_Period.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("period[0]"), Var_Period);
    }
    if(Var_Frequency != -1)
    {
        JsonObject->SetNumberField(TEXT("frequency[0]"), Var_Frequency);
    }
    if(Var_RecurringAmt != -1)
    {
        JsonObject->SetNumberField(TEXT("recurringamt[0]"), Var_RecurringAmt);
    }
    if(Var_BundleCount != -1)
    {
        JsonObject->SetNumberField(TEXT("bundlecount"), Var_BundleCount);
    }
    if(Var_BundleId != -1)
    {
        JsonObject->SetNumberField(TEXT("bundleid[0]"), Var_BundleId);
    }
    if(Var_BundleQty != -1)
    {
        JsonObject->SetNumberField(TEXT("bundle_qty[0]"), Var_BundleQty);
    }
    if(!Var_BundleDesc.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("bundle_desc[0]"), Var_BundleDesc);
    }
    if(!Var_BundleCategory.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("bundle_category[0]"), Var_BundleCategory);
    }
    FString Content;
    TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Content);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    Request->SetContentAsString(Content);
    Request->OnProcessRequestComplete().BindUObject(this, &USIK_InitTxn::OnResponseReceived);
    Request->ProcessRequest();
}
