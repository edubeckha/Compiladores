/*
 * Copyright (c) 2016
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

#ifndef DATA_H
#define DATA_H
#include <string>
#include <cassert>
#include <iostream>

class Data {
public:
	/*Tipo de dado*/
	enum DataType {integer, real, boolean, string};

	/*Construtores para os tipos de dados aceitos*/
	Data ( int inteiro );
	Data ( float real );
	Data ( bool booleano );
	Data ( std::string String );
	Data ( const Data & other );

	/*Obtém o tipo do dado*/
	DataType type() {
		return _type;
	}

	/*Obtem o valor do dado*/
	int dataInt();
	float dataFloat();
	bool dataBool();
	std::string dataString();

	/*Operadores*/

	Data somar ( Data * outro );
	Data subtrair ( Data * outro );
	Data multiplicar ( Data * outro );
	Data dividir ( Data * outro );
	Data ou ( Data outro );
	Data e ( Data * outro );
	Data maior ( Data * outro );
	Data menor ( Data * outro );
	Data igual ( Data * outro );


	/*Verifica se o dado é aritmetico*/
	bool aritmetico ();
private:

	void * _data;
	DataType _type;


};

#endif // DATA_H
