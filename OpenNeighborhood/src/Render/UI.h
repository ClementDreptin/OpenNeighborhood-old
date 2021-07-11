#pragma once

#include <ImGui/imgui.h>

using ConfirmCallbackFn = std::function<void()>;
using InputTextCallbackFn = std::function<void(const std::string&)>;

class UI
{
public:
    static void Init();

    static void BeginFrame();
    static void EndFrame();

    static void Cleanup();

    static void DisplayErrorModal();
    static void DisplayConfirmModal();
    static void DisplayInputTextModal();

    inline static void SetConfirm(bool confirm) { s_Confirm = confirm; }
    inline static void SetConfirmMessage(const std::string& message) { s_ConfirmMessage = message; }
    inline static void SetConfirmCallback(const ConfirmCallbackFn& callback) { s_ConfirmCallback = callback; }

    inline static bool IsGood() { return s_Success; }
    inline static void SetSuccess(bool success) { s_Success = success; }
    inline static void SetErrorMessage(const std::string& message) { s_ErrorMessage = message; }

    inline static void DisplayInputText(bool display) { s_InputText = display; }
    inline static void SetInputTextHeader(const std::string& header) { s_InputTextHeader = header; }
    inline static void SetInputTextCallback(const InputTextCallbackFn& callback) { s_InputTextCallback = callback; }

    inline static ImFont* GetBoldFont() { return s_OpenSansBold; }
    inline static ImFont* GetRegularFont() { return s_OpenSansRegular; }
    inline static ImFont* GetRegularBigFont() { return s_OpenSansRegularBig; }
private:
    static void SetDarkThemeColors();

    static bool s_Confirm;
    static std::string s_ConfirmMessage;
    static ConfirmCallbackFn s_ConfirmCallback;

    static bool s_Success;
    static std::string s_ErrorMessage;

    static bool s_InputText;
    static std::string s_InputTextHeader;
    static InputTextCallbackFn s_InputTextCallback;

    static ImFont* s_OpenSansBold;
    static ImFont* s_OpenSansRegular;
    static ImFont* s_OpenSansRegularBig;
};
