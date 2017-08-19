#ifndef _NGX_DATETIME_HPP
#define _NGX_DATETIME_HPP

#include "Nginx.hpp"
#include "NgxCppInc.hpp"

// Nginx�����ڹ��ܷ�װ
class NgxDatetime final
{
public:
	NgxDatetime()  = default;
	~NgxDatetime() = default;
	
public:
	static ngx_str_t since()			// ��װ ngx_time()
	{
		return ngx_time();
	}
	
	static ngx_str_t today()			// ��ȡ��ǰ����
	{
		ngx_tm_t tm;
		
		ngx_localtime(since(), &tm);	// ת��Ϊ����ʱ��
		
		static u_char buf[20] = {};		// ��̬�ַ������������
										// ��ʽ��Ϊ yyyy-mm-dd����ȡ�ַ���ĩβ
		auto p = ngx_snprintf(buf, 20, "%d-%02d-%02d",
								tm.ngx_tm_year, tm.ngx_tm_mon, tm.ngx_tm_mday);
								
		return ngx_str_t{staic_cast<std::size_t>(p - buf), buf};
	}
	
	static ngx_str_t http(std::time_t t = since())		// ʱ���ת�����ַ���
	{
		static u_char buf[50] = {};
		
		auto p = ngx_http_time(buf, t);
		
		return ngx_str_t{static_cast<std::size_t>(p - buf), buf};
	}
	
	static std::time_t http(ngx_str_t & str)			// �����ַ���תʱ���
	{
		return ngx_parse_http_time(str.data, str.len);
	}
};

#endif