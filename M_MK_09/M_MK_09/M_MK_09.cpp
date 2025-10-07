#include "pch.h"
#include <iostream>
#include <Windows.h>
#include "Core.h"



int main()
{
	Core core;
	core.Sets();
	core.MessagePump();
	core.End();

}

//여기를 일단 Core, Window 로 설정