#ifndef SCOPED_PTR_H_
#define SCOPED_PTR_H_

#include <iostream>

template <typename Data>
class scoped_ptr/*: public safe_bool<>*/
{
    private:

        bool   _is_aggregate;
        Data * _data_pointer;

        /***********************************
         * --- Safe Boolean Conversion --- *
         ***********************************/

//      struct Tester
//      {
//          Tester     (int) {}  // No default constructor
//          void dummy ()    {}
//      };
//
//      typedef void (Tester::*unspecified_bool_type)();

    public:

//      operator unspecified_bool_type() const
//      {
//          return _data_pointer ? &Tester::dummy : 0;
//      }

        /*************************************
         * --- Constructors & Destructor --- *
         *************************************/

        virtual ~scoped_ptr();
        scoped_ptr ();
        scoped_ptr (Data *, bool isAggregate = false);
        scoped_ptr (const scoped_ptr &);
        scoped_ptr (const std::initializer_list<Data> &);

        /**************************
         * --- Public Methods --- *
         **************************/

        // Accessors

        bool       any       () const;
        bool       aggregate () const;
        scoped_ptr copy      () const;
        Data     * ref       () const;

        // Mutators

        void       copy       (const scoped_ptr &);
        void       release    ();
        void       reallocate ();
        void       reallocate (const Data &);
        void       avert      ();
        void       assign     (const scoped_ptr &);
        void       swap       (scoped_ptr &);

        /********************************
         * --- Overloaded Operators --- *
         ********************************/

        // Assignment

        scoped_ptr & operator=  (Data *);
        scoped_ptr & operator=  (const scoped_ptr &);

        // Dereference

        Data       & operator*  ();
        const Data & operator*  () const;
        Data       * operator-> ();
        const Data * operator-> () const;

        // Comparator

        bool         operator== (const Data *) const;
        bool         operator!= (const Data *) const;
        bool         operator== (const scoped_ptr &)  const;
        bool         operator!= (const scoped_ptr &)  const;

        template <typename Type>
        friend bool  operator== (const Type *,
                                 const scoped_ptr<Type> &);

        template <typename Type>
        friend bool  operator!= (const Type * pointer,
                                 const scoped_ptr<Type> &);

        // Typecast Conversion

        operator Data * () const;
        operator Data   () const;

        // Subscript

        const Data & operator[] (size_t) const;
              Data & operator[] (size_t);


        class locator
        {
            private:

                Data * _data_pointer;

            public:

                friend class scoped_ptr;

                virtual ~locator ();
                locator ();
                locator (const locator &);
                locator (const scoped_ptr &);

               /**************************
                * --- Public Methods --- *
                **************************/

                // Accessors

                bool any     () const;

                // Mutators

                void avert   ();
                void assign  (const locator &);
                void swap    (locator &);

                /********************************
                * --- Overloaded Operators --- *
                ********************************/

                // Assignment

                locator    & operator=  (const locator &);
                locator    & operator=  (const scoped_ptr &);

                // Dereference

                Data       & operator*  ();
                const Data & operator*  () const;
                Data       * operator-> ();
                const Data * operator-> () const;

                // Comparator

                bool         operator== (const Data *) const;
                bool         operator!= (const Data *) const;
                bool         operator== (const locator &)  const;
                bool         operator!= (const locator &)  const;
                bool         operator== (const scoped_ptr &)  const;
                bool         operator!= (const scoped_ptr &)  const;

                bool         operator<  (const locator &)  const;
                bool         operator>  (const locator &)  const;
                bool         operator<= (const locator &)  const;
                bool         operator>= (const locator &)  const;

                template <typename Type>
                friend bool  operator==

                   (const Type *,
                    const typename scoped_ptr<Type>::locator &);

                template <typename Type>
                friend bool  operator!=

                   (const Type *,
                    const typename scoped_ptr<Type>::locator &);

                template <typename Type>
                friend bool  operator==

                   (const scoped_ptr<Type> &,
                    const typename scoped_ptr<Type>::locator &);

