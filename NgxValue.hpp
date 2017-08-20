#ifndef _NGX_VALUE_HPP
#define _NGX_VALUE_HPP

#include "Nginx.hpp"
#include "NgxCppInc.hpp"

// ��Чֵ�ķ�װ
class NgxUnsetValue final					// final ��ֹ���̳�
{
public:
	template<typename T>
	operator T () const						// ת�͵�����T
	{
		return static_cast<T>(-1);			// ʹ�� static_cast ת�� -1
	}

	template<typename T>
	operator T * () const					// ת�͵�����T*����ָ������
	{
		return reinterpret_cast<T*>(-1);
	}

public:
	static const NgxUnsetValue & get()		// ��ȡȫ��Ψһ����
	{
		static NgxUnsetValue const v = {};	// ��̬����������
		return v;
	}
};

auto&& ngx_nil = NgxUnsetValue::get();		// ��ֵ���ã���������


// ��װ���������͵Ļ�������
class NgxValue final
{
public:
	NgxValue()  = default;								// Ĭ�Ϲ���/��������
	~NgxValue() = default;

public:
	template<typename T>
	static bool invalid(const T & v)					// ��Чֵ�ж�
	{
		return v == static_cast<T>(NgxUnsetValue::get());
	}

	template<typename T, typename U>
	static void init(T & x, const U & v)
	{
		if(invalid(x))
		{
			x = v;										// ���Ϊ��Чֵ���ʼ��
		}
	}

	template<typename T, typename U, typename V>
	static void merge(T & c, const U & p, const V & d)	// ������ֵ
	{
		if(invalid(c))
		{
			c = invalid(p) ? d : p;						// ���p,��Ч���ʼ��
		}
	}

	template<typename T>
	bool operator==(const T & x, const NgxUnsetValue &)	// �� ngx_nil �Ƚ�
	{
		return NgxValue::invalid(x);
	}

public:
	template<typename T, typename ... Args>
	static void unset(T & v, Args & ... args)			// ����δ��ʼ��
	{
		v = NgxUnsetValue::get();						// ��Ϊδ��ʼ��״̬
		unset(args...);									// �ݹ鴦��ʣ��ģ�����

		static void unset() {}							// �ݹ��սắ��
	}
};

#endif