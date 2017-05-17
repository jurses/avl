#include <ctime>
#include <cstdlib>
template<class T>
class randVec{
	private:
		T* valor_;
		int tam_;
	public:
		randVec(int);
		~randVec();
		T& operator[]();
};

template<class T>
randVec::randVec(int tam):
tam_(tam)
{
	bool repetidos = false;
	valor_ = new valor_[tam_];

	for(int i=0; i<tam_; i++)
		for(int j=i; j>=0; j--)
			if(i!=j)
				if(valor_[i] == valor_[j])

}


