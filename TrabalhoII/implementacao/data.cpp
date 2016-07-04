/*
 * Copyright (c) 2016 <copyright holder> <email>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */



/*
string a;
a = "12345";
string b;
b = a+a;


string a;
a = "2";
int b;
b = 5;
a = b; //a = "5"
a + a; //22
a + b; //25
b + a; //int 7
*/

#include "data.h"

/************************************************
 ***************CONSTRUTURES********************/
Data::Data ( int inteiro ) {
	this->_type = Data::integer;
	this->_data = new int ( inteiro );
}
//////////
Data::Data ( float real ) {
	this->_type = Data::real;
	this->_data = new float ( real );
}
//////////
Data::Data ( bool booleano ) {
	this->_type =  Data::boolean;
	this->_data = new bool ( booleano );
}
//////////
Data::Data ( std::string String ) {
	this->_type = Data::string;
	this->_data = new std::string ( String );
}
//////////
Data::Data ( const Data & other ) {
	this->_type = other._type;
	this->_data = other._data;

}
/************************************************
 ***************RETORNOS DE DADO****************/

int Data::dataInt() {
	int * inteiro = ( int * ) this->_data;
	return *inteiro;
}
//////////
float Data::dataFloat() {
	float * real = ( float * ) this->_data;
	return *real;
}
//////////
bool Data::dataBool() {
	bool * booleano = ( bool * ) this->_data;
	return *booleano;
}
//////////
std::string Data::dataString() {
	std::string * String = ( std::string * ) this->_data;
	return *String;
}


/************************************************
 ***************OPERADORES**********************/
Data Data::sum ( Data * outro ) {
	assert ( aritmetico() );
	assert ( outro->aritmetico() );

	switch ( this->_type ) {
		case Data::integer: {
			switch ( outro->_type ) {
				case Data::integer: {//int com int
					return Data ( this->dataInt() + outro->dataInt() );
					break;
				}

				case Data::real: {//int com real
					return Data ( this->dataInt() + outro->dataFloat() );
					break;
				}

			}

			break;
		}

		case Data::real: {
			switch ( outro->_type ) {
				case Data::integer: {//real com int
					return Data ( this->dataFloat() + outro->dataInt() );
					break;
				}

				case Data::real: {// real com real
					return Data ( this->dataFloat() + outro->dataFloat() );
					break;
				}

			}

			break;
		}


	}//this _type

	std::cerr << "[ATENCAO - realizando uma soma com valores incosistentes!]" << std::endl;

	return Data ( 0 );//Default data return
}
//////////
Data Data::subtrair ( Data * outro ) {
	assert ( aritmetico() );
	assert ( outro->aritmetico() );

	switch ( this->_type ) {
		case Data::integer: {
			switch ( outro->_type ) {
				case Data::integer: {//int com int
					return Data ( this->dataInt() - outro->dataInt() );
					break;
				}

				case Data::real: {//int com real
					return Data ( this->dataInt() - outro->dataFloat() );
					break;
				}

			}

			break;
		}

		case Data::real: {
			switch ( outro->_type ) {
				case Data::integer: {//real com int
					return Data ( this->dataFloat() - outro->dataInt() );
					break;
				}

				case Data::real: {// real com real
					return Data ( this->dataFloat() - outro->dataFloat() );
					break;
				}

			}

			break;
		}


	}//this _type

	std::cerr << "[ATENCAO - realizando uma subtracao com valores incosistentes!]" << std::endl;
	return Data ( 0 );//Default data return
}
//////////
Data Data::multiply ( Data * outro ) {
	assert ( aritmetico() );
	assert ( outro->aritmetico() );

	switch ( this->_type ) {
		case Data::integer: {
			switch ( outro->_type ) {
				case Data::integer: {//int com int
					return Data ( this->dataInt() * outro->dataInt() );
					break;
				}

				case Data::real: {//int com real
					return Data ( this->dataInt() * outro->dataFloat() );
					break;
				}

			}

			break;
		}

		case Data::real: {
			switch ( outro->_type ) {
				case Data::integer: {//real com int
					return Data ( this->dataFloat() * outro->dataInt() );
					break;
				}

				case Data::real: {// real com real
					return Data ( this->dataFloat() * outro->dataFloat() );
					break;
				}

			}

			break;
		}


	}//this _type

	std::cerr << "[ATENCAO - realizando uma multiplicacao com valores incosistentes!]" << std::endl;
	return Data ( 0 );//Default data return
}
//////////
Data Data::divide ( Data * outro ) {
	assert ( aritmetico() );
	assert ( outro->aritmetico() );

	switch ( this->_type ) {
		case Data::integer: {
			switch ( outro->_type ) {
				case Data::integer: {//int com int
					assert ( outro->dataInt() != 0 );
					return Data ( this->dataInt() / outro->dataInt() );
					break;
				}

				case Data::real: {//int com real
					assert ( outro->dataFloat() != 0 );
					return Data ( this->dataInt() * outro->dataFloat() );
					break;
				}

			}

			break;
		}

		case Data::real: {
			switch ( outro->_type ) {
				case Data::integer: {//real com int
					assert ( outro->dataInt() != 0 );
					return Data ( this->dataFloat() * outro->dataInt() );
					break;
				}

				case Data::real: {// real com real
					assert ( outro->dataFloat() != 0 );
					return Data ( this->dataFloat() * outro->dataFloat() );
					break;
				}

			}

			break;
		}


	}//this _type

	std::cerr << "[ATENCAO - realizando uma divisao com valores incosistentes!]" << std::endl;
	return Data ( 0 );//Default data return
}
//////////
Data Data::bAnd ( Data * outro ) {
	assert ( this->type() == Data::boolean );
	assert ( outro->type() == Data::boolean );
	return Data ( this->dataBool() and outro->dataBool() );
}
//////////
Data Data::bOr ( Data * outro ) {
	assert ( this->type() == Data::boolean );
	assert ( outro->type() == Data::boolean );
	return Data ( this->dataBool() or outro->dataBool() );
}

