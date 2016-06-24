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
Data::Data( int inteiro ) {
	this->_type = Data::integer;
	this->_data = new int( inteiro );
}
Data::Data( float real ) {
	this->_type = Data::real;
	this->_data = new float( real );
}
Data::Data( bool booleano ) {
	this->_type =  Data::boolean;
	this->_data = new bool( booleano );
}

Data::Data( std::__cxx11::string String ) {
	this->_type = Data::string;
	this->_data = new std::string( String );
}

Data::Data( const Data& other ) {
	this->_type = other._type;
	this->_data = other._data;

}
/************************************************
 ***************RETORNOS DE DADO****************/

int Data::dataInt() {
	int * inteiro = ( int* )this->_data;
	return *inteiro;
}

float Data::dataFloat() {
	float * real = ( float* )this->_data;
	return *real;
}

bool Data::dataBool() {
	bool* booleano = ( bool* )this->_data;
	return *booleano;
}

const Data::string Data::dataString() {
	std::string String = ( std::string* )this->_data;
	return *String;
}


/************************************************
 ***************OPERADORES**********************/


















