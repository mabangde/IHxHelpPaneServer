#include <Windows.h>
#include <Objbase.h>
#include <stdio.h>
struct __declspec(uuid("{8cec592c-07a1-11d9-b15e-000d56bfe6ee}"))
    IHxHelpPaneServer : public IUnknown {
    virtual HRESULT __stdcall DisplayTask(PWCHAR) = 0;
    virtual HRESULT __stdcall DisplayContents(PWCHAR) = 0;
    virtual HRESULT __stdcall DisplaySearchResults(PWCHAR) = 0;
    virtual HRESULT __stdcall Execute(const PWCHAR) = 0;
};

HRESULT CoInitializeIHxHelpIds(LPGUID Clsid, LPGUID Iid) {
    HRESULT Result = S_OK;
    Result = CLSIDFromString(L"{8cec58ae-07a1-11d9-b15e-000d56bfe6ee}", Clsid);
    Result = CLSIDFromString(L"{8cec592c-07a1-11d9-b15e-000d56bfe6ee}", Iid);
    return Result;
}

INT wmain(INT argc, WCHAR* argv[]) {
    if (argc != 2) {
        return 1;
    }

    HRESULT Result = S_OK;
    GUID CLSID_IHxHelpPaneServer;
    GUID IID_IHxHelpPaneServer;
    WCHAR fullpath[256];
    swprintf_s(fullpath, L"file:///%s", argv[1]);

    IHxHelpPaneServer* Help = NULL;

    CoInitializeIHxHelpIds(&CLSID_IHxHelpPaneServer, &IID_IHxHelpPaneServer);
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    CoCreateInstance(CLSID_IHxHelpPaneServer, NULL, CLSCTX_ALL, IID_IHxHelpPaneServer, (PVOID*)&Help);

    Help->Execute(fullpath);
    Help->Release();
    CoUninitialize();

    return 0;
}
