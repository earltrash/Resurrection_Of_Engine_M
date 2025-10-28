#pragma once
#include "Commons.h"
#include "Effect.h"


struct Axis
{
	std::array<PosNCol, 6> Vertexes;
	UINT VertexCnt = 6;
};


class GridNAxis
{
public:

	friend Effect;

	GridNAxis() = default;
	~GridNAxis() = default;

	bool Set_GridNAxis(ID3D11Device*& Dev);
	bool Set_Effect(ID3D11Device*& Dev);
	void Draw();

public:
	

	ID3D11Buffer* GetAxisVB() const { return m_AxisVB; }
	ID3D11Buffer* GetGridVB() const { return m_GridVB; }
	ID3D11InputLayout* GetLayout() const { return m_LineInputLayout; }
	ID3D11VertexShader* GetVS() const { return m_LineVS; }
	ID3D11PixelShader* GetPS() const { return m_LinePS; }


public:
	std::vector<PosNCol> GridVertices;
	inline Effect* GetFX() { return fx.get(); }
private:
	ID3D11Buffer* m_AxisVB = nullptr;
	ID3D11Buffer* m_GridVB = nullptr;

	ID3D11InputLayout* m_LineInputLayout;
	ID3D11VertexShader* m_LineVS;
	ID3D11PixelShader* m_LinePS;

private:

	std::unique_ptr<Effect> fx = nullptr;
};