                template <typename Type>
                friend bool  operator!=

                   (const scoped_ptr<Type> &,
                    const typename scoped_ptr<Type>::locator &);

                // Subscript

                const Data & operator[] (size_t) const;
                      Data & operator[] (size_t);

                // Typecast Conversion

                operator Data * () const;
                operator Data   () const;
        };

        void assign (const locator & loc);
        locator loc () const;

        const locator operator+ (int) const;
        const locator operator- (int) const;
};


#ifndef scoped
#define scoped(Type)     scoped_ptr<Type>
#endif

#ifndef s_locator
#define s_locator(Type)  scoped_ptr<Type>::locator
#endif


// scoped_ptr Functions --------------------------------------------------


template <typename Type>
void avert(scoped_ptr<Type> & object)
{
    object.avert();
}

template <typename Type>
void swap(scoped_ptr<Type> & object1, scoped_ptr<Type> & object2)
{
    object1.swap(object2);
}

// Friend Comparator

template <typename Data>
bool scoped_ptr<Data>::operator!= (const scoped_ptr & object) const
{
    return _data_pointer != object._data_pointer;
}

template <typename Type>
bool operator== (const Type             * pointer,
                 const scoped_ptr<Type> & object)
{
    return pointer == object._data_pointer;
}

template <typename Type>
bool operator!= (const Type             * pointer,
                 const scoped_ptr<Type> & object)
{
    return pointer != object._data_pointer;
}


// locator Functions -----------------------------------------------------


template <typename Type>
void swap(typename scoped_ptr<Type>::locator & object1,
          typename scoped_ptr<Type>::locator & object2)
{
    object1.swap(object2);
}

// Friend Comparator

template <typename Type>
bool operator== (const Type * pointer,
                 const typename scoped_ptr<Type>::locator & object)
{
    return object == pointer;
}

template <typename Type>
bool operator!= (const Type * pointer,
                 const typename scoped_ptr<Type>::locator & object)
{
    return object != pointer;
}

template <typename Type>
bool operator== (const scoped_ptr<Type> & object1,
                 const typename scoped_ptr<Type>::locator & object2)
{
    return object2 == object1;
}

template <typename Type>
bool operator!= (const scoped_ptr<Type> & object1,
                 const typename scoped_ptr<Type>::locator & object2)
{
    return object2 != object1;
}


// locator Methods -------------------------------------------------------


/*************************************
 * --- Constructors & Destructor --- *
 *************************************/

template <typename Data>
scoped_ptr<Data>::locator::~locator() {}

template <typename Data>
scoped_ptr<Data>::locator::locator():
    _data_pointer(nullptr) {}

template <typename Data>
scoped_ptr<Data>::locator::locator(const locator & object):
    _data_pointer(object._data_pointer) {}

template <typename Data>
scoped_ptr<Data>::locator::locator(const scoped_ptr & object):
    _data_pointer(object._data_pointer) {}

/**************************
* --- Public Methods --- *
**************************/

// Accessors

template <typename Data>
bool scoped_ptr<Data>::locator::any() const
{
    return _data_pointer;
}

// Mutators

template <typename Data>
void scoped_ptr<Data>::locator::avert()
{
    if(_data_pointer)
        _data_pointer = nullptr;
}

template <typename Data>
void scoped_ptr<Data>::locator::assign(const locator & object)
{
    _data_pointer = object._data_pointer;
}

template <typename Data>
void scoped_ptr<Data>::locator::swap(locator & object)
{
    Data * temp = _data_pointer;
    _data_pointer = object._data_pointer;
    object._data_pointer = temp;
}

/********************************
 * --- Overloaded Operators --- *
 ********************************/

// Assignment

template <typename Data>
typename scoped_ptr<Data>::locator &
scoped_ptr<Data>::locator::operator=(const locator & object)
{
    _data_pointer = object._data_pointer;
    return *this;
}

template <typename Data>
typename scoped_ptr<Data>::locator &
scoped_ptr<Data>::locator::operator=(const scoped_ptr & object)
{
    _data_pointer = object._data_pointer;
    return *this;
}

