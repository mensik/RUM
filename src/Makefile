include Makefile.inc

DIRS = mesh assembly common
OBJLIBS = libmesh.a 
MY_LIBS = -L. -lmesh 

OBJS = mesh/Mesh.o mesh/Point.o mesh/Element.o mesh/Face.o mesh/Triangle.o mesh/Triangle3.o mesh/Cell.o mesh/ElementVisitor.o mesh/Brick.o mesh/Brick8.o assembly/FEMLaplaceAssembler.o assembly/AssemblyPreparer.o 

all: Test1.exe

Test1.exe: $(OBJS) test1.o
	echo Linking executable 
	$(CXX) $(CXX_FLAGS) $(OBJS) test1.o -o Test1.exe $(LINKING)
	mv Test1.exe ../deploy

clean:
	echo Cleaning up ...
	rm -f *.o *.a ../deploy/*.exe
	-for d in $(DIRS); do (cd $$d; rm -f *.o; cd .. ); done

force_look:
	rue
