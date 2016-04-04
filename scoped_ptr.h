
#ifndef SCOPED_PTR_H_
#define SCOPED_PTR_H_

#include <assert.h>
#include <iostream>

template<typename Data>
class scoped_ptr/*: public safe_bool<>*/
{
    private:

        Data * _data_pointer;

        /***********************************
         * --- Safe Boolean Conversion --- *
         ***********************************/

//		struct Tester
//		{
//			Tester     (int) {}  // No default constructor
//			void dummy ()    {}
//		};
//
//		typedef void (Tester::*unspecified_bool_type)();

	public:

//		operator unspecified_bool_type() const
//		{
//			return _data_pointer ? &Tester::dummy : 0;
//		}

        /*************************************
         * --- Constructors & Destructor --- *
         *************************************/

        scoped_ptr ();
        scoped_ptr (Data             * pointer);
        scoped_ptr (const scoped_ptr & object);
       ~scoped_ptr ();

        /**************************
         * --- Public Methods --- *
         **************************/

        // Accessors

        bool       is_null    () const;
        scoped_ptr copy       () const;
        Data     * reference  () const;

        // Mutators

        void       copy       (const scoped_ptr & object);
        void       deallocate ();
        void       reallocate ();
        void       reallocate (const Data & input);
        void       avert      ();
        void       assign     (const scoped_ptr & object);
        void       reset      ();
        void       swap       (scoped_ptr & object);

        /********************************
         * --- Overloaded Operators --- *
         ********************************/

        // Assignment

        scoped_ptr & operator=  (Data             * pointer);
        scoped_ptr & operator=  (const scoped_ptr & object);

        // Dereference

        Data       & operator*  ();
        const Data & operator*  () const;
        Data       * operator-> ();
        const Data * operator-> () const;

        // Comparator

        bool         operator== (const Data *     & pointer) const;
        bool         operator!= (const Data *     & pointer) const;
        bool         operator== (const scoped_ptr & object)  const;
        bool         operator!= (const scoped_ptr & object)  const;

        template<typename Type>
        friend bool  operator== (const Type *           & pointer,
                                 const scoped_ptr<Type> & object);

        template<typename Type>
        friend bool  operator!= (const Type *           & pointer,
                                 const scoped_ptr<Type> & object);

        // Typecast Conversion

        operator Data * () const;
        operator Data   () const;


        class locator
        {
			private:

				Data * _data_pointer;

			public:

				locator ();
				locator (const locator    & object);
				locator (const scoped_ptr & object);
			   ~locator ();

			   /**************************
				* --- Public Methods --- *
				**************************/

			    // Accessors

			    bool       is_null    () const;

			    // Mutators

		        void       avert      ();
		        void       assign     (const locator    & object);
			    void       swap       (locator          & object);

			    /********************************
			 	* --- Overloaded Operators --- *
			 	********************************/

			    // Assignment

			    locator    & operator=  (const locator    & object);
			    locator    & operator=  (const scoped_ptr & object);

			    // Dereference

			    Data       & operator*  ();
			    const Data & operator*  () const;
			    Data       * operator-> ();
			    const Data * operator-> () const;

			    // Comparator

			    bool         operator== (const Data *     & pointer) const;
			    bool         operator!= (const Data *     & pointer) const;
			    bool         operator== (const locator    & object)  const;
			    bool         operator!= (const locator    & object)  const;
			    bool         operator== (const scoped_ptr & object)  const;
			    bool         operator!= (const scoped_ptr & object)  const;

				bool         operator<  (const locator    & object)  const;
				bool         operator>  (const locator    & object)  const;
				bool         operator<= (const locator    & object)  const;
				bool         operator>= (const locator    & object)  const;

			    template<typename Type>
			    friend bool  operator==

			 	   (const Type *                             & pointer,
			 		const typename scoped_ptr<Type>::locator & object);

			    template<typename Type>
			    friend bool  operator!=

