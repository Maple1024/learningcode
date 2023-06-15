#include <iostream>
using namespace std;

void* Memcpy(void* dst, const void* src, size_t size);

int main(int argc, char* argv[])
{
	char buf[100] = "abcdefghijk"; 
	char* buff1 = (char*)malloc(strlen(buf)+1);
	//memcpy(buf + 2, buf, 5); //abcdehijk  abcdehijk
	Memcpy(buff1, buf, sizeof(buf));  //abcdehijk
	printf("%s\n", buff1 ); //
	free(buff1);
	return 0;
}

void* Memcpy(void* dst, const void* src, size_t size)//void* 是一种通用指针类型，它表示指向未知类型的内存地址的指针，也可以称为无类型指针
{
	if (dst == nullptr || src == nullptr)
		return nullptr;

	char* pdst = (char*)dst;
	char* psrc = (char*)src;

	if (psrc < pdst && (psrc + size > pdst))//在同一串字符上复制
	{
		pdst = pdst + size - 1;
		psrc = psrc + size - 1;

		while (size--)
			*pdst-- = *psrc--;
	}
	else//在不同字符串区间复制
	{
		while (size--)
		{
			*pdst++ = *psrc++;
		}
	}

	return dst;
}