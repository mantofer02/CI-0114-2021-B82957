---
tags: Arquitectura de Computadores
title: Examen Corto 2
---
# I Parte:
## Conceptos:
### Single-cycle
Es una arquitectura Single Cycle, hay que tener claro que es una instrucción por ciclo. No van a haber multiples instrucciones en el procesador concurrentemente. Las arquitecturas **single-cycle** se adaptan para que los datapaths manejen una instrucciones a la vez.
![](https://i.imgur.com/cuprYkK.png)

### Multi-cycle
En lugar de ver la instrucción como una gran tarea que debe realizarse, en Multi Cycle las instrucciones se dividen en pasos fundamentales más pequeños. Como resultado, podemos acortar el período del reloj y realizar las instrucciones de forma incremental en varios ciclos.
### Pipeline
Pipeline es una tecnica en donde multiples intrucciones se traslapan en su ejecución. Pipelining toma ventaja sobre los conceptos de paralelismo y aprovecha los recursos del hardware para reducir los tiempos de *fetch, decode* y *execution* de las instrucciones de CPU. 

Una analogia para enteder el pipeline es la linea de montaje que se usan para fabricar carros, en donde se estan haciendo diferentes tareas al mismo tiempo.


![](https://i.imgur.com/JxwZE1A.png)

Una implementación de un diseño para pipeline maneja registros especificos (color azul) los cuales retienen información de las sub-instrucciones entre cada ciclo.
En cada ciclo, una instruccion avaca de un *pipeline register* al siguiente. La notación de los registros hacen referencia al estado en el que estan.

### Pipeline II 

Otra variaciones de implementacion de pipeline es añadir unidades de control, para optimizar el manejo de instrucciones.

![](https://i.imgur.com/ENVRezM.png)

---

## Componentes CPU:
### Registros:
Por simplicidad de diseño, vamos a hacer que cada registro maneja **32 bits** de información. Vamos a tener 8 registros de uso general.
#### Componentes Logisim:
* Multiplexor
* Registros
* Splitter

### ALU:
La ALU tendra OPCODE de 16 bits, además entre sus salidas debe de mostrar los flags de 
* Overflow
* Zero
* Negative

El output de la Unidad Arimetica Logica será de 32 bits.

La ALU debe ser capaz de decodificar cada instrucción y ejecutarla. El mapeo de instrucciones debe de hacerse con antelación. Este mapeo esta definido en **Instruction Memory**

#### Componentes Logisim:
* Multiplexor
* Splitter
* Pin de Flags
* Componentes Logicos

Cabe destacar que Logisim ya maneja un componente ALU, pero si se desea hacer una implimentación multi-cycle se tiene que agregar más Datapaths

### Memoria de Instrucciones
Por el diseño de los procesadores MIPS, se maneja un Memoria de Instrucciones y Memoria de Datos en componentes aislados. 

### Unidad de Control
Para el funcionamiento del CPU, necesitamos una Unidad de Control que nos ayude con la ejecución de las instrucciones. Si manejamos un flujo de Multi Cycle, la unidad de control debera manejar varios datapaths.

La unidad de control que tener:
* Instruction Register
* Instruction Adress Register

# II Parte:
Para diseñar esta ALU, queremos una entrada de **32 bits**.

Recordemos los flags que necesitamos
* Carry out
* Overflow
* Non Negative
* Zero
![](https://i.imgur.com/D668MId.png)

De referencia usaremos esta imagen, sin embargo cabe notar que nuestra ALU debera de manejar más de 2 unidades de control, especificamente 4. Esto con la intención de tener multiples Datapaths