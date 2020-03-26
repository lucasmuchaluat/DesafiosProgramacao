# DesafiosProgramacao
Repositório da disciplina Desafios de Programação 2020.1
## APS 1
Atividade Prática Supervisionada 1
* Problema: [Ponto em Polígono](https://en.wikipedia.org/wiki/Point_in_polygon) (Geometria Computacional)
* Solução: Algoritmo [Ray Casting](https://en.wikipedia.org/wiki/Point_in_polygon#Ray_casting_algorithm) - A ideia desse algoritmo é simples e intuitiva: imagine que o robô dispara um raio em alguma direção, digamos para a direita. Se o número de vezes que esse raio cruza a parede da sala for ímpar, então p está dentro de poly. Caso contrário, não está.
* A lógica principal se encontra no arquivo [`geometry.c`](/desprog-aps1/geometry.c)
## APS 2
Atividade Prática Supervisionada 2
* Problema: Modificação em imagens digitais (como suavização ou detecção de bordas)
* Solução: Modificações automatizadas por algoritmos clássicos de [Processamento de Imagens Digitais](https://en.wikipedia.org/wiki/Digital_image_processing) obtidas a partir de filtragens no domínio das frequências, usando a Transformada Discreta de Fourier.
* A lógica principal se encontra no arquivo [`fourier.c`](/desprog-aps2/fourier.c)
