#pragma once
#include "Object.h"

void Object::SetPosition(Vector3 position)
{
	m_transform.Set_L_Pos(position);
}

void Object::SetRotation(Vector3 rotation)
{
	m_transform.Set_L_Rot(rotation);

}

void Object::SetScale(Vector3 scale)
{
	m_transform.Set_L_Scl(scale);
}

void Object::SetParent(shared_ptr<Object> parent)
{
	m_parent = parent;
}

Vector3 Object::Get_L_Pos()
{
	return m_transform.Get_L_Pos();
}


Vector3 Object::Get_L_Rot()
{
	return m_transform.Get_L_Rot();

}


Vector3 Object::Get_L_Scl()
{
	return m_transform.Get_L_Scl();

}


Vector3 Object::Get_W_Pos()
{
	return m_transform.Get_W_Pos();
}


Vector3 Object::Get_W_Rot()
{
	return m_transform.Get_W_Rot();

}


Vector3 Object::Get_W_Scl()
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
