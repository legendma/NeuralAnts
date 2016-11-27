//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <WinSDKVer.h>
#define _WIN32_WINNT 0x0600
#include <SDKDDKVer.h>

// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP

// Include <mcx.h> if you need this
#define NOMCX

// Include <winsvc.h> if you need this
#define NOSERVICE

// WinHelp is deprecated
#define NOHELP

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>
#include <CommonStates.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <Effects.h>
#include <Model.h>
#include <SimpleMath.h>

#include <algorithm>
#include <exception>
#include <list>
#include <map>
#include <memory>
#include <stack>
#include <stdexcept>


namespace DX
{
	static const float PI = 3.1415926535897932384626433832795f;
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            // Set a breakpoint on this line to catch DirectX API errors
            throw std::exception();
        }
    }

	inline void ThrowIfFailed(bool success)
	{
		if(!success)
		{
			// Set a breakpoint on this line to catch DirectX API errors
			throw std::exception();
		}
	}
}

/***********************************
  Singleton Class
***********************************/
template <typename T>
class Singleton
{ 
	Singleton(const Singleton& that) = delete;
	Singleton& operator=(Singleton const&) = delete;
public:
	static T& Instance();

protected:
	Singleton() {};

private:
	static T *m_the_instance;
};

template <typename T>
T& Singleton<T>::Instance()
{
	if(m_the_instance == nullptr)
	{
		m_the_instance = new T();
	}

	return(*m_the_instance);
}

template <typename T>
T* Singleton<T>::m_the_instance = nullptr;

/***********************************
  Utils Class
***********************************/
class Utils
{
public:
	static std::wstring ToWide(const char *str)
	{
		auto in = std::string(str);
		
		return(ToWide(in));
	}

	static std::wstring ToWide(const std::string &str)
	{
		auto in = std::string(str);
		auto required_size = MultiByteToWideChar(CP_UTF8, 0, &in[0], (int)in.size(), NULL, 0);
		auto out = std::wstring(required_size, 0);

		MultiByteToWideChar(CP_UTF8, 0, &in[0], (int)in.size(), &out[0], required_size);
		return(out);
	}

	static std::string GetFileExtension(const std::string &str)
	{
		auto found = str.find_last_of(".");
		return(str.substr(found+1));
	}

	static std::wstring GetFileExtension(const std::wstring &str)
	{
		auto found = str.find_last_of(L".");
		return(str.substr(found + 1));
	}

	static float DegreesToRadians(float degrees)
	{
		return(DX::PI * degrees / 180.0f);
	}
};
