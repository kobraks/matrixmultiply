#include "MatrixWriter.h"

#include "TypeDefs.h"

template <class T>
matrixm::matrix::MatrixWriter<T>::MatrixWriter(std::ostream& _out) : out_(_out)
{
	if (!_out.good())
		throw exceptions::MatrixReadEmptyException();
}

template <class T>
void matrixm::matrix::MatrixWriter<T>::write(const AbstractMatrix* _matrix)
{
	Matrix<T>* matrix = dynamic_cast<Matrix<T>*>(const_cast<AbstractMatrix*>(_matrix));
	if (!matrix)
		throw exceptions::MatrixUnknowTypeException();

	for (sys::uint i = 0; i < _matrix->size().y; i++)
	{
		for (sys::uint j = 0; j < _matrix->size().x; j++)
			out_ << matrix->get(j, i) << " ";

		out_ << std::endl;
	}
}


//Naprawa b³êdu linkera
template matrixm::matrix::MatrixWriter<char>;
template matrixm::matrix::MatrixWriter<short>;
template matrixm::matrix::MatrixWriter<int>;
template matrixm::matrix::MatrixWriter<long>;
template matrixm::matrix::MatrixWriter<long long>;;

template matrixm::matrix::MatrixWriter<float>;
template matrixm::matrix::MatrixWriter<double>;
template matrixm::matrix::MatrixWriter<long double>;

template matrixm::matrix::MatrixWriter<matrixm::sys::uchar>;
template matrixm::matrix::MatrixWriter<matrixm::sys::ushort>;
template matrixm::matrix::MatrixWriter<matrixm::sys::uint>;
template matrixm::matrix::MatrixWriter<matrixm::sys::ulong>;
template matrixm::matrix::MatrixWriter<matrixm::sys::ullong>;