// Dereference

template <typename Data>
Data & scoped_ptr<Data>::locator::operator*()
{
    return *_data_pointer;
}

template <typename Data>
const Data & scoped_ptr<Data>::locator::operator*() const
{
    return *_data_pointer;
}

template <typename Data>
Data * scoped_ptr<Data>::locator::operator->()
{
    return *&_data_pointer;
}

template <typename Data>
const Data * scoped_ptr<Data>::locator::operator->() const
{
    return *&_data_pointer;
}

// Comparator

template <typename Data>
bool scoped_ptr<Data>::locator::operator==(const Data * pointer) const
{
    return _data_pointer == pointer;
}

template <typename Data>
bool scoped_ptr<Data>::locator::operator!=(const Data * pointer) const
{
    return _data_pointer != pointer;
}

template <typename Data>
bool scoped_ptr<Data>::locator::operator==(const locator & object) const
{
    return _data_pointer == object._data_pointer;
}

template <typename Data>
bool scoped_ptr<Data>::locator::operator!=(const locator & object) const
{
    return _data_pointer != object._data_pointer;
}

template <typename Data>
bool
scoped_ptr<Data>::locator::operator==(const scoped_ptr & object) const
{
    return _data_pointer == object._data_pointer;
}

template <typename Data>
bool
scoped_ptr<Data>::locator::operator!=(const scoped_ptr & object) const
{
    return _data_pointer != object._data_pointer;
}

template <typename Data>
bool scoped_ptr<Data>::locator::operator<(const locator & object) const
{
    return **this <  *object;
}

template <typename Data>
bool scoped_ptr<Data>::locator::operator>(const locator & object) const
{
    return **this >  *object;
}

template <typename Data>
bool scoped_ptr<Data>::locator::operator<=(const locator & object) const
{
    return **this <= *object;
}

template <typename Data>
bool scoped_ptr<Data>::locator::operator>=(const locator & object) const
{
    return **this >= *object;
}

// Subscript

template <typename Data>
const Data & scoped_ptr<Data>::locator::operator[](size_t pos) const
{
    return _data_pointer[pos];
}

template <typename Data>
Data & scoped_ptr<Data>::locator::operator[](size_t pos)
{
    return _data_pointer[pos];
}

// Typecast Conversion

template <typename Data>
scoped_ptr<Data>::locator::operator Data*() const
{
    return _data_pointer;
}

template <typename Data>
scoped_ptr<Data>::locator::operator Data() const
{
    return *_data_pointer;
}


// scoped_ptr Methods ----------------------------------------------------


/*************************************
 * --- Constructors & Destructor --- *
 *************************************/

template <typename Data>
scoped_ptr<Data>::~scoped_ptr()
{
    release();
}

template <typename Data>
scoped_ptr<Data>::scoped_ptr():
    _is_aggregate(false),
    _data_pointer(nullptr) {}

template <typename Data>
scoped_ptr<Data>::scoped_ptr(Data * pointer, bool isAggregate):
    _is_aggregate(isAggregate),
    _data_pointer(pointer) {}

template <typename Data>
scoped_ptr<Data>::scoped_ptr(const scoped_ptr & object):
    _is_aggregate(object._is_aggregate)
{
    copy(object);
}

template <typename Data>
scoped_ptr<Data>::scoped_ptr(const std::initializer_list<Data> & list):
    _is_aggregate(true),
    _data_pointer(new Data[list.size()])
{
    std::copy(list.begin(), list.end(), _data_pointer);
}


/**************************
 * --- Public Methods --- *
 **************************/

// Accessors

template <typename Data>
scoped_ptr<Data> scoped_ptr<Data>::copy() const
{
    scoped_ptr copyPtr(*this);
    return copyPtr;
}

template <typename Data>
Data * scoped_ptr<Data>::ref() const
{
    return _data_pointer;
}

template <typename Data>
bool scoped_ptr<Data>::any() const
{
    return _data_pointer;
}

