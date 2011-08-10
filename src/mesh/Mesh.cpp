#include "Mesh.h"

void Mesh::makeBrickMesh(int n) {

	int count = 0;
	for (int i = 0; i < n + 1; i++)
		for (int j = 0; j < n + 1; j++)
			for (int k = 0; k < n + 1; k++)
				nodes.insert(std::pair<int, Point*>(count++, new Point(i, j, k)));

	count = 0;
	Point* points[8];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {

				points[0] = nodes[(i) * (n + 1) * (n + 1) + (j) * (n + 1) + (k)];
				points[1] = nodes[(i + 1) * (n + 1) * (n + 1) + (j) * (n + 1) + (k)];
				points[2]
						= nodes[(i + 1) * (n + 1) * (n + 1) + (j + 1) * (n + 1) + (k)];
				points[3] = nodes[(i) * (n + 1) * (n + 1) + (j + 1) * (n + 1) + (k)];
				points[4] = nodes[(i) * (n + 1) * (n + 1) + (j) * (n + 1) + (k + 1)];
				points[5]
						= nodes[(i + 1) * (n + 1) * (n + 1) + (j) * (n + 1) + (k + 1)];
				points[6] = nodes[(i + 1) * (n + 1) * (n + 1) + (j + 1) * (n + 1) + (k
						+ 1)];
				points[7]
						= nodes[(i) * (n + 1) * (n + 1) + (j + 1) * (n + 1) + (k + 1)];


				Brick8 *brick = new Brick8(points);
				//brick->Print();

				elements.insert(std::pair<int, Element*>(count++, brick));
			}
}

void Mesh::generateRecMesh(double m, double n, double k, double l, double h) {

	int xEdges = (int) ceil((n - m) / h);
	int yEdges = (int) ceil((l - k) / h);

	int xPoints = xEdges + 1;
	int yPoints = yEdges + 1;

	double hx = (n - m) / xEdges;
	double hy = (l - k) / yEdges;

	//Discretization
	int nodeIndex = 0;
	int elementIndex = 0;

	for (int j = 0; j < yPoints; j++)
		for (int i = 0; i < xPoints; i++) {

			double xPos = m + i * hx;
			double yPos = k + j * hy;

			Point *node = new Point(xPos, yPos);
			nodes.insert(std::pair<int, Point*>(nodeIndex, node));

			nodeIndex++;
		}

	nodeIndex = 0;
	int elIndex = 0;
	for (int j = 0; j < yPoints; j++)
		for (int i = 0; i < xPoints; i++) {

			//Element creation
			if (j < yPoints - 1 && i < xPoints - 1) {
				Triangle3 *t1, *t2;
				t1
						= new Triangle3(nodes[nodeIndex], nodes[nodeIndex + xPoints + 1], nodes[nodeIndex
								+ 1]);
				t2
						= new Triangle3(nodes[nodeIndex], nodes[nodeIndex + xPoints], nodes[nodeIndex
								+ xPoints + 1]);

				elements.insert(std::pair<int, Element*>(elIndex++, t1));
				elements.insert(std::pair<int, Element*>(elIndex++, t2));
			}
			nodeIndex++;

		}

}
