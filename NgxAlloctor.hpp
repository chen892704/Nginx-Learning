#ifndef _NGX_ALLOCTOR_HPP
#define _NGX_ALLOCTOR_HPP

#include "Nginx.hpp"
#include "NgxCppInc.hpp"
#include "NgxWrapper.hpp"

// �ڴ�������
template<typename T>
class NgxAlloctor : public NgxWrapper<ngx_pool_t>
{
public:
	typedef NgxWrapper<ngx_pool_t>	super_type;		// �����Ͷ���
	typedef NgxAlloctor				this_type;
	
public:
	typedef std::size_t	size_type;					// �ڲ����Ͷ���
	typedef T*			pointer;
	typedef T			value_type;
	
public:
	NgxAlloctor(ngx_pool_t * p) : super_type(p) {}
	
	~NgxAlloctor() = default;
	
	pointer allocate(size_type n)					// ����n��Ԫ��������ڴ�
	{
		return reinterpret_cast<pointer>(			// ʹ��Nginx�ڴ��
					ngx_pnalloc(get(), n * sizeof(T)));
	}
	
	void deallocate(pointer ptr, size_type n)		// �ͷ��ڴ棬��Nginx�����ڴ����
	{
		boost::ignore_unused(n);					// ���Գ��ڲ���n
		ngx_pfree(get(), ptr);						// �黹�ڴ��
	}
};

#endif