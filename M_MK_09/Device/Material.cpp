#include "pch.h"
#include "Material.h"
#include "ResourceManager.h"

#include <assimp/scene.h>
#include <filesystem>
#include "DX_Renderer.h"
#include "Render_Helper.h"

 
void Material::Create(aiMaterial* pAiMaterial)
{
    //TEMP
    aiColor3D color(0.f, 0.f, 0.f);
    float value = 0.f;
    aiString texturePath;

    if (AI_SUCCESS == pAiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color))
    {
        DIFFUSE = XMFLOAT4(color.r, color.g, color.b, 1);
    }
    else 
    {
        DIFFUSE = XMFLOAT4(1, 1, 1, 1);
    }

    if (AI_SUCCESS == pAiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color))
    {
        AMBIENT = XMFLOAT4(color.r, color.g, color.b, 1);
    }

    else
    {
        AMBIENT = XMFLOAT4(0.2f, 0.2f, 0.2f, 1);
    }

    
    if (AI_SUCCESS == pAiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color))
    {
        SPECULAR = XMFLOAT4(color.r, color.g, color.b, 1);
    }
    else
    {
        SPECULAR = XMFLOAT4(1, 1, 1, 1);
    }

    if (AI_SUCCESS == pAiMaterial->Get(AI_MATKEY_SHININESS, value))
    {
        POWER = value;

        POWER = clamp(POWER, 0.f, 100.f);

    }

    else
    {
        POWER = 50.f;
    }

    if (pAiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
    {
        Texture_Path = std::filesystem::path(texturePath.C_Str()).wstring();

        SetTexture(Texture_Path);

    }

    else Texture_Path = L"NOTEX";

}

//사실 이건 Phong 구조의 문조니깐. PBR로 넘어가는게 편하긴 하겠다. ㅇㅇ 
//매번 상수 버퍼를 바꿔야 하니깐. 

void Material::Bind(ID3D11DeviceContext* DXDC)
{
    cbMATERIAL* cb_m =  DX_Renderer::Instance().GetRH()->GetCB<cbMATERIAL>();
    cb_m->Set_Mat_Dif(DIFFUSE);
    cb_m->Set_Mat_Ambi(AMBIENT);
    cb_m->Set_Mat_Spc(SPECULAR);
    cb_m->Set_Mat_Pw(POWER);
    cb_m->Update(DXDC);
    
    UINT slot = cb_m->GetRegisterSlot();
    ID3D11Buffer* cb = cb_m->GetBuffer();

    DXDC->VSSetConstantBuffers(slot, 1 , &cb);
    DXDC->PSSetConstantBuffers(slot, 1, &cb);
    DXDC->PSSetShaderResources(0, 1, m_Diffuse_Texture.GetAddressOf());


}

void Material::SetTexture(std::wstring Path)
{
 Texture* texture = ResourceManager::Instance().GetTextureResource()->GetTexture(Path);
 ID3D11ShaderResourceView* Textureview = texture->GetTexture();
 m_Diffuse_Texture = Textureview;

}