			 	   (const Type *                             & pointer,
			 		const typename scoped_ptr<Type>::locator & object);

			    template<typename Type>
			    friend bool  operator==

			 	   (const scoped_ptr<Type>                   & object1,
			 		const typename scoped_ptr<Type>::locator & object2);

			    template<typename Type>
			    friend bool  operator!=

			 	   (const scoped_ptr<Type>                   & object1,
			 		const typename scoped_ptr<Type>::locator & object2);

		        // Typecast Conversion

		        operator Data * () const;
		        operator Data   () const;

		        friend class scoped_ptr;
        };

        void    assign  (const locator & pointer);

        locator pointer () const;

        const locator operator+ (int index) const;
        const locator operator- (int index) const;
};


#ifndef scoped
#define scoped(Type)     scoped_ptr<Type>
#endif

#ifndef s_locator
#define s_locator(Type)  scoped_ptr<Type>::locator
#endif


// scoped_ptr Functions --------------------------------------------------


template<typename Type>
void avert(scoped_ptr<Type> & object)
{
    object.avert();
}

template<typename Type>
void reset(scoped_ptr<Type> & object)
{
    object.reset();
}

template<typename Type>
void swap(scoped_ptr<Type> & object1, scoped_ptr<Type> & object2)
{
    object1.swap(object2);
}

// Friend Comparator

template<typename Data>
bool scoped_ptr<Data>::operator!= (const scoped_ptr & object) const
{
    return _data_pointer != object._data_pointer;
}

template<typename Type>
bool operator== (const Type *           & pointer,
                 const scoped_ptr<Type> & object)
{
    return pointer == object._data_pointer;
}

template<typename Type>
bool operator!= (const Type *           & pointer,
                 const scoped_ptr<Type> & object)
{
    return pointer != object._data_pointer;
}


// locator Functions -----------------------------------------------------


template<typename Type>
void swap(typename scoped_ptr<Type>::locator & object1,
		  typename scoped_ptr<Type>::locator & object2)
{
    object1.swap(object2);
}

// Friend Comparator

template<typename Type>
bool operator== (const Type *                             & pointer,
				 const typename scoped_ptr<Type>::locator & object)
{
	return object == pointer;
}

template<typename Type>
bool operator!= (const Type *                             & pointer,
				 const typename scoped_ptr<Type>::locator & object)
{
	return object != pointer;
}

template<typename Type>
bool operator== (const scoped_ptr<Type>                   & object1,
				 const typename scoped_ptr<Type>::locator & object2)
{
	return object2 == object1;
}

template<typename Type>
bool operator!= (const scoped_ptr<Type>                   & object1,
		         const typename scoped_ptr<Type>::locator & object2)
{
	return object2 != object1;
}


// locator Methods -------------------------------------------------------


/*************************************
 * --- Constructors & Destructor --- *
 *************************************/

template<typename Data>
scoped_ptr<Data>::locator::locator():
	_data_pointer(NULL) {}

template<typename Data>
scoped_ptr<Data>::locator::locator(const locator & object):
	_data_pointer(object._data_pointer) {}

template<typename Data>
scoped_ptr<Data>::locator::locator(const scoped_ptr & object):
	_data_pointer(object._data_pointer) {}

template<typename Data>
scoped_ptr<Data>::locator::~locator() {}

/**************************
* --- Public Methods --- *
**************************/

// Accessors

template<typename Data>
bool scoped_ptr<Data>::locator::is_null() const
{
	return _data_pointer == NULL;
}

// Mutators

template<typename Data>
void scoped_ptr<Data>::locator::avert()
{
	if(_data_pointer) _data_pointer = NULL;
}

template<typename Data>
void scoped_ptr<Data>::locator::assign(const locator & object)
{
	_data_pointer = object._data_pointer;
}

template<typename Data>
void scoped_ptr<Data>::locator::swap(locator & object)
{
	Data *          temp  =         _data_pointer;
	       _data_pointer  =  object._data_pointer;
	object._data_pointer  =                  temp;
}

