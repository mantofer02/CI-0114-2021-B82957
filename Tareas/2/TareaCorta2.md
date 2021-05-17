---
tags: Arquitectura de Computadores, UCR
title: Tarea Corta 2
---
# Tarea Corta 2
![](https://i.imgur.com/nv8D4zX.png)
![](https://i.imgur.com/fb4WpyD.png)
![](https://i.imgur.com/o58kBaZ.png)
* Pasamos `389 milimetros cuadrados` a `centimetros cuadrados`. R/ 3.89
* Usamos la fórmula `Bose Einstein con sus valores respectivos:`
    ![](https://i.imgur.com/zjTECZW.png)
    * Defects per unit area: .30
    * Die Area: 3.89
    * N: Según el libro: 
>Finally, N is a parameter called the process complexity factor, a measure  of  manufacturing  difficulty.  For  40  nm  processes  in  2010,  N ranged from 11.5 to 15.5.
    
Como no se da valor de N, se va a dejar como valor N.

a/  ![](https://i.imgur.com/GHRCowB.png)

b/ El IBM Power 5 fue manufacturado en una técnologia más grande. Según el libro 
> A simple model of integrated circuit yield, which assumes that defects are randomly distributed over the wafer and that yield is inversely proportional to the complexity of the fabrication process.
Esto nos deja concluir que, aunque Sun Niagara tienen un tamaño de manufacturación más pequeño, al incluir una cantidad parecida de transistores que el IBM Power5 esto incrementa la complejidad de estos 2 chips e incrementas sus tasas de errores.

![](https://i.imgur.com/20yzCFu.png)

Con una de las fórmulas derivadas de la ley de Ahmdal podemos calcular los siguientes speedups

![](https://i.imgur.com/LJYLCl3.png)



![](https://i.imgur.com/PzsaAk5.png)

`a) 1 / (1 - 0.4  + 0.4/2) = 1.25`

`b) 1 / (1 - 0.99 + 0.99/2) = 1.98`

Para el c y d sacamos porcentajes de los speedup ya definidos previamente

`c) 1.25 * 0.80 = 1` <font color='red'> Tendrías que multipliar por `1/0.8`. Además, te piden Overall system. Te faltó tomar en cuenta la segunda aplicación. Debido a que la segunda 
es serial, se añade multiplicar por `1/0.2`. </font>

`d) 1,98 * 0,20 = 0.396`  <font color='red'> Tendrías que multipliar por `1/0.2`. Además, te piden Overall system. Te faltó tomar en cuenta la primera aplicación. Debido a que la primera 
es serial, se añade multiplicar por `1/0.8`. </font>

