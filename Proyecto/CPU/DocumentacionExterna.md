---
title: 'Documentacion Proyecto MIPS CPU'
tags: 'Arquitectura de Computadores'
disqus: hackmd
---

Proyecto Final CI-0120
===
**Estudiantes:**
* Marco Ferraro **B82957** 
* Gabriel Revillat **B86524**
## Contenido

[TOC]


Circuito General
---
El objetivo de este proyecto es contruir un circuito en **logisim** que simule el funcionamiento de un procesador de arquitectura RISC, además de entender el funcionamiento de *pipelining*. 

**Logisim** es una aplicación desarrollada en Java que nos permite simular el funcionamiento de circuitos lógicos.


Para seguir un buen flujo de trabajo se trabajo con circuitos ya definidos por **logisim**, además de crear un subcircuito para cada componente principal de un CPU RISC.

<center>

![](https://i.imgur.com/dsVpjOz.png)

<em>Vista General del Circuito</em>

</center>


El circuito maneja un set de instrucciones de **32 bits**, definido en el enunciado del proyecto.

A continuación se mencionarán los principales componentes de del circuito, incluyendo los *stages* de *pipeline* y sus entradas y salidas respectivas.

Register File
---

El *Register File* es un componente que maneja una matriz de registros dentro del procesador. Además de esto, se puede escribir sobre la memoria de un registro. 

<center>

![](https://i.imgur.com/ydiHwjc.png)

<em>Subcircuito de Register FIle</em>
</center>

Cada registro posee **32 bits** de almacenamiento, por lo tanto al *Register File* le ingresan direcciones de 4 bits.

Los registros para visualizar se llaman **rs** y **rt**. Al registro que se le puede modificar la memoria se conoce como **rd**.

Sus salidas son los valores de los registros **rs** y **rt**

<center>

![](https://i.imgur.com/SjMiVXK.png)

<em>Lógica Interna del Register File</em>

</center>

Control Unit
---

La Unidad de Control en un componente que nos ayuda con la ejecución de las instrucciones. Si manejamos un flujo **Multi Cycle**, la unidad de control deberá manejar varios **Datapaths** y **flags**.



<center>

![](https://i.imgur.com/7UPfGKt.png)

<em>Subcircuito Unidad de Control</em>
</center>



Para determinar los valores que cada stage debería de recibir, nos basamos en el formato **R** de intrucciones para procesadores RISC.

<center>


![](https://i.imgur.com/sPKUu06.png)

<em>Splitter de Instrucciones</em>

![](https://i.imgur.com/GgTOw8l.png)

*Flujo de los valores de salida para cada Stage*

</center>


<center>

![](https://i.imgur.com/ie6AGLk.png)

*Circuito interno de la Unidad de Control*

</center>


ALU
---
La unidad de control es la encargada de expresar operaciones aritméticas y lógicas sobre nuestro CPU. Nuestra UAL o ALU recibe 2 instrucciones de **32 bits**.

<center>

![](https://i.imgur.com/dPH4Tcu.png)

*Subcircuito ALU*

</center>

<center>

![](https://i.imgur.com/atPWb95.png)
*Salidas ALU*

</center>

Nuestro ALU es de instrucciones reducidas. Notese que el espacio de **AluOP** tiene 4 bits. Las instrucciones básicas que hace es 
* Suma 
* Resta

en la parte aritmética.

En la parte lógica tenemos una serie de **flags** las cuáles nos sirven para identificar si 2 valores son iguales, si hay un overflow de negativos o positivos.

Data Memory
---

El componente de data memory es escencial para el fucionamiento del ALU. Si hay una instruccion **load**, existe un multiplexor afuera que va a girar la salida de la intruccion al **DataMemory.** Recordemos que por el **Pipelining**, la memoria a leer viene definida desde la salida del stage anterior.
<center>

![](https://i.imgur.com/dU8VtYK.png)
*Subcircuito DataMemory*

</center>



<center>

![](https://i.imgur.com/OTIRSDi.png)
*Circuito DataMemory*

</center>
Nótese que el tunnel llamado **WriteData** es el mismo que se utiliza para el **Register File**

IF/ID
---
El stage **IF/ID** se encarga del
* Instruction Fetch
* Instruction Decode
<center>

![](https://i.imgur.com/Mo7jSyE.png)
*Subcircuito IF/ID*

</center>

El proceso de **Instruction Fetch** se encarga de:
* Obtener la instruccion desde **Instruction Memory**
* Aumentar el valor de **Program Counter**


Mientras que el proceso de **Intruction Decode**:
* Obtiene los valores de los registros de la instrucción

<center>

![](https://i.imgur.com/CeRiC1A.png)
*Circuito IF/ID*

</center>

ID/EX
---
Este stage es más complejo. Ya se explico que hace un proceso **Instruction Decode** anteriormente, por lo tanto solo se va a mencionar el **Execute**.
<center>

![](https://i.imgur.com/nZ4J36N.png)
*Subcircuito ID/EX*
</center>

**Execute** es un proceso que:
*  En caso de ser una referencia de memoria, setea el OFFSET y la Base
* Es caso de recibir una referencia de un operacion aritemetica, hace la mate, por decirlo así.

<center>

![](https://i.imgur.com/lo7VZYH.png)
*Circuito*

</center>

EX/MEM
---

El proceso **Memory** se encarga de:
* Acceder a memoria
* Si recibe un Branch, modificar el Program Counter
<center>

![](https://i.imgur.com/BZqAK9q.png)
*Surcircuito EX/MEM*

</center>

<center>

![](https://i.imgur.com/DGStCQW.png)
*Circuito*

</center>

MEM/WB
---
Finalmente, tenemos **WriteBack.** WB se encarga de poner un valor en un registro respectivo, por lo tanto está en comunicación directa con el **Register File.**
<center>

![](https://i.imgur.com/hBnLOt6.png)

*SubCircuito MEM/WB*

</center>

<center>

![](https://i.imgur.com/nYc15yv.png)

*Circuito*

</center>

Componentes Externos
---

<center>

![](https://i.imgur.com/N8jcG8N.png)
*Reloj global para todo el Circuito*

</center>

<center>

![](https://i.imgur.com/EFeRXv2.png)
*Almacenamiento de las Intrucciones*
</center>

Versión de Logisim
---
Este proyecto se desarrollo con una versión de **Logisim** adjuntada en la carpeta del proyecto. 

Se puede encontrar en este [repositorio](https://https://github.com/Logisim-Ita/Logisim).

Funcionamiento
---
Para correr el proyecto se necesita ingresar instrucciones de **32 bits* en *Instruction Memory*. Las instrucciones debenes de estar bajo formato MIP. Análogamente, se necesita un pulso de reloj para completar un ciclo en todo el procesador.