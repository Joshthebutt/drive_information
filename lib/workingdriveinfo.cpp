#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

struct DiskInfo {
    int rawReadErrorRate;
};

// Function to retrieve raw read error rate
int getRawReadErrorRate() {
    int errorRate = 0;

    // Initialize COM library
    HRESULT hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize COM library. Error code: 0x" << std::hex << hres << std::dec << std::endl;
        return errorRate;
    }

    // Initialize COM security
    hres = CoInitializeSecurity(
        nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr);
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize COM security. Error code: 0x" << std::hex << hres << std::dec << std::endl;
        CoUninitialize();
        return errorRate;
    }

    // Initialize WMI
    IWbemLocator* pLoc = nullptr;
    IWbemServices* pSvc = nullptr;
    IEnumWbemClassObject* pEnumerator = nullptr;

    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres)) {
        std::cerr << "Failed to create IWbemLocator object. Error code: 0x" << std::hex << hres << std::dec << std::endl;
        CoUninitialize();
        return errorRate;
    }

    // Connect to the local WMI namespace
    BSTR namespaceStr = SysAllocString(L"ROOT\\CIMV2");
    hres = pLoc->ConnectServer(namespaceStr, nullptr, nullptr, 0, 0, 0, 0L, &pSvc);
    SysFreeString(namespaceStr);

    if (FAILED(hres)) {
        std::cerr << "Failed to connect to WMI namespace. Error code: 0x"
                  << std::hex << hres << std::dec << std::endl;
        pLoc->Release();
        CoUninitialize();
        return errorRate;
    }

    // Set the security levels on the proxy
    hres = CoSetProxyBlanket(
        pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
    if (FAILED(hres)) {
        std::cerr << "Failed to set proxy blanket. Error code: 0x" << std::hex << hres << std::dec << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return errorRate;
    }

    // Query the CIM_DiskDrive class
    BSTR queryLanguage = SysAllocString(L"WQL");
    BSTR queryString = SysAllocString(L"SELECT * FROM Win32_DiskDrive WHERE MediaType='Fixed hard disk media'");
    hres = pSvc->ExecQuery(queryLanguage, queryString, WBEM_FLAG_FORWARD_ONLY, nullptr, &pEnumerator);
    SysFreeString(queryLanguage);
    SysFreeString(queryString);

    // Iterate through the results
    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;

    while (pEnumerator) {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if (0 == uReturn)
            break;

        VARIANT vtProp;

        // Get the RawReadErrorRate property
        hres = pclsObj->Get(L"RawReadErrorRate", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            errorRate = vtProp.uintVal;
            VariantClear(&vtProp);
        }

        pclsObj->Release();
    }

    // Cleanup
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return errorRate;
}

int getReallocatedSectorsCount() {
    int reallocatedCount = 0;

    // Initialize COM library
    HRESULT hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize COM library. Error code: 0x" << std::hex << hres << std::dec << std::endl;
        return reallocatedCount;
    }

    // Initialize COM security
    hres = CoInitializeSecurity(
        nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr);
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize COM security. Error code: 0x" << std::hex << hres << std::dec << std::endl;
        CoUninitialize();
        return reallocatedCount;
    }

    // Initialize WMI
    IWbemLocator* pLoc = nullptr;
    IWbemServices* pSvc = nullptr;
    IEnumWbemClassObject* pEnumerator = nullptr;

    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres)) {
        std::cerr << "Failed to create IWbemLocator object. Error code: 0x" << std::hex << hres << std::dec << std::endl;
        CoUninitialize();
        return reallocatedCount;
    }

    // Connect to the local WMI namespace
    BSTR namespaceStr = SysAllocString(L"ROOT\\CIMV2");
    hres = pLoc->ConnectServer(namespaceStr, nullptr, nullptr, 0, 0, 0, 0L, &pSvc);
    SysFreeString(namespaceStr);

    if (FAILED(hres)) {
        std::cerr << "Failed to connect to WMI namespace. Error code: 0x"
                  << std::hex << hres << std::dec << std::endl;
        pLoc->Release();
        CoUninitialize();
        return reallocatedCount;
    }

    // Set the security levels on the proxy
    hres = CoSetProxyBlanket(
        pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
    if (FAILED(hres)) {
        std::cerr << "Failed to set proxy blanket. Error code: 0x" << std::hex << hres << std::dec << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return reallocatedCount;
    }

    // Query the CIM_DiskDrive class
    BSTR queryLanguage = SysAllocString(L"WQL");
   BSTR queryString = SysAllocString(L"SELECT * FROM Win32_DiskDrive WHERE MediaType='Fixed hard disk media'");
    hres = pSvc->ExecQuery(queryLanguage, queryString, WBEM_FLAG_FORWARD_ONLY, nullptr, &pEnumerator);
    SysFreeString(queryLanguage);
    SysFreeString(queryString);

    // Iterate through the results
    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;

     while (pEnumerator) {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if (0 == uReturn)
            break;

        VARIANT vtProp;

        // Get the ReallocatedSectors property (modify property name as needed)
        hres = pclsObj->Get(L"ReallocatedSectors", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            reallocatedCount = vtProp.uintVal;
            VariantClear(&vtProp);
        }

        pclsObj->Release();
    }


    // Cleanup
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return reallocatedCount;
}


DiskInfo getDiskInfo() {
    DiskInfo info;
    info.rawReadErrorRate = getRawReadErrorRate();
    return info;
}


extern "C" {
    __declspec(dllexport) DiskInfo getDiskInfoWrapper() {
        return getDiskInfo();
    }
}