/********************************
 * --- Overloaded Operators --- *
 ********************************/

// Assignment

template<typename Data>
typename scoped_ptr<Data>::locator &
scoped_ptr<Data>::locator::operator= (const locator & object)
{
	_data_pointer = object._data_pointer;

	return *this;
}

template<typename Data>
typename scoped_ptr<Data>::locator &
scoped_ptr<Data>::locator::operator= (const scoped_ptr & object)
{
	_data_pointer = object._data_pointer;

	return *this;
}

// Dereference

template<typename Data>
Data & scoped_ptr<Data>::locator::operator* ()
{
    assert(_data_pointer);
    return *_data_pointer;
}

template<typename Data>
const Data & scoped_ptr<Data>::locator::operator* () const
{
    assert(_data_pointer);
    return *_data_pointer;
}

template<typename Data>
Data * scoped_ptr<Data>::locator::operator-> ()
{
    assert(_data_pointer);
    return *&_data_pointer;
}

template<typename Data>
const Data * scoped_ptr<Data>::locator::operator-> () const
{
    assert(_data_pointer);
    return *&_data_pointer;
}

// Comparator

template<typename Data>
bool scoped_ptr<Data>::locator::operator== (const Data * & pointer) const
{
	return _data_pointer == pointer;
}

template<typename Data>
bool scoped_ptr<Data>::locator::operator!= (const Data * & pointer) const
{
	return _data_pointer != pointer;
}

template<typename Data>
bool scoped_ptr<Data>::locator::operator== (const locator & object) const
{
	return _data_pointer == object._data_pointer;
}

template<typename Data>
bool scoped_ptr<Data>::locator::operator!= (const locator & object) const
{
	return _data_pointer != object._data_pointer;
}

template<typename Data>
bool
scoped_ptr<Data>::locator::operator== (const scoped_ptr & object) const
{
	return _data_pointer == object._data_pointer;
}

template<typename Data>
bool
scoped_ptr<Data>::locator::operator!= (const scoped_ptr & object) const
{
	return _data_pointer != object._data_pointer;
}

template<typename Data>
bool scoped_ptr<Data>::locator::operator< (const locator & object) const
{
	return **this <  *object;
}

template<typename Data>
bool scoped_ptr<Data>::locator::operator> (const locator & object) const
{
	return **this >  *object;
}

template<typename Data>
bool scoped_ptr<Data>::locator::operator<=(const locator & object) const
{
	return **this <= *object;
}

template<typename Data>
bool scoped_ptr<Data>::locator::operator>=(const locator & object) const
{
	return **this >= *object;
}

// Typecast Conversion

template<typename Data>
scoped_ptr<Data>::locator::operator Data * () const
{
    return _data_pointer;
}

template<typename Data>
scoped_ptr<Data>::locator::operator Data () const
{
    return *_data_pointer;
}


// scoped_ptr Methods ----------------------------------------------------


/*************************************
 * --- Constructors & Destructor --- *
 *************************************/

template<typename Data>
scoped_ptr<Data>::scoped_ptr():
    _data_pointer(NULL) {}

template<typename Data>
scoped_ptr<Data>::scoped_ptr(Data * pointer):
    _data_pointer(pointer) {}

template<typename Data>
scoped_ptr<Data>::scoped_ptr(const scoped_ptr & object)
{
    copy(object);
}

template<typename Data>
scoped_ptr<Data>::~scoped_ptr() { if(_data_pointer) delete _data_pointer; }


/**************************
 * --- Public Methods --- *
 **************************/

// Accessors

template<typename Data>
scoped_ptr<Data> scoped_ptr<Data>::copy() const
{
    scoped_ptr copyPtr(*this);

    return copyPtr;
}

template<typename Data>
Data * scoped_ptr<Data>::reference() const
{
    return _data_pointer;
}

template<typename Data>
bool scoped_ptr<Data>::is_null() const
{
    return !_data_pointer;
}

