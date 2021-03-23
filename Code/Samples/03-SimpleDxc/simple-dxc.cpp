// simple-dxc.exe myshader.hlsl -E main -T ps_6_0 -Zi -D MYDEFINE=1 -Fo myshader.bin -Fd myshader.pdb -Qstrip_reflect

#include <atlbase.h>
#include <dxcapi.h>
#include <d3d12shader.h>

#include <vector>


int main(int argc, wchar_t *argv[])
{
#if 0
	std::vector<LPCWSTR> arguments;
	for (int i = 1; i < argc; ++i)
		arguments.push_back(argv[i]);
#endif

	// Create compiler and utils.
	CComPtr<IDxcUtils> pUtils;
	CComPtr<IDxcCompiler3> pCompiler;
	DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&pUtils));
	DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&pCompiler));

	// Create default include handler. (You can create your own...)
	CComPtr<IDxcIncludeHandler> pIncludeHandler;
	pUtils->CreateDefaultIncludeHandler(&pIncludeHandler);

	// simple-dxc.exe myshader.hlsl -E main -T ps_6_0 -Zi -D MYDEFINE=1
	//   -Fo myshader.bin -Fd myshader.pdb -Qstrip_reflect
	LPCWSTR pszArgs[] = {
		L"SimpleVS.hlsl",
		L"-E", L"main",
		L"-T", L"vs_6_0",
		L"-Zi",
		L"-Fo", L"output.fxo",
		L"-Qstrip_reflect",
	};

	// Open source file.
	CComPtr<IDxcBlobEncoding> pSource = nullptr;
	pUtils->LoadFile(L"SimpleVS.hlsl", nullptr, &pSource);
	DxcBuffer Source;
	Source.Ptr  = pSource->GetBufferPointer();
	Source.Size = pSource->GetBufferSize();
	Source.Encoding = DXC_CP_ACP; // Assume BOM says UTF8 or UTF16 or this is ANSI text.

	// Compile it with specified arguments.
	CComPtr<IDxcResult> pResults;
	pCompiler->Compile(&Source, pszArgs, _countof(pszArgs),
		pIncludeHandler, IID_PPV_ARGS(&pResults));
	
	// Print errors if present.
	CComPtr<IDxcBlobUtf8> pErrors = nullptr;
	pResults->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&pErrors), nullptr);
	if (pErrors != nullptr && pErrors->GetStringLength() != 0)
	{
		// Note that d3dcomp;iler would return null if no errors or warnings are present.
		// IDxcCompiler3::Compile will always return an error buffer, but its length will
		// be zero if there are errors or warnings.
		wprintf(L"Warnings and Errors:\n%S\n", pErrors->GetStringPointer());
	}

	// Quit if the compilation failed.
	HRESULT hr;
	pResults->GetStatus(&hr);
	if (FAILED(hr))
	{
		wprintf(L"Compilation Failed\n");
		return 1;
	}

	// Save shader binary.
	CComPtr<IDxcBlob> pShader = nullptr;
	CComPtr<IDxcBlobUtf16> pShaderName = nullptr;
	pResults->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&pShader), &pShaderName);
	if (pShader != nullptr)
	{
		FILE *fp = NULL;
		_wfopen_s(&fp, pShaderName->GetStringPointer(), L"wb");
		fwrite(pShader->GetBufferPointer(), pShader->GetBufferSize(), 1, fp);
		fclose(fp);
	}

	// TODO: save pdb, hash, reflection.

	wprintf(L"done.");
	return 0;
}
