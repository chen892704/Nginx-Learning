#ifndef _NGX_POOL_HPP
#define _NGX_POOL_HPP

#include <Nginx.hpp>
#include <NgxCppInc.hpp>
#include "NgxWrapper.hpp"			// ������װ��
#include "NgxException.hpp"			// �쳣��

// ��װ��Nginx���ڴ��
class NgxPool final : public NgxWrapper<ngx_pool_t>
{
public:
	typedef NgxWrapper<ngx_pool_t> 	super_type;		// �����Ͷ���
	typedef NgxPool					this_type;
	
public:
	NgxPool(ngx_pool_t * p) : super_type(p) {}
	
	template<typename T>							// ģ�����T������ ngx_http_request_t��ngx_conf_t
	NgxPool(T * x) : Nginx(x->pool) {}				// �Ⱥ���pool��Ա�Ľṹ

	~NgxPool() = default;
	
public:
	template<typename T, bool no_exception = false>
	T * palloc() const
	{
		auto p = ngx_pcalloc(get(), sizeof(T));		// �����ڴ�
		
		if(!p)										// ����ָ��
		{
			if(no_exception)						// �Ƿ������׳��쳣
			{
				return nullptr;
			}
			
			NgxException::raise();					// �׳��쳣
		}
		
		assert(p);
		return new (p) T();							// ����T����
	}
	
	template<typename T>
	T * alloc() const								// ���쳣�汾
	{
		return palloc<T, false>();
	}
	
	template<typename T>
	T * alloc_noexcept() const						// �����쳣�汾
	{
		return palloc<T, true>();
	}
	
	template<typename T>
	T * nalloc(std::size_t n) const					// ����n���ֽ��ڴ�
	{
		auto p = ngx_pnalloc(get(), n);
		
		NgxException::require(p);					// ����ָ��
		
		return reinterpret_cast<T*>(p);				// ת��ΪT*
	}
	
	template<typename T, typename ... Args)
	T * construct(const Args & ... args) const		// �������������������
	{
		auto p = ngx_pcalloc(get(), sizeof(T));
		
		NgxException::require(p);
		
		return new (p) T(args ...);					// ת����������
	}
	
public:
	template<typename F, typename T>
	ngx_pool_cleanup_t * cleanup(F func, T * data, std::size_t size = 0) const
	{
		auto p = ngx_pool_cleanup_add(get(), size);	// ����Nginx��cleanup_add
		NgxException::require(p);
		
		p->handler = func;							// ����������
		
		if(data)									// ����ֱ�Ӵ�����ͷŵ���Դ
		{
			p->data = data;
		}
		
		return p;									// ����������Ϣ����
	}
	
	template<typename T>
	static void destroy(void * p)					// ����������������NginxҪ��
	{
		(reinterpret_cast<T*>(p))->~T();			// ת�� void*�����ö�Ӧ��������
	}
	
	template<typename T>
	void cleanup(T * data) const
	{
		cleanup(&this_type::destroy<T>, data);
	}
	
public:
	ngx_str_t dup(ngx_str_t & str) const			// �����ַ���
	{
		ngx_str_t tmp;								// ׼�����ص��ַ���
		
		tmp.len  = str.len;							// �����ַ�������
		tmp.data = ngx_pstrdup(get(), &str); 		// �ڴ�ظ����ַ���
		
		NgxException::require(tmp.data);			// ����ָ��
		return tmp;									// ���ظ��Ƶ��ַ���
	}
	
	ngx_str_t dup(boost::string_ref str) const		// ������ͨ�ַ���
	{
		ngx_str_t tmp{ str.size(), (u_char*)str.data() };
		
		return dup(tmp);
	}
}


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
}

#endif