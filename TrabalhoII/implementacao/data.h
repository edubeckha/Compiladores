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

class Data
{
public:
    /*Tipo de dado*/
    enum DataType {integer, real, boolean , string, range};
//--------------------------------------------------
    /**
     * @brief Cria um dado contendo um inteiro
     *
     * @param inteiro inteiro inicial
     */
    Data ( int inteiro );
//--------------------------------------------------
    /**
     * @brief Cria um dado contendo um intervalo
     *
     * @param inicio inicio do intervalo
     * @param fim fim do intervalo
     */
    Data ( int inicio,int fim );
//--------------------------------------------------

    /**
     * @brief Cria um dado contendo um real
     *
     * @param real Real inicial
     */
    Data ( float real );
//--------------------------------------------------
    Data ( bool booleano );
    /**
     * @brief Cria um dado contendo um booleano
     *
     * @param Booleano Booleano inicial
     */
    Data ( std::string String );
//--------------------------------------------------

    /**
     * @brief Controi um novo dado a partir de um dado existente
     *
     * @param other Dado já existente
     */
    Data ( const Data & other );
//--------------------------------------------------


    /**
     * @brief Obtém o tipo do dado
     *
     * @return Data::DataType
     */
    DataType type() {
        return _type;
    }
//--------------------------------------------------

    /**
    * @brief Retorna o dado armazenado como um inteiro
    *
    * @return int
    */
    int dataInt();
//--------------------------------------------------

    /**
     * @brief Retorna o dado armazenado como um array para dois inteiros
     *
     * @return int*
     */
    int * dataRange();
//--------------------------------------------------


    /**
    * @brief Retorna o dado armazenado como um float
    *
    * @return float
    */
    float dataFloat();
//--------------------------------------------------

    /**
    * @brief Retorna o dado armazenado como um booleano
    *
    * @return bool
    */
    bool dataBool();
//--------------------------------------------------

    /**
     * @brief Retorna o dado armazenado como uma string
     *
     * @return std::string
     */
    std::string dataString();
//--------------------------------------------------
    /*Operadores*/

    /**
     * @brief Soma
     *
     * @param outro Dado a ser somado
     * @return Data
     */
    Data sum ( Data * outro );
//--------------------------------------------------

    Data subtrair ( Data * outro );
//--------------------------------------------------

    /**
     * @brief Subtração
     *
     * @param outro Dado a ser subtraido
     * @return Data
     */
    Data multiply ( Data * outro );
//--------------------------------------------------

    /**
     * @brief Divisão
     *
     * @param outro Dado a ser dividio
     * @return Data
     */
    Data divide ( Data * outro );
//--------------------------------------------------

    /**
     * @brief Ou booleano
     *
     * @param outro Dado a ser comparado
     * @return Data
     */
    Data bOr ( Data * outro );
//--------------------------------------------------

    /**
     * @brief E booleano
     *
     * @param outro Dado a ser comparado
     * @return Data
     */
    Data bAnd ( Data * outro );
//--------------------------------------------------

    /**
     * @brief Comparacao de maior
     *
     * @param outro Dado a ser comparado
     * @return Data
     */
    Data greater ( Data * outro );
//--------------------------------------------------

    /**
     * @brief Comparacao de menor
     *
     * @param outro Dado a ser comparado
     * @return Data
     */
    Data lesser ( Data * outro );
//--------------------------------------------------
    /**
     * @brief Comparacao de igualdade
     *
     * @param outro Dado a ser comparado
     * @return Data
     */
    Data equals ( Data * outro );
//--------------------------------------------------


    /*Verifica se o dado é aritmetico*/
    bool arithmetic ();
//--------------------------------------------------
    /**
     * @brief Retorna uma string com a informação do dado
     *
     * @return std::__cxx11::string
     */
    std::string toString();
//--------------------------------------------------
    /**
     * @brief Cria um objeto com valores padroes para o tipo de dado especificado
     *
     * @param tipo Tipo de dado do novo valor padrao
     * @return Data
     */
    static Data createDefault ( DataType tipo );
//--------------------------------------------------
    /**
     * @brief substring de uma string
     *
     * @param outro Dado formado pela substring
     * @return Data
     */
    Data subString ( int inicio, int fim );
//--------------------------------------------------
    /**
     * @brief tamanho de uma string
     *
     * @param outro Dado formado pelo tamanho da string
     * @return Data
     */
    Data tamanho ();
//--------------------------------------------------


//--------------------------------------------------

private:

    /**
     * @brief Dado armazenado
     *
     */
    void * _data;
//--------------------------------------------------

    /**
     * @brief Tipo do dado armazenado
     *
     */
    DataType _type;
//--------------------------------------------------


};

#endif // DATA_H
