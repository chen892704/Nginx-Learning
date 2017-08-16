#inlcude <boost/type_traits.hpp>	// ʹ�� type_traits Ԫ������������

// ��װ����һ��Nginx���ݶ�����һ�������ֻ࣬�ܱ��̳�ʹ��
template<typename T>
class NgxWrapper
{
public:
	typedef typename boost::remove_pointer<T>::type wrapped_type;

	typedef wrapped_type *							pointer_type;
	typedef wrapped_type &							reference_type;

private:
	pointer_type m_ptr = nullptr;       // ʹ��ָ�뱣�����Ĭ���ǿ�ָ��


protected:
	// ������ָ������
	NgxWrapper(pointer_type p):m_ptr(p) {}
	// ��������������
	NgxWrapper(reference_type x):m_ptr(&x) {}
	// �������������κ���(NgxWrapper �����������������ڹ������ڴ�ظ���)
	~NgxWrapper() = default;

public:
	pointer_type get() const			// ����ָ���Ա
	{
		return m_ptr;
	}

	operator bool () const				// ת��Ϊbool
	{
		return get();
	}

	operator pointer_type () const		// ת��Ϊָ������
	{
		return get();
	}

	pointer_type operator->() const		// ָ�����������
	{
		return get();
	}
}
