include Makefile.inc

DIRS = mesh 
OBJLIBS = libmesh.a 
MY_LIBS = -L. -lmesh 

all: Test1.exe

Test1.exe: FEMLaplaceAssembler.o test1.o $(OBJLIBS)
	echo Linking executable
	$(CXX) $(CXX_FLAGS) FEMLaplaceAssembler.o test1.o -o Test1.exe $(LINKING) $(MY_LIBS)
	mv Test1.exe ../deploy

libmesh.a: force_look
	echo Building Mesh
	cd mesh; make

clean:
	echo Cleaning up ...
	rm -f *.o *.a ../deploy/*.exe
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

force_look:
	true
