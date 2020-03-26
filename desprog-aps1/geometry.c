#include <math.h>

#include "geometry.h"

int verify(point p, point a, point b)
{
	// calculo distancias entre os pontos
	double distanciaPA = sqrt(pow((p.x - a.x), 2) + pow((p.y - a.y), 2));
	double distanciaPB = sqrt(pow((p.x - b.x), 2) + pow((p.y - b.y), 2));
	double distanciaAB = sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));

	// calculo do menor y
	int menory = 0;
	if (a.y > b.y)
	{
		menory = b.y;
	}
	if (a.y < b.y)
	{
		menory = a.y;
	}

	// situacao em que P esta sobre a aresta
	if (fabs(distanciaAB - distanciaPA - distanciaPB) < 10E-7)
	{
		return 2;
	}

	// eliminando caso em que A e B se sobrepoe
	if (a.x == b.x && a.y == b.y)
	{
		return 0;
	}

	// eliminando região em Y nao coberta pela aresta
	if (p.y <= a.y && p.y <= b.y)
	{
		return 0;
	}
	if (p.y > a.y && p.y > b.y)
	{
		return 0;
	}

	if (a.x != b.x && a.y != b.y)
	{
		// double coeficienteA = (a.y - b.y);
		// double coeficienteB = (a.x - b.x);
		// double coeficienteC = a.x*b.y - b.x -a.y;
		// double imagempx =  (double)(-p.y*coeficienteB - coeficienteC)/coeficienteA;

		// descobrindo equacao da reta
		double coeficienteangular = (double)(a.y - b.y) / (a.x - b.x);
		double coeficienteC = (double)(a.y - (a.x * coeficienteangular));

		// descobrindo coordenada X do ponto P projetada sobre a reta
		double imagempx = (double)(p.y - coeficienteC) / coeficienteangular;

		// caso em que P está a direita da reta
		if (imagempx < p.x)
		{
			return 0;
		}

		// caso em que P está a esquerda da reta
		if (imagempx > p.x)
		{
			// caso em que Y de P conicidiu com o menor Y da aresta
			if (p.y == menory)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}

	// caso em que a reta é horizontal
	if (a.y == b.y)
	{
		return 0;
	}

	// caso em que a reta é inclinada
	if (a.x - b.x < 10E-7)
	{
		if (a.x > p.x)
		{
			if (p.y == menory)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
		if (a.x < p.x)
		{
			return 0;
		}
	}
	return 0;
}

int inside(point p, point poly[], int n)
{
	int contador = 0;

	int borda = 0;
	for (int i = 0; i < (n - 1); i++)
	{
		int verificador = verify(p, poly[i], poly[i + 1]);
		if (verificador == 2)
		{
			borda = 1;
		}
		if (verificador == 1)
		{
			contador += 1;
		}
	}

	if (verify(p, poly[0], poly[n - 1]) == 2)
	{
		borda = 1;
	}

	if (verify(p, poly[0], poly[n - 1]) == 1)
	{
		contador += 1;
	}

	if (borda == 1)
	{
		return 1;
	}

	if (contador % 2 == 0)
	{
		return 0;
	}

	if (contador % 2 == 1)
	{
		return 1;
	}
	return 0;
}
