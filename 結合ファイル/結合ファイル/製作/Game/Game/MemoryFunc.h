#pragma once
#include"Object.h"

class MemoryFunction {
public:
	template<typename T>
	static void check_mem(T*);//ÉÅÉÇÉäämï€Ç≈Ç´ÇΩÇ©
	//template<typename T>
	//static void delete_mem(T&);
};

template<typename T>
void MemoryFunction::check_mem(T* obj)
{
	if (obj == nullptr)throw"Object is nullptr";
}

//template<typename T>
//inline void MemoryFunction::delete_mem(T& obj)
//{
//	if (*obj == nullptr)return;
//	delete obj;
//}
