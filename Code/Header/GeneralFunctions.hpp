/*
 * Nom : generalFunctions.hpp
 * Auteur : Julien Lemay & Alexandre Lessard
 * Description : Contient plusieurs fonctions nécessaire au deroulement du
 *               programme.
 * Date : 20/11/15
 */

#ifndef GENERALFUNCTIONS_HPP
#define GENERALFUNCTIONS_HPP

void GenererChromosomes(int **tableau, int P, int N);
void xChange (int index1, int index2, int *matrix);
void shiftLeft(int N, int *matrix);
void shiftRight(int N, int *matrix);

#endif /* GENERALFUNCTIONS_HPP */

