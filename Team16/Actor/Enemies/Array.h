#ifndef INCLUDED_ARRAY_1D_H
#define INCLUDED_ARRAY_1D_H

//1次元配列クラス
template< class T > class Array {
public:
	Array() : mArray(0) {}
	~Array() {
		delete[] mArray;
		mArray = 0;  //ポインタに0を入れる
	}
	void setSize(int size0) {
		if (mArray) {
			delete[] mArray;
			mArray = 0;
		}
		mSize0 = size0;
		mArray = new T[size0];
	}
	T& operator()(int index0) {
		return mArray[index0];
	}
	const T& operator()(int index0) const {
		return mArray[index0];
	}
private:
	T* mArray;
	int mSize0;
};

#endif
