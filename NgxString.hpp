#ifndef _NGX_STRING_HPP
#define _NGX_STRING_HPP

#include <Nginx.hpp>
#include <NgxCppInc.hpp>
#include "NgxWrapper.hpp"

class NgxString final : public NgxWrapper<ngx_str_t>
{
public:
	typedef NgxWrapper<ngx_str_t>	super_type;
	typedef NgxString				this_type;
	
	typedef boost::string_ref		string_ref_type;	// char* �ַ�����������
	
public:
	NgxString(ngx_str_t & str) : super_type(str) {}
	
	~NgxString() = default;
	
public:
	const char * data() const							// ��ȡ�ַ���
	{
		return reinterpret_cast<const char*>(get()->data);
	}
	
	std::size_t size() const							// ��ȡ����
	{
		return get()->len;
	}
	
	bool empty() const									// �Ƿ�Ϊ�մ�
	{
		return !get()->data || !get()->len;
	}
	
	string_ref_type str() const							// ת��Ϊ char* �ַ�����ʽ
	{
		return string_ref_type(data(), size());
	}
	
public:
	operator ngx_int_t () const							// �ַ���ת��������
	{
		return ngx_atoi(get()->data, get()->len);
	}
	
	// ���رȽϲ���������Сд���бȽ����� ngx_str_t ����
	friend bool operator==(const this_type & l, const this_type & r)
	{
		return l.size() == r.size() &&
				ngx_strncmp(l.data(), r.data(), l.size()) == 0;
	}
	
	template<typename ... Args>
	void printf(const Args & ... args) const			// ��ȫ��ʽ��
	{
		auto p = ngx_snprintf(get()->data, get()->len, args ...);
		
		// ����ʵ�ʳ���
		get()->len = static_cast<std::size_t>(p - get()->data);
	}
	
public:
	template<typename T>
	friend T & operator<<(T & o, const this_type & s)	// ���������������
	{
		o.write(s.data(), s.size());					// ���ַ���д����
		return o;
	}
};

#endif