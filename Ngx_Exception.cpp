#include <Nginx.hpp>
#include <NgxCppInc.hpp>

// �쳣��
class NgxException final : public virtual std::exception,
						   public virtual boost::exception
{
public:
	typedef boost::string_ref string_ref_type;
	
private:
	ngx_int_t		m_code = NGX_ERROR;		// �������
	std::string		m_msg;					// ������Ϣ
	
public:
	NgxException(ngx_int_t x, string_ref_type msg):
					m_code(x), m_msg(msg) {}
				 
	NgxException(ngx_int_t x = NGX_ERROR):
			NgxException(x, "") {}			// ί�й���
			
	NgxException(string_ref_type msg):
			NgxException(NGX_ERROR, msg)	// ί�й���
			
	virtual ~NgxException() noexcept		// ����������
	{}
	
public:
	ngx_int_t code() const					// ��ȡ������
	{
		return m_code; 
	}
	
	virtual const char * what() const noexcept override
	{
		return m_msg.c_str();
	}
	
public:
	static void raise(ngx_int_t rc = NGX_ERROR, string_ref_type msg = "")
	{
		throw NgxException(rc, msg);		// �׳��쳣
	}
	
	// ��������Ƿ�����
	static void require(bool cond, ngx_int_t e = NGX_ERROR)
	{
		if(!cond)							// ���������Ԥ�����׳��쳣
		{
			raise(e);
		}
	}
	
	// �������룬Ĭ��Ҫ����NGX_OK
	static void require(ngx_int_t rc, ngx_int_t x = NGX_OK)
	{
		require(rc == x, rc);				// �������OK���׳��쳣
	}
	
	// ����ָ�룬Ҫ��ָ��ǿ�
	static void require(T * p, ngx_int_t e = NGX_ERROR)
	{
		require(p != nullptr, e);			// ����ǿ�ָ�����׳��쳣
	}
	
	// require �ķ�����
	static void fail(bool cond, ngx_int_t e = NGX_ERROR)
	{
		if(cond)
		{
			raise(e);						// �������Ԥ�����׳��쳣
		}
	}
}