template<typename Data>
void scoped_ptr<Data>::assign
	(const typename scoped_ptr<Data>::locator & pointer)
{
	_data_pointer = pointer._data_pointer;
}

template<typename Data>
typename scoped_ptr<Data>::locator scoped_ptr<Data>::pointer() const
{
	locator object(*this);

	return object;
}

// Mutators

template<typename Data>
void scoped_ptr<Data>::copy(const scoped_ptr & object)
{
	if(_data_pointer)
	{
		deallocate();
	}

    if(object._data_pointer)
    {
        _data_pointer = new Data(*(object._data_pointer));
    }
    else
    {
        _data_pointer = NULL;
    }
}

template<typename Data>
void scoped_ptr<Data>::deallocate()
{
    if(_data_pointer)
    {
        delete _data_pointer;

        _data_pointer = NULL;
    }
}

template<typename Data>
void scoped_ptr<Data>::reallocate()
{
     deallocate();

    _data_pointer  = new Data;
}

template<typename Data>
void scoped_ptr<Data>::reallocate(const Data & input)
{
     deallocate();

    _data_pointer  = new Data(input);
}

template<typename Data>
void scoped_ptr<Data>::avert() { if(_data_pointer) _data_pointer = NULL; }

template<typename Data>
void scoped_ptr<Data>::assign(const scoped_ptr & object)
{
	_data_pointer = object._data_pointer;
}

template<typename Data>
void scoped_ptr<Data>::reset()
{
    if(_data_pointer)
    {
        delete _data_pointer;

		_data_pointer  = NULL;
    }
}

template<typename Data>
void scoped_ptr<Data>::swap(scoped_ptr & object)
{
	Data *          temp   =          _data_pointer;
		   _data_pointer   =   object._data_pointer;
	object._data_pointer   =                   temp;
}


/********************************
 * --- Overloaded Operators --- *
 ********************************/

// Assignment

template<typename Data>
scoped_ptr<Data> & scoped_ptr<Data>::operator= (Data * pointer)
{
    if(_data_pointer != pointer)
    {
        _data_pointer = pointer;
    }

    return *this;
}

template<typename Data>
scoped_ptr<Data> & scoped_ptr<Data>::operator= (const scoped_ptr & object)
{
    copy(object);

    return *this;
}

// Dereference

template<typename Data>
Data & scoped_ptr<Data>::operator* ()
{
    assert(_data_pointer);
    return *_data_pointer;
}

template<typename Data>
const Data & scoped_ptr<Data>::operator* () const
{
    assert(_data_pointer);
    return *_data_pointer;
}

template<typename Data>
Data * scoped_ptr<Data>::operator-> ()
{
    return *&_data_pointer;
}

template<typename Data>
const Data * scoped_ptr<Data>::operator-> () const
{
    return *&_data_pointer;
}

// Comparator

template<typename Data>
bool scoped_ptr<Data>::operator== (const Data * & pointer) const
{
    return _data_pointer == pointer;
}

template<typename Data>
bool scoped_ptr<Data>::operator!= (const Data * & pointer) const
{
    return _data_pointer != pointer;
}

template<typename Data>
bool scoped_ptr<Data>::operator== (const scoped_ptr & object) const
{
    return _data_pointer == object._data_pointer;
}

// Typecast Conversion

template<typename Data>
scoped_ptr<Data>::operator Data * () const
{
    return _data_pointer;
}

template<typename Data>
scoped_ptr<Data>::operator Data () const
{
    return *_data_pointer;
}

// Pointer Shift

template<typename Data>
const typename scoped_ptr<Data>::locator
scoped_ptr<Data>::operator+ (int index) const
{
	locator temp(*this);

	temp._data_pointer = temp._data_pointer + index;

	return temp;
}

template<typename Data>
const typename scoped_ptr<Data>::locator
scoped_ptr<Data>::operator- (int index) const
{
	return *this + -index;
}

#endif /* SCOPED_PTR_H_ */
