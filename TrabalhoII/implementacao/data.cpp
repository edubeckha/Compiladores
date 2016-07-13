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
//--------------------------------------------------
Data::Data ( float real ) {
	this->_type = Data::real;
	this->_data = new float ( real );
}
//--------------------------------------------------
Data::Data ( bool booleano ) {
	this->_type =  Data::boolean;
	this->_data = new bool ( booleano );
}

//--------------------------------------------------
Data::Data ( std::string String ) {
	this->_type = Data::string;
	this->_data = new std::string ( String );
}
//--------------------------------------------------
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
//--------------------------------------------------
float Data::dataFloat() {
	float * real = ( float * ) this->_data;
	return *real;
}
//--------------------------------------------------
bool Data::dataBool() {
	bool * booleano = ( bool * ) this->_data;
	return *booleano;
}
//--------------------------------------------------
std::string Data::dataString() {
	std::string * String = ( std::string * ) this->_data;
	return *String
;}


/************************************************
 ***************OPERADORES**********************/
Data Data::sum ( Data * outro ) {
	assert ( arithmetic() );
	assert ( outro->arithmetic() );

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

				default :
				std::cerr << "[ATENCAO - realizando uma soma com valores incosistentes!]" << std::endl;
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
			default:
			std::cerr << "[ATENCAO - realizando uma soma com valores incosistentes!]" << std::endl;
			}

			break;
		}
		case Data::string: {
		// string com string
			return Data(this->dataString() + outro->dataString());
			break;
		}

		default:
		std::cerr << "[ATENCAO - realizando uma soma com valores incosistentes!]" << std::endl;
	}//this _type

	std::cerr << "[ATENCAO - realizando uma soma com valores incosistentes!]" << std::endl;

	return Data ( 0 );//Default data return
}
//--------------------------------------------------
Data Data::subtrair ( Data * outro ) {
	assert ( arithmetic() );
	assert ( outro->arithmetic() );

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
			default:
					std::cerr << "[ATENCAO - realizando uma subtracao com valores incosistentes!]" << std::endl;
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
			default:
					std::cerr << "[ATENCAO - realizando uma subtracao com valores incosistentes!]" << std::endl;
			}

			break;
		}
		default:
				std::cerr << "[ATENCAO - realizando uma subtracao com valores incosistentes!]" << std::endl;

	}//this _type

	std::cerr << "[ATENCAO - realizando uma subtracao com valores incosistentes!]" << std::endl;
	return Data ( 0 );//Default data return
}
//--------------------------------------------------
Data Data::multiply ( Data * outro ) {
	assert ( arithmetic() );
	assert ( outro->arithmetic() );

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
default:
		std::cerr << "[ATENCAO - realizando uma multiplicacao com valores incosistentes!]" << std::endl;
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
default:
		std::cerr << "[ATENCAO - realizando uma multiplicacao com valores incosistentes!]" << std::endl;
			}

			break;
		}
default:
		std::cerr << "[ATENCAO - realizando uma multiplicacao com valores incosistentes!]" << std::endl;

	}//this _type

	std::cerr << "[ATENCAO - realizando uma multiplicacao com valores incosistentes!]" << std::endl;
	return Data ( 0 );//Default data return
}
//--------------------------------------------------
Data Data::divide ( Data * outro ) {
	assert ( arithmetic() );
	assert ( outro->arithmetic() );

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
			default:
					std::cerr << "[ATENCAO - realizando uma divisao com valores incosistentes!]" << std::endl;
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
			default:
					std::cerr << "[ATENCAO - realizando uma divisao com valores incosistentes!]" << std::endl;
			}

			break;
		}

	default:
			std::cerr << "[ATENCAO - realizando uma divisao com valores incosistentes!]" << std::endl;
	}//this _type

	std::cerr << "[ATENCAO - realizando uma divisao com valores incosistentes!]" << std::endl;
	return Data ( 0 );//Default data return
}
//--------------------------------------------------
Data Data::bAnd ( Data * outro ) {
	assert ( this->type() == Data::boolean );
	assert ( outro->type() == Data::boolean );
	return Data ( this->dataBool() and outro->dataBool() );
}
//--------------------------------------------------
Data Data::bOr ( Data * outro ) {
	assert ( this->type() == Data::boolean );
	assert ( outro->type() == Data::boolean );
	return Data ( this->dataBool() or outro->dataBool() );
}

