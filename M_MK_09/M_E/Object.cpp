#pragma once

#include "pch.h"
#include "Object.h"

void Object::SetPosition(XMFLOAT3 position)
{
	m_transform.Set_L_Pos(position);
}

void Object::SetRotation(XMFLOAT3 rotation)
{
	m_transform.Set_L_Rot(rotation);

}

void Object::SetScale(XMFLOAT3 scale)
{
	m_transform.Set_L_Scl(scale);
}

void Object::SetParent(shared_ptr<Object> parent)
{
	m_parent = parent;
}

XMFLOAT3 Object::Get_L_Pos()
{
	return m_transform.Get_L_Pos();
}


XMFLOAT3 Object::Get_L_Rot()
{
	return m_transform.Get_L_Rot();

}


XMFLOAT3 Object::Get_L_Scl()
{
	return m_transform.Get_L_Scl();

}


XMFLOAT3 Object::Get_W_Pos()
{
	return m_transform.Get_W_Pos();
}


XMFLOAT3 Object::Get_W_Rot()
{
	return m_transform.Get_W_Rot();

}


XMFLOAT3 Object::Get_W_Scl()
{
	return m_transform.Get_W_Scl();

}


weak_ptr<Object> Object::GetParent()
{
	return m_parent;
}

 Transform Object::GetTransform() 
{
	return m_transform;
}
