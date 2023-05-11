/*
 * Array.h
 *
 *  Created on: Oct 14, 2014
 *      Author: adaniels4
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include "arrayfunction.h"
#include "scoped_ptr.h"
#include "Aggregate.h"

template <typename Content_Type>
class Array: public Aggregate<Content_Type>
{
	private:

		scoped_ptr<Content_Type> _array_list;
		size_t                   _size;

	public:

		Array():
			 _array_list (NULL),
		     _size       (0){}

		Array(size_t arraySize):
			 _array_list (new Content_Type[arraySize]),
			 _size       (arraySize){}

		Array(size_t arraySize, const Content_Type & content):
			 _array_list (new Content_Type[arraySize]),
			 _size       (arraySize)
		{
			size_t index;

			foreach(*this, index) (*this)[index] = content;
		}

		Array(const Array & object):
			 _array_list (new Content_Type[object.size()]),
			 _size       (object.size())
		{
			arrayfunction::copy_values(        _array_list.reference(),
										object._array_list.reference(),
											   _size,
										object._size  );
		}

		virtual ~Array() {}

		virtual size_t size() const
		{
			return _size;
		}

        /*
        [x] issue 2023_05_03_133202
        - actual: all values uninitialized
        - expected: original values copied
        */
		virtual void resize(size_t newSize)
		{
			if(newSize >= _size)
			{
				Array temp(newSize);

				arrayfunction::copy_values( temp._array_list.reference(),
						                         _array_list.reference(),
											temp._size,
												 _size  );

				swap(_array_list, temp._array_list);
			   _size = temp._size;
			}
		}

		virtual void resize()
		{
			resize(2 * _size);
		}

		virtual const Content_Type & operator[](size_t index) const
		{
			return (_array_list)[index];
		}

		virtual Content_Type & operator[](size_t index)
		{
			return (_array_list)[index];
		}

		virtual Array & operator=(const Array & object)
		{
			if(!_array_list.is_null())
			{
				_array_list.deallocate();
			}

			_array_list = new Content_Type[object._size];
			_size       = object._size;

			for(size_t index = 0; index < _size; index++)
			{
				_array_list[index] = object._array_list[index];
			}

			return *this;
		}
};

#endif /* ARRAY_H_ */
