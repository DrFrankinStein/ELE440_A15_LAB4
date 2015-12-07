/*
 * Nom : generalFunctions.hpp
 * Auteur : Julien Lemay & Alexandre Lessard
 * Description : Contient plusieurs fonctions nécessaire au deroulement du
 *               programme.
 * Date : 20/11/15
 */

#ifndef GENERALFUNCTIONS_HPP
#define GENERALFUNCTIONS_HPP

#include "../Header/ChessBoard.hpp"

long GenererChromosomes(int **tableau, int P, int N);
void xChange (int index1, int index2, int *matrix);
void shiftLeft(int N, int *matrix);
void shiftRight(int N, int *matrix);
unsigned long long Recombinaison(int N, int P, int **parent, int **enfant);
unsigned long long Mutation(int N, int P, int **enfant);
unsigned long long Combat(int N, int P, int **parent, int **enfant, ChessBoard *board);

#endif /* GENERALFUNCTIONS_HPP */

