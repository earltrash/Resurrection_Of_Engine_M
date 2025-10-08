#pragma once 
//#include "Device.h"
#include <iostream>
#include "D3D11.h"

class IConstBuffer
{
public:
	virtual ~IConstBuffer() = default;
	virtual HRESULT Create(ID3D11Device* dev) = 0;
	virtual ID3D11Buffer* GetBuffer() const = 0;
	virtual HRESULT Update(ID3D11DeviceContext* DXDC) = 0;
	virtual UINT GetRegisterSlot() const = 0;
	virtual const std::type_info& GetTypeInfo() const = 0; // 런타임에 타입 받아오는 거 땜에 그래 template
};