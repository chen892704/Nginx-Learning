#ifndef _NGX_CLOCK_HPP
#define _NGX_CLOCK_HPP

#include "Nginx.hpp"
#include "NgxCppInc.hpp"

// Nginx��ʱ�书�ܷ�װ
class NgxClock final
{
public:
	NgxClock()  = default;
	~NgxClock() = default;
	
private:
	ngx_time_t m_time = now();			// ��ʼ��Ϊ��ǰʱ��
	
public:
	static const ngx_time_t & now()		// ��ȡ��ǰʱ��
	{
		ngx_time_update();				// ���»���ʱ��
		
		return * ngx_timeofday();		// ��ȡ����ʱ��
	}
	
	ngx_time_t delta() const			// �������ŵ�ʱ��
	{
		auto t = now();					// ��ȡ��ǰʱ��
		
		t.sec -= m_time.sec;			// �����ֵ
		t.msec -= m_time.msec;
		
		return t;
	}
	
	double elapsed() const				// ���ظ�������ʽ��ʱ��
	{
		auto t = delta();				// �������ŵ�ʱ��
										// ת��Ϊ double
		return t.sec + t.msec * 1.0 / 1000;
	}
	
	void reset()						// ��λ��ʱ��
	{
		m_time = now();
	}
};

#endif