include ../Makefile.inc

OBJS = Mesh.o Point.o Element.o Face.o Triangle.o Triangle3.o Cell.o ElementAssemblyVisitor.o Brick.o Brick8.o

all: ../libmesh.a
	
../libmesh.a: $(OBJS)
	ar -cr ${@} ${^}
	ranlib ${@}

clean:
	rm -f *.o