//--------------------------------------------------
Data Data::equals ( Data * outro ) {
	if ( this->arithmetic() && outro->arithmetic() ) {
		switch ( this->_type ) {
			case Data::integer: {
				switch ( outro->_type ) {
					case Data::integer: { //int com int
						return Data ( this->dataInt() == outro->dataInt() );
						break;
					}

					case Data::real: { // int com float
						return Data ( this->dataInt() == outro->dataFloat() );
						break;
					}
					default:
					std::cerr << "[ATENCAO - realizando uma comparacao com valores incosistentes!]" << std::endl;
				}
			}

			case Data::real: {
				switch ( outro->_type ) {
					case Data::integer: {// float com int
						return Data ( this-> dataFloat() == outro->dataInt() );
						break;
					}

					case Data::real: {// float com float
						return Data ( this->dataFloat() == outro->dataInt() );
						break;
					}
					default:
					std::cerr << "[ATENCAO - realizando uma comparacao com valores incosistentes!]" << std::endl;
				}

				break;
			}
			default:
			std::cerr << "[ATENCAO - realizando uma comparacao com valores incosistentes!]" << std::endl;
		}

	} else {

//Os dados são do mesmo tipo!
		switch ( this->_type ) {

			case Data::boolean: {
				assert ( outro->type() == Data::boolean );
				return Data ( this->dataBool() == outro->dataBool() );
				break;
			}

			case Data::string: {
				assert ( outro->type() == Data::string );
				return Data ( this->dataString().compare ( outro->dataString() ) == 0 );
				break;
			}
			default:
		std::cerr << "[ATENCAO - nao foi possivel comparar!]" << std::endl;
		}
	}
	return false;
}

//--------------------------------------------------
Data Data::greater ( Data * outro ) {
	if ( this->arithmetic() && outro->arithmetic() ) {
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
					default:
							std::cerr << "[ATENCAO - nao foi possivel comparar os valores!]" << std::endl;
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
					default:
							std::cerr << "[ATENCAO - nao foi possivel comparar os valores!]" << std::endl;
				}

				break;
			}
			default:
					std::cerr << "[ATENCAO - nao foi possivel comparar os valores!]" << std::endl;

		}//this _type

	}//aritmetico

	if ( this->type() == outro->type() && this->type() == Data::string ) {
		return Data ( this->dataString().size() > outro->dataString().size() );
	}
	return 0;
}
//--------------------------------------------------
Data Data::lesser ( Data * outro ) {
	return Data ( ! ( this->greater ( outro ).dataBool() && this->equals ( outro ).dataBool() ) );
}


/************************************************
 ***************AUXILIARES***********************/
bool Data::arithmetic() {
	return ( this->_type == Data::integer || this->_type == Data::real );
}
//--------------------------------------------------
std::string Data::toString() {

	// switch tipo de dado
	switch ( this->_type ) {
		case Data::integer: {
			return std::to_string ( this->dataInt() );
			break;
		}

		case Data::real: {
			return std::to_string ( this->dataFloat() );
			break;
		}

		case Data::boolean: {
			bool retorno = this->dataBool();
			return ( retorno ? "true" : "false" );
			break;
		}

		case Data::string: {
			return this->dataString();
			break;
		}
		default:
		std::cerr << "[ATENCAO - nao foi possivel obter a string.]" << std::endl;
	}
}
//--------------------------------------------------
Data Data::createDefault ( Data::DataType tipo ) {
	switch ( tipo ) {
		case Data::integer: {
			return Data ( 1 );
			break;
		}

		case Data::real: {
			float x = .1;
			return Data ( x );
			break;
		}

		case Data::boolean: {
			return Data ( true );
			break;
		}

		case Data::string: {
			return Data ( std::string ( "teste" ) );
			break;
		}
		default:
		std::cerr << "[ATENCAO - tipo de dado desconhecido.]" << std::endl;
	}
}

/*Biblioteca escrotissima de templates
//switch tipo de dado
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





