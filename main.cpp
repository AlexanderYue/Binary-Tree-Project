#include <iostream>
#include <fstream>
#include "Bush.h"
#include <string>
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char* argv[]) {
    //cout<<"joe";
    ArgumentManager am(argc, argv);
    ifstream fin(am.get("input"));
    ofstream fout(am.get("output"));
    //ifstream fin("input3.txt");
    //ofstream fout("output.txt");
    int size, num;
    fin >> size;
    int **array = new int*[size];

    for(int i = 0; i < size; i++) {
        array[i] = new int[i+1];
    }
    //cout << size << endl;
    for(int i = 1; i <= size; i++){
        for(int j = 0; j < i; j++){
            fin >> num;
            array[i-1][j] = num;
            //cout << num << " ";
        }
        //cout << endl;
    }

      Bush bush;
      bush.setRoot(array, size, 1, 0);
      /*for(int i = 1; i < size; i++){
        bush.InsertLeft(array[i][0], 1);
        cout<< " insertleft: " << array[i][0]<< " ";
        bush.InsertRight(array[i][i], 1);
        cout<< " insertright: " << array[i][i]<< " ";
        for(int j = 0; j < i; j++){

        }
      }*/
    //cout<<endl;
    //cout << endl;
    //cout << bush.FindMinimum() << endl;
    //cout << bush.FindMaximum() << endl;
  //cout << "-----------------------------"<<endl;
  //bush.printTreeInOrder();
  //cout<<endl;
  bush.FindMaximum(fout);
  bush.FindMinimum(fout);

    for(int i = 0; i < size; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}