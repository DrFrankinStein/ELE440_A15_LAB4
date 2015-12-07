/*
 * Nom : FileTools.cpp
 * Auteur : Julien Lemay & Alexandre Lessard
 * Description : Contient des outil pour intéragir avec des fichiers.
 * Date : 20/11/15
 */

// Include

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <climits>
#include <ctime>

#include "../Header/FileTools.hpp"

using namespace std;

int ** LoadFromFile(const char * fileName, int &P, int &N)
{
    FILE * textfile;
    char c;
    int ** matrixArray;
    int row=0, col=0;
    int tmp;
    string buffer="";
    
    textfile = fopen (fileName,"r");
    if (textfile == NULL)
    {
        perror ("Error opening file");
        N=-1;
        return NULL;
    }
    else 
    {
        do 
        {
            c = fgetc (textfile);
            if(c != EOF)
            {
                if(c>='0'&& c<='9' || c == '-')
                {
                    buffer+=c;
                }
                else
                {
                    if(c=='\t' || c == '\n' || c == ' ')
                    {
                        sscanf(buffer.c_str(),"%i",&tmp); 
                        switch(row)
                        {
                            case 0 :
                            {
                                P = tmp;
                            }break;
                            case 1 :
                            {
                                N = tmp;
                                matrixArray = new int*[N];
                                for(int i = 0; i < N; ++i)
                                matrixArray[i] = new int[N];
                            }break;
                   
                            default :
                                matrixArray[row-2][col] = tmp;
                                break;
                        }
                        if(c == '\t')
                            col++;
                        else
                        {
                            row++;
                            col=0;
                        }
                    }
                    buffer="";
                }
            }
            else
                if(buffer!="")
                {
                    sscanf(buffer.c_str(),"%i",&tmp);
                    matrixArray[row-1][col] = tmp;
                }
        } 
        while (c != EOF);
    fclose (textfile);
    }
    return matrixArray;
} 