## Resumen Ejecutivo - Tabla de Símbolos

**Profesor(a),**

Quería consultarle sobre el comportamiento de mi analizador léxico, específicamente sobre la tabla de símbolos.

### Observación:
Mi tabla de símbolos solo muestra identificadores (como `variable`, `miVar`) y palabras reservadas mal escritas (como `Entero`, `RUTINA`), pero no incluye las palabras reservadas correctas (`entero`, `rutina`), números (`42`, `123`), ni símbolos (`+`, `;`).

### Mi Análisis:
Creo que esto es correcto porque:

1. **Palabras reservadas** (`entero`, `rutina`) → Tienen tokens específicos (257-265), no necesitan almacenarse
2. **Números** (`42`, `123`) → Se almacenan como valores directamente, no como símbolos
3. **Símbolos** (`+`, `;`) → Tienen códigos ASCII específicos
4. **Palabras mal escritas** (`Entero`, `RUTINA`) → No coinciden con reservadas → Se tratan como identificadores válidos del usuario

### Pregunta:
¿Es este el comportamiento esperado según las convenciones de compiladores? ¿O debería modificar el diseño para incluir otros tipos de tokens en la tabla de símbolos?

### Evidencia:
```
Input "entero" → TOK_ENTERO (257) → No va a tabla
Input "Entero" → TOK_IDENTIFICADOR (266) → Sí va a tabla (pos: X)
Input "42"     → TOK_NUMERO (267) → No va a tabla  
Input ";"      → código ASCII (59) → No va a tabla
```

Gracias por su orientación.

**Estudiante:** [Tu nombre]
