#include <iostream>
#include "mpi.h"

#include "mpi.h"

#include "mesh/Element.h"
#include "mesh/Triangle.h"

using namespace std;

int main(int argc, char *argv[]) {

  MPI_Init(&argc, &argv);

  Element *e = new Face();

  cout << e->getDimension() << endl;

  MPI_Finalize();
  return(0);
}


