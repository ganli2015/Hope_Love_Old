#pragma once

///A functor with output data.
#define CREATE_FUNCTOR_O(funName,InputType,OutType,body)\
	class funName	\
	{	\
		OutType _output;	\
	public:	\
		funName(){}	\
		~funName(){}	\
		void operator()(const InputType& input)	\
		{	\
			body	\
		}	\
		OutType GetResult() const {return _output;}	\
	};	

///A functor with init data.
#define CREATE_FUNCTOR_I(funName,InputType,InitType,body)\
class funName	\
	{	\
	InitType _init;	\
	public:	\
	funName(const InitType& val):_init(val){}	\
	~funName(){}	\
	void operator()(const InputType& input)	\
		{	\
		body	\
		}	\
	};	

///A functor with initial data and return type.
#define CREATE_FUNCTOR_IR(funName,InitType,InputType,ReturnType,body)	\
	class funName	\
	{	\
	InitType _init;	\
	public:	\
	funName(const InitType& val):_init(val){}	\
	~funName(){}	\
	ReturnType operator()(const InputType& input)	\
		{	\
		body	\
		}	\
	};

///A functor with return type.
#define CREATE_FUNCTOR_R(funName,InputType,ReturnType,body)\
	class funName	\
	{	\
	public:	\
	funName(){}	\
	~funName(){}	\
	ReturnType operator()(const InputType& input)	\
		{	\
		body	\
		}	\
	};	