//////////
Data Data::igual ( Data * outro ) {
	if ( this->type() != outro->type() ) {
		return Data ( false );
	}

//Os dados são do mesmo tipo!
	switch ( this->_type ) {
		case Data::integer: {
			return Data ( this->dataInt() == outro->dataInt() );
			break;
		}

		case Data::real: {
			return Data ( this->dataFloat() == outro->dataFloat() );
			break;
		}

		case Data::boolean: {
			return Data ( this->dataBool() == outro->dataBool() );
			break;
		}

		case Data::string: {
			return Data ( this->dataString().compare ( outro->dataString() ) == 0 );
			break;
		}
	}

}
//////////
Data Data::maior ( Data * outro ) {
	if ( this->aritmetico() && outro->aritmetico() ) {
		switch ( this->_type ) {
			case Data::integer: {
				switch ( outro->_type ) {
					case Data::integer: {//int com int

						return Data ( this->dataInt() > outro->dataInt() );
						break;
					}

					case Data::real: {//int com real

						return Data ( this->dataInt() > outro->dataFloat() );
						break;
					}

				}

				break;
			}

			case Data::real: {
				switch ( outro->_type ) {
					case Data::integer: {//real com int

						return Data ( this->dataFloat() > outro->dataInt() );
						break;
					}

					case Data::real: {// real com real

						return Data ( this->dataFloat() > outro->dataFloat() );
						break;
					}

				}

				break;
			}


		}//this _type

	}//aritmetico

	if ( this->type() == outro->type() && this->type() == Data::string ) {
		return Data ( this->dataString().size() > outro->dataString().size() );

	}
}
////////////
Data Data::menor ( Data * outro ) {
	return Data ( ! ( this->maior ( outro ).dataBool() && this->igual ( outro ).dataBool() ) );
}


/************************************************
 ***************AUXILIARES***********************/
bool Data::aritmetico() {
	return ( this->_type == Data::integer || this->_type == Data::real );
}
//////////

/*Biblioteca escrotissima de templates
switch tipo de dado
	switch ( this->_type ) {
		case Data::integer: {
			break;
		}

		case Data::real: {
			break;
		}

		case Data::boolean: {
			break;
		}

		case Data::string: {
			break;
		}
	}
-------------------------------------------------
*/