template <typename Data>
bool scoped_ptr<Data>::aggregate() const
{
    return _is_aggregate;
}

template <typename Data>
void scoped_ptr<Data>::assign
    (const typename scoped_ptr<Data>::locator & loc)
{
    _data_pointer = loc._data_pointer;
}

template <typename Data>
typename scoped_ptr<Data>::locator scoped_ptr<Data>::pointer() const
{
    locator object(*this);

    return object;
}

// Mutators

template <typename Data>
void scoped_ptr<Data>::copy(const scoped_ptr & object)
{
    if (_data_pointer)
        release();

    _data_pointer = object._data_pointer
        ? new Data(*(object._data_pointer))
        : nullptr;
}

template <typename Data>
void scoped_ptr<Data>::release()
{
    if (!_data_pointer)
        return;

    if (_is_aggregate)
        delete[] _data_pointer;
    else
        delete _data_pointer;

	_data_pointer = nullptr;
}

template <typename Data>
void scoped_ptr<Data>::reallocate()
{
    release();
    _data_pointer = new Data;
}

template <typename Data>
void scoped_ptr<Data>::reallocate(const Data & input)
{
    release();
    _data_pointer = new Data(input);
}

template <typename Data>
void scoped_ptr<Data>::avert()
{
    if (_data_pointer)
        _data_pointer = nullptr;
}

template <typename Data>
void scoped_ptr<Data>::assign(const scoped_ptr & object)
{
    _data_pointer = object._data_pointer;
}

template <typename Data>
void scoped_ptr<Data>::swap(scoped_ptr & object)
{
    Data * temp = _data_pointer;
    _data_pointer = object._data_pointer;
    object._data_pointer = temp;
}


/********************************
 * --- Overloaded Operators --- *
 ********************************/

// Assignment

template <typename Data>
scoped_ptr<Data> & scoped_ptr<Data>::operator=(Data * pointer)
{
    if (_data_pointer != pointer)
        _data_pointer = pointer;

    return *this;
}

template <typename Data>
scoped_ptr<Data> & scoped_ptr<Data>::operator=(const scoped_ptr & object)
{
    _is_aggregate = object._is_aggregate;
    copy(object);
    return *this;
}

// Dereference

template <typename Data>
Data & scoped_ptr<Data>::operator*()
{
    return *_data_pointer;
}

template <typename Data>
const Data & scoped_ptr<Data>::operator*() const
{
    return *_data_pointer;
}

template <typename Data>
Data * scoped_ptr<Data>::operator->()
{
    return *&_data_pointer;
}

template <typename Data>
const Data * scoped_ptr<Data>::operator->() const
{
    return *&_data_pointer;
}

// Comparator

template <typename Data>
bool scoped_ptr<Data>::operator==(const Data * pointer) const
{
    return _data_pointer == pointer;
}

template <typename Data>
bool scoped_ptr<Data>::operator!=(const Data * pointer) const
{
    return _data_pointer != pointer;
}

template <typename Data>
bool scoped_ptr<Data>::operator==(const scoped_ptr & object) const
{
    return _data_pointer == object._data_pointer;
}

// Subscript

template <typename Data>
const Data & scoped_ptr<Data>::operator[](size_t pos) const
{
    return _data_pointer[pos];
}

template <typename Data>
Data & scoped_ptr<Data>::operator[](size_t pos)
{
    return _data_pointer[pos];
}

// Typecast Conversion

template <typename Data>
scoped_ptr<Data>::operator Data*() const
{
    return _data_pointer;
}

template <typename Data>
scoped_ptr<Data>::operator Data() const
{
    return *_data_pointer;
}

// Pointer Shift

template <typename Data>
const typename scoped_ptr<Data>::locator
scoped_ptr<Data>::operator+(int index) const
{
    locator temp(*this);
    temp._data_pointer = temp._data_pointer + index;
    return temp;
}

template <typename Data>
const typename scoped_ptr<Data>::locator
scoped_ptr<Data>::operator-(int index) const
{
    return *this + -index;
}

#endif /* SCOPED_PTR_H_ */
