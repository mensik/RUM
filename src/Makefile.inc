include /home/martin/documents/code/trilinos/build/packages/epetra/Makefile.export.Epetra
include /home/martin/documents/code/trilinos/build/packages/epetraext/Makefile.export.EpetraExt
include /home/martin/documents/code/trilinos/build/packages/teuchos/Makefile.export.Teuchos

# Make sure to use same compilers and flags as Trilinos
CXX=$(Epetra_CXX_COMPILER)
CC=$(Epetra_C_COMPILER)
FORT=$(Epetra_Fortran_COMPILER)

CXX_FLAGS=$(Epetra_CXX_COMPILER_FLAGS) $(USER_CXX_FLAGS)
C_FLAGS=$(Epetra_C_COMPILER_FLAGS) $(USERC_FLAGS)
FORT_FLAGS=$(Epetra_Fortran_COMPILER_FLAGS) $(USER_FORT_FLAGS)

INCLUDE_DIRS=$(Epetra_INCLUDE_DIRS) $(Epetra_TPL_INCLUDE_DIRS) $(EpetraExt_INCLUDE_DIRS) $(EpetraExt_TPL_INCLUDE_DIRS) $(Teuchos_INCLUDE_DIRS) $(Teuchos_TPL_INCLUDE_DIRS)
LIBRARY_DIRS=$(Epetra_LIBRARY_DIRS) $(Epetra_TPL_LIBRARY_DIRS) $(EpetraExt_LIBRARY_DIRS) $(EpetraExt_TPL_LIBRARY_DIRS)  $(Teuchos_LIBRARY_DIRS) $(Teuchos_TPL_LIBRARY_DIRS)

LIBRARIES=$(Epetra_LIBRARIES) $(Epetra_TPL_LIBRARIES) $(EpetraExt_LIBRARIES) $(EpetraExt_TPL_LIBRARIES) $(Teuchos_LIBRARIES) $(Teuchos_TPL_LIBRARIES)

LINK_FLAGS=$(Epetra_EXTRA_LD_FLAGS)

LINKING=$(LINK_FLAGS) $(INCLUDE_DIRS) $(DEFINES) $(LIBRARY_DIRS) $(LIBRARIES)

.cpp.o:
	echo Compiling $<
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) $(DEFINES) -o $@ -c $<

.SILENT :
